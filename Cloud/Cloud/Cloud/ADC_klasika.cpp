/* 
* ADC_klasika.cpp
*
* Created: 31.1.2018 14:12:44
* Author: Juraj
*/


#include "ADC_klasika.h"

// default constructor
ADC_klasika::ADC_klasika()
{
} //ADC_klasika
// default destructor
ADC_klasika::~ADC_klasika()
{
} //~ADC_klasika
void ADC_klasika::Nas_ADC(uint8_t hod, bool rezim){
	hod=hod&0x7;
	ADCSRA =0b10000000|hod; //  ADEN  
	if(rezim) ADCSRA |=0x20;  // autotriger
};
	
void ADC_klasika::Nas_kanal(uint8_t kan){
	kan=kan&0x07;
	ADMUX = 0b01000000|kan;	//AVCC
};
int ADC_klasika::Daj_ADC(void){
	ADCSRA |= (1<<ADSC);		// start
	while((ADCSRA & (1<<ADIF))!=(1<<ADIF)){}; //caka na koniec prvodu
	int prev = ADCL;
		prev |=ADCH<<8;
		ADCSRA |=(1<<ADIF);   //alternativa k vynulovaniu ADIF
		return prev;
	};

