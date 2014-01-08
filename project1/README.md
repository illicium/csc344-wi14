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
        -c    max chunk slices (integer > 0)
        -p    max period slices (integer > 0)
        -r    repeat chance (decimal >= 0)
        -S    random seed (integer)

Example:

    ./beatrepeat -T 170 -b 8 -c 8 -p 4 -r 0.3 -S 123456 -vv in.aif out.aif

To play the output instead of saving to file, set an output driver (exactly like SoX does it):

    # OS X
    ./beatrepeat -t coreaudio -T 170 -b 8 -c 8 -p 4 -r 0.3 -S 123456 -vv in.aif default
    
    # Linux (ALSA)
    ./beatrepeat -t alsa -T 170 -b 8 -c 8 -p 4 -r 0.3 -S 123456 -vv in.aif default
