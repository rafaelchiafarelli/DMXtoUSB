/*
 * raquet.h
 *
 *  Created on: 24 de set de 2019
 *      Author: rafae
 */

#ifndef RACKET_H_
#define RACKET_H_

#include "arduino.h"

#define DEBOUNCE_ON 5
#define DEBOUNCE_OFF 5

typedef enum{
	launching,
	locked_up,
	locked_down,
	none
}RACKET_STATUS_TYPE;

class racket {

	RACKET_STATUS_TYPE state;
	int btn_p;
	int sens_p;
	int coilH_p;
	int coilL_p;
	int debounce_on;
	int debounce_off;

public:
	void handler();

	racket(int btn_pin, int sens_pin, int coilH_pin, int coilL_pin);
	virtual ~racket();
};

#endif /* RACKET_H_ */
