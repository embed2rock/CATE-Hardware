/*
 * usb_virtual_com_port.h
 *
 *  Created on: 18/mag/2014
 *      Author: mariobarbareschi
 */

#ifndef USB_VIRTUAL_COM_PORT_H_
#define USB_VIRTUAL_COM_PORT_H_

#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"
#include "usb_dcd_int.h"

#include "stm32f4xx_exti.h"

/*
 * The USB data must be 4 byte aligned if DMA is enabled. This macro handles
 * the alignment, if necessary (it's actually magic, but don't tell anyone).
 */
__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;

/*
 * Define prototypes for interrupt handlers here. The conditional "extern"
 * ensures the weak declarations from startup_stm32f4xx.c are overridden.
 */
#ifdef __cplusplus
 extern "C" {
#endif
void OTG_FS_IRQHandler(void);
void OTG_FS_WKUP_IRQHandler(void);
#ifdef __cplusplus
}
#endif

void init_USB_VCP();
void deinit_USB_VCP();

#endif /* USB_VIRTUAL_COM_PORT_H_ */
