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
	unsigned char fx;
	unsigned char fade_out;
	unsigned char fade_in;
	sequence *seq;
	int get_idx(char *d, int s);
	bool is_channel();
	bool read_dmx(int idx);
	bool read_LED();
	bool FindStartPtr();
	bool FindTerminator();
	void set_channels(char *f,char **d, int stride,int size);
	bool last_msg;
public:
	bool get_last_msg_status(){return last_msg;};
	PCP(DMXController *p, sequence *S);
	void restart_serial(){Serial.begin(9600);};
	void Handler();
	virtual ~PCP();
};

#endif /* PCP_H_ */
