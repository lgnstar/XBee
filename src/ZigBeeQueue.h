/*
 * Queue.h
 *
 *  Created on: Mar 26, 2017
 *      Author: mbartkow
 */

#ifndef ZIGBEEQUEUE_H_
#define ZIGBEEQUEUE_H_
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#define FRAME_DATA_LENGTH 100

typedef struct ZigBeeMessage
{
	uint16_t Lenght;
	uint8_t ApiId;
	uint16_t SourceAdress;
	uint8_t Rssi;
	uint8_t Options;
	uint8_t Data[FRAME_DATA_LENGTH];
	uint8_t Crc;
}ZigBeeMessage;

void print(ZigBeeMessage msg);

typedef struct ZigBeeQueueNode
{
	ZigBeeMessage message;
	struct ZigBeeQueueNode* next;
}ZigBeeQueueNode;

typedef struct ZigBeeQueue {
	ZigBeeQueueNode* head;
	ZigBeeQueueNode* tail;
	int size;

    int (*push) (struct ZigBeeQueue*, ZigBeeMessage);
    ZigBeeMessage (*pop) (struct ZigBeeQueue*);
    ZigBeeMessage* (*peek) (struct ZigBeeQueue*);
    ZigBeeMessage* (*last)(struct ZigBeeQueue*);
    void (*display) (struct ZigBeeQueue*);

} ZigBeeQueue;

int push (ZigBeeQueue* queue, ZigBeeMessage item);
ZigBeeMessage pop (ZigBeeQueue* queue);
ZigBeeMessage* peek (ZigBeeQueue* queue);
ZigBeeMessage* last(ZigBeeQueue *queue);
void display (ZigBeeQueue* queue);
ZigBeeQueue* newZigBeeQueue();
int deleteZigBeeQueue(ZigBeeQueue* queue);

#endif /* ZIGBEEQUEUE_H_ */
