/*
 * NetServerSender.h
 *
 *  Created on: 18/giu/2014
 *      Author: Gruppo2
 */

#ifndef NETSERVERSENDER_H_
#define NETSERVERSENDER_H_

#include "FreeRTOS.h"
#include "queue.h"
#include "CateMessage.h"
//stdlib e string per utilizzare la funzione malloc
#include <stdlib.h>     /* malloc, free, rand */
#include <string.h> /* memset */

//per utilizzare i task e i delay
#include "task.h"

extern xQueueHandle netQueueOut;




#endif /* NETSERVERSENDER_H_ */
