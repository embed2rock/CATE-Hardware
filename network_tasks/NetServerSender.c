/*
 * NetServerSender.c
 *
 *  Created on: 18/giu/2014
 *      Author: Antonio
 */

#include "NetServerSender.h"



void vTaskNetServerSender( void * pvParameters )
{
	//messaggio strutturato da inviare al device android
	//cateMessage* msgToSend = (cateMessage*)malloc (sizeof(cateMessage));

	for (;;)
	{
//		while (xQueueReceive( netQueueOut,	msgToSend, 100) != pdPASS);
//		//messaggio come stringa di byte da inviare tramite VCP
//		uint8_t* bytesToSend;
//		size_t dimToSend = (size_t)((msgToSend->length)+3);
//		bytesToSend = (uint8_t*)malloc(dimToSend);
//
//		//concatenazione dell'header alla sequenza di Byte da inviare
//		memcpy ( &bytesToSend[0], &(msgToSend->header), 1 );
//		//concatenazione della length alla sequenza di Byte da inviare
//		memcpy ( &bytesToSend[1], &(msgToSend->length), 2 );
//		//concatenazione del payload alla sequenza di Byte da inviare
//		memcpy ( &bytesToSend[3], msgToSend->payload, msgToSend->length );
//
//		vTaskDelay(100);
//		//TODO: operazione di invio del messaggio sulla rete
	}

}






