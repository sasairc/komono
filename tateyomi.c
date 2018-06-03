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

static int read_file(FILE* fp, STRING*** s, size_t* rows, size_t* cols);
static int equalize(STRING** s, size_t rows, size_t cols);
static int to_char_arr2(STRING** s1, char**** s2, size_t rows);
static void tateyomi(char*** const s, size_t rows, size_t cols);
static void release(STRING** s1, char*** s2, size_t rows);

int main(void)
{
    int         status  = 0;

    size_t      rows    = 0,
                cols    = 0;

    STRING**    s1      = NULL;

    char***     s2      = NULL;

    if (read_file(stdin, &s1, &rows, &cols) < 0) {
        status = 1; goto ERR;
    }
    if (equalize(s1, rows, cols) < 0) {
        status = 2; goto ERR;
    }
    if (to_char_arr2(s1, &s2, rows) < 0) {
        status = 3; goto ERR;
    }
    tateyomi(s2, rows, cols);
    release(s1, s2, rows);

    return 0;

ERR:
    fprintf(stderr, "tateyomi: %s\n",
            strerror(errno));
    release(s1, s2, rows);

    return status;
}

static
int read_file(FILE* fp, STRING*** s, size_t* rows, size_t* cols)
{
    size_t  n       = 0,
            r_size  = DEFAULT_ROW_SIZE;

    if ((*s = (STRING**)
                malloc(sizeof(STRING*) * r_size)) == NULL)
        return -1;
    while (fgetline(fp, &(*s)[*rows]) != EOF) {
        (*s)[*rows]->chomp(&(*s)[*rows]);
        if ((n = (*s)[*rows]->mblen((*s)[*rows])) > *cols)
            *cols = n;
        if (WINVALIDCHAR(string_errno)) {
            (*s)[*rows]->release((*s)[*rows]);
            return -2;
        }
        if (*rows >= (r_size - 1)) {
            r_size += DEFAULT_ROW_SIZE;
            if ((*s = (STRING**)
                        realloc(*s, sizeof(STRING*) * r_size)) == NULL)
                return -3;
        }
        (*rows)++;
    }

    return 0;
}

static
int equalize(STRING** s, size_t rows, size_t cols)
{
    size_t  i   = 0,
            j   = 0;

    while (i < rows) {
        j = s[i]->mblen(s[i]);
        if (WINVALIDCHAR(string_errno)) {
            s[i]->release(s[i]);
            return -1;
        }
        while (j < cols) {
            s[i]->append(&s[i], "　");
            j++;
        }
        i++;
    }

    return 0;
}

static
int to_char_arr2(STRING** s1, char**** s2, size_t rows)
{
    size_t  i   = 0;

    if ((*s2 = (char***)
                malloc(sizeof(char**) * rows)) == NULL)
        return -1;

    while (i < rows) {
        s1[i]->to_char_arr(s1[i], &(*s2)[i]);
        i++;
    }

    return 0;
}

static
void tateyomi(char*** const s, size_t rows, size_t cols)
{
    size_t  i   = 0,
            j   = 0;

    while (i < cols && (j = rows)) {
        do {
            j--;
            fprintf(stdout, "%s",
                    *(*(s + j) + i));
        } while (j);
        putchar('\n');
        i++;
    }

    return;
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
