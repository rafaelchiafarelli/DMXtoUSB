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
	unsigned char l_p[NUMPIXELS*3];
	unsigned char control[MAX_EFFECT_NUMBER];
	unsigned char counter[MAX_EFFECT_NUMBER];
	unsigned char counter2[MAX_EFFECT_NUMBER];
	effect_type fx;
	unsigned char fx_fade_in;
	unsigned char fx_fade_out;
	int seq_number; // number of the sequence being displayed
	Adafruit_NeoPixel *pixels; //pixels being displayed in the hardware;
	void set_fade_in_fade_out();
	void apply_fade_in_fade_out();
	void set_fade_in_dead_out();
	void apply_fade_in_dead_out();
	void set_fade_in_live_out();
	void apply_fade_in_live_out();
	void set_fade_in_live_fade_out();
	void apply_fade_in_live_fade_out();
	void set_strobe_freq_fade_in_dead_fade_out(unsigned char f_in, unsigned char f_out);
	void apply_strobe_freq_fade_in_dead_fade_out();


public:
	void set_effect(effect_type _fx, unsigned char fade_in, unsigned char fade_out);

	unsigned char *get_ptr(){return p;};
	void handler_visual();
	void handler(); //must be called every 16milliseconds;
	sequence();
	~sequence();
};


#endif /* SEQUENCE_H_ */
