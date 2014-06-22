/*
 * operationRequests.c
 *
 *  Created on: 18/giu/2014
 *      Author: Antonio
 */


#include "operationRequests.h"
#include <stdlib.h>     /* malloc, free, rand */
#include <string.h> /* memset */


cateMessage* sensorsOneRead(uint64_t sensorsMask)
{

	cateMessage* reqSensors = (cateMessage*)malloc(sizeof(cateMessage));

	reqSensors->header = READ_SENSOR;
	reqSensors->payload = (uint8_t*)malloc(9);
	reqSensors->length = 9;

	reqSensors->payload[0] = SENSOR_ONE_READ;
	memcpy(&(reqSensors->payload[1]), &sensorsMask, 8);
	return reqSensors;

}

cateMessage* sensorsPeriodicRead(uint64_t sensorsMask, uint32_t period)
{

	cateMessage* reqSensors = (cateMessage*)malloc(sizeof(cateMessage));

	reqSensors->header = READ_SENSOR;
	reqSensors->payload = (uint8_t*)malloc(13);
	reqSensors->length = 13;

	reqSensors->payload[8] = SENSOR_PERIODIC_READ;
	memcpy(reqSensors->payload, &sensorsMask, 8);
	return reqSensors;

}
