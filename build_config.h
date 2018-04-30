#ifndef _BUILD_CONFIG_h_
#define _BUILD_CONFIG_h_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define DEVICE_ID 0X0100U // Local Device ID
#define DEVICE_TYPE 0x02  // Device type (for serial) 02=matrix

//#define _BUILD_RF24_		// ~5.5kb / 100 bytes
#define _BUILD_SERIAL_		// ~130 bytes/30 bytes SRAM
#define _BUILD_BMP_			// ~3.5kb/75 bytes SRAM
#define _BUILD_DHT_
// #define _BUILD_BUTTONS_   // ~1.5kb/6 

//#define _BUILD_FAKE_SENSOR_
//#define _BUILD_TEST_

#endif

