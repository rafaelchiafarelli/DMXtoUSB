/*
 * Manager.h
 *
 *  Created on: 27 de abr de 2020
 *      Author: rafae
 */

#ifndef MANAGER_H_
#define MANAGER_H_

class Manager {
private:
	bool Failure;
	unsigned int max_clk_count;
	unsigned int elapsed_time;
public:
	bool get_failure(){return Failure;};
	void start();
	void end();
	int get_elapsed_time(){return elapsed_time;}
	Manager();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
