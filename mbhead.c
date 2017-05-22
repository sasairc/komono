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
#define N_DEFAULT   10

int print_usage(void)
{
    fprintf(stdout, "\
Usage: %s [OPTION]... [FILE]...\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
\n\
  -c,  --characters=INT      print the first INT characters of each file\n\
  -l,  --lines=INT           print the first INT lines instead of the first %d\n\
  -q,  --quiet               never print headers giving file names\n\
  -v,  --verbose             always print headers giving file names\n\
\n\
       --help                display this help and exit\n\
", PROGNAME, N_DEFAULT);

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

void do_file_chars(FILE* fp, int n)
{
    int     i       = 0,
            s       = 0,
            c       = 0;

    char    buf[6]  = {'\0'};

    while ((c = fgetc(fp)) != EOF && n > 0) {
        if ((s = get_character_size(c) - 1) > 0) {
            buf[0] = c;
            fread(buf + 1, sizeof(char), s, fp);
            fprintf(stdout, "%s", buf);
            memset(buf, '\0', sizeof(buf));
        } else {
            putchar(c);
        }
        n--;
    }

    return;
}

void do_file_lines(FILE* fp, int n)
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

int main(int argc, char* argv[])
{
    int     n       = N_DEFAULT,
            res     = 0,
            index   = 0;

    short   vflag   = 0;

    FILE*   fp      = NULL;

    void    (*proc)(FILE* fp, int n) = do_file_lines;

    struct option opts[] = {
        {"characters",  required_argument,  NULL,   'c'},
        {"lines",       required_argument,  NULL,   'n'},
        {"quiet",       no_argument,        NULL,   'q'},
        {"verbose",     no_argument,        NULL,   'v'},
        {"help",        no_argument,        NULL,    0 },
        {0, 0, 0, 0},
    };

    while ((res = getopt_long(argc, argv, "c:n:qv", opts, &index)) != -1) {
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
            case    'q':
                vflag = 0;
                break;
            case    'v':
                vflag = 1;
                break;
            case    0:
                print_usage();
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
            if (vflag == 1)
                fprintf(stdout, "==> %s <==\n",
                        *(argv + optind));
            proc(fp, n);
            if (vflag == 1)
                fprintf(stdout, "\n\n",
                        *(argv + optind));
            fclose(fp);
            fp = NULL;
            optind++;
        }
    } else {
        proc(stdin, n);
    }

RELEASE:
    if (fp != NULL)
        fclose(fp);

    return res;
}
