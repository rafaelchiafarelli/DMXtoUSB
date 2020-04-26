/*
 * InductiveSensor.cpp
 *
 *  Created on: 26 de set de 2019
 *      Author: rafae
 */

#include "InductiveSensor.h"

InductiveSensor::InductiveSensor() {
	// TODO Auto-generated constructor stub
	  Serial.begin(9600);
	  pinMode(pulsePin, OUTPUT);
	  digitalWrite(pulsePin, LOW);
	  pinMode(capPin, INPUT);
	  pinMode(buz, OUTPUT);
	  digitalWrite(buz, LOW);
	  pinMode(led, OUTPUT);
}

InductiveSensor::~InductiveSensor() {
	// TODO Auto-generated destructor stub
}


int InductiveSensor::handler()
{
  int minval=1023;
  int maxval=0;
  int ret;
  long unsigned int sum=0;
  for (int i=0; i<256; i++)
  {

    //reset the capacitor
    pinMode(capPin,OUTPUT);
    digitalWrite(capPin,LOW);
    delayMicroseconds(20);
    pinMode(capPin,INPUT);
    applyPulses();

    //read the charge of capacitor
    int val = analogRead(capPin);   //takes 13x8=104 microseconds
    minval = min(val,minval);
    maxval = max(val,maxval);
    sum+=val;

    long unsigned int cTime=millis();
    char buzState=0;
    if (cTime<pTime+10)
    {
      if (diff>0)
        buzState=1;
      else if(diff<0)
        buzState=2;
    }
    if (cTime>pTime+buzPeriod)
    {
      if (diff>0)
      buzState=1;
      else if (diff<0)
      buzState=2;
      pTime=cTime;
    }
    if (buzPeriod>300)
    buzState=0;

    if (buzState==0)
    {
    	ret = 0;

    }
    else if (buzState==1)
    {
    	ret =1;
    }

    else if (buzState==2)
    {
    	ret =1;
    }
  }

  //subtract minimum and maximum value to remove spikes
  sum-=minval;
  sum-=maxval;

  if (sumExpect==0)
  sumExpect=sum<<6;   //set sumExpect to expected value
  long int avgsum=(sumExpect+32)>>6;
  diff=sum-avgsum;
  if (abs(diff)<avgsum>>10)
  {
    sumExpect=sumExpect+sum-avgsum;
    ignor=0;
  }
  else
    ignor++;
  if (ignor>64)
  {
    sumExpect=sum<<6;
    ignor=0;
  }
  if (diff==0)
    buzPeriod=1000000;
  else
  buzPeriod=avgsum/(2*abs(diff));

  return ret;
}

void InductiveSensor::applyPulses()
{
    for (int i=0;i<3;i++)
    {
      digitalWrite(pulsePin,HIGH); //take 3.5 uS
      delayMicroseconds(3);
      digitalWrite(pulsePin,LOW);  //take 3.5 uS
      delayMicroseconds(3);
    }
}
