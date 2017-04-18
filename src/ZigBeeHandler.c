#include "ZigBeeHandler.h"
#include "ZigBeeQueue.h"
#include <time.h>
#include <stdlib.h>

#define  SD 0x7E

uint8_t calcCrc (ZigBeeMessage message)
{
	uint8_t Crc=0;;
	for(int i=0; i < message.Lenght-1; ++i)
		Crc += message.Data[i];
	Crc &= 0xff;
	Crc = 0xff - Crc;
	return Crc;
}
int checkCrc (ZigBeeMessage message,uint8_t Crc)
{
	uint8_t Sum=0;
	for(int i=0; i < message.Lenght; ++i)
		Sum += message.Data[i];
		Sum += Crc;
	if ( Sum == 0xFF)
		return 1;
	else
		return 0;
}
int sendMessage (ZigBeeHandler* handler,ZigBeeMessage message)
{
	uint8_t *Frame;
	unsigned int DataLenght=message.Lenght;

}
