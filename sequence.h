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

#include "types.h"
#include "Arduino.h"

class sequence
{
private:
	unsigned char p[NUMPIXELS*3];

	effect_type fx;
	unsigned char fx_fade_in;
	unsigned char fx_fade_out;
	int seq_number; // number of the sequence being displayed
	Adafruit_NeoPixel *pixels; //pixels being displayed in the hardware;

public:
	void set_effect(effect_type _fx, unsigned char fade_in, unsigned char fade_out);

	unsigned char *get_ptr(){return p;};
	void handler(); //must be called every 16milliseconds;
	sequence();
	~sequence();
};


#endif /* SEQUENCE_H_ */
