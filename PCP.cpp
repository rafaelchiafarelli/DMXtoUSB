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
	Serial.begin(9600);
	Serial.setTimeout(20);
	Serial.print("PCP iniciado");
	Serial.flush();
}

PCP::~PCP() {
	// TODO Auto-generated destructor stub
}

void PCP::Handler(){
	Serial.begin(9600);
	memset(msg_raw,0,MAX_FILE_SIZE);
	if(Serial.find('<'))
	{
		int r = Serial.readBytesUntil('>',msg_raw,MAX_FILE_SIZE);
		if(r>0){
			char *ptr;
			unsigned char idx = 0;
			for(ptr=msg_raw; ptr<ptr+MAX_FILE_SIZE; ptr++)
			{
				if ((*ptr == 'i' && *(ptr+1)=='d' && *(ptr+2) == 'x'))
				{
					idx = *(ptr+5);
				}
				if(idx<5)
				{
					if (*ptr == 'c' && *(ptr+1) =='h')
					{
						int j=0;
						ptr = ptr+5;

						while(j<MAX_DMX_CHANNELS)
						{
							ptr_d[idx][j] = *ptr;
							Serial.println((int)ptr_d[idx][j],10);
							Serial.flush();
							ptr++;
							j++;
						}
						break;
					}
				}
				else
				{
					if (*ptr == 'c' && *(ptr+1) =='h')
					{
						int j=0;
						ptr = ptr+5;

						while(j<NUMPIXELS*3)
						{
							ptr_l[j] = *ptr;
							Serial.println((int)ptr_l[j],10);
							Serial.flush();
							ptr++;
							j++;
						}
						break;
					}
				}
			}
		}
	}
}

