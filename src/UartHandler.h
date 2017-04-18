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

/*! @struct UartHandler
 * 	@brief Structure is handling UART module via serial port.
 *
 */
typedef struct UartHandler
{
	struct termios Settings; 	/*! Serial port settings */
	int PortNum; 				/*! UART module number 1,2... */
	int BaudRateKilos;			/*! Baud rate value for UART */
	int DataBits;				/*! Data bits */
	int Fd;						/*! File descriptor */
	uint8_t Buffer[UART_BUFFER_SIZE];	/*! Buffer for receiving data from serial port */
	int ReceivedBytes;
	int SendedBytes;
	int (*send)(struct UartHandler*,uint8_t*,int);
	

}UartHandler;

/*! @brief Function is setting up UART module with certain values
 * 	@param handler UartHandler pointer to previously created object
 * 	@param num UART number
 * 	@param bd Baud rate in kilos for 960
 * 	@param db Data bits
 */
int setupUart (UartHandler* handler,int num,int bd,int db);
void printfUartSettings (UartHandler* handler);
int sendData(UartHandler* handler, uint8_t *message,int k);
int receiveData (UartHandler* handler);

UartHandler* newUartHandler();
void deleteUartHandler(UartHandler* handler);

#endif /* UARTHANDLER_H_ */
