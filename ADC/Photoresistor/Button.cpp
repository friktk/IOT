/* 
* Button.cpp
*
* Created: 21.1.2020 13:59:58
* Author: Lukas
*/


#include "Button.h"

// default constructor
Button::Button()
{
	cbi(DDRD,BTN);		// set as input
	sbi(PORTD,BTN);		// set pull-up 
} //Button

// default destructor
Button::~Button()
{
} //~Button

bool Button::isPressed(void)
{
/*	while((PIND & (1<<BTN))!=0){};			// wait, BTN=1
	_delay_ms(10);							// delay
	while((PIND & (1<<BTN))==0){};			// wait for release button	 
	return true;							// if BTN = 0  . . . pressed
*/
	if((PIND & (1<<BTN))==0) return true;	// pressed
	else return false;						// released
}