# beatrepeat

A rhythmic beat mangler/stutterer. Kind of like Ableton Live's Beat Repeat, but not really.

## Dependencies

* scons
* sox

## Building

Run `scons`

## Usage

    beatrepeat [options] infile outfile

    Options:

        -v    verbose. specify more to be more verbose
        -t    output file type/driver (see equivalent sox option)
        -T    tempo (decimal > 0)
        -b    beats (integer > 0)
        -o    offset (integer >= 0)
        -h    max hunk slices (integer > 0)
        -c    max chunk slices (integer > 0)
        -s    shuffle chance (decimal >= 0)
        -r    repeat chance (decimal >= 0)
        -S    random seed (integer)

Example:

    ./beatrepeat -T 128 -b 4 -h 8 -c 8 -o 2 -s 0.7 -r 0.5 -S 1234 -vv in.aif out.aif

To play the output instead of saving to file, set an output driver (exactly like SoX does it):

    # OS X
    ./beatrepeat -t coreaudio ... in.aif default
    
    # Linux (ALSA)
    ./beatrepeat -t alsa ... in.aif default
