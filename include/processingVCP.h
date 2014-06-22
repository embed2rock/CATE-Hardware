/*
 * processingVCP.h
 *
 *  Created on: 17/giu/2014
 *      Author: Antonio
 */

#ifndef PROCESSINGVCP_H_
#define PROCESSINGVCP_H_

#include "CateMessage.h"

#include "UsbVCPServerSender.h"
#include "CateMessage.h"

#include "FreeRTOS.h"
#include "CateMessage.h"


#include <stdlib.h>     /* malloc, free, rand */
#include <string.h> /* memset */
#include <unistd.h> /* close */

//handle della coda di input e output da VCP
extern xQueueHandle vcpQueueIn;
extern xQueueHandle vcpQueueOut;

void vTaskProcessingVCP( void * pvParameters );
void processSensorValues(cateMessage* msgToProcess);

#endif /* PROCESSINGVCP_H_ */
