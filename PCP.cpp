/*
 * PCP.cpp
 *
 *  Created on: 22 de abr de 2020
 *      Author: rafae
 */
#include "Arduino.h"
#include "PCP.h"

PCP::PCP(DMXController *p) {
	// TODO Auto-generated constructor stub
	ptr_d = (char **)(p->get_ptr());
}

PCP::~PCP() {
	// TODO Auto-generated destructor stub
}

void PCP::Handler(){

	if(Serial.find('<'))
	{
		int a = Serial.readBytesUntil('>',msg_raw,MAX_FILE_SIZE);
		Serial.print(a,10);
		int j =0;
		for(int i = 0; i<MAX_FILE_SIZE; ++i)
		{
			if ((msg_raw[i] >= 'a' && msg_raw[i]<='z') ||
					(msg_raw[i] >= 'A' && msg_raw[i]<='Z') ||
					(msg_raw[i] >= '0' && msg_raw[i]<='9') ||
					(msg_raw[i] == ',') ||(msg_raw[i] == ':')
					)
			{
				if(msg_raw[i] == ',')
				msg[j++] = ' ';
				else
				msg[j++] = msg_raw[i];
			}
		}
		int idx = get_idx(msg,j);
		if(idx>=0)
		{
			set_channels(msg,ptr_d,idx,j);
		}
	}
}


void PCP::set_channels(char *f,char **d, int stride,int size)
{
	int j,ret = -1;
	char res[4];
	char *ptr;
    for(ptr=f; ptr<ptr+size; ptr++)
    {
        if (*ptr == 'c' && *(ptr+1) =='h')
        {
        	j=0;
        	ptr = ptr+3;
        	while(j<MAX_DMX_CHANNELS)
        	{
        		memset(res,0,4);
        		int k;
            	for( k=0; k<4; k++)
            	{
            		if(*(ptr+k) != ' '){
            			res[k] = *(ptr+k);

            		}
            		else
            		{
            			break;
            		}
            	}
            	ptr = ptr+k+1;
            	ret = atoi(res);
            	d[stride][j] = (unsigned char )ret;
            	j++;
        	}
        	break;
        }
    }
}

int PCP::get_idx(char *d, int s)
{
	int j,k,ret = -1;
    for(int i = 0; i<s; ++i)
    {
    	j = i +1;
    	k = j +1;
        if ((d[i] == 'i' && d[j]=='d' && d[k] == 'x'))
        {
        	ret = atoi(&d[k+1]);
        	break;
        }

    }
    return ret;
}
