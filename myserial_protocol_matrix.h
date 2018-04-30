#ifndef __MYSERIAL_PROTOCOL_H__
#define __MYSERIAL_PROTOCOL_H__

// PROTOCOL VERSION
#define SERIAL_PROTOVER 0x0200   


#define SERIAL_CMD_RTC 2  // => realtime clock timestamp
// Main device report timestamp (every minute, master can broadcast it to slaves)
// value[0] year
// value[1] month
// value[2] day
// value[3] hour
// value[4] seconds
// value[5] unix timestamp (uint32_t)
// ** not implemented yet

#define SERIAL_CMD_Q_RADIO_PING   20  
// Ping remote sensor
//   value[0] uint16_t device_id (pipe must determine by master), =0 for all devices (sensors)

#define SERIAL_CMD_Q_RADIO_RAW    21
// Send radio packet
// value[0] destination device id (0 = broadcast)
// value[1] command
// value[2...n] radio_packet_t values
// ** not implemented yet

// #define SERIAL_CMD_Q_SENS_LIST  22 // -  => sens_id,sens_name,sens_caps  (несколько команд по числу датчиков)

#define SERIAL_CMD_Q_SENS_VALUES  23 
//  Query device sensor values
//   value[0] uint16_t = sensor.owner (0 = all)
//   value[1] byte local_id (0 = all)

#define SERIAL_CMD_Q_DISP_MSG  30 
//  Query device sensor values
//   value[0] uint16_t device_id (0 = all)
//   value[1] byte disp_id (0 = all)
//   value[2] byte flag (b7=1 for beep)
//   value[3] byte duration_sec
//   value[4] byte message length (up to 255)  // new in 20150816
//   value[5] text

// Device -> Serial
//#define SERIAL_CMD_R_PING_RESP  120 // -  => sens_id,sens_name,sens_caps  (несколько команд по числу датчиков)
//#define SERIAL_CMD_R_SENS_LIST  122 // -  => sens_id,sens_name,sens_caps  (несколько команд по числу датчиков)

#define SERIAL_CMD_R_SENS_VALUES  123 
// Device Sensor values 
//   value[0] uint16_t = sensor.owner
//   value[1] uint8_t sensor.local_id
//   value[2] uint8_t v.kind
//   value[3] uint8_t v.id
//   value[4] float v.value

#define SERIAL_CMD_R_IR 40
// IRemote command
//   value[0]=type
//   value[1]=value


#define SERIAL_CMD_SYS_FREE_RAM 111
// manual command request free SRAM
// response only one number: free ram

#define SERIAL_CMD_SYS_EEPROM_DUMP 112
// dump of EEPROM in hex view
//   value[0]=uint16_t address
//   value[1]=uint16_t size

#define SERIAL_CMD_SYS_EEPROM_SET 113
// set of EEPROM values in hex (*not implemented)
//   value[0]=uint16_t device_id
//   value[1]=uint16_t offset
//   value[2]=uint16_t size
//   value[3...3+size-1]=bytes(hex, separated SEPARATOR)

#define SERIAL_CMD_SYS_RTC 114
// set RTC for device
//   value[0]=uint16_t year
//   value[1]=uint8_t month
//   value[2]=uint8_t day
//   value[3]=uint8_t day of week (monday=1....sunday=7)
//   value[4]=uint8_t hour
//   value[5]=uint8_t minutes
//   value[6]=uint8_t seconds


#define SERIAL_CMD_Q_SET_STRBANK 32
//  Reset all string bank
//  Query:
// 	value[0] uint16_t device_id (must be set!)
//   	value[1] bank_n (0 = all)
//  	< value[2+0] uint16_t strId  value[2+1] string ... SERIAL_FLD_SEPARATOR >
//  Response:
//	

#define SERIAL_CMD_Q_GET_STRBANK 33
//  Reset all string bank
//  Query:
//   	value[0] uint16_t device_id (0 = all)
//  	value[1] bank_n (0 = all)
//  	value[2] strId  (0 = all)
//  Response:
//	idx;strId;String
//      ....


#endif
