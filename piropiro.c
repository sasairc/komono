/*
 * ぴろぴろ
 *
 * gcc piropiro.c -lm -lsndfile -o piropiro
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <sndfile.h>

#define SAMPLESIZE  1562
#define P_ZERO      640
#define P_ONE       1024

void write_sndfile(FILE* fp, SNDFILE* snf, short sq0[8], short sq1[8]);
char* char_to_bin(char src);

int main(int argc, char* argv[])
{
    int         i       = 0;

    FILE*       fp      = NULL;

    short       sq0[SAMPLESIZE],
                sq1[SAMPLESIZE];

    SF_INFO     sfi;
    SNDFILE*    snf = NULL;

    sfi.channels    = 1;
    sfi.samplerate  = 44100;
    sfi.format      = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    if ((fp = fopen(argv[1], "rb")) == NULL) {
        perror("piropiro");

        return 1;
    }
    if (argc <= 2) {
        fprintf(stderr, "Usage: piropiro input output.wav\n");

        return 2;
    }
    if ((snf = sf_open("out.wav", SFM_WRITE, &sfi)) == NULL) {
        fprintf(stderr, "sf_open() failure\n");

        return 3;
    }

    i = 0;
    while (i < SAMPLESIZE) {
        sq0[i] = sin(((i * (2 * M_PI)) / 44100) * P_ZERO) * (pow(2,14));
        sq1[i] = sin(((i * (2 * M_PI)) / 44100) * P_ONE) * (pow(2,14));
        i++;
    }

    write_sndfile(fp, snf, sq0, sq1);
    sf_write_sync(snf);
    sf_close(snf);

    return 0;
}

void write_sndfile(FILE* fp, SNDFILE* snf, short sq0[8], short sq1[8])
{
    int     i   = 0,
            j   = 0,
            k   = 0,
            fs  = 0;

    char    ch  = '\0',
        *   bin = NULL;

    fseek(fp, 0, SEEK_END);
    fs = ftell(fp);
    rewind(fp);

    while (i < fs) {
        fread(&ch, 1, 1, fp);
        bin = char_to_bin(ch);
        j = 0;
        fprintf(stdout, "%d: %s\n", i, bin);
        while (j < 8) {
            k = 0;
            if (bin[j] == '1') {
                while (k < SAMPLESIZE) {
                    sf_write_short(snf, &sq1[k], 1);
                    k++;
                }
            } else if (bin[j] == '0') {
                while (k < SAMPLESIZE) {
                    sf_write_short(snf, &sq0[k], 1);
                    k++;
                }
            }
            j++;
        }
        free(bin);
        bin = NULL;
        i++;
    }

    return;
}

char* char_to_bin(char src)
{
    int     i       = 0,
            num     = 0;

    char*   dest    = NULL;;

    dest = malloc(8);
    while (i < 8) {
        dest[i] = '0';
        i++;
    }
    num = src;

    i = 7;
    while (i >= 0) {
        dest[i] = (num % 2) + 48;
        num /= 2;
        i--;
    }

    return dest;
}
