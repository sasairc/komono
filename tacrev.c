/*
 * tacrev.c - tac と rev でやれ
 *
 * gcc tacrev.c -lbenly_typestring -o tacrev
 *
 */
#include <benly/typestring.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static
int read_file(FILE* fp, size_t* lines, STRING*** dest)
{
    size_t      th_lines    = 256;

    STRING**    s           = NULL;

    if ((s = (STRING**)
                malloc(sizeof(STRING*) * (th_lines + 1))) == NULL) {
        perror("malloc"); goto ERR;
    }
    *lines = 0;
    string_errno = 0;
    while (fgetline(fp, &s[*lines]) != EOF) {
        if (string_errno < 0)
            goto ERR;
        if (*lines == (th_lines - 1)) {
            th_lines += th_lines;
            if ((s = (STRING**)
                        realloc(s, sizeof(STRING*) * th_lines)) == NULL) {
                perror("realloc"); goto ERR;
            }
        }
        (*lines)++;
    }
    *dest = s;

    return 0;

ERR:
    th_lines = 0;
    if (s != NULL) {
        while (th_lines < *lines) {
            if (s[th_lines] != NULL) {
                s[th_lines]->release(s[th_lines]);
            }
            th_lines++;
        }
        free(s);
    }

    return -1;
}

static
void do_tacrev(STRING** s, size_t lines)
{
    while (lines > 0) {
        lines--;
        s[lines]->chomp(&s[lines]);
        s[lines]->reverse(&s[lines]);
        fputline(stdout, s[lines]);
        s[lines]->release(s[lines]);
        putchar('\n');
    }
    free(s);

    return;
}

static
int source_pipe(void)
{
    size_t      lines   = 0;

    STRING**    s        = NULL;

    if (read_file(stdin, &lines, &s) < 0)
        return -1;
    else
        do_tacrev(s, lines);

    return 0;
}

static
int source_argument(char* path)
{
    FILE*       fp      = NULL;

    size_t      lines   = 0;

    STRING**    s       = NULL;

    if ((fp = fopen(path, "r")) == NULL) {
        fprintf(stdout, "tacrev: %s: %s\n",
                path, strerror(errno));
        return -1;
    }
    if (read_file(fp, &lines, &s) < 0) {
        fclose(fp);
        return -2;
    }
    fclose(fp);
    do_tacrev(s, lines);

    return 0;
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        while (argc > 1) {
            argc--;
            if (source_argument(argv[argc]) < 0)
                return 1;
        }
    } else {
        if (source_pipe() < 0)
            return 2;
    }

    return 0;
}
