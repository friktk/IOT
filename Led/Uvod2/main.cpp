/*
 * Uvod2.cpp
 *
 * Created: 21.1.2020 13:19:25
 * Author : Lukas
 */ 

#include "Led.h"


int main(void)
{
	Led rgb;			// create object of class Led
	Led *rgb_ptr;		// pointer to class Led
	rgb_ptr = &rgb;		// set pointer to adress of rgb object
	
	rgb.set(0,1,0);		// green led on;
	_delay_ms(1000);
	rgb_ptr->set(0,0,0); // call method using pointer
	
	rgb.set(purple);
	_delay_ms(1000);
    /* Replace with your application code */
    while (1) 
    {
		rgb.blick(0,0,1,200);	// blick blue led (200 ms)
    }
}

