/* 
* Client.h
*
* Created: 4.3.2018 18:31:52
* Author: Lukas
*/


#ifndef __CLIENT_H__
#define __CLIENT_H__
#include "Usart.h"

class Client:public Usart
{
//variables
public:
protected:
private:

//functions
public:
	Client();
	~Client();
	bool nastav_klienta(const char* ssid, const char* pass );		//char *meno, char*pass);
	bool nahraj_hodnotu(uint8_t kanal, uint16_t hodnota, const char* api_kluc, uint8_t field);
	bool napisIP();
	uint8_t cakaj_IPD(void);		//vracia cislo kanala
	bool test_LNLN(void);			//test konca ziadosti CRLNCRLN CRLNLN
	uint8_t test_GET(void);			// vracia prvy znak za "GET /"
	
	
protected:
private:
	bool test_zhody(uint8_t max_cas, const char* data);
	bool test_zhody2(const char* data);
	bool posli_data(uint8_t kanal, uint16_t pocet);
	void zatvor_spojene(uint8_t kanal);

}; //Client

#endif //__CLIENT_H__
