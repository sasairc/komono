/*
 * mbhead - output the first part of files
 *
 * mbhead.c
 *
 * Copyright (c) 2017 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>

#define PROGNAME    "mbhead"
#define AUTHOR      "sasairc"
#define MAIL_TO     "sasairc@ssiserver.moe.hm"

#define N_DEFAULT   10      /* default put lines */
#define M_PIPE      (1 << 1)
#define M_VERBOSE   (1 << 2)

int print_usage(void);
int print_version(void);
int strisdigit(char* str);
int get_character_size(unsigned char code);
void do_file_chars(FILE* fp, int n, short flag);
void do_file_lines(FILE* fp, int n, short flag);

int print_usage(void)
{
    fprintf(stdout, "\
Usage: %s [OPTION]... [FILE]...\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
\n\
  -c,  --characters=INT      print the first INT characters of each file\n\
  -l,  --lines=INT           print the first INT lines instead of the first %d\n\
  -p,  --pipe                print the first characters/lines, after append line-feed\n\
  -q,  --quiet, --silent     never print headers giving file names\n\
  -v,  --verbose             always print headers giving file names\n\
\n\
       --help                display this help and exit\n\
       --version             output version infomation and exit\n\
\n\
Report %s bugs to %s <%s>\n\
" , PROGNAME, N_DEFAULT, PROGNAME, AUTHOR, MAIL_TO);

    exit(0);
}

int print_version(void)
{
    fprintf(stdout, "%sのバージョン？んなものは無い。\n",
            PROGNAME);

    exit(0);
}

int get_character_size(unsigned char code)
{
    size_t  byte    = 0;

    if ((code & 0x80) == 0x00)
        byte = 1;
    else if ((code & 0xE0) == 0xC0)
        byte = 2;
    else if ((code & 0xF0) == 0xE0)
        byte = 3;
    else if ((code & 0xF8) == 0xF0)
        byte = 4;
    else if ((code & 0xFC) == 0xF8)
        byte = 5;
    else if ((code & 0xFE) == 0xFC)
        byte = 6;
    else
        return 1;

    return byte;
}

int strisdigit(char* str)
{
    char*   p   = str;

    while (*p != '\0') {
        if (!isdigit(*p))
            return -1;
        p++;
    }

    return 0;
}

void do_file_chars(FILE* fp, int n, short flag)
{
    int     c       = 0;

    size_t  s       = 0;

    char    buf[6]  = {'\0'};

    while ((c = fgetc(fp)) != EOF && n > 0) {
        if ((s = get_character_size(c) - 1) > 0) {
            buf[0] = c;
            fread(buf + 1, sizeof(char), s , fp);
            fprintf(stdout, "%s", buf);
            memset(buf, '\0', sizeof(buf));
        } else {
            putchar(c);
        }
        n--;
    }
    /* put LF */
    if (flag & M_PIPE)
        putchar(0x0A);

    return;
}

void do_file_lines(FILE* fp, int n, short flag)
{
    int     c   = 0;

    while ((c = fgetc(fp)) != EOF && n > 0) {
        switch (c) {
            case    EOF:
                return;
            case    '\n':
                n--;
            default:
                putchar(c);
        }
    }

    return;
}

int main(int argc, char* argv[])
{
    int     n       = N_DEFAULT,
            res     = 0,
            index   = 0;

    short   flag    = 0;

    FILE*   fp      = NULL;

    void    (*proc)(FILE* fp, int n, short flag) = do_file_lines;

    struct option opts[] = {
        {"characters",  required_argument,  NULL,   'c'},
        {"lines",       required_argument,  NULL,   'n'},
        {"quiet",       no_argument,        NULL,   'q'},
        {"verbose",     no_argument,        NULL,   'v'},
        {"pipe",        no_argument,        NULL,   'p'},
        {"silent",      no_argument,        NULL,    0 },
        {"help",        no_argument,        NULL,    1 },
        {"version",     no_argument,        NULL,    2 },
        {0, 0, 0, 0},
    };

    while ((res = getopt_long(argc, argv, "c:n:vqp", opts, &index)) != -1) {
        switch (res) {
            case    'c':
                if (strisdigit(optarg) < 0) {
                    fprintf(stderr, "%s: %s: invalid number of characters\n",
                            PROGNAME, optarg); 
                    return 1;
                }
                n = atoi(optarg);
                proc = do_file_chars;
                break;
            case    'n':
                if (strisdigit(optarg) < 0) {
                    fprintf(stderr, "%s: %s: invalid number of lines\n",
                            PROGNAME, optarg); 
                    return 2;
                }
                n = atoi(optarg);
                proc = do_file_lines;
                break;
            case    'v':
                flag |= M_VERBOSE;
                break;
            case    'q':
            case    0:
                flag &= ~M_VERBOSE;
                break;
            case    'p':
                flag |= M_PIPE;
                break;
            case    1:
                print_usage();
            case    2:
                print_version();
            case    '?':
                return -1;
        }
    }

    res = 0;
    if (optind < argc) {
        while (optind < argc) {
            if ((fp = fopen(*(argv + optind), "r")) == NULL) {
                fprintf(stderr, "%s: %s: %s\n",
                        PROGNAME, *(argv + optind), strerror(errno));
                res = errno; goto RELEASE;
            }
            if (flag & M_VERBOSE)
                fprintf(stdout, "==> %s <==\n",
                        *(argv + optind));
            proc(fp, n, flag);
            fclose(fp);
            fp = NULL;
            if ((optind + 1 < argc) && flag & M_VERBOSE)
                putchar('\n');
            optind++;
        }
    } else {
        proc(stdin, n, flag);
    }

RELEASE:
    if (fp != NULL)
        fclose(fp);

    return res;
}
