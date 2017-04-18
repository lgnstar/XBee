/*
 * ZigBeeHandler.h
 *
 *  Created on: Mar 29, 2017
 *      Author: mbartkow
 */

#ifndef ZIGBEEHANDLER_H_
#define ZIGBEEHANDLER_H_

#include "ZigBeeQueue.h"
#include "UartHandler.h"

typedef struct ZigBeeHandler
{
	ZigBeeQueue *frameQueue;
	UartHandler *uartHandler;
	int Status;

	ZigBeeMessage (*startListen) ( struct ZigBeeHandler* );
	int (*sendMessage) (ZigBeeMessage);


}ZigBeeHandler;

ZigBeeHandler* newZigBeeHandler();

ZigBeeMessage startListen (ZigBeeHandler* handler);
int sendMessage (ZigBeeHandler* handler,ZigBeeMessage message);
uint8_t calcCrc (ZigBeeMessage);
int checkCrc (ZigBeeMessage,uint8_t);

int testUart();

void generate(int k);
#endif /* ZIGBEEHANDLER_H_ */
