//ConectareMQTT.h

#ifndef ConectareMQTT_h
#define	ConectareMQTT_h
#include "Arduino.h"
#include "WiFi.h"
#include "PubSubClient.h"
#include "ConectareMQTT.h"

class ConectareMQTTClass
{

 public:
	#define mqtt_port 1883
	#define MQTT_SERIAL_PUBLISH_CH "Lumini/Esp32"
	#define MQTT_SERIAL_RECEIVER_CH "Lumini/Esp32"
	#define ID_MAP_LENGTH 5
	 const char* ssid = "MyWifi";
	 const char* password = "parola";
	 String txt, txtCopy;
	 const char* mqtt_server = "192.168.0.105";
	 ConectareMQTTClass();
	 void Publica(const char * text);
	 void setup_wifi();
     void reconnect();
	 void callback(char * topic, uint8_t * payload, unsigned int length);
	 void setupM();
	 void loopM();
};
#endif


