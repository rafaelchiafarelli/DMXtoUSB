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
	setFrameDisplayed(0);
	pixels = new Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB);
	pixels->begin();
}

void sequence::setFrameDisplayed(int j)
{
	seq_number = j;
}
#define FREQ_TOTAL 20
void sequence::handler()
{
	static unsigned int count = 0;
	int pos = 0;
	for(int i =0 ; i< NUMPIXELS;i++)
	{
	  pixels->setPixelColor(i,p[pos],p[pos+1],p[pos+2]);
	  pos+=3;
	}
	pixels->show();   // Send the updated pixel colors to the hardware.
	count++;
	if (count>FREQ_TOTAL)
		count = 0;
}






