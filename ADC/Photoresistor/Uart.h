/* 
* Uart.h
*
* Created: 21.1.2020 14:51:34
* Author: Lukas
*/


#ifndef __UART_H__
#define __UART_H__

#include "Board.h"

class Uart
{
//variables
public:
protected:
private:
	FILE *uart_ptr;

//functions
public:
	Uart();
	~Uart();
	static int hwSendByte(char data, FILE *stream);
	static int hwReceiveByte(FILE *stream);
	
	static int swSendByte(char data, FILE *stream);
	static int swReceiveByte(FILE *stream);
protected:
private:
	static void sendByteSw(uint8_t c);
	static uint8_t receiveByteSw(void);


}; //Uart

#endif //__UART_H__
