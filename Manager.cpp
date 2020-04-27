/*
 * Manager.cpp
 *
 *  Created on: 27 de abr de 2020
 *      Author: rafae
 */

#include "Manager.h"
#include "Arduino.h"

Manager::Manager() {

	max_clk_count = 8250;
	Failure = false;
	elapsed_time = 0;
}

Manager::~Manager() {

}

void Manager::start()
{
//start the timer
TIFR5 = 0x2f;//writes one to clear the flag (weird)
TCCR5A=0x00;
TCCR5B=0x03;
TCCR5C=0x00;
TCNT5 = 0x0000;
}

void Manager::end()
{
//get the timer and log a failure if time was bigger then the configured;
unsigned int count=0;
count=TCNT5;
elapsed_time = count;
if((elapsed_time>max_clk_count))
	Failure=true;
while(TCNT5<max_clk_count);
}
