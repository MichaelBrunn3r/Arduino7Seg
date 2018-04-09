#include "Arduino.h"
#include "OneDigit7SegDisplay.h"

OneDigit7SegDisplay::OneDigit7SegDisplay(unsigned char pins[]) {
	for(int i=0; i<8; i++) {
		this->pins[i] = pins[i];
	}
	mAlphabet = Dictionary<char, unsigned char>(42);
	mAlphabet.put('0', a+b+c+d+e+f);
	mAlphabet.put('1', b+c);
	mAlphabet.put('2', a+b+e+d+g);
	mAlphabet.put('3', a+b+c+d+g);
	mAlphabet.put('4', b+c+f+g);
	mAlphabet.put('5', a+c+d+f+g);
	mAlphabet.put('6', a+c+d+e+f+g+h);
	mAlphabet.put('7', a+b+c);
	mAlphabet.put('8', a+b+c+d+e+f+g);
	mAlphabet.put('9', a+b+c+d+f+g);
	mAlphabet.put('a', a+b+c+e+f+g);
	mAlphabet.put('b', c+d+e+f+g);
	mAlphabet.put('c', a+d+e+f);
	mAlphabet.put('d', b+c+d+e+g);
	mAlphabet.put('e', a+d+e+f+g);
	mAlphabet.put('f', a+e+f+g);
	mAlphabet.put('g', a+c+d+e+f);
	mAlphabet.put('h', c+e+f+g);
	mAlphabet.put('i', e+f);
	mAlphabet.put('j', b+c+d+e);
	mAlphabet.put('k', a+c+e+f+g);
	mAlphabet.put('l', d+e+f);
	mAlphabet.put('m', a+c+e+g);
	mAlphabet.put('n', c+e+g);
	mAlphabet.put('o', c+d+e+g);
	mAlphabet.put('p', a+b+e+f+g);
	mAlphabet.put('q', a+b+c+f+g);
	mAlphabet.put('r', e+g);
	mAlphabet.put('s', a+c+d+f+g);
	mAlphabet.put('t', d+e+f+g);
	mAlphabet.put('u', b+c+d+e+f);
	mAlphabet.put('v', c+d+e);
	mAlphabet.put('w', b+d+f);
	mAlphabet.put('x', b+c+e+f+g);
	mAlphabet.put('y', b+c+d+f+g);
	mAlphabet.put('z', a+b+e+d+g);
	mAlphabet.put('.', h);
	mAlphabet.put(',', c);
	mAlphabet.put('-', g);
	mAlphabet.put('_', d);
	mAlphabet.put('\'', b);
	mAlphabet.put('"', b+f);
}

unsigned char OneDigit7SegDisplay::getPin(Segment seg) {
	switch(seg) {
		case a: return pins[0];
		case b: return pins[1];
		case c: return pins[2];
		case d: return pins[3];
		case e: return pins[4];
		case f: return pins[5];
		case g: return pins[6];
		case h: return pins[7];
		default: return PIN_UNDEFINED;
	}
}

void OneDigit7SegDisplay::on(unsigned char segments) {
	if((segments & a) == a) digitalWrite(getPin(a), HIGH);
	if((segments & b) == b) digitalWrite(getPin(b), HIGH);
	if((segments & c) == c) digitalWrite(getPin(c), HIGH);
	if((segments & d) == d) digitalWrite(getPin(d), HIGH);
	if((segments & e) == e) digitalWrite(getPin(e), HIGH);
	if((segments & f) == f) digitalWrite(getPin(f), HIGH);
	if((segments & g) == g) digitalWrite(getPin(g), HIGH);
	if((segments & h) == h) digitalWrite(getPin(h), HIGH);
}

void OneDigit7SegDisplay::off(unsigned char segments) {
	if((segments & a) == a) digitalWrite(getPin(a), LOW);
	if((segments & b) == b) digitalWrite(getPin(b), LOW);
	if((segments & c) == c) digitalWrite(getPin(c), LOW);
	if((segments & d) == d) digitalWrite(getPin(d), LOW);
	if((segments & e) == e) digitalWrite(getPin(e), LOW);
	if((segments & f) == f) digitalWrite(getPin(f), LOW);
	if((segments & g) == g) digitalWrite(getPin(g), LOW);
	if((segments & h) == h) digitalWrite(getPin(h), LOW);
}

void OneDigit7SegDisplay::display(int num) {
	if((num >= 0) && (num <= 9)) {
		char ch = '0' + num;
		on(*mAlphabet.get(ch));
	}
}

void OneDigit7SegDisplay::display(char ch) {
	ch = tolower(ch);
	on(*mAlphabet.get(ch));
}

void OneDigit7SegDisplay::clear() {
	off(a+b+c+d+e+f+g+h);
}