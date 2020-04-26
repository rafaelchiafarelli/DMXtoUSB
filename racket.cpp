/*
 * raquet.cpp
 *
 *  Created on: 24 de set de 2019
 *      Author: rafae
 */

#include "racket.h"

racket::racket(int btn_pin, int sens_pin, int coilH_pin, int coilL_pin) {
	// TODO Auto-generated constructor stub
	state = locked_down;
	pinMode(btn_pin, INPUT_PULLUP);
	pinMode(sens_pin, INPUT_PULLUP);
	pinMode(coilH_pin, OUTPUT);
	pinMode(coilL_pin, OUTPUT);
	digitalWrite(coilH_pin, LOW);
	digitalWrite(coilL_pin, LOW);
	btn_p=btn_pin;
	sens_p = sens_pin;
	coilH_p = coilH_pin;
	coilL_p = coilL_pin;
	debounce_on = 0;
	debounce_off = 0;
}

racket::~racket() {
	// TODO Auto-generated destructor stub
}

void racket::handler()
{
	//pegar o stado do botão e do sensor
	//acionar os reles de acordo
	int relay_h = 1;
	int relay_l = 1;
	int btn = (!digitalRead(btn_p))&0x01;
	int sens = (!digitalRead(sens_p))&0x01;

	switch(state)
	{
	case none:

		break;
	case launching:
		if(btn)
		{
			relay_h = 0;
			if(sens)
			{
				debounce_on++;
				if(debounce_on)
				{
					relay_h = 1;
					relay_l = 0;
					state = locked_up;
				}

			}
			else
			{
				debounce_on = 0;
			}
		}
		else
		{
			state = locked_down;
			relay_h = 1;
			relay_l = 1;
		}
		break;
	case locked_up:
		if(btn)
		{
			relay_h = 1;
			relay_l = 0;
			if(sens)
			{
				debounce_off=0;
			}
			else
			{
				debounce_off++;
				if(debounce_off>DEBOUNCE_OFF)
				{
				state = launching;
				}
			}
		}
		else
		{
			state = locked_down;
		}
		break;
	case locked_down:

		if(btn)
		{
			debounce_on++;
			if(debounce_on>DEBOUNCE_ON)
			{
				state = launching;
				relay_h = 0;
				relay_l = 1;
			}
		}
		else
		{
		state = locked_down;
		debounce_on = 0;
		}
		break;


	}

	digitalWrite(coilH_p,relay_h);
	digitalWrite(coilL_p,relay_l);

}
