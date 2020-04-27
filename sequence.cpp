/*
 * sequence.cpp
 *
 *  Created on: 30 de ago de 2019
 *      Author: rafae
 */
#include <Adafruit_NeoPixel.h>
#include "sequence.h"


sequence::~sequence()
{
	delete pixels;
}

sequence::sequence()
{

	pixels = new Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB);
	pixels->begin();
}


void sequence::set_effect(effect_type _fx, unsigned char fade_in, unsigned char fade_out)
{
fx = _fx;
fx_fade_in = fade_in;
fx_fade_out = fade_out;


}

void sequence::handler()
{

	int pos = 0;
	for(int i =0 ; i< NUMPIXELS;i++)
	{
	  pixels->setPixelColor(i,p[pos],p[pos+1],p[pos+2]);
	  pos+=3;
	}
	pixels->show();   // Send the updated pixel colors to the hardware.


}






