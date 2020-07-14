/* 
* ADC_klasika.h
*
* Created: 31.1.2018 14:12:44
* Author: Juraj
*/


#ifndef __ADC_KLASIKA_H__
#define __ADC_KLASIKA_H__
#include "Board.h"

class ADC_klasika
{
//variables
public:
protected:
private:

//functions
public:
	ADC_klasika();
	~ADC_klasika();
void Nas_ADC(uint8_t hod, bool rezim);
void Nas_kanal(uint8_t);
int Daj_ADC(void);
protected:
private:
//	ADC_klasika( const ADC_klasika &c );
//	ADC_klasika& operator=( const ADC_klasika &c );

}; //ADC_klasika

#endif //__ADC_KLASIKA_H__
