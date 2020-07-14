/* 
* ESP1.h
*
* Created: 16.2.2018 20:18:14
* Author: Juraj
*/


#ifndef __ESP1_H__
#define __ESP1_H__
#include "Zobraz.h"
#include "Usart.h"

class Esp1: Usart, Zobraz
{
//variables
public:
protected:
private:

//functions
public:
	Esp1();
	~Esp1();
	bool Echo(bool);	//false zakaze,  true povoli
	//bool TestOK(void);  //true OK  false ERROR a timeout
	bool Restart(void);	// restartuje ESP12
	bool NastavUSART(int);	//v buducnosti rozsirit 
protected:
private:
	bool TestOK(void);  //true OK  false ERROR a timeout

}; //Esp1

#endif //__ESP1_H__
