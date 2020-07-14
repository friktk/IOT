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
	static int sendByte(char data, FILE *stream);
	static int receiveByte(FILE *stream);
protected:
private:


}; //Uart

#endif //__UART_H__
