#include "./ysh.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int ysh_chdir(char** args)
{
    char*   pwd = NULL;

    if (args[1] == NULL)
        pwd = getenv("HOME");
    else
        pwd = args[1];

    if (chdir(pwd) < 0) {
        perror("chdir");

        return errno;
    }

    return 0;
}

int ysh_exit(cmd_t* cmd)
{
    release_cmd_t(cmd);

    exit(0);
}
