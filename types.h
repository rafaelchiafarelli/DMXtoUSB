/*
 * types.h
 *
 *  Created on: 22 de abr de 2020
 *      Author: rafae
 */

#ifndef TYPES_H_
#define TYPES_H_
//global global macros
#define MAX_DMX_CHANNELS 512
#define MAX_DMX_UNIVERSES 3
#define MAX_FILE_SIZE 1200
#define DMXSPEED 250000L

typedef enum{
	DMX_TIME = 0,
	SERIAL_TIME,
	NEOPIXEL_TIME

}state_type;


#endif /* TYPES_H_ */
