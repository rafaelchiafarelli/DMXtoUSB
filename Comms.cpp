/*
 * Comms.cpp
 *
 *  Created on: 26 de set de 2019
 *      Author: rafae
 */

#include "Comms.h"

Comms::Comms() {
	// TODO Auto-generated constructor stub
inserted_variables = 0;
memset(names,0,NUMBER_OF_VARIABLES*NAMES_MAX_SIZE);
memset(ptr_var,0,NUMBER_OF_VARIABLES);

}

Comms::~Comms() {
	// TODO Auto-generated destructor stub
}
/*
 * put a variable adress to be sended, so, during handler, the variable will be read and concatenated with the rest
 *
 * */
bool Comms::put_var(void *ptr,char *name,int name_size, var_type type_of_var)
{
	if(inserted_variables > NUMBER_OF_VARIABLES)
		return false;
	inserted_variables++;
	memcpy(names[inserted_variables],name,name_size);
	ptr_var[inserted_variables] = ptr;

	return true;
}
void Comms::handler()
{

}
