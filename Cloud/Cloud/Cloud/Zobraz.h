/* 
* Zobraz.h
*
* Created: 16.1.2018 19:35:24
* Author: Juraj
*/


#ifndef __ZOBRAZ_H__
#define __ZOBRAZ_H__
#include "Board.h"

class Zobraz
{
//variables
public:
protected:
private:

//functions
public:
	Zobraz();
	~Zobraz();
		
	void RGB(bool R,bool G,bool B);
	void BLIK(uint8_t cas, bool R, bool G, bool B);  //cas v ms
	void DSP(uint8_t znak);
protected:
private:
	void zobr(uint8_t vys);   // do tejto fcie nema nikto liest
//	Zobraz( const Zobraz &c );
//	Zobraz& operator=( const Zobraz &c );

}; //Zobraz

#endif //__ZOBRAZ_H__
