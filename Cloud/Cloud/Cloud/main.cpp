/*
* Server4.cpp
*
* Created: 25.2.2018 19:37:51
* Author : Juraj, Lukas
*/
#include "Usart.h"
#include "Esp1.h"
#include "Zobraz.h"
#include "ADC_klasika.h"
#include "Client.h"

/************************************** TU NASTAVIT *************************************************/
/***************************************************************************************************/

const char* SSID = "xxxxxx";				// SSID siete
const char* PSWD = "xxxxxx";				// Heslo siete
const char* API_KEY = "xxxxxxx";			// Write API kluc pre zapis do daneho kanalu (ThingSpeak)

/***************************************************************************************************/
/***************************************************************************************************/

int main(void)
{

	uint8_t kanal=0;		// kanal ESP, ktory budem pouzivat na uploadovanie sprav
	uint8_t field=1;		// field do ktoreho budem uploadovat spravy (namerane hodnoty)

	// HW reset ESP8266
	sbi(PORTD,RST_D);
	sbi(DDRD,RST_D);
	cbi(PORTD,RST_D);	// nie je potrebne   HW RESET
	_delay_ms(1);
	sbi(PORTD,RST_D);
	_delay_ms(1500);		//caka 1.5s
	
	// ADC
	ADC_klasika ADCk;
	ADCk.Nas_ADC(4, false);  // hodiny delene 16 jednorazovy rezim
	ADCk.Nas_kanal(0);
	// ADC
	
	//	Usart USART;  //nedeklarujeme bola deklarovana v Usart.h
	
	USART.begin( 115200,255, UsartModeEL::ASYNC_DOUBLE_SPEED );
	//USART.nastavSW_prijimac(16);		//len ak vyuzijeme SWRx buffer
	USART.Swrite("MODUL V REZIME KLIENT - STA\r\n");

	Client K;
	Zobraz Z1;
	Z1.DSP(1);


	K.nastav_klienta(SSID, PSWD);
//	K.napisIP();						Nepotrebujem vediet IP
	USART.Swrite("\n MODUL JE NASTAVENY\r\n");
	while(1)
	{
		// Odpocitavanie 15s - najmensi interval pre upload spravy (ThingSpeak)
		for(int8_t i=14; i>=0; i--)
		{
			Z1.DSP(i);
			_delay_ms(1000);
		}
		
		if(K.nahraj_hodnotu(kanal,ADCk.Daj_ADC(),API_KEY,field))
			Z1.DSP(1);
		else			// Ak nastala chyba
		{
			Z1.DSP(17);	// zobrazi err
			_delay_ms(1000);
		}
	}
}

