/*
 * チョット待ってね
 *
 * waiting.c
 *
 * Copyright (c) 2018 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include <benly/spinner.h>
#include <benly/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <getopt.h>

#define PROGNAME        "waiting"
#define DEFAULT_MESSAGE "waiting...\0"
#define DEFAULT_SYMBOL  "|/-\\|/-\\\0"

static int print_usage(void);

int main(int argc, char* argv[])
{
    int         res     = 0,
                index   = 0,
                status  = 0;

    useconds_t  usec    = DEFAULT_DELAY_TIME;

    char*       msg     = DEFAULT_MESSAGE,
        *       sym     = DEFAULT_SYMBOL,
        *       cmd     = NULL;

    SPINNER*    sp      = NULL;

    struct option opts[] = {
        {"command", required_argument, NULL, 'c'},
        {"message", required_argument, NULL, 'm'},
        {"symbol",  required_argument, NULL, 's'},
        {"delay",   required_argument, NULL, 't'},
        {"help",    no_argument,       NULL,  0 },
        {0, 0, 0, 0},
    };

    while ((res = getopt_long(argc, argv, "c:m:s:t:", opts, &index)) != -1) {
        switch (res) {
            case    'c':
                cmd = optarg;
                break;
            case    'm':
                msg = optarg;
                break;
            case    's':
                sym = optarg;
                break;
            case    't':
                if (strisdigit(optarg) < 0) {
                    fprintf(stderr, "%s: %s: invalid time interval\n",
                            PROGNAME, optarg);
                    return -1;
                }
                sscanf(optarg, "%u", &usec);
                break;
            case    0:
                print_usage();
            case    '?':
                return -1;
        }
    }

    if (fork() == 0) {
        if (cmd == NULL)
            exit(execvp(*(argv + optind), argv + optind));
        else
            exit(system(cmd));
    }
    init_spinner(&sp);
    if (usec != DEFAULT_DELAY_TIME)
        sp->chg_delay_time(&sp, usec);
    sp->until(&sp, msg, sym);
    wait(&status);
    sp->done(sp);
    sp->release(sp);

    return WEXITSTATUS(status);
}

static
int print_usage(void)
{
    fprintf(stdout, "\
Usage: %s [OPTION]... [-c COMMAND || COMMAND]\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
\n\
  -c,  --command=CMD         read commands from this operand\n\
  -m,  --message=STR         specify waiting message, default \"%s\"\n\
  -s,  --symbol=STR          specify waiting symbol, default \"%s\"\n\
  -t,  --delay=USEC          specify delay time, default %u usec\n\
\n\
       --help                display this help and exit\n\
", PROGNAME, DEFAULT_MESSAGE, DEFAULT_SYMBOL, DEFAULT_DELAY_TIME);

    exit(0);
}
