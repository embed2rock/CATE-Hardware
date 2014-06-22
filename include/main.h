/*
 * main.h
 *
 *  Created on: 17/giu/2014
 *      Author: Gruppo2
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "semphr.h"

#define	VCPQueueLength	1024
#define NETQueueLength 1024


//handle della coda di input e output da VCP
xQueueHandle vcpQueueIn;
xQueueHandle vcpQueueOut;

//handle della coda di input e output da rete
xQueueHandle netQueueIn;
xQueueHandle netQueueOut;





#endif /* MAIN_H_ */
