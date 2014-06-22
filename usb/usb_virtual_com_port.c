/*
 * usb_virtual_com_port.c
 *
 *  Created on: 18/mag/2014
 *      Author: mariobarbareschi
 */

#include "usb_virtual_com_port.h"

void init_USB_VCP() {

	USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb,
			&USR_cb);
}

void deinit_USB_VCP() {
	USBD_DeInit(&USB_OTG_dev);
}

/*
 * Interrupt Handlers
 */

void OTG_FS_IRQHandler(void) {
	USBD_OTG_ISR_Handler(&USB_OTG_dev);
}

void OTG_FS_WKUP_IRQHandler(void) {
	if (USB_OTG_dev.cfg.low_power) {
		*(uint32_t *) (0xE000ED10) &= 0xFFFFFFF9;
		SystemInit();
		USB_OTG_UngateClock(&USB_OTG_dev);
	}
	EXTI_ClearITPendingBit(EXTI_Line18);
}
