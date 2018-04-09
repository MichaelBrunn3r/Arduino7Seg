#include "Arduino.h"
#include "SevenSegDisplay.h"

SevenSegDisplay::SevenSegDisplay(byte digitPins[], byte segPins[]) : SevenSegDisplay(1, digitPins, segPins) {}

SevenSegDisplay::SevenSegDisplay(const unsigned int numDigits, byte digitPins[], byte segPins[]) 
    : SevenSegDisplay(numDigits, digitPins, segPins, 500, FLAG_7SEG_COMMON_GROUND) {}

SevenSegDisplay::SevenSegDisplay(const unsigned int numDigits, byte digitPins[], byte segPins[], const unsigned long tLEDOn) 
    : SevenSegDisplay(numDigits, digitPins, segPins, tLEDOn, FLAG_7SEG_COMMON_GROUND) {}

SevenSegDisplay::SevenSegDisplay(const unsigned int numDigits, byte digitPins[], byte segPins[], const unsigned long tLEDOn, const unsigned int flags) 
    : mNumDigits(numDigits), mTLEDOn(tLEDOn), mTLastUpdateMicros(micros()), mIndexLastUpdatedDigit(numDigits) 
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
        display();
    }
}

void SevenSegDisplay::display() {
    unsigned int indexCurrentDigit = (mIndexLastUpdatedDigit + 1) % mNumDigits;

    digitalWrite(mDigitPins[mIndexLastUpdatedDigit], mDigitOff);
    digitalWrite(mDigitPins[indexCurrentDigit], mDigitOn);

    digitalWrite(getSegPin(b), (mDigitCodes[indexCurrentDigit] & b) == b);
    digitalWrite(getSegPin(c), (mDigitCodes[indexCurrentDigit] & c) == c);
    digitalWrite(getSegPin(d), (mDigitCodes[indexCurrentDigit] & d) == d);
    digitalWrite(getSegPin(e), (mDigitCodes[indexCurrentDigit] & e) == e);
    digitalWrite(getSegPin(f), (mDigitCodes[indexCurrentDigit] & f) == f);
    digitalWrite(getSegPin(g), (mDigitCodes[indexCurrentDigit] & g) == g);
    digitalWrite(getSegPin(h), (mDigitCodes[indexCurrentDigit] & h) == h);
    digitalWrite(getSegPin(a), (mDigitCodes[indexCurrentDigit] & a) == a);

    mIndexLastUpdatedDigit = indexCurrentDigit;
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