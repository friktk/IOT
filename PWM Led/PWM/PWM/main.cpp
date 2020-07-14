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
	
    /* Replace with your application code */
	uint8_t pom=0;
    while (1) 
    {
		for(uint8_t i=0 ; i<255 ; i++)
		{
			switch(pom)
			{
				case 0 :	rgb.setIntensity(i,0,0);
							break;
				case 1 :	rgb.setIntensity(0,i,0);
							break;
				case 2 :	rgb.setIntensity(0,0,i);
							break;
				default:	rgb.setIntensity(0,0,0);
							pom =0;
							break;
			}
			_delay_ms(15);
		}
		pom++;
    }
}

