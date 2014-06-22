/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#include "UsbVCPServerReceiver.h"
#include "UsbVCPServerSender.h"
#include "processingVCP.h"

#include "usb/usb_virtual_com_port.h"

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "main.h"
#include "CateMessage.h"

#include <stdlib.h>     /* malloc, free, rand */
#include <string.h> /* memset */
#include <unistd.h> /* close */

#include "testTask.h"

/*
 * Set up the hardware
 */
static void prvSetupHardware( void );


/*-----------------------------------------------------------*/

int main(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Here the GPIOA module is initialized.
	 * We want to use PA0 as an input because
	 * the USER button on the board is connected
	 * between this pin and VCC.
	 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;		  // we want to configure PA0
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; 	  // we want it to be an input
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//this sets the GPIO modules clock speed
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   // this sets the pin type to push / pull (as opposed to open drain)
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;   // this enables the pulldown resistor --> we want to detect a high level
	GPIO_Init(GPIOA, &GPIO_InitStruct);


	/* Configure the hardware ready to run the test. */
	prvSetupHardware();
	static unsigned char ucParameterToPass;
	TaskHandle_t xHandle = NULL;

	while (!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
	{

	}

	/*	genero le code circolari da utilizzare per salvare i dati
	 * 	di input/output da VCP e input/output da rete
	 */

	vcpQueueIn = xQueueCreate( VCPQueueLength, sizeof(cateMessage));
	vcpQueueOut = xQueueCreate( VCPQueueLength, sizeof(cateMessage));

	netQueueIn = xQueueCreate( NETQueueLength, sizeof(cateMessage));
	netQueueOut = xQueueCreate( NETQueueLength, sizeof(cateMessage));


	 xTaskCreate( vTaskUsbVCPReceiver, "UsbVCPReceiver", 1024, &ucParameterToPass, tskIDLE_PRIORITY, &xHandle );

	 xTaskCreate( vTaskUsbVCPSender, "UsbVCPSender", 1024, &ucParameterToPass, tskIDLE_PRIORITY, &xHandle );

	 xTaskCreate( vTaskProcessingVCP, "ProcessingVCP", 1024, &ucParameterToPass, tskIDLE_PRIORITY, &xHandle );

	 xTaskCreate( testTask, "testTask", 1024, &ucParameterToPass, tskIDLE_PRIORITY, &xHandle );

	 // configASSERT( xHandle );


	/* Start the scheduler. */
	vTaskStartScheduler();

	for( ;; )
	{
	}
}
/*-----------------------------------------------------------*/



static void prvSetupHardware( void )
{
	/* Setup STM32 system (clock, PLL and Flash configuration) */
	SystemInit();
 	init_USB_VCP();
	/* Ensure all priority bits are assigned as preemption priority bits. */
	//NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );


}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{

}
/*-----------------------------------------------------------*/


/*-----------------------------------------------------------*/

void TIM3_IRQHandler( void )
{

}
/*-----------------------------------------------------------*/

void TIM2_IRQHandler( void )
{

}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

void EXTI9_5_IRQHandler(void)
{

}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{

}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{

}
/*-----------------------------------------------------------*/
