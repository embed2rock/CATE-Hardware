/*
 * NetworkMessage.h
 *
 *  Created on: 18/giu/2014
 *      Author: Antonio
 */

#ifndef NETWORKMESSAGE_H_
#define NETWORKMESSAGE_H_




#include <string.h>
#include <stdlib.h>
#include "FreeRTOS.h"

typedef struct {
	uint8_t type;
	uint16_t length;
	uint8_t* payload;
}networkMessage;


#endif /* NETWORKMESSAGE_H_ */
