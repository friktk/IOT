/*
* Led.cpp
*
* Created: 21.1.2020 13:23:56
* Author: Lukas
*/


#include "Led.h"

// default constructor
Led::Led()
{
	/* set as outputs */
	sbi(DDRD,R_LED);
	sbi(DDRD,B_LED);
	sbi(DDRD,G_LED);
	
	set(false,false,false);	// set all leds off
} //Led

// default destructor
Led::~Led()
{
} //~Led

void Led::set(bool r,bool g,bool b)
{
	if(r) cbi(PORTD,R_LED); else sbi(PORTD,R_LED);
	if(g) cbi(PORTD,G_LED); else sbi(PORTD,G_LED);
	if(b) cbi(PORTD,B_LED); else sbi(PORTD,B_LED);
}

void Led::set(Colour c)
{
	switch(c)
	{
		case 0:		set(1,0,0);
		break;
		case 1:		set(0,1,0);
		break;
		case 2:		set(0,0,1);
		break;
		case 3:		set(1,0,1);
		break;
		default:	set(0,0,0);
	}
}

void Led::blick(bool r,bool g,bool b, int timeMs)
{
	this->set(r,g,b);
	for(int i=0; i<timeMs; i++) _delay_ms(1);
	this->set(0,0,0);
	for(int i=0; i<timeMs; i++) _delay_ms(1);
}