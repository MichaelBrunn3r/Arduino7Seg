#ifndef OneDigit7SegDisplay_HEADER
#define OneDigit7SegDisplay_HEADER

#define PIN_UNDEFINED 255

#include "Arduino.h"
#include "Segments.h"
#include <Dictionary.h>

class OneDigit7SegDisplay {
	public:
		OneDigit7SegDisplay(unsigned char pins[]);
		unsigned char getPin(Segment seg);
		void on(unsigned char segs);
		void off(unsigned char segs);
		void display(int num);
		void display(char ch);
		void clear();
	private:
		unsigned char pins[8];
		Dictionary<char, unsigned char> mAlphabet;
};

#endif