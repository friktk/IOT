/*
 * Uvod.cpp
 *
 * Created: 21.1.2020 12:56:28
 * Author : Lukas
 */ 

#ifndef F_CPU
	#define F_CPU 12000000UL	// define clock frequency
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	/* set as output */
	DDRD |= (1<<PORTD6);	// red led
	DDRD |= (1<<3);			// green led (alternative notation)
	DDRD |= (1<<PD5);		// blue led  (alternative notation)
    
	/* Default, all leds are on because of default state of PORT register (log.0 --> led on , log.1 led off) */
	
	/* turn all leds off */
	PORTD |= (1<<PORTD6);	// turn off red led
	PORTD |= (1<<PORTD3);	// turn off green led
	PORTD |= (1<<PORTD5);	// turn off blue led
	
	
	/* infinite loop (only zero is false, everything else is true in C++) */
    while (1) 
    {
		PORTD &= ~(1<<PORTD6);	// turn on red led
		_delay_ms(500);
		PORTD |= (1<<PORTD6);	// turn off red led
		_delay_ms(500);
    }
}

