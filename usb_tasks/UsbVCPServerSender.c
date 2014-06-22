/*
 * UsbVCPServerSender.c
 *
 *  Created on: 10/giu/2014
 *      Author: Antonio
 */

#include "UsbVCPServerSender.h"
#include "CateMessage.h"

//librerie necessarie per l'utilizzo della porta USB vcp
#include "../usb/usbd_cdc_vcp.h"
#include "../usb/usb_virtual_com_port.h"
#include "stm32f4xx_exti.h"
//fine librerie utilizzate per la VCP

#include "FreeRTOS.h"
#include "task.h"

#include <stdlib.h>     /* malloc, free, rand */
#include <string.h> /* memset */
#include <unistd.h> /* close */


void vTaskUsbVCPSender( void * pvParameters )
{
	//messaggio strutturato da inviare al device android
	cateMessage* msgToSend = (cateMessage*)malloc (sizeof(cateMessage));

	for (;;)
	{


		while (xQueueReceive( vcpQueueOut,	msgToSend, 100) != pdPASS);
		//messaggio come stringa di byte da inviare tramite VCP
		uint8_t* bytesToSend;
		size_t dimToSend = (size_t)((msgToSend->length)+3);
		bytesToSend = (uint8_t*)malloc(dimToSend);

		//concatenazione dell'header alla sequenza di Byte da inviare
		memcpy ( &bytesToSend[0], &(msgToSend->header), 1 );
		//concatenazione della length alla sequenza di Byte da inviare
		memcpy ( &bytesToSend[1], &(msgToSend->length), 2 );
		//concatenazione del payload alla sequenza di Byte da inviare
		memcpy ( &bytesToSend[3], msgToSend->payload, msgToSend->length );
		destroyCateMessage(msgToSend);

		vTaskDelay(100);
		VCP_send_buffer(bytesToSend,(int)dimToSend);
		free(bytesToSend);


	}



}
