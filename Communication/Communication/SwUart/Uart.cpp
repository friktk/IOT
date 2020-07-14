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
	
	/* SW UART */
//	cbi(DDRC,SRX);			//Set as input
	sbi(DDRC,STX);			// set as output 
	sbi(PORTD,STX);			// log.1 on STX
	sbi(PORTD,SRX);			// pull-up
	
	uart_ptr = fdevopen(Uart::swSendByte, Uart::swReceiveByte);		//send , receive methods
	stdout = stdin = uart_ptr;
} //Uart

// default destructor
Uart::~Uart()
{
} //~Uart

int Uart::hwSendByte(char data, FILE *stream)
{
	if(data == '\n')
		hwSendByte('\r',0);	
	while(!(UCSR0A & (1<<UDRE0))){};
	UDR0 = data;
	return 0;
}

int Uart::hwReceiveByte(FILE *stream)
{
	uint8_t data;
	while(!(UCSR0A & (1<<RXC0))){};
	data = UDR0;
	//USART_send_byte(u8data,stream);  //echo
	return data;
}

/************************************************* SW UART ********************************************* */

int Uart::swSendByte(char data, FILE *stream)
{
	 if(data == '\n')
		 swSendByte('\r',0); 
	 sendByteSw(data);			// this method must be static
	 return 0;
}

int Uart::swReceiveByte(FILE *stream)
{
	 uint8_t data;
	 data = receiveByteSw();	// this method must be static
	 //USART_send_byte(u8data,stream);  //echo
	 return data;
}

/************************************************* private ********************************************** */
void Uart::sendByteSw(uint8_t c)
{
	sbi(DDRC,STX);						// set as output 
	cbi(PORTC,STX);						// start bit
	_delay_us(52);						// 104/2 us
	for(uint8_t i = 0; i < 8; i++)
	{
		if((c & 1) == 1)sbi(PORTC,STX); else cbi(PORTC,STX);
		c = c >> 1;
		_delay_us(52);					
	}
	sbi(PORTC,STX);						// 1 stop bit
	_delay_us(52);						// 104
}

uint8_t Uart::receiveByteSw(void)
{
	uint8_t c = 0;
	while((PINC & (1<<SRX))!= 0){}	//caka na start bit
	_delay_us(26);					// 52
	for(uint8_t i = 0; i < 8; i++)
	{
		c = c>>1;
		_delay_us(51);			// 103 us + 16 instrukcii
		if((PINC & (1<<SRX)) == (1<<SRX)) c = c | 0b10000000;
	}
	return c;
}