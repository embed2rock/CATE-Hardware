/*
 * processingNet.c
 *
 *  Created on: 17/giu/2014
 *      Author: Gruppo2
 */


#include "processingVCP.h"

void vTaskProcessingNET( void * pvParameters )
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
