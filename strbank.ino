#include <EEPROM.h>
// eeprom messages library

// eeprom offset: 0x40

// byte messages_count
// [ byte str_size+1 [byte str[]] ]
// .....

#define EEPROM_OFFSET_STRBANK 0x40		// start of messages, 960 bytes total
#define EEPROM_OFFSET_STRBANK_MAX 0x3F0 // max offset
#define STRBANK_STR_MAX_SIZE = 80; // 80 chars. =255 for not found marker

uint8_t strbank_count=0;
uint16_t strbank_write_next=0; // address of next free address

#define DEBUG_PRINT(txt) Serial.print(txt);
#define DEBUG_PRINTLN(txt) Serial.println(txt);


void strbank_init(){
	uint16_t addr= EEPROM_OFFSET_STRBANK;
	strbank_count = eeprom_read_byte(addr);
	strbank_write_next=eeprom_read_word(addr);
	if (strbank_write_next<EEPROM_OFFSET_STRBANK || strbank_write_next>EEPROM_OFFSET_STRBANK_MAX) {
		DEBUG_PRINTLN(F("StrBank: data corrupt."));
		strbank_clear();
	} else {
		strbank_printInfo();
	}
}


void strbank_printInfo() {
		DEBUG_PRINT(F("StrBank. Items=")); DEBUG_PRINT(strbank_count); DEBUG_PRINT(F(" FreeSize="));DEBUG_PRINTLN(strbank_freeSize());
}

// return left size
uint16_t strbank_freeSize() {
	return EEPROM_OFFSET_STRBANK_MAX-strbank_write_next;
}

// prepare
void strbank_clear() {
	strbank_count=0;
	strbank_write_next=EEPROM_OFFSET_STRBANK+1+2;
}

// update bank meta data (messages_count, message_addr_next)
void strbank_updateHdr() {
	uint16_t addr = EEPROM_OFFSET_STRBANK;
	eeprom_update_byte(addr, strbank_count);
	eeprom_update_word(addr, strbank_write_next);
}


// uint8_t strbank_add(uint16_t id, char* s, uint8_t size, bool updateHeader) {


// return messages_count
// 0 if error
uint8_t strbank_add(uint16_t id, char* s, uint8_t size, bool updateHeader, bool dupCheck) {
	// todo:check duplicated?
	if (strbank_count==0xff ||	strbank_write_next+size+1+2>= EEPROM_OFFSET_STRBANK_MAX) {
		DEBUG_PRINTLN(F("StrBank: No space left"));
		return 0;
	}

	if (dupCheck && strbank_get(id, NULL, 0, true)!=0xff) {
		DEBUG_PRINT(F("StrBank: dup id=")); DEBUG_PRINT(id);
		return 0;
	}
	
	// uint16_t addr = ;
// DEBUG_PRINT(F("StrBank: write at 0x")); Serial.println(strbank_write_next, HEX); // DEBUG_PRINT(strbank_write_next);
	eeprom_update_byte(strbank_write_next, size+1+2); // block size = str_length + this byte + strId
	eeprom_update_word(strbank_write_next, id);
	eeprom_update_block((const void*) s, (void*) strbank_write_next, size);
	strbank_write_next+=size;
	strbank_count++;
	if (updateHeader) {
		strbank_updateHdr();
	}
	return strbank_count;
}


uint8_t strbank_add(uint16_t id, char* s, bool dupCheck) {
	return strbank_add(id, s, strlen(s), false, dupCheck);
}



// return strLen and write buf[0]
// buf can be NULL
uint8_t strbank_get(uint16_t id, char* buf, uint8_t bufSize, bool idIsIdx) {
	
	if (!(idIsIdx && id>=strbank_count)) {
		uint8_t idx=0;
		uint16_t addr = EEPROM_OFFSET_STRBANK+1+2; // + count + write_addr
		while (idx<strbank_count && addr<EEPROM_OFFSET_STRBANK_MAX-1-2) {
			
			uint8_t blckSize = eeprom_read_byte(addr);
			if (blckSize<1+2) {
				DEBUG_PRINTLN(F("StrBank: corrupted!"));
				break; // corrupted or EOB
			}
		
			uint16_t strId = eeprom_read_word(addr);
//DEBUG_PRINT(F("StrBank: check id=")); DEBUG_PRINT(strId);
//DEBUG_PRINT(F("\taddr=0x")); Serial.println(addr, HEX);
			
			if ((idIsIdx && id==idx) || (!idIsIdx && id==strId)) {
				uint8_t strLen = min(blckSize-1-2, bufSize);
				// DEBUG_PRINT(F("\tbufSize=")); DEBUG_PRINTLN(bufSize);
				if (buf) {
					eeprom_read_block((void*) buf, (const void*) addr, strLen);
					buf[strLen]=0;
				}
				//DEBUG_PRINT(F("strLen=")); DEBUG_PRINTLN(strLen);
				return strLen;
			}
		
			addr+=blckSize-1-2; // blckSize+strId
			idx++;
		}
	}
	if (buf) buf[0]=0;
	// DEBUG_PRINT(F("StrBank: NotFound:")); DEBUG_PRINTLN(id);
	return 0xff;
}


// id=zero for all
extern void strbank_print(int16_t id, bool printId) {
	if (!id) strbank_printInfo();
	if (!strbank_count) return;
	
	uint8_t idx=0;
	uint16_t addr = EEPROM_OFFSET_STRBANK+1+2; // + count + write_addr
	while (idx<strbank_count && addr<EEPROM_OFFSET_STRBANK_MAX-1-2) {
			
		uint8_t blckSize = eeprom_read_byte(addr);
		if (blckSize<1+2) {
			// DEBUG_PRINTLN(F("StrBank: corrupted!"));
			break; // corrupted or EOB
		}
		
		uint16_t strId = eeprom_read_word(addr);
		if (!id || strId==id) {
			if (printId) { Serial.print(strId); Serial.print('='); }
			uint8_t strLen = blckSize-1-2;
			// todo; print strLen ?
			//eeprom_read_block((void*) buf, (const void*) addr, strLen);
			while (strLen) {
				Serial.print((char)eeprom_read_byte(addr));
				strLen--;
			}
			Serial.println();
			if (id) return;
		}
			
		// addr+=blckSize-1-2; // blckSize+strId
		idx++;
	}
}
