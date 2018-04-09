#ifndef SevenSeg_HEADER
#define SevenSeg_HEADER

/**
 * Segments of a Seven Segment Display
 *  aaa
 * f   b
 * f   b
 *  ggg
 * e   c
 * e   c
 *  ddd   hh
 **/

/**
 * Binary codes for each Segment, so a state can be represented in one byte.
 **/
enum Segment {
    a=1, b=2, c=4, d=8, e=16, f=32, g=64, h=128
};

#endif