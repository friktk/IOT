/*
* Client.cpp
*
* Created: 4.3.2018 18:31:52
* Author: Lukas
*/


#include "Client.h"

// default constructor
Client::Client()
{
} //Client

// default destructor
Client::~Client()
{
} //~Client

bool Client::nastav_klienta(const char* ssid, const char* pass ){				//char *meno, char*pass
	this->write("ATE0");hwcrlf;
	if(!(this->test_zhody(10,"OK\r\n"))) return false;   // timeout 0.2s
	_delay_ms(100);
	
	this->write("AT"); hwcrlf;
	if(!(this->test_zhody(10,"OK\r\n"))) return false;   // timeout 0.2s
	_delay_ms(100);
	
	this->write("AT+CWMODE_CUR=1");	hwcrlf;	//nastavenie rezimu STA
	if(!(this->test_zhody(50,"OK\r\n"))) return false; // timeout 1s
	_delay_ms(100);
	
	this->write("AT+CIPMUX=1");	hwcrlf;	//podpora viacerych spojeni
	if(!(this->test_zhody(50,"OK\r\n"))) return false; // timeout 1s
	_delay_ms(100);
	
	this->write("AT+CWJAP_CUR=\"");
	this->write(ssid);
	this->write("\",\"");
	this->write(pass);
	this->write("\"");hwcrlf;
	_delay_ms(5000);
	
	if(!(this->test_zhody(250,"OK\r\n"))) return false; // timeout 5s
	_delay_ms(100);
	return true;
};

bool Client::nahraj_hodnotu(uint8_t kanal, uint16_t hodnota, const char* api_kluc, uint8_t field){
	uint8_t dlzka = 46; // dlzka bez hodnoty
	if (hodnota < 10)
		dlzka=dlzka+1;  // 1 cifra
	else if (hodnota < 100)
		dlzka=dlzka+2;  // 2 cifry
	else if (hodnota < 1000)
		dlzka=dlzka+3;  // 3 cifry
	else if (hodnota < 10000)
		dlzka=dlzka+4;  // 4 cifry
	else
		dlzka=dlzka+5;	// 5 cifier
		
	this->write("AT"); hwcrlf;
	if(!(this->test_zhody(10,"OK\r\n"))) return false;   // timeout 0.2s
	_delay_ms(100);
	
	this->write("AT+CIPSTART=");
	this->write(kanal);
	this->write(",\"TCP\",\"api.thingspeak.com\",80");
	hwcrlf;
	if(!(this->test_zhody(75,"OK\r\n"))) return false; // timeout 1.5s
	_delay_ms(100);
		
	posli_data(kanal,dlzka);													// posielanie spravy danej dlzky na dany kanal
	USART.clear();
	
//	this->write("GET /update?api_key=QSBQSRMAAK97DBBG&field1=");
	this->write("GET /update?api_key=");
	this->write(api_kluc);
	this->write("&field");
	this->write(field);
	this->write("=");
	this->write(hodnota);	
	hwcrlf;
	USART.clear();
//	_delay_ms(100);
//	if(!(this->test_zhody(50,"CLOSED"))) return false; // timeout 1s
	_delay_ms(100);
	
	zatvor_spojene(kanal);		// zatvorim spojenie
	USART.clear();
	return true;	
};

void Client::zatvor_spojene(uint8_t kanal){
	this->write("AT+CIPCLOSE=");
	this->write(kanal);
	hwcrlf;
	this->test_zhody2("OK\r\n");
};

bool Client::test_zhody(uint8_t max_cas, const char* data){
	int8_t pocitadlo = 0;
	_delay_ms(10);
	while((USART.available())==0){			//this->   ????
		_delay_ms(20);
		pocitadlo++;
		if(pocitadlo > max_cas){ this->Swrite(" TIMEOUT\r\n");
		return false; } // break; prekrocil sa cas odozvy
	}
	_delay_ms(20);					// aby dokoncil citanie do buff
	
	if(USART.find(data,true)){ USART.clear(); this->Swrite(" OK\r\n");	//this->
		return true;
	}
	else {this->Swrite(" CHYBA\r\n");
		return false;
	};
	USART.clear();
	return true;
};


bool Client::test_zhody2(const char* data){	//jednoduchy test zhody bez timeout
	for(uint8_t i=0;i<250;i++){
		_delay_ms(10);					// 10ms=100 prijatych znakov
		if((USART.available())>5)
		if(USART.find(data,true))return true;
	}
	return false;
};


bool Client::posli_data(uint8_t kanal, uint16_t pocet){
	this->write("AT+CIPSEND=");
	this->write(kanal);
	this->write(",");
	this->write(pocet);
	hwcrlf;
	while(1){
		while(USART.available()==0){};
		if(USART.read()=='>') return true;
	}
};

uint8_t Client::cakaj_IPD(void){		//vracia cislo kanala
	uint8_t pomoc1;
	uint8_t pomoc2=0;
	uint8_t x=0;
	while(1){
		while(USART.available()==0){};
		pomoc1= USART.read(true);
		switch(pomoc2)
		{
			case 0: if(pomoc1=='I') pomoc2=1;  else pomoc2=0; break;
			
			case 1: if(pomoc1=='P') pomoc2=2;  else pomoc2=0; break;
			
			case 2: if(pomoc1=='D') pomoc2=3;  else pomoc2=0; break;
			
			case 3: if(pomoc1==',') pomoc2=4;  else pomoc2=0; break;
			
			case 4: {x=pomoc1-48; pomoc2=5;} break;
			
			case 5: pomoc2++; if(pomoc1==',') break; else x = x*10 + pomoc1-48; break;
			
			default: pomoc2=0;
		}
		
		if(pomoc2==6)return x;
	}
};




bool Client::napisIP(){
	
	this->write("AT+CIFSR"); hwcrlf;
	int8_t pocitadlo = 0;
	while((USART.available())==0){			//this->   ????
		_delay_ms(20);
		pocitadlo++;
		if(pocitadlo > 40){ this->Swrite(" TIMEOUT\r\n");
		return false; } // break; prekrocil sa cas odozvy
	}
	
	_delay_ms(20);
	uint8_t pocet = USART.available();
	for(uint8_t i=0; i<pocet; i++)USART.SwriteByte(USART.read(true));
	USART.clear();
	return true;
};


bool Client::test_LNLN(void){
	
	uint8_t x=0;
	uint8_t pomoc1;
	while(1){
		while(USART.available()==0){};
		pomoc1=USART.read(true);
		
		switch(x){
			case 0: if(pomoc1=='\r')x=1;else x=0;  //CR  0xd
			break;
			case 1: if(pomoc1=='\n')x=2;else x=0;	 //LN  0xa
			break;
			case 2: if(pomoc1=='\r')x=2;else if(pomoc1=='\n')x=3; else x=0;    //CR    alebo   LN
			break;
			case 3: if(pomoc1=='\n')x=3;else x=0;
			break;
			default: x=0;
		}
		if(x==3){ USART.clear(); return true; }
		
	}
};

uint8_t Client::test_GET(void){
	
	uint8_t x=0;
	uint8_t pomoc1;
	uint8_t pomoc2=0;
	while(1){
		
		while(USART.available()==0){};
		pomoc1=USART.read(true);
		
		switch(pomoc2)
		{
			case 0: if(pomoc1=='G') pomoc2=1;  else pomoc2=0; break;
			
			case 1: if(pomoc1=='E') pomoc2=2;  else pomoc2=0; break;
			
			case 2: if(pomoc1=='T') pomoc2=3;  else pomoc2=0; break;
			
			case 3: if(pomoc1==' ') pomoc2=4;  else pomoc2=0; break;
			
			case 4: if(pomoc1=='/') pomoc2=5;  else pomoc2=0; break;
			
			default: pomoc2=0;
			
		}
		
		if(pomoc2==5){
			while(USART.available()==0){};
			x=USART.read(true);
			return x;		// vracia znak nasledujuci za GET /
		}
	}
};