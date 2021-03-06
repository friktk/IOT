/*
 * Uvod2.cpp
 *
 * Created: 21.1.2020 13:19:25
 * Author : Lukas
 */ 

#include "Led.h"
#include "Button.h"
#include "Display.h"
#include "Uart.h"

int main(void)
{
	Led rgb;			// create object of class Led
	Led *rgb_ptr;		// pointer to class Led
	rgb_ptr = &rgb;		// set pointer to adress of rgb object
	rgb.set(0,1,0);		// green led on [rgb_ptr->set(0,1,0)];

	Button btn;					// create object of class Button
	while(!btn.isPressed()){}	// wait until btn is pressed
	rgb.set(0,0,0);				// turn off leds

	Display dsp;				// create object of class Display
	Uart serial;				// create object of class Uart (initialization of UART interface & redirect stdin and stdout to this interface)
	
	
	/* set baudrate to 19 200 & connect to SW UART interface */
	printf ("Hello from IoT board. This is Sw serial interface :) \r\n");
	char c;
	while (1)
	{
		printf("press any key :  ");
		c = getchar();			// waiting to receive character from keyboard
		printf("\r\n\nYou pressed :  %c \r\n", c);
	}
}


