/*
 * DMXController.cpp
 *
 *  Created on: 22 de abr de 2020
 *      Author: rafae
 */
#include "Arduino.h"
#include "DMXController.h"

typedef enum{
	SENDING = 0,
	STOPPED = 1,
	INVALID
}DMX_STATUS_TYPE;


// calculate prescaler from baud rate and cpu clock rate at compile time.
// This is a processor specific formular from the datasheet.
// It implements rounding of ((clock / 16) / baud) - 1.
#define CalcPreScale(B) (((((F_CPU) / 8) / (B)) - 1) / 2)

unsigned char dmx_data[MAX_DMX_UNIVERSES][MAX_DMX_CHANNELS];

DMX_STATUS_TYPE dmx_universe_1;
DMX_STATUS_TYPE dmx_universe_2;
DMX_STATUS_TYPE dmx_universe_3;

DMXController::DMXController() {
	_DMX_dmxPreScale = CalcPreScale(DMXSPEED);
	memset(dmx_data[0],0,MAX_DMX_CHANNELS);
	memset(dmx_data[1],0,MAX_DMX_CHANNELS);
	memset(dmx_data[2],0,MAX_DMX_CHANNELS);

	dmx_universe_1 = STOPPED;
	dmx_universe_2 = STOPPED;
	dmx_universe_3 = STOPPED;
	/* -- debug -- */
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

DMXController::~DMXController() {
	// TODO Auto-generated destructor stub
}

void *DMXController::get_ptr(){
	return dmx_data;
}

void DMXController::Handler(){
	if(dmx_universe_1 == STOPPED || dmx_universe_2 == STOPPED || dmx_universe_3 == STOPPED)
	{
		send();
	}
}

void DMXController::send(){
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



