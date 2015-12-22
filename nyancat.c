/*
 * にゃんぱす投げ
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <getopt.h>
#include <n_cipher.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PROGNAME    "nyancat"
#define PORT        1024

#define REG_IPV4    "^([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5]).([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5]).([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5]).([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])$"

typedef struct {
    int         sflag;
    int         pflag;
    uint16_t    net_port;
    char*       net_ipv4_addr;
} nc_t;

int sender(nc_t* nyan, char** data, int datalen);
int is_ipaddr(char* src);
char* nslookup(char* hostname);
int p_count_file_lines(char** buf);
char** p_read_file_char(int t_lines, size_t t_length, FILE* fp);
int print_usage(void);
int print_version(void);
void release(nc_t* nyan);

int main(int argc, char* argv[])
{
    int     i       = 0,
            res     = 0,
            index   = 0,
            datalen = 0;
    char**  data    = NULL;

    nc_t    nyan    = {
        1, 0, 0, NULL,
    };
    
    struct  option opts[] = {
        {"send",    no_argument,        NULL, 's'},
        {"port",    required_argument,  NULL, 'p'},
        {"help",    no_argument,        NULL, 'h'},
        {"version", no_argument,        NULL, 'v'},
        {0, 0, 0, 0},
    };

    while ((res = getopt_long(argc, argv, "sp:hv", opts, &index)) != -1) {
        switch (res) {
            case    's':
                nyan.sflag = 1;
                break;
            case    'p':
                for (i = 0; i < strlen(optarg); i++) {
                    if (!isdigit(*(optarg + i))) {
                        fprintf(stderr, "%s: %s: invalid port number\n",
                                PROGNAME, optarg);
                        return -1;
                    }
                }
                nyan.net_port = atoi(optarg);
                nyan.pflag = 1;
                break;
            case    'h':
                print_usage();
            case    'v':
                print_version();
            case    '?':
                return -1;
        }
    }

    /* check required argument */
    if (optind != (argc - 1)) {
        fprintf(stderr, "%s: invalid values\n",
                PROGNAME);

        return 1;
    }

    /* set default port */
    if (nyan.pflag == 0)
        nyan.net_port = PORT;

    /* set hostname */
    if (is_ipaddr(argv[optind]) == 0) {
        nyan.net_ipv4_addr = nslookup(argv[optind]);
    } else {
        if ((nyan.net_ipv4_addr = (char*)malloc(sizeof(char) * (strlen(argv[optind])) + 1)) == NULL)
            fprintf(stderr, "%s: malloc() failure\n",
                    PROGNAME);
        else
            strcpy(nyan.net_ipv4_addr, argv[optind]);
    }

    /* reading stdin */
    if (nyan.sflag == 1) {
        if ((data = p_read_file_char(512, 512, stdin)) == NULL) {
            fprintf(stderr, "%s: p_read_file_char() failure\n",
                    PROGNAME);

            return 3;
        }
        datalen = p_count_file_lines(data);
        if (sender(&nyan, data, datalen) != 0) {
            fprintf(stderr, "%s: sender failure\n",
                    PROGNAME);
            release(&nyan);

            return 4;
        }
    }
    release(&nyan);

    return 0;
}

int sender(nc_t* nyan, char** data, int datalen)
{
    int     i       = 0,
            sv      = 0,
            sv_ac   = 0,
            optval  = 1;
    char*   dest    = NULL;

    struct sockaddr_in  addr;

    if ((sv = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");

        return 1;
    }
    if ((setsockopt(sv, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval)) < 0) {
        perror("setsockopt");

        return 2;
    }

    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(nyan->net_ipv4_addr);
    addr.sin_port = htons(nyan->net_port);

    if (bind(sv, (struct sockaddr *)&addr, sizeof addr) < 0) {
        perror("bind");

        return 3;
    }

    listen(sv, SOMAXCONN);
    sv_ac = accept(sv, 0, 0);

    for (i = 0; i < datalen; i++) {
        dest = encode_n_cipher(data[i], SEED, DELIMITER);
        write(sv_ac, dest, strlen(dest));
        if (dest != NULL) {
            free(dest);
            dest = NULL;
        }
    }
    close(sv);
    close(sv_ac);

    return 0;
}

int is_ipaddr(char* src)
{
    int         ret;
    regex_t     reg;

    if (regcomp(&reg, REG_IPV4, REG_NOSUB | REG_EXTENDED) != 0)
        return -1;

    ret = regexec(&reg, src, 0, NULL, 0);
    regfree(&reg);

    ret ^= 1;

    return ret;
}

char* nslookup(char* hostname)
{
    char*   dest    = NULL,
        *   tmp     = NULL;

    struct  sockaddr_in addr;
    struct  hostent*    host    = NULL;

    if ((host = gethostbyname(hostname)) == NULL)
        return NULL;
    else
        addr.sin_addr = *(struct in_addr*)(host->h_addr_list[0]);

    tmp = inet_ntoa(addr.sin_addr);
    if ((dest = (char*)malloc(sizeof(char) * (strlen(tmp) + 1))) == NULL)
        return NULL;
    else
        strcpy(dest, tmp);

    return dest;
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
    /* no data */
    if (x == 0 && y == 0) {
        buf[y] = NULL;
        free(str);

        return buf;
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
    free(str);

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

void release(nc_t* nyan)
{
    if (nyan->net_ipv4_addr != NULL) {
        free(nyan->net_ipv4_addr);
        nyan->net_ipv4_addr = NULL;
    }

    return;
}
