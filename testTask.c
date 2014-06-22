/*
 * testTask.c
 *
 *  Created on: 18/giu/2014
 *      Author: Antonio
 */
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "CateMessage.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include <stdlib.h>     /* malloc, free, rand */
#include <string.h> /* memset */
#include <unistd.h> /* close */
#include "UsbVCPServerReceiver.h"
#include "UsbVCPServerSender.h"
#include "processingVCP.h"

#include "usb/usb_virtual_com_port.h"

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "testTask.h"

//librerie necessarie per l'utilizzo della porta USB vcp
#include "usb/usbd_cdc_vcp.h"
#include "usb/usb_virtual_com_port.h"
#include "stm32f4xx_exti.h"
//fine librerie utilizzate per la VCP

#include "FreeRTOS.h"
#include "task.h"

#include <stdlib.h>     /* malloc, free, rand */
#include <string.h> /* memset */
#include <unistd.h> /* close */

#include "operationRequests.h"
#include "CateMessage.h"

void testTask( void * pvParameters )
{

	uint64_t mask = ACCELERATOR_X;
	//uint64_t mask = 0xFFFFFFFFFFFFFFFF;
	cateMessage* reqSensors;

	for( ;; )
	{
		vTaskDelay(500);
		while (!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));
		reqSensors = sensorsOneRead(mask );
		vTaskDelay(500);
		while (xQueueSendToBack( vcpQueueOut,reqSensors,100) != pdPASS);
	}



}
