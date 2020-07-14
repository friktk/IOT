/* 
* Uart.cpp
*
* Created: 21.1.2020 14:51:34
* Author: Lukas
*/


#include "Uart.h"

// default constructor
Uart::Uart()
{
	DDRD |= (1<<HTX);					// Tx as output (not necessary, when TXEN is set, also TX is set as output)
	UBRR0H = (uint8_t)(UBRR_VALUE>>8);	// BAUDERATE
	UBRR0L = (uint8_t)UBRR_VALUE;
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);  // 8 bits, no parity, 1 stop
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);	// enable rx and tx
	UCSR0A |= (1<<U2X0);				// double speed mode
	
	uart_ptr = fdevopen(sendByte, receiveByte);		//send , receive methods
	stdout = stdin = uart_ptr;
} //Uart

// default destructor
Uart::~Uart()
{
} //~Uart

int Uart::sendByte(char data, FILE *stream)
{
	if(data == '\n')
		sendByte('\r',0);	
	while(!(UCSR0A & (1<<UDRE0))){};
	UDR0 = data;
	return 0;
}

int Uart::receiveByte(FILE *stream)
{
	uint8_t data;
	while(!(UCSR0A & (1<<RXC0))){};
	data = UDR0;
	//USART_send_byte(u8data,stream);  //echo
	return data;
}