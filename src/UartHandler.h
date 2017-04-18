/*
 * UART.h
 *
 *  Created on: Feb 23, 2017
 *      Author: mbartkow
 */

#ifndef UARTHANDLER_H_
#define UARTHANDLER_H_

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#define UART_BUFFER_SIZE 32


typedef struct UartHandler
{
	struct termios Settings;
	uint8_t PortNum;
	uint8_t BaudRateKilos;
	uint8_t DataBits;
	int Fd;
	uint8_t Buffer[UART_BUFFER_SIZE];
	int ReceivedBytes;
	int SendedBytes;
	int (*send)(struct UartHandler*,uint8_t*,int);
	

}UartHandler;


int setupUart (UartHandler* handler,int num,int bd,int db,int canon);
void printfUartSettings (UartHandler* handler);
void printfUartBuffer(UartHandler* handler);
int sendData(UartHandler* handler, uint8_t *message,int k);
int receiveData (UartHandler* handler);

UartHandler* newUartHandler();
void deleteUartHandler(UartHandler* handler);

#endif /* UARTHANDLER_H_ */
