/*
 * Comms.h
 *
 *  Created on: 26 de set de 2019
 *      Author: rafae
 */

#ifndef COMMS_H_
#define COMMS_H_
/*
 * This is the protocol for the communication array.
 * In order to communicate with the raspberry pi, we need to have a structure so, when we transmitt we know
 * how long it takes.
 * It is imperative that we send messages and receive messages in a ordely fashion
 *
 * */
#include "string.h"
#define NUMBER_OF_VARIABLES 50
#define NAMES_MAX_SIZE 8
typedef enum
{
	Integer,
	UnsignedInt,
	Char,
	UnsignedChar,
	Float,
	Double,
	String

}var_type;

typedef struct
{
	char begin[3];
	char msg_number[6];
	char end[3];
}header_type;

typedef struct
{
	header_type h;
	char body[100];
	char footer[10];
}msg;
class Comms {
	char names[NUMBER_OF_VARIABLES][NAMES_MAX_SIZE];
	void *ptr_var[NUMBER_OF_VARIABLES];
	int inserted_variables;
public:
	// put var into stream to be outed
	bool put_var(void *ptr,char *name,int name_size, var_type type_of_var);
	void handler();
	Comms();
	virtual ~Comms();
};

#endif /* COMMS_H_ */
