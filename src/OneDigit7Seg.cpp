#include "Arduino.h"
#include "OneDigit7Seg.h"
#include "SevenSeg.h"
#include "ConstASCIIMap.h"

////////////////////////
// Con-/Deconstructor //
////////////////////////

OneDigit7Seg::OneDigit7Seg(uint8_t segmentPins[], uint8_t flags) {
    uint8_t numChars = SEVSEG_CHARS_ALL_LEN;
    char chars[] = SEVSEG_CHARS_ALL;
    uint8_t segConfigs[] = {SEVSEG_SEG_CONF_ALL};
    
    init(segmentPins, numChars, chars, segConfigs, flags);
}

OneDigit7Seg::OneDigit7Seg(uint8_t segmentPins[], size_t numChars, char chars[], uint8_t segConfigs[], uint8_t flags) {
    init(segmentPins, numChars, chars, segConfigs, flags);
}

OneDigit7Seg::~OneDigit7Seg() {
    delete mSegPins;
}

////////////////////
// Public Methods //
////////////////////

void OneDigit7Seg::displSegs(const uint8_t segConfig) {
    refresh(segConfig);
}

void OneDigit7Seg::displChar(const char c) {
    char ch = c;
    if (ch >= 'A' && ch <= 'Z') ch|32;

    displSegs(*mSegTruthTable->get(ch));
}

uint8_t* OneDigit7Seg::getSegPins() {
    return mSegPins;
}

uint8_t OneDigit7Seg::getFlags() {
    return mContainer.flags;
}

/////////////////////
// Private Methods //
/////////////////////

void OneDigit7Seg::init(uint8_t segmentPins[], size_t numChars, char chars[], uint8_t segConfigs[], uint8_t flags=SEVSEG_FLAG_EVERY_DIGIT_HAS_DECIMAL) {
    // Config Flags
    mContainer.flags = flags;
    if(FLAG_IS_SET(mContainer.flags,SEVSEG_FLAG_COMMON_GROUND)) mContainer.segOn = HIGH; 

    // Config Pins
    size_t numSegments = FLAG_IS_SET(mContainer.flags, SEVSEG_FLAG_EVERY_DIGIT_HAS_DECIMAL) ? 8 : 7;
    mSegPins = segmentPins;
    for(int i=0; i<numSegments; i++) pinMode(mSegPins[i], OUTPUT);

    // Config Truth Table
    mSegTruthTable = new ConstASCIIMap<uint8_t>(numChars, chars, segConfigs);
}

void OneDigit7Seg::refresh(const uint8_t segConfiguration) {
    digitalWrite(mSegPins[0], FLAG_IS_SET(segConfiguration, a) ? mContainer.segOn : !mContainer.segOn);
    digitalWrite(mSegPins[1], FLAG_IS_SET(segConfiguration, b) ? mContainer.segOn : !mContainer.segOn);
    digitalWrite(mSegPins[2], FLAG_IS_SET(segConfiguration, c) ? mContainer.segOn : !mContainer.segOn);
    digitalWrite(mSegPins[3], FLAG_IS_SET(segConfiguration, d) ? mContainer.segOn : !mContainer.segOn);
    digitalWrite(mSegPins[4], FLAG_IS_SET(segConfiguration, e) ? mContainer.segOn : !mContainer.segOn);
    digitalWrite(mSegPins[5], FLAG_IS_SET(segConfiguration, f) ? mContainer.segOn : !mContainer.segOn);
    digitalWrite(mSegPins[6], FLAG_IS_SET(segConfiguration, g) ? mContainer.segOn : !mContainer.segOn);
    digitalWrite(mSegPins[7], FLAG_IS_SET(segConfiguration, h) ? mContainer.segOn : !mContainer.segOn);
}