/* 
* ESP1.cpp
*
* Created: 16.2.2018 20:18:13
* Author: Juraj
*/


#include "ESP1.h"



// default constructor
Esp1::Esp1()
{
} //ESP1

// default destructor
Esp1::~Esp1()
{
} //~ESP1

extern Usart USART;

bool Esp1::Echo(bool x){
	if(x){this->write("ATE1");} else this->write("ATE0");
	hwcrlf;
	this->BLIK(10,0,0,1);
	return this->TestOK();
	return true;
};
bool Esp1::TestOK(void){
	bool x;
	while(1){
		_delay_ms(5);
		if(USART.find("OK",false)){ x =true; break;}
			if(USART.find("ERROR",false)){ x =false; break;}
	}
	return x;
	}; 
	
	bool Esp1::Restart(void){
	this->write("AT+RST");	hwcrlf;
	
	return this->TestOK();
		};	// res
		
	bool Esp1::NastavUSART(int){
		
		return true;
		};
		
		
		