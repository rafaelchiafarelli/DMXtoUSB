/*
 * images.h
 *
 *  Created on: 29 de ago de 2019
 *      Author: rafae
 */

#ifndef SEQUENCE_H_
#define SEQUENCE_H_


#include <Adafruit_NeoPixel.h>
#include "config.h"
#include "bin.h"

#include "Arduino.h"

class sequence
{
private:
	unsigned char p[NUMPIXELS*3];

	int seq_number; // number of the sequence being displayed
	Adafruit_NeoPixel *pixels; //pixels being displayed in the hardware;

public:
	void setFrameDisplayed(int i);
	unsigned char *get_ptr(){return p;};
	void handler(); //must be called every 16milliseconds;
	sequence();
	~sequence();
};


#endif /* SEQUENCE_H_ */
