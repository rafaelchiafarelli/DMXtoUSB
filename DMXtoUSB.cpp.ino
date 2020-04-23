/*

 */
#include "Arduino.h"
#include "types.h"
#include "string.h"
#include "DMXController.h"
#include "PCP.h"

DMXController dmx;
PCP protocol(&dmx);

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	Serial.setTimeout(70);
}

// the loop function runs over and over again forever
void loop() {
static state_type st = DMX_TIME;
	switch(st){
		case DMX_TIME:
			st = SERIAL_TIME;
			dmx.Handler();
			break;
		case SERIAL_TIME:
			st = NEOPIXEL_TIME;
			protocol.Handler();
			break;
		case NEOPIXEL_TIME:
			st = DMX_TIME;
			delay(50);
			break;
		}

}



