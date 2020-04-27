/*
 * PCP.cpp
 *
 *  Created on: 22 de abr de 2020
 *      Author: rafae
 */
#include "Arduino.h"
#include "PCP.h"

PCP::PCP(DMXController *p, sequence *S) {
	// TODO Auto-generated constructor stub
	ptr_d = (char **)(p->get_ptr());
	ptr_l = S->get_ptr();
	seq = S;
	Serial.begin(250000);
	Serial.setTimeout(20);
	Serial.flush();
}

PCP::~PCP() {
	// TODO Auto-generated destructor stub
}

void PCP::Handler(){
	Serial.begin(250000);
	Serial.println("GETdata");
	Serial.flush();

	int idx;
	if(FindStartPtr())
	{
	idx = Serial.read();
		if(idx>0){
			if(idx<5)
				last_msg = read_dmx(idx);
			else
				last_msg = read_LED();
		}
	}
}

bool PCP::is_channel()
{
	int r;
	bool ret = false;
	r = Serial.read();

	if((char)r == ',')
	{
		r = Serial.read();
		if((char)r == 'c')
		{
			r = Serial.read();
			if((char)r == 'h')
			{
				r = Serial.read();
				if((char)r == ':')
				{
					ret = true;
				}
			}
		}
	}
	return ret;
}


bool PCP::read_dmx(int idx)
{
	int j=0,r = 0;
	if(is_channel())
		while(j<MAX_DMX_CHANNELS)
		{
			r = Serial.read();
			ptr_d[idx][j] = (char)r;
			j++;
		}
	return FindTerminator();
}

bool PCP::read_LED()
{
	int j=0,r=0;
	if(is_channel())
		while(j<NUMPIXELS*3)
		{
			r = Serial.read();
			ptr_l[j] = (char)r;
			j++;
		}
	r = Serial.read();
	if((char)r == 'f')
	{
		r = Serial.read();//"}]>",msg_ptr,MAX_FILE_SIZE);
		if((char)r == 'x')
		{
			r = Serial.read();//"}]>",msg_ptr,MAX_FILE_SIZE);
			if((char)r == ':')
			{
				unsigned char efct = Serial.read();
				unsigned char f_in = Serial.read();
				unsigned char f_out = Serial.read();
				seq->set_effect((effect_type)efct,f_in,f_out);
			}
		}
	}
	return FindTerminator();
}
bool PCP::FindStartPtr()
{
	bool ret = false;
	int r=0;
	if(Serial.find((char *)"<un:[{"))
	{
		r = Serial.read();
		if((char)r == 'i')
		{
			r = Serial.read();
			if((char)r == 'd')
			{
				r = Serial.read();
				if((char)r == 'x')
				{
					r = Serial.read();
					if((char)r == ':')
					{
					ret = true;
					}
				}
			}
		}
	}
	return ret;
}
bool PCP::FindTerminator()
{
	bool ret = false;
	int r = 0;
	r = Serial.read();//"}]>",msg_ptr,MAX_FILE_SIZE);
	if((char)r == '}')
	{
		r = Serial.read();//"}]>",msg_ptr,MAX_FILE_SIZE);
		if((char)r == ']')
		{
			r = Serial.read();//"}]>",msg_ptr,MAX_FILE_SIZE);
			if((char)r == '>')
			{
				ret = true;
			}
		}
	}
	return ret;
}

