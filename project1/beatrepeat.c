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
            "    -c    max chunk slices (integer > 0)\n"
            "    -p    max period slices (integer > 0)\n"
            "    -s    shuffle chance (decimal >= 0)\n"
            "    -r    repeat chance (decimal >= 0)\n"
            "    -S    random seed (integer)\n");
}

typedef struct _arguments {
    double tempo;
    double beats;
    unsigned int chunk_slices;
    unsigned int period_slices;
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

int main(int argc, char *argv[]) {
    static sox_format_t *in, *out;
    sox_sample_t *buf;
    double buf_period;
    size_t buf_size;
    size_t read;
    arguments args;

    args.tempo = 120;
    args.beats = 4;
    args.chunk_slices = 8;
    args.period_slices = 8;
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
    while ((c = getopt(argc, argv, "vt:T:b:c:p:o:s:r:S:")) != -1) {
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
        case 'c': /* chunk slices */
            args.chunk_slices = strtoumax(optarg, NULL, 10);
            break;
        case 'p': /* period slices */
            args.period_slices = strtoumax(optarg, NULL, 10);
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

    if ((in = sox_open_read(argv[optind++], NULL, NULL, NULL)) == NULL) {
        fprintf(stderr, "error: could not read input file\n");
        exit(EXIT_FAILURE);
    }

    if ((out = sox_open_write(argv[optind++], &in->signal,
                    NULL, args.output_type, NULL, NULL)) == NULL) {
        fprintf(stderr, "error: could not open output\n");
        exit(EXIT_FAILURE);
    }

    buf_period = secs_per_beat(args.tempo) * args.beats;
    buf_size = bufsize(in, buf_period);

    unsigned int period_slices;
    double buf_period_slice;
    size_t buf_size_slice;

    buf = (sox_sample_t *) malloc(sizeof(sox_sample_t) * buf_size);

    while ((read = sox_read(in, buf, buf_size)) != 0) {
        period_slices = (2 * ((rand() % args.period_slices) + 1));
        buf_period_slice = buf_period / period_slices;
        buf_size_slice = bufsize(in, buf_period_slice);

        double r;
        for (unsigned int p = 0; p < period_slices; p++) {
            r = rand() / (double) RAND_MAX;

            unsigned int period_slice;
            if (r < args.shuffle_chance) {
                period_slice = rand() % period_slices;
            } else {
                period_slice = p;
            }

            unsigned int chunk_slices = (rand() % 2 == 0 ? 2 : 3) *
                ((rand() % (args.chunk_slices - 1)) + 1);

            size_t chunklen = ((buf_size_slice / in->signal.channels) /
                chunk_slices) * in->signal.channels;

            unsigned int chunk = 0;
            for (unsigned int c = 0; c < chunk_slices; c++) {
                if (c > args.offset) {
                    r = rand() / (double) RAND_MAX;
                }

                if (r > args.repeat_chance) {
                    chunk = c;
                }

                sox_write(out,
                        buf + (period_slice * buf_size_slice) +
                            (chunk * chunklen), 
                        chunklen);
            }
        }
    }

    sox_close(out);
    sox_close(in);
    sox_quit();

    return 0;
}
