/* 
* Adc.cpp
*
* Created: 20.11.2019 10:06:02
* Author: Lukas
*/


#include "Adc.h"

// default constructor
Adc::Adc()
{
	PRR &=~(1<<PRADC);				/* enable ADC */
} //Adc

// default destructor
Adc::~Adc()
{
	PRR |=(1<<PRADC);				/* disable ADC */
} //~Adc

void Adc::init(uint8_t clock, bool mode)
{
	clock=clock&0x7;									
	ADCSRA =0b10000000|clock;		/*  ADEN, ADSC, ADATE, ADIF, ADIE,ADPS2,1,0 */
	if(mode) ADCSRA |=0x20;			/* ADATE: autotriger; */
}

void Adc::setChannel(uint8_t channel)	/* Channel 0 - F */
{
	channel &= 0x0F;
	ADMUX &= 0xF0;
	ADMUX |= channel;				/* AVCC  010... 10bit  0110... 8bit - ADLAR=1 */
}

void Adc::setRef(uint8_t ref)
{
	ref=ref & 0b00000011;			/* mask */
	ADMUX &= 0b00111111;
	ADMUX |= (ref<<6);
}

int Adc::getAdc(void)
{
	ADMUX &=~(1<<ADLAR);			/* ADLAR=0   0b11011111; */
	ADCSRA |= (1<<ADSC);			/* start */
	while((ADCSRA & (1<<ADIF))!=(1<<ADIF)){}; /* waiting for the end of conversion */
	int prev = ADCL;
	prev |=ADCH<<8;
	ADCSRA |=(1<<ADIF);
	return prev;
}

uint8_t Adc::getAdc8(void)
{
	ADMUX |=(1<<ADLAR);
	ADCSRA |= (1<<ADSC);		
	while((ADCSRA & (1<<ADIF))!=(1<<ADIF)){};
	uint8_t pom=ADCH;
	ADCSRA |=(1<<ADIF);
	return pom;
}