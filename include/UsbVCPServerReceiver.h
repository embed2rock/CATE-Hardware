/*
 * UsbVCPServerReceiver.h
 *
 *  Created on: 10/giu/2014
 *      Author: Antonio
 */

#ifndef USBVCPSERVERRECEIVER_H_
#define USBVCPSERVERRECEIVER_H_

#include "FreeRTOS.h"
#include "semphr.h"



void vTaskUsbVCPReceiver( void * pvParameters );
void onReceive(uint8_t* buffer, uint16_t length);
void startActionDispatcher();

extern xQueueHandle vcpQueueIn;
extern xQueueHandle vcpQueueOut;

typedef enum {
	HEADER_RECEIVED, length_INCOMPLETE, length_COMPLETE, PAYLOAD_INCOMPLETE, COMPLETE, DISPATCHED
}messageStateType;


#endif /* USBVCPSERVERRECEIVER_H_ */
