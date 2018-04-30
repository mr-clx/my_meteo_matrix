#ifndef __HELPER_PRINT_H__
#define __HELPER_PRINT_H__

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


// extern int test1;

extern void serial_print_P(const char* s)
{
	char c;
	while ((c = pgm_read_byte_near(s++))) Serial.print(c);
}

extern void serial_print_P_arr(const char* const strArr[], uint8_t idx) {
	char* ptr = (char*)pgm_read_word(&(strArr[idx]));
	serial_print_P(ptr);
}

extern void serial_printHex(uint8_t v) {
	Serial.print(v>>4 &0x0f, HEX);
	Serial.print(v & 0x0f, HEX);
}

extern void serial_printHex(uint16_t v) {
	serial_printHex((uint8_t) (v >> 8));
	serial_printHex((uint8_t) (v & 0xff));
}

#endif 