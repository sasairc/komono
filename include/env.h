/*
 *
 *
 * env.h
 *
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#ifndef ENV_H
#define ENV_H

typedef struct ENV_T {
    int     envs;
    char**  envc;
} env_t;

extern env_t* split_env(char* env);
extern void release_env_t(env_t* env);

#endif