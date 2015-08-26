/*
 * うに
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <glib.h>
#include <getopt.h>

int get_codepoint(char* str);
int p_count_file_lines(char** buf);
char** p_read_file_char(int t_lines, size_t t_length, FILE* fp);
int print_usage(void);
int print_version(void);

int main(int argc, char* argv[])
{
    int     i       = 0,
            res     = 0,
            index   = 0,
            lflag   = 0,
            lines   = 0;
    char**  buf     = NULL;

    struct option opts[] = {
        {"print-lf",    no_argument,    NULL,   'l'},
        {"help",        no_argument,    NULL,    0 },
        {"version",     no_argument,    NULL,    1 },
        {0, 0, 0, 0},
    };

    while ((res = getopt_long(argc, argv, "l", opts, &index)) != -1) {
        switch (res) {
            case    'l':
                lflag = 1;
                break;
            case    0:
                print_usage();
            case    1:
                print_version();
            case    '?':
                return -1;
            }
    }

    if ((buf = p_read_file_char(640, 640, stdin)) == NULL) {
        fprintf(stderr, "p_read_file_char() failure\n");

        return 1;
    }
    lines = p_count_file_lines(buf);

    for (i = 0; i < lines; i++) {
        if (lflag == 1)
            buf[i][strlen(buf[i]) - 1] = '\0';

        get_codepoint(buf[i]);
        free(buf[i]);

        if (lflag == 1)
            putchar('\n');
    }
    free(buf);

    return 0;
}

int get_codepoint(char* str)
{
    int         i       = 0,
                ch      = 0;
    gunichar*   cpoints;

    setlocale(LC_CTYPE, "ja_JP.UTF-8");

    while (i < strlen(str)) {
        ch = mblen(&str[i], MB_CUR_MAX);

        cpoints = g_utf8_to_ucs4_fast(&str[i], sizeof(str[i]), NULL);
        fprintf(stdout, "\\u%04x", *cpoints);
        g_free(cpoints);

        if (ch > 1) {
            i += ch;
        } else {
            i++;
        }
    }

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
            length  = t_length,
            i       = 0,
            x       = 0,
            y       = 0,
            c       = 0;
    char*   str     = (char*)malloc(sizeof(char) * t_length),   /* allocate temporary array */
        **  buf     = (char**)malloc(sizeof(char*) * t_lines);  /* allocate array of Y coordinate */

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
                if ((buf[y] = (char*)malloc(sizeof(char) * (strlen(str) + 1))) == NULL) {

                    goto ERR;
                }
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
        if ((buf[y] = (char*)malloc(sizeof(char) * (strlen(str) + 1))) == NULL) {

            goto ERR;
        }
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

int print_usage(void)
{
    fprintf(stdout, "んなものはない\n");

    exit(0);
}

int print_version(void)
{
    fprintf(stdout, "んなものもない\n");

    exit(0);
}
