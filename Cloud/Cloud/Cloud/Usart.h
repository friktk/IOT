/*
 * Usart.h
 * Trieda Usart vychádza z kódu autora Mircea Diaconescu  a je upravena/zjednodusena a rozsirena 
 * o softwerovy USART. Povodny kod je dobre strukturovany a lahko pochopitelny. Preto som ho vybral
 * ako vhodny pre vyuzitie pri vyucbe.
 * Clenske fcie (metody) prevzate z originalu su:
 *_______________________fcie definujuce parametre HW USART-u_______________________
 * void setFrameLength( UsartFrameLengthEL frameLength);
 
 * void setStopBit( UsartStopBitEL stopBit);
 
 * void setParity( UsartParityEL parity);

 * void begin( const uint32_t baud, uint16_t rxBuffMaxLen, UsartModeEL mode = UsartModeEL::ASYNC_DOUBLE_SPEED);
 * inline void begin( const uint32_t baud, UsartModeEL mode = UsartModeEL::ASYNC_DOUBLE_SPEED) { begin( baud, 64, mode);};
 *______________________________________________________________________________________________
 * uint16_t getMaxLength();									// vracia max pocet bytov v buffery	
 * uint16_t getRxLostBytesNr();								// vracia pocet stratenych bytov 
 * uint16_t available();									// vracia pocet bytov v buffri
 * bool clear();											// inicializuje pointre buffra
 * bool find( const char* data, bool removeReadByte = true);// hlada data v buffri
 * bool findFromPM( const char pmData[], bool removeReadByte = true); //hlada data v buffri
 *_________________________________________________________// a porovnava ich s retazcom z PM
 * void writeByte( uint8_t ub);								// vystup Bytu na HW USART
 * void writeBytes( uint8_t* data, const uint16_t dataLen); // vystup datalen bytov
 * void write( const char* data);							// vystup char
 * void write( long num);									// vystup cisla long	
 * void write( unsigned long num);							// vystup neznamienkoveho long
 * void write( int num);									// vystup int
 * void write( unsigned int num);							// vystup neznamienkoveho int
 * uint8_t read( bool removeReadByte = true);				// citanie jedneho znaku z buff
 *__________________________________________________________// ak true znak v buffri sa zmaze
 * bool find( const char* data, bool removeReadByte = true);	// hladanie zhody data s obsahom buffra
 * bool findFromPM( const char pmData[], bool removeReadByte = true); // zhody PM a buffra  
 *__________________________________________________________________________
 * 
 * Mena vsetkych funkcii pre SW USART zacinaju pismenom S nie vsetky fcie z HW su implenetovane aj v SW
 * Nie je to vsak problem rozhodol som sa neimplementovat prijimaci buffer na SW prijimac 
 * je to odskusane a opoznamkovane. Pre nase ucely kde SW USART je vyhradeny pre referencne vypisy to nie 
 * je potrebne. Vyznam SW fcii je rovnaky ako pri HW Usarte.
 *_________________________________________________________
 * uint8_t SreadByte(void);
 * void SwriteByte( uint8_t ub);
 * void SwriteBytes( uint8_t* data, const uint16_t dataLen);
 * void Swrite( const char* data);
 * void Swrite( long num);
 * void Swrite( unsigned long num);
 * void Swrite( int num);
 * void Swrite( unsigned int num);
 * void SwriteFromPM( const char pmData[]);
 * Uprava: 12.12.2017 14:46:01
 *  Author upravy: Juraj
 */ 

#ifndef USART_H_
#define USART_H_
#ifndef F_CPU
#define F_CPU 12000000UL
#endif
#include "Util.h"
#include "Board.h"

/****************************************************************/
/* Enumeration of communication modes supported by USART        */
/****************************************************************/
enum class UsartModeEL {			//enum class UsartModeEL {
  ASYNC_NORMAL = 0,
  ASYNC_DOUBLE_SPEED = 1,
  SYNC_MASTER = 2
};

/****************************************************************/
/* Enumeration defining communication parity modes              */
/****************************************************************/
enum class UsartParityEL {  
  NONE = 0,
  EVEN = 2,
  ODD = 3
};

/****************************************************************/
/* Enumeration defining communication stop bits                 */
/****************************************************************/
enum class UsartStopBitEL {		
  ONE = 1,
  TWO = 2
};

/****************************************************************/
/* Enumeration defining communication frame length              */
/****************************************************************/
enum class UsartFrameLengthEL {
  FIVE_BITS = 5,
  SIX_BITS = 6,
  SEVEN_BITS = 7,
  EIGHT_BITS = 8,
  NINE_BITS = 9
 };

/****************************************************************/
/* Define the Usart class implementing the USART communication  */
/****************************************************************/
class Usart {
  public:
    Usart();		
    ~Usart();
   // void nastavSW_prijimac(uint16_t);	//Len ak vyuzivame Rx buffer pri SW UARTe
    void setFrameLength( UsartFrameLengthEL frameLength);
    
    void setStopBit( UsartStopBitEL stopBit);
    
    void setParity( UsartParityEL parity);
  
    void begin( const uint32_t baud, uint16_t rxBuffMaxLen, UsartModeEL mode = UsartModeEL::ASYNC_DOUBLE_SPEED);
    inline void begin( const uint32_t baud, UsartModeEL mode = UsartModeEL::ASYNC_DOUBLE_SPEED) { begin( baud, 64, mode);};
   // hardverovy USART
    uint8_t readByte(void);  // len bez prijimacieho buffra
	void writeByte( uint8_t ub);
    void writeBytes( uint8_t* data, const uint16_t dataLen);
    void write( const char* data);
    void write( long num);
    void write( unsigned long num);
    void write( int num);
    void write( unsigned int num);
	void writeFromPM( const char pmData[]);
    //sofvertovy USART 19200 Bd
	 uint8_t SreadByte(void);
	 void SwriteByte( uint8_t ub);
	 void SwriteBytes( uint8_t* data, const uint16_t dataLen);
	 void Swrite( const char* data);
	 void Swrite( long num);
	 void Swrite( unsigned long num);
	 void Swrite( int num);
	 void Swrite( unsigned int num);
	 void SwriteFromPM( const char pmData[]);
    // funkcie vztahujuce sa k buffer-u
	uint16_t getMaxLength();
    uint16_t getRxLostBytesNr();
    uint8_t read( bool removeReadByte = true);
    uint16_t available();
    bool clear();
    bool find( const char* data, bool removeReadByte = true);
    bool findFromPM( const char pmData[], bool removeReadByte = true);
    // friend operation which deals with USARTn_RX_vector(s) interrupts
    // using friend operation allows to access private fields of this class
    friend void ::rxVector( void);
//	friend void ::SrxVector( void);  // len ak chces aj SWUART s buffrom
  private:
    // Define the ring buffer pointer.
    // Must be volatile because write by interrupts.
    volatile uint8_t* rxBuffStart;
    volatile uint8_t* rxBuffEnd;
    volatile uint8_t* rxDataStart;
    volatile uint8_t* rxDataTStart;
    volatile uint8_t* rxDataEnd;
   
    // Current number of bytes stored in the buffer.
    // Must be volatile because write by interrupts.
    volatile uint16_t rxLength;
    // The number of bytes lost from the buffer because 
    // it was not read and the buffer received more data
    // that it can store without overriding existing data.
    // Must be volatile because write by interrupts.
    volatile uint16_t rxLostBytesNr=0;
    // maximum receive buffer length
    uint16_t rxMaxLength=255;
    // communication baud rate in bits per second (e.g., 115200bps = 115.2kbps)
    uint32_t baud;
      
    volatile uint8_t znak;
  };


extern Usart USART;

#endif /* USART_H_ */