/*
 * UsbVCPServerSender.h
 *
 *  Created on: 10/giu/2014
 *      Author: Antonio
 */

#ifndef USBVCPSERVERSENDER_H_
#define USBVCPSERVERSENDER_H_

#include "FreeRTOS.h"
#include "semphr.h"

void vTaskUsbVCPSender( void * pvParameters );

//handle della coda di input e output da VCP
//extern xQueueHandle vcpQueueIn;
extern xQueueHandle vcpQueueOut;

#endif /* USBVCPSERVERSENDER_H_ */
