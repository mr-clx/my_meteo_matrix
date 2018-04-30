#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>  // for fix Wire.h noes not found in libs

#include "build_config.h"

#include "DS3231.h"

#include "helper_system.h"
#include "helper_print.h"
#include "helper_convert.h"
#include "helper_datetime.h"
#include "helper_eeprom.h"

#include "MySensor/MySensor.h"
#define MySensorValue MySensorValueUni
#define MySensor MySensorUni<MySensorValue>

#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include "fonts.h"

#include "MySerial/myserial.h"
#include "MySerial/myserial_protocol_common.h"
#include "myserial_protocol_matrix.h"

//
// Config
//
#define INTERVAL_SENSOR_SCAN_SEC 30               // auto-scan interval
#define INTERVAL_DISP_MODE_CHANGE_SEC 5		      //
#define INTERVAL_DISP_DAY_MESSAGE_SEC 300         // message of the day interval

#define MATRIX_STRING_CAPACITY 100                      // text string buffer size
#define DISP_MSG_MAX_SIZE MATRIX_STRING_CAPACITY

// product name and version
//const char product_name[] PROGMEM = {"MyMeteo-Matrix "};
//const char product_version[] PROGMEM = { "v0.1 b150816-1 " };
//const char product_author[] PROGMEM = {"(aleksey.clx@gmail.com) "};
const char product_name_and_version[] PROGMEM = {"MyMeteo-Matrix v0.2 b150913-1 (aleksey.clx@gmail.com)"};
const char app_help[] PROGMEM = {"To set RTC: #114;year;month;day;dayOfWeek;hours;minutes;seconds;"};

// MAIN SENSOR GROUP OBJECT
MySensor sensor;

extern bool serial_read_eol;

// RTC
DS3231 rtc(SDA, SCL);


// timers
uint32_t last_tick_ping;              // last tick radio ping to master
uint32_t last_tick_radio_sens_values; // last radio send sensor info
uint32_t last_tick_radio_rcvd;        // last radio received command
uint32_t last_tick_sd_flush;          // last tick SDCard flush data
uint32_t last_tick_disp_message;      // last tick of day message

//
// Display mode selector
//
typedef enum disp_mode_e
{ disabled=(0),			// display off
	s_temperature=(1),	// temperature
	s_humidity=(2),		// humidity
	s_pressure=(3),		// pressure
	now_time=(4),		// RTC time
	now_date=(5),		// RTC date
	message=(6),		// display disp_values_master
	nochange=(7)		// no mode changes
};


const uint8_t disp_mode_duration_sec[] PROGMEM = { 0, 5, 5, 5, 10, 5, 10, 0}; // display mode durations

disp_mode_e disp_mode = now_time;            // current display mode
disp_mode_e disp_mode_next = s_temperature;  // next display mode
uint16_t    disp_mode_next_sec = 5;          // when turn to next disp mode (0=disabled)
uint32_t    last_tick_disp_mode_change;      // when last disp mode changed
bool disp_need_update=true;                  // disp mode changes during processing, after update info it will set to false
uint8_t disp_mode_changed=0;

bool disp_cycle_modes = true;               // ???????????? ??????? ?? ????? ?????????????

uint32_t last_tick_500ms;
bool ticked_500ms;

uint8_t disp_mode_sub = 0; // todo: submode

// display info from remote
// #define MATRIX_MESSAGE_MAX_LEN 80		// max message size
// char disp_msg[MATRIX_MESSAGE_MAX_LEN];	// current displaying message
// STRING BUFFER (receive from remote)
static char disp_msg[DISP_MSG_MAX_SIZE]; // static string buffer
static int  disp_msg_len;    // size in chars
static int  disp_msg_width;  // width in matrix pixels (for matrix)
static int  disp_msg_pos;    // current position

bool overrideSensScan;
bool overrideRadioSensValues;
bool overridePing;
uint32_t tick=0;

// rtcTime
Time rtc_time;

bool test1() {
	Serial.print("test1");
	return true;
}


void test() {

/*	matrix_begin();
	matrix_print(0xA0); // '
	matrix_print(0xA1); // t
	matrix_print(0xA2); // h
	matrix_print(0xA3); // p
	matrix_end(none, 1);
	delay(1000);

	matrix_begin();
	matrix_print(0x7F); // BRICK
	matrix_print(0xA4); // zont
	matrix_print(0xA5); // cloud
	matrix_print(0xA6); // barometer
	matrix_print(0xA7); // :-)
	matrix_print(0x7F); // BRICK
	matrix_end(fx_scroll_horizontal, 0);
	delay(5000);


	matrix_begin();
	matrix_print(0xA9);  // seg 0
	matrix_print(0xAA);  // seg 1/4
	matrix_print(0xAB);  // seg 2/4
	matrix_print(0xAC);  // seg 3/4
	matrix_print(0xAD);  // seg full
	matrix_end(fx_scroll_horizontal, 1);
	delay(5000);
	
	setup();
	char buf[10];
	// int idx=0; intToStrDec(12345, 5, &buf[0], idx); buf[idx]=0; Serial.println(buf);
	int idx; 
	idx=0; floatToStr(123, 0, 2, &buf[0], idx); buf[idx]=0; Serial.println(buf);
	idx=0; floatToStr(123.45, 0, 2, &buf[0], idx); buf[idx]=0; Serial.println(buf);
	idx=0; floatToStr(-123.456, 0, 2, &buf[0], idx); buf[idx]=0; Serial.println(buf);
	// idx=0; floatToStr(-123, 0, &buf[0], idx); buf[idx]=0; Serial.println(buf);
	// Serial.println(1234);*/
	// matrix_begin();
	// matrix_printNumI(1, 2);
	//matrix_print("  ", 0, 0);
	// matrix_printNumFloat(-1.234, 0, 2);
	// matrix_end();
	
	
	strbank_init();
	uint8_t id;
	
	/*eeprom_setmem(0x40, 0, 0x80);
	
	Serial.println("==Writing bank==");
	strbank_clear();
	
	id = strbank_add(1, "1234", false);
	strbank_printInfo();
	
	id = strbank_add(2, "5678", false);
	strbank_printInfo();
	
	id = strbank_add(3, "Third message", false);
	strbank_printInfo();
	
	strbank_updateHdr();
	//strbank_printInfo();
	*/
	
	eeprom_dumpSerial(0x40, 0x80);
	
	
	// 
	char buf[100];
	Serial.println("==Reading bank==");
	
	if (strbank_get(101, buf, sizeof(buf)-1, false)) {
		Serial.println(buf);
	}

	if (strbank_get(102, buf, sizeof(buf)-1, false)) {
		Serial.println(buf);
	}

	if (strbank_get(103, buf, sizeof(buf)-1, false)) {
		Serial.println(buf);
	}

	if (strbank_get(104, buf, sizeof(buf)-1, false)) {
		Serial.println(buf);
	}
	
	
	while(1);
	
	
}


//
// init sensors for local SENSOR
//
void sensor_init(MySensor& s) {

#ifdef _BUILD_FAKE_SENSOR_
	s.setValueF(0xff, MYSENSOR_VALUE_KIND_TEMPERATURE, NAN);		// id = 0xff - emulated debug
	s.setValueF(0xff, MYSENSOR_VALUE_KIND_RELATIVE_HUMIDITY, NAN);
	s.setValueF(0xff, MYSENSOR_VALUE_KIND_PRESSURE, NAN);           
#endif
	sensor.scan_interval_sec = INTERVAL_SENSOR_SCAN_SEC;
#ifdef _BUILD_DHT_
	dht_init(s);
#endif
	
#ifdef _BUILD_BMP_
	bmp_init(s);
#endif
}

//
// scan all sensors values
//
uint8_t sensor_scan(MySensor& s, bool overrideDataChanged){
	s.scan_state = 1;
	uint8_t dataChanged =0;
	
#ifdef _BUILD_FAKE_SENSOR_
    dataChanged =1;
	s.setValueF(0xff, MYSENSOR_VALUE_KIND_TEMPERATURE, tick&0x1F);		// id = 0xff - emulated debug
	s.setValueF(0xff, MYSENSOR_VALUE_KIND_RELATIVE_HUMIDITY, tick&0x2F);
	s.setValueF(0xff, MYSENSOR_VALUE_KIND_PRESSURE, 740+tick&0x0F);
#endif	

#ifdef _BUILD_DHT_
	dataChanged|=dht_read(s);
#endif
	
#ifdef _BUILD_BMP_
	dataChanged|=bmp_read(s);
#endif
	// get temp from RTC
	// hasNew |= sensor.setValueF(3, MYSENSOR_VALUE_KIND_AMBIENT_TEMPERATURE, rtc.getTemp(), 0);
	s.scan_state = 2;  // scanned
	return dataChanged;
}


void setup()
{

	/* add setup code here */
	Serial.begin(9600);
  
	serial_print_P(product_name_and_version);
	serial_print_P(app_help);
	Serial.println();
	
	// test string bank init
	strbank_init();
	
	// rtc ds3231 init
	rtc.begin();
	
	// matrix max7219
	matrix_init();
	//matrix_scroll_text_P(product_name_and_version, true, true);

#ifdef _BUILD_TEST_
	Serial.println("TEST");
	test();
#endif  

	
	// sensor.on_init = &sensor_init;
	sensor_init(sensor);
	sensor.on_scan = &sensor_scan;
	
    serial_write_init(SERIAL_PROTOVER, DEVICE_TYPE, DEVICE_ID);
	
	rtc_time.dow=0;
	
}

// main loop code
void loop()
{
	/* add main program code here */
	tick = millis();

	overrideSensScan=false;
	overrideRadioSensValues=false;
	// overridePing=false;
	disp_mode_changed=false;


	//
	// 500 ms tick
	//
	if ((tick-last_tick_500ms)>=500) {
		last_tick_500ms = tick;
		ticked_500ms=1;
	} else {
		ticked_500ms=0;
	}


	//
	// Tick: Auto-Change display mode
	//
	if (disp_mode_next_sec>0 &&
	(tick-last_tick_disp_mode_change>=disp_mode_next_sec*1000UL)) {
		last_tick_disp_mode_change = tick;
		disp_mode_changed = 1;
		disp_mode = disp_mode_next;

		// disp_mode = disp_mode==nochange? humidity : (disp_mode_e)(((uint8_t) disp_mode)+1);
		// prepare auto-next mode
		switch (disp_mode)
		{
			case (now_time):
				disp_mode_next = s_temperature;
				break;
			
			case (now_date):
				disp_mode_next = now_time;
				break;
			
			case (s_temperature):
				disp_mode_next = s_humidity;
				break;
			
			case (s_humidity):
#ifdef _BUILD_BMP_
				disp_mode_next = s_pressure;
#else
				disp_mode_next = now_time;
#endif
				break;
			
			case (s_pressure):
				disp_mode_next = now_time;
				break;
				
			/*case (message):
				disp_mode_next = now*/

		}
		//Serial.print("disp_mode_next=");Serial.println(disp_mode_next);

		// time to switch to next mode (only if disp_mode_cycle)
		disp_mode_next_sec=disp_cycle_modes? pgm_read_byte_near(disp_mode_duration_sec+disp_mode) : 0;

		disp_need_update=1;
	}


	//if (Serial.available())	{
		//byte b = Serial.read();
		//Serial.println(b);
	//}


#ifdef _BUILD_SERIAL_

	//
	// Check serial cmd
	//
	uint8_t s_cmd = myserial_read_cmd_begin();
	if (s_cmd) {
		Serial.print(F("Received s_cmd:"));  Serial.println(s_cmd);

		uint16_t toDevice=0;
		uint8_t toSensId=0;
		uint8_t toDisp=0;

		// cmd: query sensor values
		if (s_cmd == SERIAL_CMD_Q_SENS_VALUES) {
			/*myserial_read_uint16(&toDevice); // todo: can check EOL
			myserial_read_byte(&toSensId);

			// set NeedToScan
			overrideBroadcastRadioScan = !toDevice;
			for (uint8_t i =0; i<sensors.count;i++) {
				MySensor *s = sensors.items[i];
				if ((s->owner==toDevice!=0? toDevice : DEVICE_ID) &&
				(!toSensId || s->local_id==toSensId)) {
					s->last_tick_scan = 0; // time to scan
				}
			}*/
			serial_write_err_not_supported();
		}

		// cmd: freeRam
		else if (s_cmd==SERIAL_CMD_SYS_FREE_RAM) {
			Serial.println(freeRam());
		}
	
		// Display message on matrix
		else if (s_cmd == SERIAL_CMD_Q_DISP_MSG) {
			myserial_read_uint16(&toDevice);
			// todo:check destination device!
			uint8_t flags=0x80; // with beep default
			uint8_t duration=5; // 5 sec default      // 0xff for just scroll
			myserial_read_byte(&toDisp);
			myserial_read_byte(&flags);
			myserial_read_byte(&duration);

			uint8_t msgLen=myserial_read_str(disp_msg, MATRIX_STRING_CAPACITY);
			disp_msg[msgLen]=(byte) 0;
			disp_msg_len = msgLen;
			disp_msg_width = matrix_text_width(disp_msg);
			disp_msg_pos = - disp_msg_width;
			
			Serial.print(F("Display message: ")); Serial.println(disp_msg);
			// Serial.println((byte)disp_msg[0]);
			last_tick_disp_message = 0;
			/*matrix_scroll_text(disp_msg, flags & 0x40, flags & 0x20);
			delay(1000);
			disp_mode = now_time;
			disp_mode_changed = 1;
			disp_need_update = 1;*/
		}
		
		// Set str bank value
		else if (s_cmd== SERIAL_CMD_Q_SET_STRBANK) {
			// full set of str bank
			myserial_read_uint16(&toDevice); // todo:check destination device!
			uint8_t strBank=0;
			myserial_read_byte(&strBank);
			// todo: check device id and bank N
			// update device strBank			
			if (toDevice == DEVICE_ID) {
				Serial.println(F("Updating StrBank.."));
				// Serial.setTimeout(5000);
				// full rewrite!
				//cli();
				strbank_clear();
				//sei();
				// todo: backup and restore disp_msg to EEPROM!
				while (!myserial_read_eol) {
					uint16_t strId=0;
					myserial_read_uint16(&strId);
					if (strId) {
						uint8_t strLen = myserial_read_str(disp_msg, MATRIX_STRING_CAPACITY);
						disp_msg[strLen]=(byte) 0;
						Serial.println(disp_msg);
				//cli();
						strbank_add(strId, disp_msg, false);
				//sei();
						Serial.println(F("EEPROM:OK"));
					}
				}
				strbank_updateHdr();
				strbank_print(0, true);
				// eeprom_dumpSerial(0x40, 0x80);
				last_tick_disp_message = 1; // to print message of the day (0 causes print last message)
			}
			
		}

		// Get str bank message
		else if (s_cmd == SERIAL_CMD_Q_GET_STRBANK) {
			myserial_read_uint16(&toDevice); // todo:check destination device!
			uint8_t strBank=0;
			myserial_read_byte(&strBank);
			uint8_t strId=0;
			myserial_read_byte(&strId);
			strbank_print(strId, !strId);
		}
		
		// dump EEPROM
		else if (s_cmd == SERIAL_CMD_SYS_EEPROM_DUMP) {
			uint16_t addr=0, size = EEPROM_SIZE;
			eeprom_dumpSerial(addr, max(size, EEPROM_SIZE));
		}
		
		
		
		// if (!eol) serial_read_until(&msg[0], SERIAL_TOKEN_FLD_SEPARATOR, strlen(msg), &eol);
			/*radio_packet.prepare(toDevice, RADIO_CMD_DISP_LED_TXT);
			radio_packet.valueWrite<uint8_t>(toDisp);
			radio_packet.valueWrite<uint8_t>(flags);
			radio_packet.valueWrite<uint8_t>(duration);
			memcpy(&radio_packet.p.values[radio_packet.idx], &msg[0], 4);
			radio_packet.printActivity(true, "DISP_MSG "); Serial.println(msg);
			radio_packet.send(radio);*/
		
		else if (s_cmd == SERIAL_CMD_SYS_RTC) {
			Serial.print(F("Setting RTC..."));
			uint16_t dy=0;
			uint8_t dm, dd, dow=0;
			myserial_read_uint16(&dy);
			myserial_read_byte(&dm);
			myserial_read_byte(&dd);
			if (dy && dm && dd)	rtc.setDate(dd, dm, dy);
			myserial_read_byte(&dow);
			if (dow) rtc.setDOW(dow);
			// uint8_t th, tm, ts = 0xff;
			uint8_t t;
			if (myserial_read_byte(&t)) {
				rtc.setHour(t);
				if (myserial_read_byte(&t)) {
					rtc.setMinute(t);
					if (myserial_read_byte(&t)) {
						rtc.setSecond(t);
					}
				}
			}
			Serial.println(F("OK"));
		}

		
	    // read to the EOL
	    myserial_read_until_eol();
	}
	
#endif

	//
	// time to scroll message of the day?
	//Serial.println(tick-last_tick_disp_message);
	uint32_t elapsed = tick-last_tick_disp_message;
	
	if ((!last_tick_disp_message || (elapsed >INTERVAL_DISP_DAY_MESSAGE_SEC*1000UL))) {
		// Serial.println(tick-last_tick_disp_message);
	
		//matrix_flash();
		//matrix_fade(1, 0);
		if (last_tick_disp_message) {
			uint16_t strId = 100+rtc_time.dow;
			Serial.print(F("Display msg of day. Id=")); Serial.println(strId);
			// try to get message of the day from string bank
			disp_msg_len = strbank_get(strId, disp_msg, sizeof(disp_msg)-1, false);
			// Serial.print(F("strLen=")); Serial.println(strLen);
			// disp_msg_len = strLen;
			if (disp_msg_len==0xff) disp_msg_len=0;
			//Serial.println(disp_msg_len);
		}
		if (disp_msg_len) {
			Serial.println(disp_msg);
			matrix_fade(0, 1);
			matrix_scroll_text(disp_msg, 1, 1);
			delay(1000);
			last_tick_disp_mode_change = millis(); // reset disp mode timer
			disp_mode = now_time;
			disp_mode_changed = 1;
			disp_need_update = 1;
		}
		last_tick_disp_message = tick;
	}


	//
	// Tick: Scan sensor (DHT11 + BMP)
	//
	// Serial.print("OverrideSensScan="); Serial.println(overrideSensScan);
if (overrideSensScan) Serial.println("overrideSensScan");
	uint8_t sensDataChanged = sensor.scanOnDemand(tick, overrideSensScan, 0);
	if (sensDataChanged){
Serial.println("sensDataChanged");
		disp_need_update|=(disp_mode==s_humidity || disp_mode==s_temperature || disp_mode == s_pressure); // only if mode = temp, humidity !
	}

	// time: flash dots
	disp_need_update|=(disp_mode == now_time) && ticked_500ms;
	//if (disp_need_update) Serial.println("disp_need_update");

	//
	// LED Display need update info?
	//
	if (disp_need_update) {

		// mode changed - need to fade out
		if (disp_mode_changed) {
			//matrix_fade(0, 1); < - make it not clearing buffer!
Serial.println("disp_mode_changed");
		}

		
		// Time update
		// Time rtc_time = rtc.getTime();
		rtc_time = rtc.getTime();
		
		MySensorValue *v;
		max7219_update_fx_e fx=none;
		matrix_begin();
		// Serial.print("disp update, mode=");Serial.println(disp_mode);
		switch (disp_mode) 
		{
			case (disabled):
				break;

			case (now_time):
				matrix_setCursor(4,0);
				matrix_printNumI(rtc_time.hour, 2);
				matrix_print((tick&512)? ':' : '.');
				matrix_printNumI(rtc_time.min, 2);
				fx=fx_fill_vertical;
				break;

			case (now_date):
				matrix_print("Date");
				fx=fx_fill_bits;
				break;


			case (s_temperature):

#ifdef _BUILD_FAKE_SENSOR_
				v = sensor.getValue(99, MYSENSOR_VALUE_KIND_TEMPERATURE, false);
#elif defined (_BUILD_BMP_)
				v=  sensor.getValue(2, MYSENSOR_VALUE_KIND_TEMPERATURE, false);
#elif defined (_BUILD_DHT_)
				v = sensor.getValue(1, MYSENSOR_VALUE_KIND_TEMPERATURE, false);
#else	
				v = NULL;
#endif
				matrix_print(0xA4); // temp = A1
				if (v) {
					if (v->value.asFloat>0) matrix_print('+');
					matrix_printNumI(round(v->value.asFloat), 0);
					matrix_print(0xA0); // '
					matrix_print("C");
				} else {
					matrix_print("---");
				}
				fx=fx_fill_vertical;
				break;

			case (s_humidity):
#ifdef _BUILD_FAKE_SENSOR_
				v = sensor.getValue(99, MYSENSOR_VALUE_KIND_RELATIVE_HUMIDITY, false);
#elif defined(_BUILD_DHT_)
				v = sensor.getValue(1, MYSENSOR_VALUE_KIND_RELATIVE_HUMIDITY, false);
#else
				v = NULL;
#endif
				matrix_print(0xA5); // or A2 humidity
				matrix_print(' ');
				if (v) {
					matrix_printNumI(round(v->value.asFloat), 0);
					matrix_print("%");
				} else {
					matrix_print("---");
				}
				fx=fx_fill_bits;
				break;

			case (s_pressure):
#ifdef _BUILD_FAKE_SENSOR_
				v = sensor.getValue(99, MYSENSOR_VALUE_KIND_PRESSURE, false);
#elif defined(_BUILD_BMP_)
				v = sensor.getValue(2, MYSENSOR_VALUE_KIND_PRESSURE, false);
#else
				v = NULL;
#endif
				matrix_print(0xA3);  // pressure = A6
				if (v) {
					matrix_printNumI(round(v->value.asFloat), 0);
					matrix_print("mm");
				}
				else {
					matrix_print("---");
				}
				fx=fx_fill_bits;
				break;

			case (message):
				// led_disp_text(disp_msg_master);
				break;

			default:
				break;
			
		}
		matrix_end(disp_mode_changed? fx: none, false);
		disp_need_update=0;
	
		if (disp_mode_changed) {
			//matrix_fade(1, 0);
			//matrix_flash();
		}
		
	}
		
	delay(100);
		
}
