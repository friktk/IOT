/*
 * Usart.cpp
 *
 * Created: 12.12.2017 14:46:18
 *  Author: Juraj
 */ 
#include "Usart.h"

/************************************************************************/
/* @constructor                                                         */
/* Create a Usart object                                                */
/************************************************************************/
Usart::Usart() {		
  
  /** default communication settings **/  
  // use no parity
  this->setParity( UsartParityEL::NONE);
  // use one stop bit
  this->setStopBit( UsartStopBitEL::ONE);
  // frame (data) length = 8 bits
  this->setFrameLength( UsartFrameLengthEL::EIGHT_BITS);
  sbi(DDRC,STX);
  sbi(PORTC,STX);  // stav H na linke vysielaca
  cbi(DDRC,SRX);
  sbi(PORTC,SRX);	// pull up
};

/************************************************************************/
/* @destructor                                                          */
/* Destroy the Usart object by freeing up the allocated memory          */
/************************************************************************/
Usart::~Usart() {
  delete this->rxBuffStart; 
//  PCMSK1 &= ~(1<<PCINT11);  //maskovat prerusenie od SRX len pri pouziti Buf v SW UARTe
};
/************************************************************************/
/* clenska fcia      Len ak chceme vyuzivat Rx buffer pri pouzivani SW UARTu                                                     */
/* nastav SWprijimac                            */
/* bez parametrov                                                   */
/* povoli povolenie prerusenia od SRX  a nastavi buffer vyhradi priestor na halde*/
/************************************************************************/
/*
void Usart::nastavSW_prijimac(uint16_t rxBuffMaxLen){
	PCMSK1 |=(1<<PCINT11);	// odmaskovat SRX
	PCICR |=(1<<PCIE1);		//odmaskovat skupinu
	this->rxBuffStart = (uint8_t*)malloc( this->rxMaxLength);
	this->rxBuffEnd = this->rxBuffStart + this->rxMaxLength;
	this->rxDataStart = this->rxBuffStart;
	this->rxDataTStart = this->rxBuffStart;
	this->rxDataEnd = this->rxBuffStart;
	this->rxLength = 0;
	this->rxLostBytesNr = 0;
	this->rxMaxLength = rxBuffMaxLen;
		
	sei();					// globalne povolit prerusenia
};
   */
/************************************************************************/
/* @method                                                              */
/* Set UART/USART frame length (5 to 9 bits)                            */
/* @param frameLength                                                   */
/*          the frame length - values from UsartFrameLengthEL.xxx       */
/************************************************************************/
void Usart::setFrameLength( UsartFrameLengthEL frameLength) {
  switch ( frameLength) {
    case UsartFrameLengthEL::FIVE_BITS: 
      // set data transmission mode: 5-bit (UCSZn2 = 0; UCSZn1 = 0; UCSZn0 = 0;)
    
      UCSR0C &= ~(1<<UCSZ00) | ~(1<<UCSZ01);
	  // UCSZn2 bit is located in UCSRnB registry!
   
	  UCSR0B &=~(1<<UCSZ02);  
    break;
    case UsartFrameLengthEL::SIX_BITS: 
      // set data transmission mode: 6-bit (UCSZn2 = 0; UCSZn1 = 0; UCSZn0 = 1;)
  
    UCSR0C |=(1<<UCSZ00);
	  
     UCSR0C &= ~(1<<UCSZ01);
	  // UCSZn2 bit is located in UCSRnB registry!
  
	UCSR0B &= ~(1<<UCSZ02);
    break;
    case UsartFrameLengthEL::SEVEN_BITS: 
      // set data transmission mode: 7-bit (UCSZn2 = 0; UCSZn1 = 1; UCSZn0 = 0;)
    
     UCSR0C &= ~(1<<UCSZ00);
	 
      UCSR0C |= (1<<UCSZ01);
	  // UCSZn2 bit is located in UCSRnB registry!
    
    UCSR0B &= ~(1<<UCSZ02);
	break;
    case UsartFrameLengthEL::EIGHT_BITS: 
      // set data transmission mode: 8-bit (UCSZn2 = 0; UCSZn1 = 1; UCSZn0 = 1;)
    
     UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
	  // UCSZn2 bit is located in UCSRnB registry!
    
     UCSR0B &= ~(1<<UCSZ02);
    break;
    case UsartFrameLengthEL::NINE_BITS: 
      // set data transmission mode: 9-bit (UCSZn2 = 1; UCSZn1 = 1; UCSZn0 = 1;)
       
     UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
	  // UCSZn2 bit is located in UCSRnB registry!
    
	UCSR0B |= (1<<UCSZ02);
    break;
  }  
};


/************************************************************************/
/* @method                                                              */
/* Set UART/USART transmission parity                                   */
/* @param parity                                                        */
/*          the parity - values from UsartParityEL.xxx                  */
/************************************************************************/
void Usart::setParity( UsartParityEL parity) {
  switch ( parity) {
    case UsartParityEL::NONE:
      // set data transmission mode: no parity ( UPMn0 = 0; UPMn1 = 0;)
     
	UCSR0C &= ~(1<<UPM00) | ~(1<<UPM01);
    break;
    case UsartParityEL::EVEN: 
      // set data transmission mode: even ( UPMn0 = 0; UPMn1 = 1;)
  
   UCSR0C &= ~(1<<UPM00);
   UCSR0C |= (1<<UPM01);
    break;
    case UsartParityEL::ODD:
      // set data transmission mode: odd ( UPMn0 = 1; UPMn1 = 1;)
  
	UCSR0C |= (1<<UPM00) | (1<<UPM01);
    break;
  }
};


/************************************************************************/
/* @method                                                              */
/* Set UART/USART transmission stop bit                                 */
/* @param stopBit                                                       */
/*          the stop bit - values from UsartStopBitEL.xxx               */
/************************************************************************/
void Usart::setStopBit( UsartStopBitEL stopBit) {
  switch ( stopBit) {
    // one stop bit
    case UsartStopBitEL::TWO:
  
    UCSR0C &= ~(1<<USBS0);
	break; 
    // two stop bits
    case UsartStopBitEL::ONE:

    UCSR0C |= (1<<USBS0);
    break;
  }
};

/************************************************************************/
/* @method                                                              */
/* Check if any data is stored in the RX buffer                         */
/* @return the number of bytes available in the RX buffer (0 if empty)  */
/************************************************************************/
uint16_t Usart::available() {
 	return this->rxLength;				
 };

/************************************************************************/
/* @method                                                              */
/* Clear the RX buffer - reset buffer pointers to their initial state   */
/* @return true so it can be used in logical expressions with ease      */
/************************************************************************/
bool Usart::clear() {
 
 bool txEnabled =  (UCSR0B & (1<<TXEN0)) > 0;
  // disable USART data receiving until clearing the buffer
  if ( txEnabled) {
  
   UCSR0B &= ~(1<<TXEN0);
  }
  this->rxDataStart = this->rxBuffStart;	//USART.xxxxx
  this->rxDataTStart = this->rxBuffStart;
  this->rxDataEnd = this->rxBuffStart;
  this->rxLength = 0;
  this->rxLostBytesNr = 0;
  // if TX was enabled when entering this method
  // then enable it back after cleared the buffer
  if ( txEnabled) {
  //  *(USART.ucsrb) |= (1 << USART.txen);
  UCSR0B |=(1<<TXEN0);
  }
  return true;
};

/************************************************************************/
/* @method                                                              */
/* Get the maximum length of the RX buffer                              */
/* @return the maximum number of bytes stored by the RX buffer          */
/************************************************************************/
uint16_t Usart::getMaxLength() {
  return this->rxMaxLength;
};

/************************************************************************/
/* @method                                                              */
/* Get the number of bytes which were lost because TX buffer overrun    */
/* The number of bytes are computed from the last time when the buffer  */
/* was cleared (by calling the 'clear' method.                          */
/* NOTE: the value is represented as a 16 bits unsigned integer!        */
/* @return the number of RX bytes lost because buffer overrun           */
/************************************************************************/
uint16_t Usart::getRxLostBytesNr() {
  return this->rxLostBytesNr;
};

/************************************************************************/
/* @method                                                              */
/* Start USART communication                                            */
/* NOTE: calling this produces also the RX buffer memory allocation     */
/* @param baud                                                          */
/*          the baud rate (in bps, e.g. 9600)                           */
/* @param rxBuffMaxLen                                                  */
/*          the maximum size (number of bytes) stored by the RX buffer  */
/* @param mode                                                          */
/*           the usart mode (one of UsartModeEL.xxx)                    */
/************************************************************************/
void Usart::begin( const uint32_t baud, uint16_t rxBuffMaxLen, UsartModeEL mode) {
  uint16_t bRate = 0;
  uint8_t bMode = 0;
  // initialize the buffer
  this->rxBuffStart = (uint8_t*)malloc( this->rxMaxLength);	//USART.xxx
 
  this->rxBuffEnd = this->rxBuffStart + this->rxMaxLength;
  this->rxDataStart = this->rxBuffStart;
  this->rxDataTStart = this->rxBuffStart;
  this->rxDataEnd = this->rxBuffStart;
  this->rxLength = 0;
  this->rxLostBytesNr = 0;
  this->rxMaxLength = rxBuffMaxLen;
  
  // store baud rate
  this->baud = baud;
  // compute baud rate value for UBRR register
  switch ( mode) {
    case UsartModeEL::SYNC_MASTER:
      bRate = ( F_CPU / 2 / baud - 1) / 2;
      bMode = 0;
      // UMSELn0 = 1 and UMSELn1 = 0 for synchronous mode 
   
     UCSR0C |=(1<<UMSEL00);
	
	UCSR0C &= ~(1<<UMSEL01);
    break;
    case UsartModeEL::ASYNC_DOUBLE_SPEED:
      bRate = ( F_CPU / 4 / baud - 1) / 2;
      bMode = 1;
      // UMSELn0 = 0 and UMSELn1 = 0 for asynchronous mode 
    
	UCSR0C &= ~(1<<UMSEL00) | ~(1<<UMSEL01); 
    break;
    case UsartModeEL::ASYNC_NORMAL:
      bRate = ( F_CPU / 8 / baud - 1) / 2;
      bMode = 0;
      // UMSELn0 = 0 and UMSELn1 = 0 for asynchronous mode 
   
	UCSR0C &= ~(1<<UMSEL00) | ~(1<<UMSEL01); 
    break;
  }
  // Set USART transmission mode:
  // U2Xn = 0 for asynchronous, normal speed or synchronous 
  // U2Xn = 1 for asynchronous, double speed
 // *(this->ucsra) = ( bMode << this->u2x);
  UCSR0A = (bMode<<U2X0); 
  // set the USART High register byte
 
	UBRR0H = (bRate>>8);
  // set the USART Low register byte

	UBRR0L = bRate;
  // enable USART transmission
	UCSR0B |=(1<<TXEN0);
  // enable USART reception & USARTn_RX_vect interrupt

	UCSR0B |= (1<<RXEN0) | (1<<RXCIE0);
  // set asynchronous USART mode (UMSEL00 = 0; UMSEL01 = 0;)
  /*UCSR0C &= ~(1 << UMSEL00) | ~(1 << UMSEL01);
 
 */
  // enable interrupts
  sei();
};

/************************************************************************/
/* @method                                                              */
/* Read the next byte from the RX buffer                                */
/* NOTE: call this method only after checking that the buffer is not    */
/*       empty, i.e., by calling the 'available' method, otherwise the  */
/*       returned value will be 0!                                      */
/* @param removeReadByte                                                */
/*          flag allowing to specify if the byte is deleted from buffer */
/* @return the next byte from the buffer                                */
/************************************************************************/
uint8_t Usart::read( bool removeReadByte) {
  uint8_t data = 0;
  // return 0 if the buffer is empty
  if (this->rxLength == 0) {		//USART.xxxx
    return 0;
  }
  if ( removeReadByte) {
  
  	data = *(this->rxDataStart);	
	   this->rxDataStart++;		// ++;
    if ( this->rxDataStart == this->rxBuffEnd) {
      this->rxDataStart = this->rxBuffStart;
    }
   this->rxLength--;					// this->rxLength--;
  } else {
    data = *(this->rxDataTStart);
    this->rxDataTStart++;
    if (this->rxDataTStart == this->rxBuffEnd) {
      this->rxDataTStart = this->rxBuffStart;
    }
  }
  return data; 
};
/*************************************************************************************
* Tuto metodu som doplnil pre jednoduchy (nebufrovany) vstup prostrednicvom
* USART. Je to z toho dovodu aby som vyskusal kolko zdrojov usetrim, ak nepouzijem
 buff vstup. Pre usporu je potrebne zakazat ISR, RXvect, read, available, 
 *clear... a modifikovat/poznamkovat vsetky cleny suvisiace s pouzivanim buffra.
* vracia: prijaty znak uint8_t (char)
**************************************************************************************/
uint8_t Usart::readByte(void){
	loop_until_bit_is_set( UCSR0A, RXC0);  //this->rxc *(this->ucsra)
	// citanie dat z registra UDR0
	return UDR0;		
};

/*************************************************************************************
* Tuto metodu som doplnil pre jednoduchy (nebufrovany) vstup prostrednicvom 
* vyvodu SRX predpoklada sa frame 8N1 a rychlost prenosu 19200 Bd v buducnosti by bolo 
* vhodne metodu SreadByte rozsirit o argument komunikacna rychlost. Podla mna by bolo 
* mozne pri Clkmain 12 MHz dosiahnut modulacnu rychlost az do 100000 Bd. 
* vracia: prijaty znak uint8_t (char)
**************************************************************************************/
uint8_t Usart::SreadByte(void){
	while((PINC & (1<<SRX))==(1<<SRX)){};   // start bit
	this->znak = 0;
	_delay_us(26);					// 52
	for(uint8_t i = 0; i < 8; i++)
	{
		this->znak = this->znak>>1;
		_delay_us(51);			// 103 us + 16 instrukcii
		if((PINC & (1<<SRX)) == (1<<SRX)) this->znak = this->znak | 0b10000000;
	}
	return this->znak;
};
/************************************************************************/
/* @method                                                              */
/* Write a new byte in the UDRn register, for being transmitted         */
/* @param ub                                                            */
/*          the unsigned byte to write                                  */
/************************************************************************/
void Usart::writeByte( uint8_t ub) {
  // Wait for URD0 register to be ready for the next data byte.
  // The URDE0 bit from the UCSR0A registry is set when USART 
  // data register is empty and new data can be transmitted
 	loop_until_bit_is_set(UCSR0A, UDRE0 );		//*(this->ucsra), this->udre
  // write the next data byte
	UDR0 = ub;									//*(this->udr) = ub;
};

void Usart::SwriteByte( uint8_t ub) {	//19200 Bd 8N1
	
	cbi(PORTC,STX);						// start bit
	_delay_us(52);						// 104
	for(uint8_t i = 0; i < 8; i++)
	{
		if((ub & 1) == 1)sbi(PORTC,STX); else cbi(PORTC,STX);
		ub = ub >> 1;
		_delay_us(52);					//103
	}
	sbi(PORTC,STX);						// 1 stop bit
	_delay_us(52);						//104
};

/************************************************************************/
/* @method                                                              */
/* Write a string to USART where the string source is PROGMEM           */
/* @param pmData                                                        */
/*          the PROGMEM source                                          */
/************************************************************************/
void Usart::writeFromPM( const char pmData[]) {
  char c = 0;
  while ( 0 != ( c = pgm_read_byte(pmData++))) {
    this->writeByte( c);
  } 
};
  void Usart::SwriteFromPM( const char pmData[]){
	  char c = 0;
	  while ( 0 != ( c = pgm_read_byte(pmData++))) {
		  this->SwriteByte( c);
	  }
  };
/************************************************************************/
/* @method                                                              */
/* Write a set of unsigned bytes value to USART output.                 */
/* @param data                                                          */
/*          the pointer referencing the set of bytes to write           */
/* @param dataLen                                                       */
/*          the length (number of bytes) of the data to be transmitted  */
/************************************************************************/
void Usart::writeBytes( uint8_t* data, const uint16_t dataLen) {
  for ( uint16_t i = 0; i < dataLen; i++) {
    this->writeByte( *(data++));
  }
};

void Usart::SwriteBytes( uint8_t* data, const uint16_t dataLen) {
	for ( uint16_t i = 0; i < dataLen; i++) {
		this->SwriteByte( *(data++));
	}
};
/************************************************************************/
/* @method                                                              */
/* Write a string ( '\0' terminated char array/pointer) to USART.       */
/* Maximum allowed length for the string depends on the memory size!    */
/* @param data                                                          */
/*          the pointer referencing the string to write                 */
/************************************************************************/
void Usart::write( const char* data) {
  for ( const char* s = data; *s; ++s) {
    this->writeByte( *s);
  }
};

void Usart::Swrite( const char* data) {
	for ( const char* s = data; *s; ++s) {
		this->SwriteByte( *s);
	}
};
/************************************************************************/
/* @method                                                              */
/* Write a signed long number to USART.                                 */
/* @param num                                                           */
/*          the number to write                                         */
/************************************************************************/
void Usart::write( long num) {
  if ( num < 0) {
    this->writeByte( '-');
  }
  this->write( ( unsigned long) num);
}

void Usart::Swrite( long num) {
	if ( num < 0) {
		this->SwriteByte( '-');
	}
	this->Swrite( ( unsigned long) num);
}
/************************************************************************/
/* @method                                                              */
/* Write an unsigned long number to USART.                              */
/* @param num                                                           */
/*          the number to write                                         */
/************************************************************************/
void Usart::write( unsigned long num) {
  // max digits number for signed/unsigned long is 10
  char digits[10];
  uint8_t len = 0;
  do {
    digits[len] = '0' + ( num % 10);
    len++;
  } while ( num /= 10);
  while ( len > 0) {
     this->writeByte( digits[--len]);  
  }
}

void Usart::Swrite( unsigned long num) {
	// max digits number for signed/unsigned long is 10
	char digits[10];
	uint8_t len = 0;
	do {
		digits[len] = '0' + ( num % 10);
		len++;
	} while ( num /= 10);
	while ( len > 0) {
		this->SwriteByte( digits[--len]);
	}
}
/************************************************************************/
/* @method                                                              */
/* Write a signed integer number to USART.                              */
/* @param num                                                           */
/*          the number to write                                         */
/************************************************************************/
void Usart::write( int num) {
  this->write((long) num);
}
void Usart::Swrite( int num) {
	this->Swrite((long) num);
}
/************************************************************************/
/* @method                                                              */
/* Write an unsigned integer number to USART.                           */
/* @param num                                                           */
/*          the number to write                                         */
/************************************************************************/
void Usart::write( unsigned int num) {
  this->write(( unsigned long) num);
}

void Usart::Swrite( unsigned int num) {
	this->Swrite(( unsigned long) num);
}

/************************************************************************/
/* @method                                                              */
/* Find data in the USART buffer                                        */
/* This method clears the USART buffer up to, and including the data,   */
/* if the data is found, otherwise clears all the data from the buffer  */ 
/* NOTE: the maximum data length is 255!                                */
/*                                                                      */
/* @param data                                                          */
/*          the data to search for in the buffer                        */
/* @return true if data was found, false otherwise                      */
/************************************************************************/
bool Usart::find( const char* data, bool removeReadByte) {
  uint8_t pos = 0, len = 0, avl = 0;
  const char* s;
  for ( s = data; *s; ++s, len++); 
  // null search data..
  if ( *data == 0) {
    return false;
  }
  // searching the TX buffer as long as it contains data
  avl = this->available();
  this->rxDataTStart = this->rxDataStart;
  while ( avl > 0) {
    // char/byte match on current position
    if ( *(data + pos) == this->read( removeReadByte)) {
      pos++;
    } 
    // no match for current position
    else {
      pos = 0;
    }
    // full data match!
    if ( pos == len) {
      return true;
    }
    avl--;
  }
  // no match if this point was reached
  return false;
};

/************************************************************************/
/* @method                                                              */
/* Find data in the USART buffer - the data to find is extracted        */
/* from PROGMEM ( program memory area)                                  */
/* This method clears the USART buffer up to, and including the data,   */
/* if the data is found, otherwise clears all the data from the buffer  */
/* NOTE: the maximum data length is 255!                                */
/*                                                                      */
/* @param pmData                                                        */
/*          the PROGMEM data to search for in the buffer                */
/* @return true if data was found, false otherwise                      */
/************************************************************************/
bool Usart::findFromPM( const char pmData[], bool removeReadByte) {
  char c = 0;
  const char* data = pmData;
  char* ramData = nullptr;
  uint8_t len = 0;
  bool result = false;
  // read the data from PROGMEM for length computation
  while ( 0 != ( c = pgm_read_byte(data++))) {
    len++;
  }  
  // load the data from PROGMEM and store it in RAM
  ramData = (char*)malloc( len + 1);
  data = pmData;
  while ( 0 != ( c = pgm_read_byte(data++))) {
    *(ramData) = c;
    ramData++;
  } 
  *(ramData) = '\0';
  ramData -= len;
  result = this->find( ramData, removeReadByte);
  free( ramData); 
  return result;
};

/************************************************************************/
/* @method                                                              */
/* Define the actions performed by the interrupt. This method is used   */
/* with the USARTn_RX_vector to perform a USART buffered reading.       */
/* @param udr                                                           */
/*          the UDRn register                                           */
/* @param usart                                                         */
/*          the Usart instance used with the interrupt (USARTn)         */
/************************************************************************/

class Usart USART;		

void rxVector() {
 
 
   *(USART.rxDataEnd) = UDR0;    
								
  USART.rxDataEnd++;
 
  if ( USART.rxDataEnd >= USART.rxBuffEnd) {
   USART.rxDataEnd = USART.rxBuffStart;
  }
  
  if ( USART.rxLength == USART.rxMaxLength) {
    USART.rxLostBytesNr++;
      if ( ( USART.rxDataStart + 1) == USART.rxBuffEnd) {
      USART.rxDataStart = USART.rxBuffStart;
	  }
	else    USART.rxDataStart++;
  }
 	else   USART.rxLength++; 
	
 }    
 
  
 /*      // Len ak chceme vyuzivat buffer aj na prijem cez softwarovy UART
 void SrxVector() {
	
	if((PINC & (1<<SRX))!=(1<<SRX))   // start bit
	 USART.znak = 0;
	_delay_us(26);					// 52
	for(uint8_t i = 0; i < 8; i++)
	{
		USART.znak = USART.znak>>1;
		_delay_us(51);			// 103 us + 16 instrukcii
		if((PINC & (1<<SRX)) == (1<<SRX)) USART.znak = USART.znak | 0b10000000;
	}
	 *(USART.rxDataEnd) = USART.znak;    // *(usart.rxDataEnd) +2
	 USART.rxDataEnd++;
	 
	 if ( USART.rxDataEnd == USART.rxBuffEnd) {
		 USART.rxDataEnd = USART.rxBuffStart;
	 }
	 
	 if ( USART.rxLength == USART.rxMaxLength) {
		 USART.rxLostBytesNr++;
		 if ( ( USART.rxDataStart + 1) == USART.rxBuffEnd) {
			 USART.rxDataStart = USART.rxBuffStart;
		 }
		 else    USART.rxDataStart++;
	 }
	 else   USART.rxLength++;
	 
 }
 */
 
 ISR( USART_RX_vect) {
 rxVector();
  };

 
/*  // Len ak vyuzivame Rx buffer aj pri SW UARTe
  ISR( PCINT1_vect){
	
	PCMSK1 &= ~(1<<PCINT11);	// maska prerusenia   
	SrxVector();
	PCMSK1 |= (1<<PCINT11);	// povolenie prerusenia
  };
  */