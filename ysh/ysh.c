#include "./ysh.h"
#include "./buildin.h"
#include "./config.h"
#include "./string.h"
#include "./file.h"
#include "./memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <wait.h>
#include <errno.h>

int parse_cmdline(char* str, cmd_t** dest_cmd, cmd_t** dest_start)
{
    int     len     = 0,
            head    = 0,
            tail    = 0;

    char*   tmp     = NULL;

    cmd_t*  cmd     = NULL,
         *  start   = NULL;

    if ((cmd = (cmd_t*)
                malloc(sizeof(cmd_t))) == NULL)
        return -1;

    start = cmd;
    cmd->io = NULL;
    cmd->next = NULL;
    cmd->prev = NULL;

    while (1) {
        if (str[head] == ';'        ||
                str[head] == '|'    ||
                str[head] == '&'    ||
                str[head] == '>'    ||
                str[head] == '<'    ||
                str[head] == '\n') {
            if ((tmp = (char*)
                        malloc(sizeof(char) * (head - tail))) == NULL)
                goto ERR;

            memcpy(tmp, str + tail, head - tail);
            tmp[head - tail] = '\0';
            trim(tmp);
            cmd->args = str_to_args(tmp);
            free(tmp);

            if (str[head] == '>' || str[head] == '<') {
                if ((cmd->io = (io_t*)
                            malloc(sizeof(io_t))) == NULL)
                    goto ERR;

                if (str[head] == '>') {
                    if (str[head + 1] == '>') {
                        cmd->io->io_flag = IOCAT;
                        head++;
                    } else {
                        cmd->io->io_flag = IOWRITE;
                    }
                } else if (str[head] == '<') {
                    if (str[head + 1] == '<') {
                        cmd->io->io_flag = IOHERE;
                        head++;
                    } else {
                        cmd->io->io_flag = IOREAD;
                    }
                }

                head++;
                while (isspace(str[head]))
                    head++;

                len = 0;
                while (!isspace(str[head + len])    &&
                        str[head + len] != ';'      &&
                        str[head + len] != '|'      &&
                        str[head + len] != '&'      &&
                        str[head + len] != '>'      &&
                        str[head + len] != '<'      &&
                        str[head + len] != '\n')
                    len++;
                if ((cmd->io->io_name = (char*)
                            malloc(sizeof(char) * (len + 1))) == NULL)
                    goto ERR;

                memcpy(cmd->io->io_name, str + head, len);
                cmd->io->io_name[len] = '\0';
                fprintf(stdout, "io_name = %s\n", cmd->io->io_name);
                head += len;
            }
            if (str[head] == '\0' || str[head] == '\n') {
                cmd->type = TCOM;
                break;
            }

            switch (str[head]) {
                case    ';':
                    cmd->type = TPAREN;
                    break;
                case    '|':
                    if (str[head + 1] == '|') {
                        cmd->type = TOR;
                        head++;
                    } else {
                        cmd->type = TPIPE;
                    }
                    break;
                case    '&':
                    if (str[head + 1] == '&') {
                        cmd->type = TAND;
                        head++;
                    } else {
                        cmd->type = TCOM;
                    }
                    break;
            }
            head++;
            tail = head;
            if ((cmd->next = (cmd_t*)
                        malloc(sizeof(cmd_t))) == NULL)
                goto ERR;

            cmd->next->prev = cmd;
            cmd = cmd->next;
            cmd->next = NULL;
            cmd->io = NULL;
        } else {
            head++;
        }
    }
    if (cmd->args[0][0] == '\0')
        goto ERR;

    *dest_cmd = start;
    *dest_start = start;

    return 0;

ERR:

    release_cmd_t(start);

    return -2;

}

void redirect(int oldfd, int newfd)
{
    if (oldfd != newfd)
        if (dup2(oldfd, newfd) == -1)
            close(oldfd);

    return;
}

int file_redirect(cmd_t* cmd)
{
    int fd  = 0;
    
    switch (cmd->io->io_flag) {
        case    IOREAD:
        case    IOHERE:
            if ((fd = open(cmd->io->io_name, O_RDONLY)) < 0) {
                perror("ysh: fopen");
                close(fd);

                return -1;
            }
            close(0);
            dup2(fd, 0);
            break;
        case    IOWRITE:
            if ((fd = open(cmd->io->io_name, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0) {
                perror("ysh: fopen");
                close(fd);

                return -1;
            }
            close(1);
            dup2(fd, 1);
            break;
        case    IOCAT:
            if ((fd = open(cmd->io->io_name, O_WRONLY | O_CREAT | O_APPEND, 0666)) < 0) {
                perror("ysh: fopen");
                close(fd);

                return -1;
            }
            close(1);
            dup2(fd, 1);
            break;
    }
    close(fd);

    return 0;
}

int exec_cmd(cmd_t* cmd, int in_fd)
{
    int     fd[2]   = {0},
            status  = 0;

    pid_t   pid     = 0;

    /*
     * buildin command
     */
    if (strcmp(cmd->args[0], "cd") == 0) {
        ysh_chdir(cmd->args);
        if (cmd->next != NULL)
            exec_cmd(cmd->next, STDIN_FILENO);

        return 0;
    }
    if (strcmp(cmd->args[0], "exit") == 0)
        ysh_exit(cmd);

    /*
     * pipe (last)
     */
    if (cmd->prev != NULL) {
        if (cmd->prev->type == TPIPE && cmd->next == NULL) {
            redirect(in_fd, STDIN_FILENO);
            if (cmd->io != NULL) {
                if (file_redirect(cmd) < 0)
                    exit(1);
            }
            execvp(cmd->args[0], cmd->args);
            fprintf(stderr, "%s: command not found: %s\n",
                    PROGNAME, cmd->args[0]);

            exit(errno);
        }
    }

    /*
     * command
     */
    if (cmd->type != TPIPE) {
        switch (pid = fork()) {
            case    -1:
                fprintf(stderr, "%s: fork() failure",
                        PROGNAME);

                return errno;
            case    0:
                if (cmd->io != NULL) {
                    if (file_redirect(cmd) < 0)
                        exit(1);
                }

                execvp(cmd->args[0], cmd->args);
                fprintf(stderr, "%s: command not found: %s\n",
                        PROGNAME, cmd->args[0]);

                exit(errno);
            default:
                wait(&status);
                if (cmd->next != NULL)
                    exec_cmd(cmd->next, STDIN_FILENO);

                return 0;
        }
    }

    /*
     * pipe
     */
    switch (fork()) {
        case    -1:
            fprintf(stderr, "%s: fork() failure",
                    PROGNAME);

            return errno;
        case    0:
            break;
        default:
            wait(&status);
            return 0;
    }
    if (pipe(fd) < 0) {
        fprintf(stderr, "%s: pipe() failure\n",
                PROGNAME);

        return errno;
    }

    switch (fork()) {
        case    -1:
            fprintf(stderr, "%s: fork() failure\n",
                    PROGNAME);

            return errno;
        case    0:
            close(fd[0]);
            redirect(in_fd, STDIN_FILENO);
            redirect(fd[1], STDOUT_FILENO);
            execvp(cmd->args[0], cmd->args);
            fprintf(stderr, "%s: command not found: %s\n",
                    PROGNAME, cmd->args[0]);
            exit(errno);
        default:
            close(fd[1]);
            close(in_fd);
            wait(&status);
            if (cmd->next != NULL)
                exec_cmd(cmd->next, fd[0]);
    }

    exit(0);
}

void release_cmd_t(cmd_t* cmd)
{
    cmd_t*  tmp = NULL;

    while (cmd != NULL) {
        tmp = cmd->next;
        if (cmd->io != NULL) {
            if (cmd->io->io_name != NULL) {
                free(cmd->io->io_name);
            }
            free(cmd->io);
        }
        free2d(cmd->args, p_count_file_lines(cmd->args));
        free(cmd);
        cmd = tmp;
    }

    return;
}

int main(int argc, char* argv[])
{
    char    buf[MAXLEN];

    cmd_t*  cmd     = NULL,
         *  start   = NULL;

    while (1) {
        memset(buf, '\0', MAXLEN);
        fprintf(stdout, "%s", PROMPT);
        fgets(buf, MAXLEN, stdin);
        if (parse_cmdline(buf, &cmd, &start) < 0)
            continue;
        exec_cmd(cmd, STDIN_FILENO);
        release_cmd_t(start);
    }

    return 1;
}
