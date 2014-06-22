/*
 * CateMessage.c
 *
 *  Created on: 09/giu/2014
 *      Author: Antonio
 */

#include "CateMessage.h"
#include <string.h>
#include <stdlib.h>



cateMessage* newCateMessage()
{
	return (cateMessage*)malloc(sizeof(cateMessage));

}

void destroyCateMessage(cateMessage* inMessage)
{
	free(inMessage->payload);
	free(inMessage);
}
