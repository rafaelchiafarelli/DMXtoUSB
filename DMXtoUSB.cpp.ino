/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */
#include "Arduino.h"
#include "string.h"

typedef enum{
	SENDING = 0,
	STOPPED = 1,
	INVALID
}DMX_STATUS_TYPE;

//global global variables
#define MAX_DMX_CHANNELS 512
#define MAX_DMX_UNIVERSES 3
#define DMXSPEED 250000L
unsigned char dmx_data[MAX_DMX_UNIVERSES][MAX_DMX_CHANNELS];
DMX_STATUS_TYPE dmx_universe_1;
DMX_STATUS_TYPE dmx_universe_2;
DMX_STATUS_TYPE dmx_universe_3;

// calculate prescaler from baud rate and cpu clock rate at compile time.
// This is a processor specific formular from the datasheet.
// It implements rounding of ((clock / 16) / baud) - 1.
#define CalcPreScale(B) (((((F_CPU) / 8) / (B)) - 1) / 2)

const int32_t _DMX_dmxPreScale = CalcPreScale(DMXSPEED); // BAUD prescale factor for DMX speed.
int get_idx(char *d, int s);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
	// TODO Auto-generated constructor stub
	memset(dmx_data[0],0,MAX_DMX_CHANNELS);
	memset(dmx_data[1],0,MAX_DMX_CHANNELS);
	memset(dmx_data[2],0,MAX_DMX_CHANNELS);

	dmx_universe_1 = STOPPED;
	dmx_universe_2 = STOPPED;
	dmx_universe_3 = STOPPED;


  Serial.begin(9600);

  for(int i =0; i< 512; i++)
  {
	  if(i<255)
	  {
		  dmx_data[0][i] = 15;
		  dmx_data[1][i] = 15;
		  dmx_data[2][i] = 15;

	  }
	  else{
		  dmx_data[0][i] = 240;
		  dmx_data[1][i] = 240;
		  dmx_data[2][i] = 240;

	  }

  }

}
#define MAX_FILE_SIZE 2500
char msg_raw[MAX_FILE_SIZE];
char msg[MAX_FILE_SIZE];

// the loop function runs over and over again forever
void loop() {


	if(dmx_universe_1 == STOPPED || dmx_universe_2 == STOPPED || dmx_universe_3 == STOPPED)
	{
		send();
	}

		if(Serial.find('<'))
		{
			Serial.setTimeout(70);
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
		    	set_channels(msg,idx,j);
		    }

		}


	delay(50);


}

void set_channels(char *f, int stride,int size)
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
            	dmx_data[stride][j] = (unsigned char )ret;
            	j++;
        	}
        	break;
        }
    }
}

int get_idx(char *d, int s)
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

/*
 *
 * LOCAL GLOBAL ROUTINES AND INTERRUPT SERVICE ROUTINES
 *
 * */
void send(){
	//pre-configure the channels registers (don´t activate yet)

	UCSR1A = 0;//
    UBRR1H = _DMX_dmxPreScale >> 8;
    UBRR1L = _DMX_dmxPreScale;
    UCSR1C = SERIAL_8N2; // send with 2 stop bits for compatibility

	UCSR2A = 0;
    UBRR2H = _DMX_dmxPreScale >> 8;
    UBRR2L = _DMX_dmxPreScale;
    UCSR2C = SERIAL_8N2; // send with 2 stop bits for compatibility

	UCSR3A = 0;
    UBRR3H = _DMX_dmxPreScale >> 8;
    UBRR3L = _DMX_dmxPreScale;
    UCSR3C = SERIAL_8N2; // send with 2 stop bits for compatibility

	/*
	 * send high into all the out pins
	 *
	 * wait 100us
	 * send low into all the out pins
	 * wait 88us
	 * send high into all the out pins
	 * wait 8us
	 * send high into all the out pins
	 * wait 44us
	 * send high into all the out pins
	 * wait 3us
	 * */
    //send the start package
    DDRD = 255;
    DDRH = 255;
    DDRJ = 255;

    PORTD = 8;
    PORTJ = 2;
    PORTH = 2;

    delayMicroseconds(100);
    PORTD = 0;
    PORTJ = 0;
    PORTH = 0;

    delayMicroseconds(88);
    PORTD = 8;
    PORTJ = 2;
    PORTH = 2;

    delayMicroseconds(8);
    PORTD = 0;
    PORTJ = 0;
    PORTH = 0;

    delayMicroseconds(44);
    PORTD = 8;
    PORTJ = 2;
    PORTH = 2;




    //enable all the channels

    UCSR1B = ((1 << TXEN1) | (1 << UDRIE1));
    UCSR2B = ((1 << TXEN2) | (1 << UDRIE2));
    UCSR3B = ((1 << TXEN3) | (1 << UDRIE3));


	dmx_universe_1 = SENDING;
	dmx_universe_2 = SENDING;
	dmx_universe_3 = SENDING;

	//load the send registers
    UDR1 = dmx_data[0][0];
    UDR2 = dmx_data[1][0];
    UDR3 = dmx_data[2][0];


}




// this interrupt occurs after data register was emptied by handing it over to the shift register.
ISR(USART1_UDRE_vect)
{
	static int counter= 1;
	UDR1 = dmx_data[0][counter];
	counter++;
	if(counter>=MAX_DMX_CHANNELS){
		counter = 1;
		UCSR1B = ((0 << TXEN1) | (0 << UDRIE1));
		dmx_universe_1 = STOPPED;
	}
} // ISR(USARTn_UDRE_vect)

// this interrupt occurs after data register was emptied by handing it over to the shift register.
ISR(USART2_UDRE_vect)
{
	static int counter= 1;
	UDR2 = dmx_data[1][counter];
	counter++;
	if(counter>=MAX_DMX_CHANNELS){
		counter = 1;
		UCSR2B = ((0 << TXEN2) | (0 << UDRIE2));
		dmx_universe_2 = STOPPED;

	}
} // ISR(USARTn_UDRE_vect)

// this interrupt occurs after data register was emptied by handing it over to the shift register.
ISR(USART3_UDRE_vect)
{
	static int counter= 1;
	UDR3 = dmx_data[2][counter];
	counter++;
	if(counter>=MAX_DMX_CHANNELS){
		counter = 1;
		UCSR3B = ((0 << TXEN3) | (0 << UDRIE3));
		dmx_universe_3 = STOPPED;
	}
} // ISR(USARTn_UDRE_vect)




