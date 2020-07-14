/* 
* Zobraz.cpp
*
* Created: 16.1.2018 19:35:24
* Author: Juraj
*/


#include "Zobraz.h"

// default constructor
Zobraz::Zobraz()
{
	//*******RGB*********
  sbi(DDRD,R_LED);  //nastavi smer vystupov pre RGB_LED
  sbi(DDRD,B_LED);
  sbi(DDRD,G_LED);
	sbi(PORTD,R_LED);  //zhasne RGB_LED
	sbi(PORTD,B_LED);
	sbi(PORTD,G_LED);

//***********DSP******	
	sbi(DDRC,SER);	//nastavi smer vystupov pre LED_znak
	sbi(DDRC,OE);
	sbi(DDRD,RCLK);
	sbi(DDRB,SRCLK);
}; //Zobraz

// default destructor
Zobraz::~Zobraz()
{
}; //~Zobraz

//***********************************public************************
void Zobraz::RGB(bool R,bool G,bool B)
{
	if(R) cbi(PORTD,R_LED); else sbi(PORTD,R_LED);
	if(G) cbi(PORTD,G_LED); else sbi(PORTD,G_LED);
	if(B) cbi(PORTD,B_LED); else sbi(PORTD,B_LED);
}
void Zobraz::BLIK(uint8_t cas, bool R, bool G, bool B)
{
	if(R) cbi(PORTD,R_LED); else sbi(PORTD,R_LED);
	if(G) cbi(PORTD,G_LED); else sbi(PORTD,G_LED);
	if(B) cbi(PORTD,B_LED); else sbi(PORTD,B_LED);
	for(uint8_t i=0; i<cas; i++)_delay_ms(1);
	sbi(PORTD,R_LED); 
	sbi(PORTD,G_LED); 
	sbi(PORTD,B_LED); 
};
void Zobraz::DSP(uint8_t znak)
{
	uint8_t vys;
	znak= znak & 0x1f;
	switch(znak)
	{
		case 0: vys=nula; break;
		case 1: vys=jedna; break;
		case 2: vys=dva; break;
		case 3: vys=tri; break;
		case 4: vys=styri; break;
		case 5: vys=pat; break;
		case 6: vys=sest; break;
		case 7: vys=sedem; break;
		case 8: vys=osem; break;
		case 9: vys=devat; break;
		case 10: vys=ahex; break;
		case 11: vys=bhex; break;
		case 12: vys=chex; break;
		case 13: vys=dhex; break;
		case 14: vys=ehex; break;
		case 15: vys=fhex; break;
		case 16: vys=dot; break;
		case 17: vys=err; break;
		case 18: vys=non; break;
		default: vys=nula;
	}
	
	this->zobr(vys);
};


//*****************************private****************************
void Zobraz::zobr(uint8_t vys){
	sbi(PORTC,OE);			//vystup do stavu HI
	for(uint8_t i=0;i<8;i++)
	{
		if((vys&0b10000000)==0b10000000) sbi(PORTC,SER);else cbi(PORTC,SER);//data
		sbi(PORTB,SRCLK);
		cbi(PORTB,SRCLK);  //hodiny
		vys=vys<<1;
	}
	sbi(PORTD,RCLK);		//prepis z posuvneho registra do pamate
	cbi(PORTD,RCLK);		// naspat
	cbi(PORTC,OE);			//set output
};