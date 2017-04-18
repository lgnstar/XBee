/*
 * Queue.c
 *
 *  Created on: Mar 26, 2017
 *      Author: mbartkow
 */
#include "ZigBeeQueue.h"

void print(ZigBeeMessage msg)
{
	printf("\nL:%d ApiId:%d SourceAdress:%d", msg.Lenght,msg.ApiId,msg.SourceAdress);
	printf("Rssi:%d Opt:%d Data:", msg.Rssi, msg.Options);
	for(int i=0;i<FRAME_DATA_LENGTH;++i)
	            	printf("%02x ",(uint8_t)msg.Data[i]);
	printf("CRC:%d", msg.Crc);
}
int push (ZigBeeQueue* queue, ZigBeeMessage message) {

	ZigBeeQueueNode* n = (ZigBeeQueueNode*) malloc (sizeof(ZigBeeQueueNode));
		if(n == NULL)
			return -1;
    n->message = message;
    n->next = NULL;

    if (queue->head == NULL) { // no head
        queue->head = n;
    } else{
        queue->tail->next = n;
    }
    queue->tail = n;
    queue->size++;
    return 0;
}

ZigBeeMessage pop (ZigBeeQueue* queue) {
    // get the first item
	if(queue->size > 0)
	{
	ZigBeeQueueNode* head = queue->head;
    ZigBeeMessage item = head->message;
    // move head pointer to next node, decrease size
    queue->head = head->next;
    queue->size--;
    // free the memory of original head
    free(head);
    return item;
	}
	//else
	//return NULL;
}
ZigBeeMessage* peek (ZigBeeQueue* queue) {
	if (queue->size > 0)
	{
	ZigBeeQueueNode* head = queue->head;
    return &(head->message);
	}else
	return NULL;
}
ZigBeeMessage* last(ZigBeeQueue *queue){
	if (queue->size > 0)
		{
		ZigBeeQueueNode* tail = queue->tail;
	    return &(tail->message);
		}else
		return NULL;
}

void display (ZigBeeQueue* queue) {
    printf("\nDisplay: ");
    // no item
    if (queue->size == 0)
        printf("No item in queue.\n");
    else { // has item(s)
    	ZigBeeQueueNode* head = queue->head;
        int i, size = queue->size;
        printf("%d item(s):\n", queue->size);
        for (i = 0; i < size; i++) {
            if (i > 0)
            	print(head->message);
            head = head->next;
        }
    }
    printf("\n\n");
}
/**
 * Create and initiate a Queue
 */
ZigBeeQueue* newZigBeeQueue () {

	ZigBeeQueue *queue=(ZigBeeQueue*) malloc (sizeof(ZigBeeQueue));

	if(queue == NULL)
		return NULL;

    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
    queue->push = &push;
    queue->pop = &pop;
    queue->peek = &peek;
    queue->display = &display;
    queue->last=&last;
    return queue;
}
int deleteZigBeeQueue(ZigBeeQueue* queue)
{
	while(queue->size)
		queue->pop(queue);
	if(queue->size == 0)
		{
			free(queue);
			queue=NULL;
			return 0;
		}
	else
		return -1;

}

