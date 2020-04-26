/*
 * generalpurpose_types.h
 *
 *  Created on: 18 de set de 2019
 *      Author: rafae
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "stdint.h"

typedef enum {
	TRAIN_BACK,
	TRAIN_FWRD,
	FLASH,
	SMOTH_BLINK,
	STROBE,
	STROBE_TRAIN,
	AWESOME_BLINK,
	SMOOTHY_TRAIN,
	RAMDOM,

	NONE

}fx;

class alignas(3) color
{
public:
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

class alignas(3) screen
{
public:
	color pixel[NUMPIXELS];
};








#endif /* GENERALPURPOSE_TYPES_H_ */
