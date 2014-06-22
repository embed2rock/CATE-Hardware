/*
 * processingVCPin.c
 *
 *  Created on: 17/giu/2014
 *      Author: Antonio
 */

//processa i messaggi giunti dal terminale android


#include "processingVCP.h"

void vTaskProcessingVCP( void * pvParameters )
{
	for(;;)
	{
		//messaggio ricevuto dal terminale android
		cateMessage* msgToProcess = (cateMessage*)malloc (sizeof(cateMessage));
		while (xQueueReceive( vcpQueueIn,	msgToProcess, 100) != pdPASS);

		switch(msgToProcess->header)
		{
			case READ_SENSOR:
				processSensorValues(msgToProcess);
			break;
			case SMS:

			break;
			case NETWORKING:

			break;
			case CALL:

			break;
			case HE_CMD:

			break;
			case OS_CMD:

			break;
			case NOTIFICATION:

			break;
			case INTRA_COM:

			break;
			case INTER_COM:

			break;

		}
	}

}

void processSensorValues(cateMessage* msgToProcess)
{
	uint16_t numOfMeasurements = ((msgToProcess->length)-9)/4;
	uint16_t index;
	float currentMeasurement;
	for (index=0;index<numOfMeasurements;index++)
	{
		memcpy(&currentMeasurement,&(msgToProcess->payload[(4*index)+9]), 4);
	}
}



