// Temperature.h

#ifndef _TEMPERATURE_h
#define _TEMPERATURE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <dht.h>

class TemperatureClass
{
private:
#define DHT22_PIN 23

public:
	TemperatureClass();
	void setupT();
	float getTemperature();
	float getHumidity();

	void loopT();

};
#endif


