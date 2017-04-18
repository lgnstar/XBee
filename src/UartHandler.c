#include "UartHandler.h"



/*! @brief Configuring the Serial Port
*	@param handler Uart handler pointer
*	@param num UART number
*	@param bd Baud Rate
*	@param db Data Bits
*/
int setupUart(UartHandler* handler,int num,int bd,int db)
{

	char SerialPath[32]="/dev/ttyO";
	char SerialNum[5]="0";

	sprintf(SerialNum,"%d",num);
	strcat(SerialPath,SerialNum);
	printf("UART: Opening %s \n", SerialPath);

	handler->Fd = open(SerialPath, O_RDWR | O_NOCTTY);
	if (handler->Fd == -1)
	{
		printf("UART:Opening serial port: %s\n", strerror(errno));
		return -1;
	}

	if(!isatty(handler->Fd))
	{ 
		printf("UART:Choosen port is not serial port! \n");
		return -1;
	}
	
	if (tcgetattr(handler->Fd, &handler->Settings) < 0)
	{
		printf("UART:Getting serial port attributes: %s\n", strerror(errno));
		return -1;
	}

	cfsetospeed(&handler->Settings, (speed_t)bd);
	cfsetispeed(&handler->Settings, (speed_t)bd);

	switch (bd)
	{
	case B4800: printf("UART:Setting baud rate to B4800 \n"); break;
	case B9600: printf("UART:Setting baud rate to B9600 \n"); break;
	case B19200:printf("UART:Setting baud rate to B19200 \n"); break;
	case B38400:printf("UART:Setting baud rate to B38400 \n"); break;
	case B115200:;printf("UART:Setting baud rate to B11520 \n"); break;
		default: printf("UART:Wrong baud rate, setup failed! \n"); return -1;
	}


	handler->Settings.c_cflag &= ~PARENB;
	handler->Settings.c_cflag &= ~CSTOPB;
	handler->Settings.c_cflag &= ~CSIZE;

	switch (db)
		{
		case 5: handler->Settings.c_cflag |= CS5;printf("UART:Setting data bits to 5 \n"); break;
		case 6: handler->Settings.c_cflag |= CS6;printf("UART:Setting data bits to 6 \n"); break;
		case 7: handler->Settings.c_cflag |= CS7;printf("UART:Setting data bits to 7 \n"); break;
		case 8: handler->Settings.c_cflag |= CS8;printf("UART:Setting data bits to 8 \n"); break;
			default: handler->Settings.c_cflag |= CS8;printf("UART:Setting data bits to default value (8) \n"); break;
		}

	handler->Settings.c_cflag &= ~CRTSCTS;
	handler->Settings.c_cflag |= (CLOCAL | CREAD );
	handler->Settings.c_iflag &= ~(IXON | IXOFF | IXANY);
	handler->Settings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	handler->Settings.c_cc[VMIN] = 4;
	handler->Settings.c_cc[VTIME] = 0;

	if ( tcsetattr(handler->Fd,TCSANOW,&handler->Settings) != 0)
	{
		printf("UART:Setting serial port attributes: %s\n", strerror(errno));
		return -1;
	}

	handler->DataBits=db;
	handler->BaudRateKilos=bd;
	printf("UART:Setting serial port finished! \n");
	return 0;
}

int sendData (UartHandler* handler, uint8_t *message,int k)
{
	int n= write(handler->Fd, message,k);
	if (n > 0)
	{
		handler->SendedBytes=n;
		return n;
	}
	else
		return -1;
}

int receiveData (UartHandler* handler)
{
	int n= read(handler->Fd,handler->Buffer, UART_BUFFER_SIZE);
	if (n > 0)
	{
		handler->ReceivedBytes=n;
		return n;
	}
	else
		return -1;
}
void printfUartSettings(UartHandler *handler)
{
	printf("UART: Using UART%d \n", handler->PortNum);
	printf("UART: Baud rate %d k \n", handler->BaudRateKilos);
	printf("UART: Data bits %d \n", handler->DataBits);
}
UartHandler* newUartHandler()
{
	UartHandler* handler=(UartHandler*)malloc(sizeof(UartHandler));

	handler->Fd=0;
	handler->BaudRateKilos=0;
	memset(handler->Buffer,'0',UART_BUFFER_SIZE);
	handler->DataBits=0;
	handler->PortNum=0;
	handler->send=&sendData;

	return handler;

}
void deleteUartHandler(UartHandler* handler)
{
	close(handler->Fd);
	free(handler);
}

