/*
 * Board.h
 *
 * Created: 21.1.2020 13:19:52
 *  Author: Lukas
 */ 


#ifndef BOARD_H_
#define BOARD_H_

#ifndef F_CPU
	#define F_CPU 12000000UL
#endif


#include <avr/io.h>
#include <util/delay.h>

/************************** MACROS ****************************/
#define sbi(x,y) x |= _BV(y)		// set bit (1<<y) [log. 1]
#define cbi(x,y) x &= ~(_BV(y))		// clear bit - using bitwise AND operator [log. 0]
#define tbi(x,y) x ^= _BV(y)		// toggle bit - using bitwise XOR operator
/**************************************************************/

/************************** RGB ****************************/
#define R_LED PORTD6
#define G_LED PORTD3
#define B_LED PORTD5

 enum Colour {						// enumerable type - default: 0, 1, 2, 3...
	 red, green, blue, purple
 };
/***********************************************************/

/************************** BUTTON ****************************/
#define BTN PORTD2
/**************************************************************/
#endif /* BOARD_H_ */