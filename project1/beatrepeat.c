#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>

#include "sox.h"

void usage() {
    printf("beatrepeat [options] infile outfile\n\n"
            "Options:\n\n"
            "    -v    verbose. specify more to be more verbose\n"
            "    -t    output file type/driver (see equivalent sox option)\n"
            "    -T    tempo (decimal > 0)\n"
            "    -b    beats (integer > 0)\n"
            "    -o    offset (integer >= 0)\n"
            "    -h    max hunk slices (integer > 0)\n"
            "    -c    max chunk slices (integer > 0)\n"
            "    -s    shuffle chance (decimal >= 0)\n"
            "    -r    repeat chance (decimal >= 0)\n"
            "    -S    random seed (integer)\n");
}

typedef struct _arguments {
    double tempo;
    double beats;
    unsigned int hunk_slices;
    unsigned int chunk_slices;
    unsigned int offset;
    double shuffle_chance;
    double repeat_chance;
    unsigned int seed;
    char *output_type;
} arguments;

size_t bufsize(sox_format_t *format, double period) {
    size_t buf_size;
    buf_size = period * format->signal.rate * format->signal.channels + .5;
    buf_size -= buf_size % format->signal.channels;
    return buf_size;
}

double secs_per_beat(double tempo) {
    return (1.0 / tempo) * 60;
}

double drand() {
    return rand() / (double) RAND_MAX;
}

unsigned int rand_interval(unsigned int min, unsigned int max) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int main(int argc, char *argv[]) {
    static sox_format_t *in, *out;
    sox_sample_t *buf;
    double buf_period;
    size_t buf_size;
    size_t read;
    arguments args;

    args.tempo = 120;
    args.beats = 4;
    args.hunk_slices = 8;
    args.chunk_slices = 8;
    args.offset = 2;
    args.shuffle_chance = 0.3;
    args.repeat_chance = 0.75;
    args.seed = time(NULL);

    if (sox_init() != SOX_SUCCESS) {
        fprintf(stderr, "error: could not initialize SoX\n");
        exit(EXIT_FAILURE);
    }

    /* parse arguments */
    char c;
    while ((c = getopt(argc, argv, "vt:T:b:h:c:o:s:r:S:")) != -1) {
        switch (c) {
        case 'v': /* verbose */
            sox_get_globals()->verbosity++;
            break;
        case 't': /* output type */
            args.output_type = optarg;
            break;
        case 'T': /* tempo */
            args.tempo = strtod(optarg, NULL);

            if (args.tempo <= 0) {
                fprintf(stderr, "error: tempo must be greater than zero\n");
                exit(EXIT_FAILURE);
            }

            break;
        case 'b': /* beats */
            args.beats = strtod(optarg, NULL);

            if (args.beats <= 0) {
                fprintf(stderr, "error: beats must be greater than zero\n");
                exit(EXIT_FAILURE);
            }

            break;
        case 'h': /* hunk slices */
            args.hunk_slices = strtoumax(optarg, NULL, 10);
            break;
        case 'c': /* chunk slices */
            args.chunk_slices = strtoumax(optarg, NULL, 10);
            break;
        case 'o': /* offset */
            args.offset = strtoumax(optarg, NULL, 10);
            break;
        case 's': /* shuffle chance */
            args.shuffle_chance = strtod(optarg, NULL);

            if (args.repeat_chance < 0) {
                fprintf(stderr, "error: shuffle chance must be zero or more\n");
                exit(EXIT_FAILURE);
            }

            break;
        case 'r': /* repeat chance */
            args.repeat_chance = strtod(optarg, NULL);

            if (args.repeat_chance < 0) {
                fprintf(stderr, "error: repeat chance must be zero or more\n");
                exit(EXIT_FAILURE);
            }

            break;
        case 'S': /* random seed */
            args.seed = strtoumax(optarg, NULL, 10);
            break;
        }
    }

    if (argc - optind < 2) {
        usage();
        exit(EXIT_FAILURE);
    }

    srand(args.seed);

    /* open input file */

    if ((in = sox_open_read(argv[optind++], NULL, NULL, NULL)) == NULL) {
        fprintf(stderr, "error: could not read input file\n");
        exit(EXIT_FAILURE);
    }

    /* open output file/device */

    if ((out = sox_open_write(argv[optind++], &in->signal,
                    NULL, args.output_type, NULL, NULL)) == NULL) {
        fprintf(stderr, "error: could not open output\n");
        exit(EXIT_FAILURE);
    }

    /* buffer contains the specified number of beats each time we read */
    buf_period = secs_per_beat(args.tempo) * args.beats;
    buf_size = bufsize(in, buf_period);
    buf = (sox_sample_t *) malloc(sizeof(sox_sample_t) * buf_size);

    while ((read = sox_read(in, buf, buf_size)) != 0) {
        /* the buffer is virtually sliced into equally sized portions */
        unsigned int hunks = args.hunk_slices;
        size_t hunk_len = ((buf_size / in->signal.channels) /
                hunks) * in->signal.channels;

        for (unsigned int h = 0; h < hunks; h++) {
            /* choose a random hunk, if we are lucky (shuffle chance) and
             * if the shuffling is not offset (offset causes the hunks in
             * the beginning to be in regular order). this is not really
             * shuffling though. */
            unsigned int hunk;
            if (h >= args.offset && drand() < args.shuffle_chance) {
                hunk = rand_interval(args.offset, hunks - 1);
            } else {
                hunk = h;
            }

            /* slice the hunk further into chunks */

            unsigned int chunks = rand_interval(1, args.chunk_slices);
            size_t chunk_len = ((hunk_len / in->signal.channels) /
                chunks) * in->signal.channels;

            unsigned int chunk = 0;
            for (unsigned int c = 0; c < chunks; c++) {
                if (drand() > args.repeat_chance) {
                    chunk = c;
                }

                sox_write(out,
                        buf + (hunk * hunk_len) + (chunk * chunk_len),
                        chunk_len);
            }
        }
    }

    sox_close(out);
    sox_close(in);
    sox_quit();

    return 0;
}
