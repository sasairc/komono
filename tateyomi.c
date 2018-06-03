/*
 * tateyomi.c
 *
 * require. libbenly >= 1.0.0-33
 *
 * % gcc -lbenly_typestring tateyomi.c -o tateyomi
 */
#include <benly/typestring.h>
#include <stdio.h>
#include <stdlib.h> /* malloc(), realloc(), free() */
#include <string.h> /* strerror() */
#include <errno.h>  /* errno */

#define DEFAULT_ROW_SIZE    32

static void release(STRING** s1, char*** s2, size_t rows);

int main(void)
{
    int         status  = 0;

    size_t      i       = 0,
                j       = 0,
                rows    = 0,
                cols    = 0,
                r_size  = DEFAULT_ROW_SIZE;

    STRING**    s1      = NULL;

    char***     s2      = NULL;

    if ((s1 = (STRING**)
                malloc(sizeof(STRING*) * r_size)) == NULL) {
        status = 1; goto ERR;
    }
    while (fgetline(stdin, &s1[rows]) != EOF) {
        s1[rows]->chomp(&s1[rows]);
        if ((i = s1[rows]->mblen(s1[rows])) > cols)
            cols = i;
        if (WINVALIDCHAR(string_errno)) {
            status = 2; goto ERR;
        }
        if (rows >= (r_size - 1)) {
            r_size += DEFAULT_ROW_SIZE;
            if ((s1 = (STRING**)
                        realloc(s1, sizeof(STRING*) * r_size)) == NULL) {
                status = 3; goto ERR;
            }
        }
        rows++;
    }
    i = 0;
    while (i < rows) {
        j = s1[i]->mblen(s1[i]);
        while (j < cols) {
            s1[i]->append(&s1[i], "　");
            j++;
        }
        i++;
    }
    if ((s2 = (char***)
                malloc(sizeof(char**) * rows)) == NULL) {
        status = -4; goto ERR;
    }
    i = 0;
    while (i < rows) {
        s1[i]->to_char_arr(s1[i], s2 + i);
        i++;
    }
    i = 0;
    while (i < cols && (j = rows)) {
        do {
            j--;
            fprintf(stdout, "%s",
                    *(*(s2 + j) + i));
        } while (j);
        putchar('\n');
        i++;
    }
    release(s1, s2, rows);

    return 0;

ERR:
    fprintf(stderr, "tateyomi: %s\n",
            strerror(errno));
    release(s1, s2, rows);

    return status;
}

static
void release(STRING** s1, char*** s2, size_t rows)
{
    size_t  i   = 0;

    while (i < rows) {
        if (s1 != NULL && s1[i] != NULL) {
            if (s2 != NULL && *(s2 + i) != NULL)
                release_char_arr(s1[i], 0, *(s2 + i));
            s1[i]->release(s1[i]);
        }
        i++;
    }
    if (s1 != NULL)
        free(s1);
    if (s2 != NULL)
        free(s2);

    return;
}
