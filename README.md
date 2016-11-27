Halftone 2 Source
=================

For creating c++ source code data images for 128x128 Sharp Memory LCDs.

It uses [lodepng](http://lodev.org/lodepng/) from Lode Vandevenne.

The output is 128 rows of 16 bytes where each bit represents a pixel being on or off.

Usage
-----

First convert an existing 128x128 RGB png file and outputs a 128x128 half-tone image

    brew install imagemagick
    convert chad.png -brightness-contrast 30 -colorspace Gray -ordered-dither h4x4a chad_h4x4a.png

Then use halftone2src to convert the RGB halftone PNG into source code (hex).

    g++ lodepng.cpp halftone2src.cpp -ansi -pedantic -Wall -Wextra -O3 -o halftone2src
    ./halftone2src chad_h4x4a.png

Then take those codes and surround it with:

    unsigned const char chad_data[128*128/8] PROGMEM = {
        ...
    }
