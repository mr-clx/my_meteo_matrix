#ifndef __HELPER_CONVERT_H__
#define __HELPER_CONVERT_H__

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <inttypes.h>


extern void charToStr(char c, char* buf, int& idx) {
	buf[idx]=c;
	idx++;
}

extern void termStr(char* buf, int& idx) {
	buf[idx]=0;
}

// fixedWidth can be zero -> auto calculate (but buf must have enough of size!)
// todo: optimize speed An alternative approach to avoiding DIV is to multiply by (2^N/10) and then shift right by N bits. So for N=16, x/10 ~= (x*6554)>>16. Close enough for most digits, anyway
extern void intToStrDec(int16_t value, uint8_t fixedWidth, char* buf, int& idx) {
	if (value<0) {
		buf[idx]='-'; idx++;
		value = abs(value);
	}
	uint8_t w=fixedWidth;
	
	// auto determine width
	if (!w) {
		w++;  // w=1
		int v = value;
		while (v>9) { w++; v/=10; } 
	}
	
	// convert
	for (int i=idx+w-1; i>=idx;i--) {
		uint8_t d = value % 10;
		buf[i]= '0'+d;
		value/=10;
	}
	idx+=w;
}



extern void uintToStrHex(uint16_t value, uint8_t width, char* buf, int& idx) {
	for (int i=idx+width-1; i>=idx; i--) {
		uint8_t d = value & 0xf;
		buf[i]= (d<=9)? char((byte)'0'+d) : char((byte)'A'+(d-10));
		value >>=4;
	}
	idx+=width;
}



// be sure there is enough of buf space!
extern void floatToStr(float value, uint8_t fixedWidth, uint8_t decDigs, char* buf, int& idx) {
	if (!decDigs) {
		intToStrDec(round(value), fixedWidth, buf, idx);
		return;
	}

	if (value<0) {
		buf[idx]='-'; idx++;
		value = abs(value);
	}
	
	// make its integer
	for(uint8_t i=0;i<decDigs;i++) value*=10;
	long v = round(value); // just long!

	// auto determine width
	uint8_t w=fixedWidth;
	if (!w) {
		w++;  // w=1
		long v1 = v;
		while (v1>9) { w++; v1/=10; }
		w++; // for .
	}
	
	// convert
	for (int i=idx+w-1; i>=idx;i--) {
		if (!decDigs) {
			buf[i]='.';
			decDigs=0xff;
		}
		else {
			uint8_t d = v % 10;
			buf[i]= '0'+d;
			if (decDigs!=0xff) decDigs--;
			v/=10; // todo: optimize
		}
	}
	idx+=w;
}


#endif