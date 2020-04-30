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
switch(fx)
{

case FADE_IN_FADE_OUT:
	set_fade_in_fade_out();
	break;
case FADE_IN_DEAD_OUT:
	set_fade_in_dead_out();
	break;
case FADE_IN_LIVE_OUT:
	set_fade_in_live_out();
	break;
case FADE_IN_LIVE_OUT_FADE_OUT:
	set_fade_in_live_fade_out();
	break;
case STROBE_LIVE_FADE_IN_DEAD_FADE_OUT:
	set_strobe_freq_fade_in_dead_fade_out(fade_in,fade_out);
	break;
case STROBE_FREQ_FADE_IN_DEAD_FADE_OUT:
	break;
case STROVE_FREQ_INCREASE_FADE_IN:
	break;
case NO_EFFECT:
	break;
default:
	break;
}

}
void sequence::handler_visual()
{
	switch(fx)
		{
		case FADE_IN_FADE_OUT:
			apply_fade_in_fade_out();
			break;
		case FADE_IN_DEAD_OUT:
			apply_fade_in_dead_out();
			break;
		case FADE_IN_LIVE_OUT:
			apply_fade_in_live_out();
			break;
		case FADE_IN_LIVE_OUT_FADE_OUT:
			apply_fade_in_live_fade_out();
			break;
		case STROBE_LIVE_FADE_IN_DEAD_FADE_OUT:
			apply_strobe_freq_fade_in_dead_fade_out();
			break;
		case STROBE_FREQ_FADE_IN_DEAD_FADE_OUT:
			break;
		case STROVE_FREQ_INCREASE_FADE_IN:
			break;
		case NO_EFFECT:
			break;
		default:
			break;
		}
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

void sequence::set_fade_in_fade_out()
{
	control[FADE_IN_FADE_OUT] = 0;
	counter[FADE_IN_FADE_OUT] = 0;
	counter2[FADE_IN_FADE_OUT] = 0;
	for(int i=0;i<NUMPIXELS;i++)
	{
		l_p[i]=p[i];
		p[i] = 0;
	}
}

void sequence::apply_fade_in_fade_out()
{
	double adjust_in = counter[FADE_IN_FADE_OUT]/fx_fade_in;
	double adjust_out = counter[FADE_IN_FADE_OUT]/fx_fade_out;
	if(control[FADE_IN_FADE_OUT]==0)
	{
		for(int i =0;i<NUMPIXELS*3 ;i++)
		{
			p[i] = (unsigned char)((double)l_p[i]*adjust_in);
		}
		counter[FADE_IN_FADE_OUT]+=1;
		if(counter[FADE_IN_FADE_OUT]>=fx_fade_in){
			control[FADE_IN_FADE_OUT] = 1;
			counter[FADE_IN_FADE_OUT] = 0;
		}
	}
	else
	{
		for(int i =0;i<NUMPIXELS*3 ;i++)
		{
			p[i] = l_p[i]-(unsigned char)((double)l_p[i]*adjust_out);
		}
		counter[FADE_IN_FADE_OUT]+=1;
		if(counter[FADE_IN_FADE_OUT]>=fx_fade_out){
			control[FADE_IN_FADE_OUT] = 0;
			counter[FADE_IN_FADE_OUT] = 0;
		}
	}
}

void sequence::set_fade_in_dead_out()
{
	control[FADE_IN_DEAD_OUT] = 0;
	counter[FADE_IN_DEAD_OUT] = 0;
	counter2[FADE_IN_DEAD_OUT] = 0;
	for(int i=0;i<NUMPIXELS;i++)
	{
		l_p[i]=p[i];
		p[i] = 0;
	}
}

void sequence::apply_fade_in_dead_out()
{
	double adjust_in = counter[FADE_IN_DEAD_OUT]/fx_fade_in;

	if(control[FADE_IN_DEAD_OUT]==0)
	{
		for(int i =0;i<NUMPIXELS*3 ;i++)
		{
			p[i] = (unsigned char)((double)l_p[i]*adjust_in);
		}
		counter[FADE_IN_DEAD_OUT]+=1;
		if(counter[FADE_IN_DEAD_OUT]>=fx_fade_in){
			control[FADE_IN_DEAD_OUT] = 1;
			counter[FADE_IN_DEAD_OUT] = 0;
		}
	}
	else
	{
		if(counter[FADE_IN_DEAD_OUT] == 0)
			for(int i =0;i<NUMPIXELS*3 ;i++)
			{
				p[i] = 0;
			}
		counter[FADE_IN_DEAD_OUT]+=1;
		if(counter[FADE_IN_DEAD_OUT]>=fx_fade_out){
			control[FADE_IN_DEAD_OUT] = 0;
			counter[FADE_IN_DEAD_OUT] = 0;
		}
	}
}

void sequence::set_fade_in_live_out()
{
	control[FADE_IN_LIVE_OUT] = 0;
	counter[FADE_IN_LIVE_OUT] = 0;
	counter2[FADE_IN_LIVE_OUT] = 0;
	for(int i=0;i<NUMPIXELS;i++)
	{
		l_p[i]=p[i];
		p[i] = 0;
	}
}

void sequence::apply_fade_in_live_out()
{
	double adjust_in = counter[FADE_IN_LIVE_OUT]/fx_fade_in;
	if(control[FADE_IN_LIVE_OUT]==0)
	{
		for(int i =0;i<NUMPIXELS*3 ;i++)
		{
			p[i] = (unsigned char)((double)l_p[i]*adjust_in);
		}
		counter[FADE_IN_LIVE_OUT]+=1;
		if(counter[FADE_IN_LIVE_OUT]>=fx_fade_in){
			control[FADE_IN_LIVE_OUT] = 1;
			counter[FADE_IN_LIVE_OUT] = 0;
		}
	}
	else
	{
		if(counter[FADE_IN_DEAD_OUT] == 0)
			for(int i =0;i<NUMPIXELS*3 ;i++)
			{
				p[i] = l_p[i];
			}
		counter[FADE_IN_LIVE_OUT]+=1;
		if(counter[FADE_IN_LIVE_OUT]>=fx_fade_out){
			control[FADE_IN_LIVE_OUT] = 0;
			counter[FADE_IN_LIVE_OUT] = 0;
			for(int i =0;i<NUMPIXELS*3 ;i++)
			{
				p[i] = 0;
			}
		}
	}
}


void sequence::set_fade_in_live_fade_out()
{
	control[FADE_IN_LIVE_OUT_FADE_OUT] = 0;
	counter[FADE_IN_LIVE_OUT_FADE_OUT] = 0;
	counter2[FADE_IN_LIVE_OUT_FADE_OUT] = 0;
	for(int i=0;i<NUMPIXELS;i++)
	{
		l_p[i]=p[i];
		p[i] = 0;
	}
}

void sequence::apply_fade_in_live_fade_out()
{
	double adjust_out = counter[FADE_IN_LIVE_OUT_FADE_OUT]/fx_fade_out;
	if(control[FADE_IN_LIVE_OUT_FADE_OUT]==0)
	{
		if(counter[FADE_IN_LIVE_OUT_FADE_OUT] == 0)
			for(int i =0;i<NUMPIXELS*3 ;i++)
			{
				p[i] = l_p[i];
			}
		counter[FADE_IN_LIVE_OUT_FADE_OUT]+=1;
		if(counter[FADE_IN_LIVE_OUT_FADE_OUT]>=fx_fade_in){
			control[FADE_IN_LIVE_OUT_FADE_OUT] = 1;
			counter[FADE_IN_LIVE_OUT_FADE_OUT] = 0;
		}
	}
	else
	{
		for(int i =0;i<NUMPIXELS*3 ;i++)
		{
			p[i] = l_p[i]-(unsigned char)((double)l_p[i]*adjust_out);
		}
		counter[FADE_IN_FADE_OUT]+=1;
		if(counter[FADE_IN_FADE_OUT]>=fx_fade_out){
			control[FADE_IN_FADE_OUT] = 0;
			counter[FADE_IN_FADE_OUT] = 0;
		}
	}
}

//STROBE_LIVE_FADE_IN_DEAD_FADE_OUT

void sequence::set_strobe_freq_fade_in_dead_fade_out(unsigned char f_in, unsigned char f_out)
{
	//fx_fade_in =
	control[STROBE_FREQ_FADE_IN_DEAD_FADE_OUT] = 0;
	counter[STROBE_FREQ_FADE_IN_DEAD_FADE_OUT] = fx_fade_in;
	counter2[STROBE_FREQ_FADE_IN_DEAD_FADE_OUT] = fx_fade_out;
}

void sequence::apply_strobe_freq_fade_in_dead_fade_out()
{
	if(control[STROBE_FREQ_FADE_IN_DEAD_FADE_OUT] == 0)
	{
		counter[STROBE_FREQ_FADE_IN_DEAD_FADE_OUT]-=1;
		if(counter[STROBE_FREQ_FADE_IN_DEAD_FADE_OUT] == 0)
		{
			control[STROBE_FREQ_FADE_IN_DEAD_FADE_OUT]  = 1;
			counter[STROBE_FREQ_FADE_IN_DEAD_FADE_OUT]  = fx_fade_out;
			for(int i =0;i<NUMPIXELS*3 ;i++)
			{
				p[i] = 0;
			}
		}
	}
	else
	{
		counter[STROBE_FREQ_FADE_IN_DEAD_FADE_OUT]-=1;
		if(counter[STROBE_FREQ_FADE_IN_DEAD_FADE_OUT] == 0)
		{
			counter[STROBE_FREQ_FADE_IN_DEAD_FADE_OUT]  = fx_fade_in;
			control[STROBE_FREQ_FADE_IN_DEAD_FADE_OUT]  = 0;
			for(int i =0;i<NUMPIXELS*3 ;i++)
			{
				p[i] = l_p[i];
			}
		}
	}
}





