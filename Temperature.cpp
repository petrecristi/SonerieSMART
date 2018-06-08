#include "Temperature.h"

//constructor
TemperatureClass::TemperatureClass() {
}



//create an instance of DHT sensor
dht DHT;
unsigned long startMilliss;

void TemperatureClass::setupT() {
	//Serial.begin(115200);
	
	startMilliss = millis();
}

float TemperatureClass::getTemperature() {
	if (millis() - startMilliss > 2200) {
		startMilliss = millis();
		DHT.read22(DHT22_PIN);
		return DHT.temperature;
	}
	else {
		return 9999.1f;
	}
}

float TemperatureClass::getHumidity() {
	if(millis()-startMilliss>2200){
		startMilliss = millis();
		DHT.read22(DHT22_PIN);
		return DHT.humidity;
	}
	else {
		return 9999.1f;
	}
}

void TemperatureClass::loopT() {
	//use the functions which are supplied by library.
	
}
