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
	
	TCCR0A = (1<<WGM01)|(1<<WGM00);		// fast PWM TC0
	TCCR0B = (1<<CS02);					// clkio/256    (183 Hz)
	TCCR2A = (1<<WGM21)|(1<<WGM20);		// fast PWM TC2
	TCCR2B = (1<<CS22);
	
	set(0,0,0);	// set all leds off
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

void Led::setIntensity(uint8_t r, uint8_t g, uint8_t b)
{
	if(r==0) 
	{
		cbi(TCCR0A,COM0A0);
		cbi(TCCR0A,COM0A1); 
		sbi(PORTD,R_LED);
	} 
	else
	{ 
		sbi(TCCR0A, COM0A0);
		sbi(TCCR0A, COM0A1); 
		OCR0A = r;
	}

	if(g==0) 
	{
		cbi(TCCR2A,COM2B0);
		cbi(TCCR2A,COM2B1);
		sbi(PORTD,G_LED);
	} 
	else
	{ 
		sbi(TCCR2A, COM2B0);
		sbi(TCCR2A, COM2B1); 
		OCR2B = g;
	}

	if(b==0) 
	{
		cbi(TCCR0A,COM0B0);
		cbi(TCCR0A,COM0B1); 
		sbi(PORTD,B_LED);
	} 
	else
	{ 
		sbi(TCCR0A, COM0B0);
		sbi(TCCR0A, COM0B1); 
		OCR0B = b; 
	}
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