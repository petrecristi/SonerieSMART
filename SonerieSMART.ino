
#include "ConectareMQTT.h"
#define LIGHT_ACTIVATE_PIN 2
#define BUTTON_RING_PIN  5
#define BUZZER_PIN 21

volatile bool state = false;
volatile bool buzzerTaskAlive = false;
ConectareMQTTClass mqtt;
TaskHandle_t Buzzer_Task;

void codeForBuzzer_Task(void *parameter) {
	for (;;) {
		digitalWrite(BUZZER_PIN, HIGH);
		vTaskDelay(2000);
		digitalWrite(BUZZER_PIN, LOW);
		vTaskDelay(500);
		//if (Buzzer_Task != NULL)
		if (Buzzer_Task == NULL)
		{
			vTaskDelete(Buzzer_Task);
		}

	}
}

//if i get "BecPornit" -> LIGHT_ACTIVATE_PIN = HIGH
//if i get "BecOprit" -> LIGHT_ACTIVATE_PIN = LOW
void  ConectareMQTTClass::callback(char* topic, uint8_t *payload, unsigned int length)
{
	payload[length] = '\0';
	txt = ((char*)payload);

	if (!txt.equals(txtCopy)) {

		if (txt.equals("BecPornit")) {
			txtCopy = txt;
			digitalWrite(LIGHT_ACTIVATE_PIN, HIGH);
			Publica("Am aprins becul.");
		}
		else if (txt.equals("BecOprit")) {
			txtCopy = txt;
			digitalWrite(LIGHT_ACTIVATE_PIN, LOW);
			Publica("Am stins becul.");
		}
		else {
			txtCopy = txt;
		}

	}

}

	// TODO: attach interrupts to one of esp32 pins to get button push
void interruptsHandle() {
	//digitalWrite(LIGHT_ACTIVATE_PIN, !digitalRead(LIGHT_ACTIVATE_PIN));
	// chose one pin for buzzer and change LIGHT_ACTIVATE_PIN with that one in this task  ///DONE
	// if BUTTON_RING_PIN has been triggered make a new task to set buzzer_pin: 2 sec high and 0.5 sec low, in loop ///DONE
	// after 30 sec set BUZZER_PIN->LOW and remove task 
	if (buzzerTaskAlive == false) {
		xTaskCreatePinnedToCore(codeForBuzzer_Task, "buzzer_task", 1024, NULL, 1, &Buzzer_Task, 1);
		buzzerTaskAlive = true;
	}
}

void setup()
{
	pinMode(LIGHT_ACTIVATE_PIN, OUTPUT);
	pinMode(BUZZER_PIN, OUTPUT);
	pinMode(BUTTON_RING_PIN, INPUT);
	attachInterrupt(digitalPinToInterrupt(BUTTON_RING_PIN), interruptsHandle, CHANGE);

	mqtt.setup_wifi();
	mqtt.setupM();
	mqtt.reconnect();
}

void loop()
{
	mqtt.loopM();
 
}
