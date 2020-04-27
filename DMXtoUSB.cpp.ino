#include "Arduino.h"
#include "types.h"
#include "string.h"
#include "DMXController.h"
#include "PCP.h"
#include "sequence.h"
#include "Manager.h"


DMXController dmx;
sequence S;
PCP protocol(&dmx,&S);
Manager GeneralManager;



// the setup function runs once when you press reset or power the board
void setup() {
}

// the loop function runs over and over again forever
void loop() {

static state_type st = DMX_TIME;
GeneralManager.start();
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
		S.handler();
		break;
	}
protocol.restart_serial();
GeneralManager.end();
}


