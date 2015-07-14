/*
 * body - Print the center 10 lines of each FILE to standard output.
 *
 * body.c
 *
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>

#define PROGNAME    "body"
#define AUTHOR      "sasairc"
#define MAIL_TO     "sasairc@ssiserver.moe.hm"

#define N_DEFAULT   10

typedef struct BODY_T {
    int nflag;
    int qflag;
    int vflag;
    int narg;
} body_t;

FILE* sopen_file(char* path);
int check_file_access(char* path);
int print_body(int lines, char** buf, body_t* bodyopt);
int p_count_file_lines(char** buf);
char** p_read_file_char(int t_lines, size_t t_length, FILE* fp);
void release(char** buf, int y);
void print_usage(void);
void print_version(void);

int main(int argc, char* argv[])
{
    FILE*   fp;
    int     i;
    int     res, index, lines;
    char*   path = NULL;
    char**  buf  = NULL;

    body_t bodyopt = {
        0, 0, 0, 0,
    };
    struct option opts[] = {
        {"lines",   required_argument,  NULL, 'n'},
        {"quiet",   no_argument,        NULL, 'q'},
        {"verbose", no_argument,        NULL, 'v'},
        {"help",    no_argument,        NULL,  0 },
        {"version", no_argument,        NULL,  1 },
        {0, 0, 0, 0}
    };

    while ((res = getopt_long(argc, argv, "n:qv", opts, &index)) != -1) {
        switch (res) {
            case    'n':
                bodyopt.nflag = 1;
                bodyopt.narg = atoi(optarg);
                break;
            case    'q':
                bodyopt.qflag = 1;
                break;
            case    'v':
                bodyopt.vflag = 1;
                break;
            case    0:
                print_usage();
                exit(0);
            case    1:
                print_version();
                exit(0);
            case    '?':
                return -1;
        }
    }

    if (optind < argc) {
        for (i = optind; i < argc; i++) {
            if (check_file_access(argv[i]) != 0)
                return 1;

            fp = sopen_file(argv[i]);
            buf = p_read_file_char(1024, 1024, fp);
            lines = p_count_file_lines(buf);
            fclose(fp);

            if (i > optind)
                putchar('\n');
            if (bodyopt.vflag == 1)
                fprintf(stdout, "==> %s <==\n", argv[i]);

            print_body(lines, buf, &bodyopt);
            release(buf, lines);
        }
    } else {
        if ((buf = p_read_file_char(1024, 1024, stdin)) == NULL) {
            fprintf(stderr, "%s p_read_file_char() failure\n", PROGNAME);
            
            return 2;
        }
        lines = p_count_file_lines(buf);
        print_body(lines, buf, &bodyopt);
        release(buf, lines);
    }

    return 0;
}

FILE* sopen_file(char* path)
{
    FILE*   fp;

    if ((fp = fopen(path, "r")) == NULL) {
        fprintf(stderr, "%s: fopen() failure\n", PROGNAME);

        exit(3);
    }

    return fp;
}

int check_file_access(char* path)
{
    struct  stat statbuf;

    if (access(path, R_OK)) {
        fprintf(stderr, "%s: cannnot open '%s' for reading: Permission denied\n", PROGNAME, path);

        return 1;
    }

    if (stat(path, &statbuf) != 0) {
        fprintf(stderr, "%s: cannnot open '%s' for reading: No such file or directory\n", PROGNAME, path);

        return 2;
    }
    if (S_ISDIR(statbuf.st_mode)) {
        fprintf(stderr, "%s: error reading '%s': Is a directory\n", PROGNAME, path);

        return 2;
    }

    return 0;
}

int print_body(int lines, char** buf, body_t* bodyopt)
{
    int i;
    unsigned int b_center;
    unsigned int n_center;

    b_center = lines / 2;

    if (bodyopt->nflag == 1) {
        if (lines >= bodyopt->narg) {
            n_center = bodyopt->narg / 2;
        } else {
            for (i = 0; i < lines; i++)
                fprintf(stdout, "%s", buf[i]);

            return 0;
        }
    } else {
        n_center = N_DEFAULT / 2;
    }

    for (i = (b_center - n_center); i < (b_center + n_center); i++)
            fprintf(stdout, "%s", buf[i]);

    return 0;
}

int p_count_file_lines(char** buf)
{
    int i;

    for (i = 0; buf[i] != NULL; i++);

    return i;
}

char** p_read_file_char(int t_lines, size_t t_length, FILE* fp)
{
    int     lines   = t_lines,
            length  = t_length;
    int     i       = 0,
            x       = 0,
            y       = 0;
    char    c;
    char*   str     = (char*)malloc(sizeof(char) * t_length);   /* allocate temporary array */
    char**  buf     = (char**)malloc(sizeof(char*) * t_lines);  /* allocate array of Y coordinate */

    if (str == NULL || buf == NULL) {

        return NULL;
    } else if (t_lines == 0 || t_length == 0 || fp == NULL) {
        free(str);
        free(buf);

        return NULL;
    }

    while ((c = fgetc(fp)) != EOF) {
        switch (c) {
            case    '\n':
                str[x] = c;

                /* reallocate array of Y coordinate */
                if (y == (lines - 1)) {
                    lines += t_lines;
                    if ((buf = (char**)realloc(buf, sizeof(char*) * lines)) == NULL) {

                        goto ERR;
                    }
                }
                /* allocate array for X coordinate */
                buf[y] = (char*)malloc(sizeof(char) * (strlen(str) + 1));
                strcpy(buf[y], str);    /* copy, str to buffer */
                for (i = 0; i < length; i++) {
                    str[i] = '\0';      /* refresh temporary array */
                }

                x = 0;
                y++;
                break;
            default:
                /* reallocate temporary array */
                if (x == (length - 1)) {
                    length += t_length;
                    if ((str = (char*)realloc(str, length)) == NULL) {

                        goto ERR;
                    }
                }

                str[x] = c;
                x++;
                continue;
        }
    }

    if (str[0] != '\0') {
        if (y == (lines - 1)) {
            str[x] = c;
            lines += t_lines;
            if ((buf = (char**)realloc(buf, sizeof(char*) * lines)) == NULL) {

                goto ERR;
            }
        }
        buf[y] = (char*)malloc(sizeof(char) * (strlen(str) + 1));
        strcpy(buf[y], str);
        y++;
    }
    buf[y] = NULL;

    return buf;


ERR:
    lines   -= t_lines;
    length  -= t_length;

    if (buf != NULL) {
        for (i = 0; i < lines; i++) {
            if (buf[i] != NULL) {
                free(buf[i]);
                buf[i] = NULL;
            }
        }
        free(buf);
    }
    if (str != NULL)
        free(str);

    return NULL;
}

void release(char** buf, int y)
{
    int i;

    for (i = 0; i < y; i++) {
        if (buf[i] != NULL) {
            free(buf[i]);
            buf[i] = NULL;
        }
    }
    free(buf);

    return;
}

void print_usage(void)
{
    fprintf(stdout, "\
Usage: body [OPTION]... [FILE]...\n\
Print the center 10 lines of each FILE to standard output.\n\
With more than one FILE, precede each with a header giving the file name.\n\
With no FILE, or when FILE is -, read standard input.\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
  -n, --lines=[-]K         print the center K lines instead of the center 10\n\
  -q, --quiet              never print headers giving file names\n\
  -v, --verbose            allways print headers giving file names\n\
\n\
      --help               display this help and exit\n\
      --version            output version information and exit\n\
\n\
Report %s bugs to %s <%s>\n\
",
    PROGNAME,
    AUTHOR, MAIL_TO);

    exit(0);
}

void print_version(void)
{
    fprintf(stdout, "body\n");

    exit(0);
}
