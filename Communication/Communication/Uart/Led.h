/*
* Led.h
*
* Created: 21.1.2020 13:23:56
* Author: Lukas
*/


#ifndef __LED_H__
#define __LED_H__

#include "Board.h"

class Led
{
	//variables
	public:
	protected:
	private:

	//functions
	public:
	Led();
	~Led();
	void set(bool r,bool g,bool b);
	void set(Colour c);
	void blick(bool r,bool g,bool b, int timeMs);
	protected:
	private:


}; //Led

#endif //__LED_H__
