/*
 * NetworkMessage.c
 *
 *  Created on: 18/giu/2014
 *      Author: Gruppo2
 */

#include "NetworkMessage.h"

networkMessage* newNetworkMessage()
{
	return (networkMessage*)malloc(sizeof(networkMessage));

}

void destroyNetworkMessage(networkMessage* inMessage)
{
	free(inMessage->payload);
	free(inMessage);
}
