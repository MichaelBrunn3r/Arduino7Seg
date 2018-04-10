#ifndef SevenSegUtils_HEADER
#define SevenSegUtils_HEADER

#include "Arduino.h"
#include "SevenSeg.h"
#include "OneDigit7Seg.h"

#define SEVSEGUTILS_PRINT_7SEG_LAYOUT \
    Serial.println("Seven Segment Display Layout:"); \
    Serial.println(" aaa "); \
    Serial.println("f   b"); \
    Serial.println("f    b"); \
    Serial.println(" ggg "); \
    Serial.println("e   c"); \
    Serial.println("e   c"); \
    Serial.println(" ddd  hh");

namespace SevenSegUtils {
    void findPinMapping(OneDigit7Seg* displ) {
        SEVSEGUTILS_PRINT_7SEG_LAYOUT

        size_t numSegments = FLAG_IS_SET(displ->getFlags(),SEVSEG_FLAG_EVERY_DIGIT_HAS_DECIMAL) ? 8 : 7;
        uint8_t currentSeg = 1;
        uint8_t mapping[numSegments] = {}; 

        // Get the Pin Mapping
        int i=0;
        while(i<numSegments) {
            Serial.print("Which Segment is turned on?");
            displ->displSegs(currentSeg);

            // Wait until user responds
            while(!Serial.available()){}

            char c = Serial.read();
            switch(c) {
                case 'a': mapping[0] = displ->getSegPins()[i];
                                 break;
                case 'b': mapping[1] = displ->getSegPins()[i];
                                 break;
                case 'c': mapping[2] = displ->getSegPins()[i];
                                 break;
                case 'd': mapping[3] = displ->getSegPins()[i];
                                 break;
                case 'e': mapping[4] = displ->getSegPins()[i];
                                 break;
                case 'f': mapping[5] = displ->getSegPins()[i];
                                 break;
                case 'g': mapping[6] = displ->getSegPins()[i];
                                 break;
                case 'h': mapping[7] = displ->getSegPins()[i];
                                 break;
                default: Serial.println("Invalid Input.");
                         continue;
            }

            Serial.print(" -> ");
            Serial.println(c);
            currentSeg = currentSeg<<1;
            i++;
        }

        Serial.print("Mapping: ");
        for(int i=0; i<numSegments; i++) {
            Serial.print(mapping[i]);
            if(i<numSegments-1) Serial.print(',');
        }
    }
}

#endif // SevenSegUtils_HEADER