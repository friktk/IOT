/*
 * Uvod2.cpp
 *
 * Created: 21.1.2020 13:19:25
 * Author : Lukas
 */ 

#include "Led.h"
#include "Button.h"
#include "Display.h"


int main(void)
{
	Led rgb;			// create object of class Led
//	Led *rgb_ptr;		// pointer to class Led
//	rgb_ptr = &rgb;		// set pointer to adress of rgb object	
	rgb.set(0,1,0);		// green led on;

	Button btn;					// create object of class Button
	while(!btn.isPressed()){}	// wait until btn is pressed
	rgb.set(0,0,0);				// turn off leds

	Display dsp;				// create object of class Display
	
	for (uint8_t i=0; i<=18;i++)
	{
		dsp.show(i);
		_delay_ms(500);	
	}
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

