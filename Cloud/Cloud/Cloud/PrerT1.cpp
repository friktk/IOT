/* 
* Preusenia.cpp
*
* Created: 20.1.2018 16:24:03
* Author: Juraj
*/


#include "PrerT1.h"


//static uint16_t Timer0;  //volatile
//static uint32_t Timer1;  // pri 0.1s pretecie za 117361 hodin
//static uint16_t Timer1;  // pri 0.1s pretecie za 1.8 hodinu



	/************************************************/
	PrerT1::PrerT1()
	{
		PRR &=~(1<<PRTIM1);			// zapneme TIM0 napriek tomu, ze je def. zapnute
		uint8_t sreg = SREG;
		cli();						// atomicka operacia
		TCNT1 = TIMER1_TIMEOUT;
		SREG = sreg;
		TCCR1B |= d1024;			// nastavenie preddelicky clkio
		TIMSK1 |= (1<<TOIE1);		// povolenie prerusenia
		this->Timer1 = TIMER1_TIMEOUT;
	}
	PrerT1::~PrerT1()
	{
		TIMSK1 &=~(1<<TOIE1);	// zakazanie prerusenia
		//	PRR |=(1<<PRTIM1);	// vypneme TIM0 ak chceme setrit, ale pozor nepojde nic
	}
	
	/**********************metody public*************************/
	uint16_t PrerT1::getTim1(void){
		return this->Timer1;
	};

	void  PrerT1::setTim1(uint16_t hod){
		this->Timer1 = hod;
	};
	
	class PrerT1 Timer01;
	
	void PrerT1::OverflowInterrupt1(void) //staticka funkcia
												//nemozeme pouzit this
	{
		TCNT1 = TIMER1_TIMEOUT;		//restart
		Timer01.Timer1++;
		// kod obsluhy
	};
	
	void PrerT1::CompAInterrupt1(void)
	{
		
		//kod obsluhy
	};
	
	void PrerT1::CompBInterrupt1(void)
	{
		
		//kod obsluhy
	};
	void PrerT1::CaptInterrupt1(void)
	{
		
		//kod obsluhy
	};
	
	