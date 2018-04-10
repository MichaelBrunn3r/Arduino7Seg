#ifndef SevenSeg_HEADER
#define SevenSeg_HEADER

#include "Arduino.h"

#define SEVSEG_CHARS_NUM "0123456789"
#define SEVSEG_CHARS_HEX "0123456789abcdef"
#define SEVSEG_CHARS "abcdefghijklmnopqrstuvwxyz"
#define SEVSEG_CHARS_SPECIAL ".,-_'\"öü"
#define SEVSEG_CHARS_ALL "0123456789abcdefghijklmnopqrstuvwxyz.,-_\'\"öü"
#define SEVSEG_CHARS_NUM_LEN 10
#define SEVSEG_CHARS_HEX_LEN 16
#define SEVSEG_CHARS_LEN 26
#define SEVSEG_CHARS_SPECIAL_LEN 8 
#define SEVSEG_CHARS_ALL_LEN 44

#define SEVSEG_SEG_CONF_NUM a+b+c+d+e+f,b+c,a+b+e+d+g,a+b+c+d+g,b+c+f+g,a+c+d+f+g,a+c+d+e+f+g+h,a+b+c,a+b+c+d+e+f+g,a+b+c+d+f+g
#define SEVSEG_SEG_CONF_HEX a+b+c+d+e+f,b+c,a+b+e+d+g,a+b+c+d+g,b+c+f+g,a+c+d+f+g,a+c+d+e+f+g+h,a+b+c,a+b+c+d+e+f+g,a+b+c+d+f+g,a+b+c+e+f+g, \
                            c+d+e+f+g,a+d+e+f,b+c+d+e+g,a+d+e+f+g,a+e+f+g
#define SEVSEG_SEG_CONF_CHARS a+b+c+e+f+g,c+d+e+f+g,a+d+e+f,b+c+d+e+g,a+d+e+f+g, a+e+f+g,a+c+d+e+f,c+e+f+g,e+f,b+c+d+e,a+c+e+f+g, \
                              d+e+f,a+c+e+g,c+e+g,c+d+e+g,a+b+e+f+g,a+b+c+f+g,e+g,a+c+d+f+g,d+e+f+g,b+c+d+e+f,c+d+e,b+d+f,b+c+e+f+g, \
                              b+c+d+f+g,a+b+e+d+g
#define SEVSEG_SEG_CONF_SPECIAL h,c,g,d,b,b+f,a+c+d+e+g,a+c+d+e
#define SEVSEG_SEG_CONF_ALL a+b+c+d+e+f,b+c,a+b+e+d+g,a+b+c+d+g,b+c+f+g,a+c+d+f+g,a+c+d+e+f+g+h,a+b+c,a+b+c+d+e+f+g,a+b+c+d+f+g, \
                            a+b+c+e+f+g,c+d+e+f+g,a+d+e+f,b+c+d+e+g,a+d+e+f+g, a+e+f+g,a+c+d+e+f,c+e+f+g,e+f,b+c+d+e,a+c+e+f+g, \
                            d+e+f,a+c+e+g,c+e+g,c+d+e+g,a+b+e+f+g,a+b+c+f+g,e+g,a+c+d+f+g,d+e+f+g,b+c+d+e+f,c+d+e,b+d+f,b+c+e+f+g, \
                            b+c+d+f+g,a+b+e+d+g
                                
#define SEVSEG_FLAG_COMMON_ANODE 1 // If this Flag is set, the Displays LEDs are HIGH Active
#define SEVSEG_FLAG_COMMON_CATHODE 2 // If this Flag is set, the Displays LEDs are Low Active
#define SEVSEG_FLAG_COMMON_GROUND 2 // If this Flag is set, the Displays LEDs are Low Active
#define SEVSEG_FLAG_EVERY_DIGIT_HAS_DECIMAL 3

#define FLAG_IS_SET(FLAGS, FLAG) ((FLAGS & FLAG) == FLAG)

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
 * Binary represantation for each Segment, so one state of a Seven Segment Display can be represented in one byte.
 **/
enum Segment {
    a=1, b=2, c=4, d=8, e=16, f=32, g=64, h=128
};

#endif