/*
 * InductiveSensor.h
 *
 *  Created on: 26 de set de 2019
 *      Author: rafae
 */

#ifndef INDUCTIVESENSOR_H_
#define INDUCTIVESENSOR_H_
#include "Arduino.h"

#define capPin A5
#define buz 9
#define pulsePin A4

#define led 10


class InductiveSensor {
public:
	long unsigned int sumExpect=0; //running sum of 64 sums
	long unsigned int ignor=0;   //number of ignored sums
	long int diff=0;        //difference between sum and avgsum
	long unsigned int pTime=0;
	long unsigned int buzPeriod=0;
	int handler();
	void applyPulses();
	InductiveSensor();
	virtual ~InductiveSensor();
};



#endif /* INDUCTIVESENSOR_H_ */
