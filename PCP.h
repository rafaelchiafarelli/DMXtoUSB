/*
 * PCP.h
 *
 *  Created on: 22 de abr de 2020
 *      Author: rafae
 */

#ifndef PCP_H_
#define PCP_H_

#include "types.h"
#include "DMXController.h"
#include "sequence.h"
class PCP {
private:
	char **ptr_d;
	unsigned char *ptr_l;
	char msg_raw[MAX_FILE_SIZE];
	int get_idx(char *d, int s);
	void set_channels(char *f,char **d, int stride,int size);
public:
	PCP(DMXController *p, sequence *S);
	void restart_serial(){Serial.begin(9600);};
	void Handler();
	virtual ~PCP();
};

#endif /* PCP_H_ */
