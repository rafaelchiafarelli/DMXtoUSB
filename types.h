/*
 * types.h
 *
 *  Created on: 22 de abr de 2020
 *      Author: rafae
 */

#ifndef TYPES_H_
#define TYPES_H_
typedef enum{
	FADE_IN_FADE_OUT,
	FADE_IN_DEAD_OUT,
	FADE_IN_LIVE_OUT,
	FADE_IN_LIVE_OUT_FADE_OUT,

	STROBE_LIVE_FADE_IN_DEAD_FADE_OUT,
	STROBE_FREQ_FADE_IN_DEAD_FADE_OUT,
	STROVE_FREQ_INCREASE_FADE_IN



}effect_type;

typedef enum{
	DMX_TIME = 0,
	SERIAL_TIME,
	NEOPIXEL_TIME

}state_type;


#endif /* TYPES_H_ */
