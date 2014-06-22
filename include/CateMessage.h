/*
 * CateMessage.h
 *
 *  Created on: 09/giu/2014
 *      Author: Gruppo2
 */

#ifndef CATEMESSAGE_H_
#define CATEMESSAGE_H_

#include "FreeRTOS.h"

#define MAX_MESSAGE_LENGHT 1024


typedef struct {
	uint8_t header;
	uint16_t length;
	uint8_t* payload;
}cateMessage;


	/*
	 * Definitions for the first header byte, the command
	 */

#define READ_SENSOR 		0x00
#define SMS 				0x01 //inivio, registrazione su un particolare numero
#define NETWORKING			0x02
#define CALL				0x03
#define HE_CMD				0x04 //accendi il led, alza volume, play, stop, display, etc. etc.
#define OS_CMD				0x05 //stessi comandi file linux (mkdir, touch, write, read, seek, etc.)
#define NOTIFICATION		0x06 //print su activity, scan su activity, ballon, notification, etc.
#define INTRA_COM			0x07 //print su activity, scan su activity, ballon, notification, etc.
#define INTER_COM			0x08 //print su activity, scan su activity, ballon, notification, etc.


	/*
	 * Definitions for the sensor field type, the command
	 */

#define ACCELERATOR_X				0x0000000000000001
#define ACCELERATOR_Y				0x0000000000000002
#define ACCELERATOR_Z				0x0000000000000004
#define LIGHT						0x0000000000000008
#define GRAVITY_X					0x0000000000000010
#define GRAVITY_Y					0x0000000000000020
#define GRAVITY_Z					0x0000000000000040
#define TEMPERATURE					0x0000000000000080
#define GYROSCOPE_X					0x0000000000000100
#define GYROSCOPE_Y					0x0000000000000200
#define GYROSCOPE_Z					0x0000000000000400
#define PROXIMITY					0x0000000000000800
#define MAGNETIC_X					0x0000000000001000
#define MAGNETIC_Y					0x0000000000002000
#define MAGNETIC_Z					0x0000000000004000
#define HUMIDITY					0x0000000000008000
#define PRESSURE					0x0000000000010000

	/*
	 * Definitions for the sensors read command option
	 */

#define SENSOR_ONE_READ						0x00
#define SENSOR_PERIODIC_READ				0x01
#define SENSOR_EVENT_READ					0x02

#define SENSOR_UNREGISTER_PERIODIC_READ		0x80 | SENSOR_PERIODIC_READ
#define SENSOR_UNREGISTER_EVENT_READ		0x80 | SENSOR_EVENT_READ

cateMessage* newCateMessage();
void destroyCateMessage(cateMessage* inMessage);


#endif /* CATEMESSAGE_H_ */
