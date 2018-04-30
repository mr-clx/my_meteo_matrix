#ifndef __MYEEPROM_H_
#define __MYEEPROM_H_

#include <Arduino.h>
#include <eeprom.h>
#include <inttypes.h>

#define EEPROM_SIZE 0x400

extern uint8_t eeprom_read_byte(uint16_t& addr) {
	return EEPROM[addr++];
}

extern uint16_t eeprom_read_word(uint16_t& addr) {
	
	uint16_t v= eeprom_read_word((const uint16_t*) addr);
	// eeprom_read_block(&v, addr, 2); //  EEPROM[addr]+((int)EEPROM[addr+1]<<8);
	addr+=2;
	return v;
}


extern void eeprom_write_byte(uint16_t& addr, uint8_t value) {
	eeprom_write_byte((uint8_t*) addr, value);
	addr++;
}

extern void eeprom_update_byte(uint16_t& addr, uint8_t value) {
	eeprom_update_byte((uint8_t*) addr, value);
	addr++;
}

extern void eeprom_update_word(uint16_t& addr, uint16_t value) {
	eeprom_update_word((uint16_t*) addr, value);
	addr+=2;
}

extern void eeprom_dumpSerial(uint16_t addr, uint16_t size) {
	Serial.print(F("EEPROM_DUMP 0x")); Serial.print(addr, HEX);
	Serial.print(F("..0x")); Serial.println(addr+size-1, HEX);

	uint8_t i=0;
	while (size>0) {
		if ((i&0xf)==0) { serial_printHex(addr); Serial.print(F("\t")); }
		serial_printHex((byte)EEPROM[addr]);
		Serial.print(' ');

		addr++;
		size--;
		i++;
		if ((i&0xf)==0) {
			Serial.println();
		}
	}
	Serial.println(F("\r\n---"));
}

extern void eeprom_setmem(uint16_t addr, uint8_t value, uint16_t size) {
	// DEBUG_PRINTLN(F("Filling EEPROM.."));
	uint16_t addrEnd = min(addr+size, EEPROM_SIZE)-1;
	while (addr<=addrEnd) {
		eeprom_update_byte(addr, value);
	}
	//DEBUG_PRINTLN(F("OK"));
}

#endif