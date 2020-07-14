/*
 * Board.h
 *
 * Created: 16.11.2017 21:19:29
 *  Author: Juraj
 */ 


#ifndef BOARD_H_
#define BOARD_H_
#ifndef F_CPU
#define F_CPU 12000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "Util.h"
//***********USART****
#define HTX PORTD1
#define HRX PORTD0
#define STX PORTC2
#define SRX PORTC3
//************DSP*****
#define SER PORTC5
#define OE PORTC4
#define RCLK PORTD7
#define SRCLK PORTB1
//**************RGB***
#define R_LED PORTD6
#define G_LED PORTD3
#define B_LED PORTD5
//**********TLACIDLO****
#define TL PORTD2
#define FOTO PORTC0
//**********************
#define RST_D PORTD4		//IoT_2018 PORTD4 PORTD5 starsie verzie
#define BAUDERATE 115200   //9600
#define UBRR_VALUE ((F_CPU / (BAUDERATE * 8L)) -1)  //   8....51  ,  16.....25  12.....12

#define sbi(x,y) x |= _BV(y)	 //nastav bit     (1<<y)
#define cbi(x,y) x &= ~(_BV(y)) //nuluj bit - using bitwise AND operator
#define tbi(x,y) x ^= _BV(y)    //zmen bit - using bitwise XOR operator
#define hwcrlf loop_until_bit_is_set(UCSR0A, UDRE0 );UDR0=0xd;loop_until_bit_is_set(UCSR0A, UDRE0 );UDR0=0xa;

#define nula	0b00111111
#define jedna	0b00000110
#define dva		0b01011011
#define tri		0b01001111
#define styri	0b01100110
#define pat		0b01101101
#define sest	0b01111101
#define sedem	0b00000111
#define osem	0b01111111
#define devat	0b01101111
#define ahex	0b01110111
#define bhex	0b01111100
#define chex	0b01011000
#define dhex	0b01011110
#define ehex	0b01111001
#define fhex	0b01110001
#define dot		0b10000000
#define err		0b01001001
#define non		0b00000000

#define S_IDLE  0b00000000		// idle
#define S_ADC   0b00010000		//ADC noise reduction
#define S_PWD	0b00100000		//power down
#define S_PWS	0b00110000		//power save
#define S_STD	0b10100000		//stand by
#define S_EST	0b10110000		//extended stand by
#define S_SE	0b01000000		//sleep enable

enum delic_hodin{
	dSTOP,
	d1,
	d8,
	d64,
	d256,
	d1024,
	EXT_F,
	EXT_R
};
enum externint{
	low,
	zmena,
	zaverna,
	nabezna
};
#endif /* BOARD_H_ */