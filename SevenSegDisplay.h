#ifndef SevenSegDisplay_HEADER
#define SevenSegDisplay_HEADER

#include "Arduino.h"
#include <Dictionary.h>
#include "Segments.h"

#define DEFAULT_7SEG_CHARS "0123456789abcdefghijklmnopqrstuvwxyz.,-_'\""
#define DEFAULT_7SEG_CHARS_COUNT strlen(DEFAULT_7SEG_CHARS)
#define DEFAULT_7SEG_CHAR_CODES {a+b+c+d+e+f,b+c,a+b+e+d+g,a+b+c+d+g,b+c+f+g,a+c+d+f+g,a+c+d+e+f+g+h,a+b+c, \
                                 a+b+c+d+e+f+g,a+b+c+d+f+g,a+b+c+e+f+g,c+d+e+f+g,a+d+e+f,b+c+d+e+g,a+d+e+f+g, \
                                 a+e+f+g,a+c+d+e+f,c+e+f+g,e+f,b+c+d+e,a+c+e+f+g,d+e+f,a+c+e+g,c+e+g,c+d+e+g, \
                                 a+b+e+f+g,a+b+c+f+g,e+g,a+c+d+f+g,d+e+f+g,b+c+d+e+f,c+d+e,b+d+f,b+c+e+f+g, \
                                 b+c+d+f+g,a+b+e+d+g,h,c,g,d,b,b+f}                            
#define FLAG_7SEG_COMMON_ANODE 1 // LEDs are HIGH Active
#define FLAG_7SEG_COMMON_CATHODE 2 // LEDs are Low Active
#define FLAG_7SEG_COMMON_GROUND FLAG_7SEG_COMMON_CATHODE

class SevenSegDisplay {
    private:
        bool mDigitOn, mDigitOff, mSegOn, mSegOff;
        unsigned int mNumDigits; // Number of Digits
        byte* mDigitPins; // Array containing the Arduino pins for the Digits
        byte* mSegPins; // Array containing the Arduino pins for the Segments 
        byte* mDigitCodes;
        byte mSegStates; // The current states (on/off) of all Segments, saved in one byte
        unsigned int mIndexLastUpdatedDigit;
        unsigned long mTLEDOn; // Time each LED is on
        unsigned long mTLastUpdateMicros; // Last Update Time in micro seconds
        Dictionary<char,byte> mCharCodes;
    public:
        SevenSegDisplay(byte digitPins[], byte segPins[]);
        SevenSegDisplay(const unsigned int numDigits, byte digitPins[], byte segPins[]);
        SevenSegDisplay(const unsigned int numDigits, byte digitPins[], byte segPins[], const unsigned long tLEDOn);
        SevenSegDisplay(const unsigned int numDigits, byte digitPins[], byte segPins[], const unsigned long tLEDOn, const unsigned int flags);
        void setSegs(const int digit, const byte segments);
        void setChar(const int digit, const char ch);
        void setStr(const size_t length, const char str[]);
        void tick();
        byte getSegPin(const Segment seg);
};

#endif