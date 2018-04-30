#include "DHT.h"

#ifdef _BUILD_DHT_

// Uncomment whatever type you're using!
// #define DHT_TYPE DHT11   // DHT 11
#define DHT_TYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

#define DHT_PIN 4     // what pin we're connected to

DHT dht(DHT_PIN, DHT_TYPE);

void dht_init(MySensor& s)
{
    Serial.println(F("Init sensor DHT22..."));
    dht.begin();
    
	//s.init(DEVICE_ID, 1, "DHT11", INTERVAL_DHT_SCAN_SEC);			// src=DEVICE_ID, id = 1 (group num), auto-scan interval
    s.setValueF(1, MYSENSOR_VALUE_KIND_TEMPERATURE, NAN);			// id=4 = DHT22
    s.setValueF(1, MYSENSOR_VALUE_KIND_RELATIVE_HUMIDITY, NAN);		// id=4 = DHT22
    //s->setValueF(1, MYSENSOR_VALUE_KIND_HEAT_INDEX, NAN, 0);		// id=4 = DHT22 (comfort zone)
    Serial.println(F("OK"));
}

//
// return true if sensor has changed value (different from previous)
// 
bool dht_read(MySensor& s)
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature(false);
    float h = dht.readHumidity();

  Serial.print("DHT22 t="); Serial.print(t);
  Serial.print("\th="); Serial.print(h);
  Serial.println();

    //float hi = dht.computeHeatIndex (t, h, false);
    //bool changed = overrideNew;
	bool changed=0;
    changed|=s.setValueF(1, MYSENSOR_VALUE_KIND_TEMPERATURE, t);
    changed|=s.setValueF(1, MYSENSOR_VALUE_KIND_RELATIVE_HUMIDITY, h);
    //changed |=s->setValueF(1, MYSENSOR_VALUE_KIND_HEAT_INDEX, hi, 0);
    return changed;
}

#endif
