#ifndef OneDigit7Seg_HEADER
#define OneDigit7Seg_HEADER

#include "Arduino.h"
#include "SevenSeg.h"

#define FLAG_7SEG_NO_

class OneDigit7Seg {
    public:
        OneDigit7Seg(uint8_t segmentPins[], uint32_t flags);
        ~OneDigit7Seg();

        void setSegs(uint8_t segments);
        void setChar(char c);
    private:
        struct Container {
            bool digitOn:1; segOn:1;
            uint8_t flags;
        } mContainer;
        uint8_t* mSegPins;
        ConstASCIIMap<uint8_t> mSegTruthTable;

        void refresh();
}

#endif // OneDigit7Seg_HEADER