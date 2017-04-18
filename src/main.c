/*
 ============================================================================
 Name        : ProjectTemplate.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "UartHandler.h"
#include "ZigBeeHandler.h"

int main(void) {

	UartHandler *uart2=newUartHandler();
	uint8_t message[32]="Hello to ja twoja wiadomoic\n";

	setupUart(uart2,2,B9600,8,1);

				while(1)
				{
					sendData(uart2,message,32);
					sleep(1);
					receiveData(uart2);
					printf("Received bytes: %d \n", uart2->ReceivedBytes);
					printf("Message:");
					printfUartBuffer(uart2);

				}

	  return 0;
}
