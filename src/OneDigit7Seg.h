#ifndef OneDigit7Seg_HEADER
#define OneDigit7Seg_HEADER

#include "Arduino.h"
#include "SevenSeg.h"
#include "ConstASCIIMap.h"

class OneDigit7Seg {
    public:
        OneDigit7Seg(uint8_t segmentPins[], uint8_t flags=SEVSEG_FLAG_EVERY_DIGIT_HAS_DECIMAL);
        OneDigit7Seg(uint8_t segmentPins[], size_t numChars, char chars[], uint8_t segConfigs[], uint8_t flags=SEVSEG_FLAG_EVERY_DIGIT_HAS_DECIMAL);
        ~OneDigit7Seg();

        void displSegs(const uint8_t segConfiguration);
        void displChar(const char c);
        uint8_t* getSegPins();
        uint8_t getFlags();
    private:
        struct Container {
            bool segOn:1;
            uint8_t flags;
        } mContainer;
        uint8_t* mSegPins;
        ConstASCIIMap<uint8_t>* mSegTruthTable;

        void init(uint8_t segmentPins[], size_t numChars, char chars[], uint8_t segConfigs[], uint8_t flags=SEVSEG_FLAG_EVERY_DIGIT_HAS_DECIMAL);
        void refresh(const uint8_t segConfig);
};

#endif // OneDigit7Seg_HEADER