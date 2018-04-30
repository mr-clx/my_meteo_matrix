#ifdef _BUILD_BMP_

#define BMP_ID 10085

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(BMP_ID);

// BMP180

/* Initialize the sensor */
void bmp_init(MySensor& s) {
    Serial.println(F("Init sensor BMP180..."));
    if(!bmp.begin()) //BMP085_MODE_ULTRAHIGHRES))
    {
		Serial.println(F("Error: no BMP085 detected!"));
    } else {
		s.setValueF(2, MYSENSOR_VALUE_KIND_TEMPERATURE, NAN);  // id = 2 for BMP180
		s.setValueF(2, MYSENSOR_VALUE_KIND_PRESSURE, NAN);             // id = 2 for BMP180
		// bmpDisplaySensorDetails();
		Serial.println(F("OK"));
	}
}

// read available info from sensor
// todo: return true if changed values
bool bmp_read(MySensor& s)
{
    bool changed=0;
    // if (!s.values_count) return false;

	sensors_event_t event;
    bmp.getEvent(&event);
    if (event.pressure) {
      changed|= s.setValueF(2, MYSENSOR_VALUE_KIND_PRESSURE, event.pressure*0.75006375541921);
      float t;
      bmp.getTemperature(&t);
      changed|= s.setValueF(2, MYSENSOR_VALUE_KIND_TEMPERATURE, t);
    } else  {
      changed|= s.setValueF(2, MYSENSOR_VALUE_KIND_TEMPERATURE, NAN);  // id = 2 for BMP180
	  changed|= s.setValueF(2, MYSENSOR_VALUE_KIND_PRESSURE, NAN);             // id = 2 for BMP180
      Serial.println(F("Error: unable to read BMP sensor!"));
    }
	return changed;
}

#endif
