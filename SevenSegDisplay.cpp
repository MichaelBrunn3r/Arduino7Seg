#include "Arduino.h"
#include "SevenSegDisplay.h"

SevenSegDisplay::SevenSegDisplay(const size_t numDigits, byte digitPins[], byte segPins[], const unsigned long tLEDOn, const unsigned int flags) 
    : mNumDigits(numDigits), mTLEDOn(tLEDOn), mIndexLastUpdatedDigit(numDigits) 
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
    mUpdateRequired = true;
}

void SevenSegDisplay::setChar(const int digit, const char ch) {
    char c = tolower(ch);
    setSegs(digit, *mCharCodes.get(c));
}

void SevenSegDisplay::setStr(const size_t length, const char str[]) {
    for(int i=0; i<mNumDigits; i++) {
        if(i < length) setChar(i, str[i]);
        else setSegs(i, 0);
    }
}

void SevenSegDisplay::tick() {
    unsigned long tCurrent = micros();
    if(mUpdateRequired && (unsigned long)(tCurrent - mTLastUpdateMicros) >= mTLEDOn) {
        mTLastUpdateMicros = tCurrent;
        update();

        // Displays with multiple Digits need constant updates, because only one digit can be displayed at a time.
        // Displays with one Digit only need updates when the Digit Codes change.
        if(mNumDigits == 1) mUpdateRequired = false;
    }
}

void SevenSegDisplay::update() {
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