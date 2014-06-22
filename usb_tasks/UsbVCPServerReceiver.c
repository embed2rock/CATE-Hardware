/*
 * UsbVCPServerReceiver.c
 *
 *  Created on: 10/giu/2014
 *      Author: Antonio
 */

#include "USBVCPServerReceiver.h"

//gestisce task e delay
#include "task.h"
#include "FreeRTOS.h"
#include "CateMessage.h"
#include <string.h>
#include <stdlib.h>

#include "main.h"

//librerie necessarie per l'utilizzo della porta USB vcp
#include "../usb/usbd_cdc_vcp.h"
#include "../usb/usb_virtual_com_port.h"
#include "stm32f4xx_exti.h"
//fine librerie utilizzate per la VCP


void vTaskUsbVCPReceiver( void * pvParameters )
{
	uint8_t vcpBuffer[1000];
	int vcpLength;
	VCP_get_buffer(vcpBuffer);
	for( ;; )
	{
		vcpLength = VCP_get_buffer(vcpBuffer);


		if(vcpLength>0)
		{
			vTaskDelay(1000);
			onReceive(vcpBuffer,vcpLength);

		}
	}
}


/*
 *  Estrae dallo stream di byte ricevuti sulla USB, i messaggi 'cm'.
 *  I messaggi sono composti da header + lunghezza + payload.
 *  I messaggi, di tipo cateMessage, sono salvati nella coda circolare messageQueue
 *  tramite la funzione enqueueMessage.
 */

cateMessage* cm = NULL;
uint16_t partialPayloadLenght;
uint8_t* partialPayload;
messageStateType cateMessageState = COMPLETE;

void onReceive(uint8_t* buffer, uint16_t length) {
	// TODO Auto-generated method stub
	uint8_t target[1024];
	//ByteBuffer target;

	while (length > 0) {
		switch (cateMessageState) {
		//stato iniziale in cui ogni precedente ricezione è terminata
		case COMPLETE:
			cateMessageState = HEADER_RECEIVED;
			cm = newCateMessage();
			cm->header = buffer[0];

			memcpy (target, buffer, length);
			length--;
			memcpy (buffer, &target[1],  length);
			break;
		//leggo length del messaggio
		case HEADER_RECEIVED:
			if (length >= 2) {
				//operazioni eseguite se è giunto tutto il campo length
				cateMessageState = length_COMPLETE;
				cm->length = (uint16_t) (((uint16_t) buffer[1]) << 8 | buffer[0]);

				memcpy (target, buffer, length);
				length -= 2;
				memcpy (buffer, &target[2], length);
			} else {
				//operazioni eseguite se è giunto un solo byte del campo length
				cateMessageState = length_INCOMPLETE;
				cm->length = (uint16_t) ((uint16_t) buffer[0]);
				memcpy (target, buffer, length);
				length--;
				memcpy (buffer, &target[1], length);
			}
			break;
		//lettura del secondo byte del campo length a seguito di una nuova acquisizione da VCP
		case length_INCOMPLETE:
			//acquisizione del byte rimanente del campo length
			cm->length = (uint16_t) (cm->length | ((uint16_t) buffer[0]) << 8);
			cateMessageState = length_COMPLETE;
			memcpy (target, buffer, length);
			length--;

			memcpy (buffer, &target[1], length);
			break;
		//acquisizione del campo relativo al payload del messaggio
		case length_COMPLETE:
			if (length >= cm->length) {
				//controllo che sia giunto l'intero payload e lo acquisisco
				uint8_t* bufferPayload = (uint8_t*)malloc((cm->length)*sizeof(uint8_t));
				memcpy (target, buffer, length);
				length -= cm->length;
				memcpy (bufferPayload, target, cm->length);
				memcpy (buffer, target, length);

				cm->payload = bufferPayload;

				cateMessageState = COMPLETE;
				startActionDispatcher();
			} else {
				//se è giunta solo una parte del payload la salvo in partialPayload
				partialPayloadLenght = (uint16_t) (length);
				partialPayload = (uint8_t*)malloc(cm->length);
				memcpy (target, buffer, length);
				memcpy (partialPayload, target, length);
				length = 0;
				cateMessageState = PAYLOAD_INCOMPLETE;
			}
			break;
		//acquisisco una nuova parte del payload
		case PAYLOAD_INCOMPLETE:
			if (length >= cm->length - partialPayloadLenght) {
				//acquisisco tutto il payload rimanente, relativo al messaggio
				uint8_t* bufferPayload = (uint8_t*)malloc((cm->length) - partialPayloadLenght);


				memcpy (target, buffer, length);
				length -= (cm->length - partialPayloadLenght);
				memcpy (bufferPayload , target , cm->length-partialPayloadLenght );
				memcpy (&partialPayload[partialPayloadLenght], bufferPayload,cm->length	- partialPayloadLenght);

				memcpy (buffer,target, length);

				partialPayloadLenght = -1;
				cm->payload = partialPayload;
				//cancello la memoria puntata da bufferPayload
				free(bufferPayload);
				cateMessageState = COMPLETE;
				startActionDispatcher();
			} else {
				//acquisisco una parte del payload rimanente e torno nello stesso stato
				//per acquisisre il restante
				uint8_t* bufferPayload = (uint8_t*)malloc(length*sizeof(uint8_t));
				memcpy (target, buffer, length);
				memcpy (bufferPayload , target, length);
				memcpy (&partialPayload[partialPayloadLenght], bufferPayload, length);

				partialPayloadLenght += (uint16_t) (length);
				length = 0;
				cateMessageState = PAYLOAD_INCOMPLETE;
			}
			break;
		default:
			break;
		}
	}
}

void startActionDispatcher(){
	if(cm != NULL){

		//inserisco il messaggio cate nella lista dei messaggi in ingresso da VCP
		while (xQueueSendToBack( vcpQueueIn,cm,100) != pdPASS);

		//inserisco il messaggio cate nella lista dei messaggi in uscita su VCP per testare la ricezione in loopback
		//while (xQueueSendToBack( vcpQueueOut,cm,100) != pdPASS);

	}
}






