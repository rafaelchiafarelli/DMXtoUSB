/*
 * DMXController.h
 *
 *  Created on: 22 de abr de 2020
 *      Author: rafae
 */

#ifndef DMXCONTROLLER_H_
#define DMXCONTROLLER_H_

#include "types.h"

class DMXController {
private:
	int32_t _DMX_dmxPreScale; // BAUD prescale factor for DMX speed.

	void send();
public:
	void *get_ptr();
	void Handler();
	DMXController();
	virtual ~DMXController();
};

#endif /* DMXCONTROLLER_H_ */
