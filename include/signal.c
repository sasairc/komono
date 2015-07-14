/*
 *
 *
 * signal.c
 *
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include "./signal.h"
#include <signal.h>
#include <stdlib.h>

int set_signal(int sig, void (*func)(int sig))
{
    if (signal(sig, func) == SIG_ERR) {

        return 1;
    }

    return 0;
}

int set_signal_siglist(siglist_t* siglist)
{
    int i;

    if (siglist == NULL) {

        return 1;
    }

    for (i = 0; (siglist + i)->sig != 0 && (siglist + i)->func != NULL; i++) {
        if (signal((siglist + i)->sig, (siglist + i)->func) == SIG_ERR) {

            return 2;
        }
    }

    return 0;
}

void handl_zombie_proc(void)
{
    struct  sigaction sa;

    sa.sa_handler   = SIG_IGN;
    sa.sa_flags     = SA_NOCLDWAIT;

    if (sigaction(SIGCHLD, &sa, NULL) == -1) {

        exit(1);
    }
}
