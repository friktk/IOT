/* 
* Preusenia.h
*
* Created: 20.1.2018 16:24:03
* Author: Juraj
*/


#ifndef __PRERT1_H__
#define __PRERT1_H__

#include "Board.h"
#include  <avr/interrupt.h>
#define STRINGIFY(name) #name

#define CLASS_IRQ(name, vektor) \
static void name(void) asm (STRINGIFY(vektor)) \
__attribute__((signal, __INTR_ATTRS))


#define TIMER1_TIMEOUT 1172;	// TIMEOUT= cas/[(1/FCPU)*delic_hodin];   16-bit
								//  100ms:	0.1/(0.000000083*d1024) = 1172; 
#define TIMER2_TIMEOUT 100;		//	8-bit


/***************************************************/
#define STRINGIFY(name) #name

#define CLASS_IRQ(name, vektor) \
static void name(void) asm (STRINGIFY(vektor)) \
__attribute__((signal, __INTR_ATTRS))


class PreruseniaT0
{
//variables
public:
protected:
private:
volatile uint16_t Timer0;  //volatile
//functions
public:
	PreruseniaT0();
	~PreruseniaT0();
	uint16_t getTim0(void);
	void setTim0(uint16_t);
			
	private:
	CLASS_IRQ(OverflowInterrupt0, TIMER0_OVF_vect);
	CLASS_IRQ(CompAInterrupt0, TIMER0_COMPA_vect);
	
}; //PreruseniaT0
/******************************************************/
class PrerT1
{
	//variables
	public:
	protected:
	private:
	volatile uint16_t Timer1;  //volatile
	//functions
	public:
	PrerT1();
	~PrerT1();
	uint16_t getTim1(void);
	void setTim1(uint16_t);
	
	
	private:
		
	CLASS_IRQ(OverflowInterrupt1, TIMER1_OVF_vect);
	CLASS_IRQ(CompAInterrupt1, TIMER1_COMPA_vect);
	CLASS_IRQ(CompBInterrupt1, TIMER1_COMPB_vect);
	CLASS_IRQ(CaptInterrupt1, TIMER1_CAPT_vect);
}; //PrerT1


#endif //__PRERT1_H__
