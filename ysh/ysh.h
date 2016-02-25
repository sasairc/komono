/*
 * ysh.h
 */

#ifndef YSH_H
#define YSH_H

#define TCOM    1   /* command */
#define TPAREN  2   /* a ; b */
#define TPIPE   3   /* a | b */
#define TAND    4   /* a && b */
#define TOR     5   /* a || b*/

#define IOREAD  1   /* < */
#define IOHERE  2   /* << */
#define IOWRITE 3   /* > */
#define IOCAT   4   /* >> */

typedef struct IO_T {
    short   io_flag;
    char*   io_name;
} io_t;

typedef struct CMD_T {
    int             num;
    int             type;
    char**          args;
    struct IO_T*    io;
    struct CMD_T*   next;
    struct CMD_T*   prev;
} cmd_t;

extern int parse_cmdline(char* str, cmd_t** dest_cmd, cmd_t** dest_start);
extern int file_redirect(cmd_t* cmd);
extern int exec_cmd(cmd_t* cmd, int in_fd);
extern void redirect(int oldfd, int newfd);
extern void mwait(void);
extern void release_cmd_t(cmd_t* cmd);

#endif
