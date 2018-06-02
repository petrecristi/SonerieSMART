#include "ConectareMQTT.h"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

//constructor
ConectareMQTTClass::ConectareMQTTClass() {

}

void ConectareMQTTClass::Publica(const char *text) {

	client.publish(MQTT_SERIAL_PUBLISH_CH, text);
}

void ConectareMQTTClass::setup_wifi() {
	
	//Serial.begin(115200);
	delay(10);
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		//Serial.print(".");
		delay(500);
	}

	randomSeed(micros());
	//Serial.println(WiFi.localIP());
}


void ConectareMQTTClass::reconnect() {
	// Loop until we're reconnected

	while (!client.connected()) {

		String clientId = "ESP32ClientTest-";
		clientId += String(random(0xffff), HEX);
		String textSalut = "Salut. Sunt " + (String)clientId + " si m-am conectat la MQTT!";

		String cc = clientId;
		cc+= " IP: ";
		cc+= (char*)WiFi.localIP().toString().c_str();

		if (client.connect(clientId.c_str())) {
			//   Serial.println("connected");
			//Once connected, publish an announcement...

			client.publish(MQTT_SERIAL_PUBLISH_CH, textSalut.c_str());
			client.publish(MQTT_SERIAL_PUBLISH_CH, cc.c_str());
			//client.publish(MQTT_SERIAL_PUBLISH_CH, "Sunt Esp32, m-am conectat la mqtt. ");
			// ... and resubscribe
			client.subscribe(MQTT_SERIAL_RECEIVER_CH);
			//Serial.println("M=am conectat la mqtt");
		}
		else {
			//Serial.println("Nu s-a conectat la mqtt");
			delay(5000);
		}
	}
}



void ConectareMQTTClass::setupM() {

	client.setServer(mqtt_server, mqtt_port);
	client.setCallback([this](char* topic, uint8_t* payload, unsigned int length) {this->callback(topic, payload, length);  });
}


void ConectareMQTTClass::loopM() {
	client.loop();
}