#include "Arduino.h"
#include "SevenSegDisplay.h"

SevenSegDisplay::SevenSegDisplay(byte digitPins[], byte segPins[]) : SevenSegDisplay(1, digitPins, segPins) {}

SevenSegDisplay::SevenSegDisplay(const unsigned int numDigits, byte digitPins[], byte segPins[]) 
    : SevenSegDisplay(numDigits, digitPins, segPins, 500, FLAG_7SEG_COMMON_GROUND) {}

SevenSegDisplay::SevenSegDisplay(const unsigned int numDigits, byte digitPins[], byte segPins[], const unsigned long tLEDOn) 
    : SevenSegDisplay(numDigits, digitPins, segPins, tLEDOn, FLAG_7SEG_COMMON_GROUND) {}

SevenSegDisplay::SevenSegDisplay(const unsigned int numDigits, byte digitPins[], byte segPins[], const unsigned long tLEDOn, const unsigned int flags) 
    : mNumDigits(numDigits), mSegStates(0), mTLEDOn(tLEDOn), mTLastUpdateMicros(micros()), mIndexLastUpdatedDigit(0) 
{
    // Configure & Initialize Pins
    mDigitPins = digitPins;
    mSegPins = segPins;
    for(int i=0; i<mNumDigits; i++) {
        pinMode(mDigitPins[i], OUTPUT);
    }
    for(int i=0; i<8; i++) {
        pinMode(mSegPins[i], OUTPUT);
    }

    // Initialize digit Codes
    mDigitCodes = new byte[mNumDigits];
    for(int i=0; i<mNumDigits; i++) mDigitCodes[i] = 0;

    // Populate Char Codes
    mCharCodes = Dictionary<char,byte>(DEFAULT_7SEG_CHARS_COUNT);
    char chars[] = DEFAULT_7SEG_CHARS;
    byte codes[] = DEFAULT_7SEG_CHAR_CODES;
    mCharCodes.putAll(DEFAULT_7SEG_CHARS_COUNT, chars, codes);

    // Configure Common Cathode/Anode
    if((flags & FLAG_7SEG_COMMON_GROUND) == FLAG_7SEG_COMMON_GROUND) mDigitOn = mSegOff = !(mDigitOff = mSegOn = HIGH);
    else mDigitOn = mSegOff = !(mDigitOff = mSegOn = LOW);
}

void SevenSegDisplay::setSegs(const int digit, const byte segments) {
    mDigitCodes[digit] = segments;
}

void SevenSegDisplay::setChar(const int digit, const char ch) {
    char c = tolower(ch);
    setSegs(digit, *mCharCodes.get(c));
}

void SevenSegDisplay::setStr(const size_t length, const char str[]) {
    for(int i=0; i<mNumDigits; i++) {
        if(i+1 > length) return;
        setChar(i, str[i]);
    }
}

void SevenSegDisplay::tick() {
    unsigned long tCurrent = micros();
    if((unsigned long)(tCurrent - mTLastUpdateMicros) >= mTLEDOn) {
        mTLastUpdateMicros = tCurrent;

        mIndexLastUpdatedDigit = (mIndexLastUpdatedDigit + 1) % mNumDigits;

        for(int j=0; j<mNumDigits; j++) {
            if(j != mIndexLastUpdatedDigit) digitalWrite(mDigitPins[j], mDigitOff);
        }

        digitalWrite(getSegPin(a), mSegOff);
        digitalWrite(getSegPin(b), mSegOff);
        digitalWrite(getSegPin(c), mSegOff);
        digitalWrite(getSegPin(d), mSegOff);
        digitalWrite(getSegPin(e), mSegOff);
        digitalWrite(getSegPin(f), mSegOff);
        digitalWrite(getSegPin(g), mSegOff);
        digitalWrite(getSegPin(h), mSegOff);

        digitalWrite(mDigitPins[mIndexLastUpdatedDigit], mDigitOn);

        if((mDigitCodes[mIndexLastUpdatedDigit] & a) == a) digitalWrite(getSegPin(a), mSegOn);
        if((mDigitCodes[mIndexLastUpdatedDigit] & b) == b) digitalWrite(getSegPin(b), mSegOn);
        if((mDigitCodes[mIndexLastUpdatedDigit] & c) == c) digitalWrite(getSegPin(c), mSegOn);
        if((mDigitCodes[mIndexLastUpdatedDigit] & d) == d) digitalWrite(getSegPin(d), mSegOn);
        if((mDigitCodes[mIndexLastUpdatedDigit] & e) == e) digitalWrite(getSegPin(e), mSegOn);
        if((mDigitCodes[mIndexLastUpdatedDigit] & f) == f) digitalWrite(getSegPin(f), mSegOn);
        if((mDigitCodes[mIndexLastUpdatedDigit] & g) == g) digitalWrite(getSegPin(g), mSegOn);
        if((mDigitCodes[mIndexLastUpdatedDigit] & h) == h) digitalWrite(getSegPin(h), mSegOn);

    }
}

byte SevenSegDisplay::getSegPin(const Segment seg) {
    switch(seg) {
		case a: return mSegPins[0];
		case b: return mSegPins[1];
		case c: return mSegPins[2];
		case d: return mSegPins[3];
		case e: return mSegPins[4];
		case f: return mSegPins[5];
		case g: return mSegPins[6];
		case h: return mSegPins[7];
	}
}