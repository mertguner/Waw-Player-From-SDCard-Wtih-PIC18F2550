/***************************************************

PIC18F SPI functions

*****************************************************/
#include <htc.h>
#include "spi_pic18.h"

void init_spi(void)
{
	SS_TRIS();				// SS pin
	TRISCbits.TRISC7 = 0;	// MOSI pin
	TRISBbits.TRISB0 = 1;	// MISO pin
	TRISBbits.TRISB1 = 0;	// SCK pin

	//ADCON1 = 0xFF;

	SSPSTAT &= 0x3F;			// power on state 
	SSPCON1 = 0x00;				// power on state

    SSPSTATbits.CKE = 1;		// Transmit occurs on transition from active to Idle clock state
    SSPSTATbits.SMP = 0;		// Input data sampled at middle of data output time

	SSPCON1 |= SPI_FOSC_64;			// select serial mode
	SSPCON1 |= SSPENB;              // enable synchronous serial port

	SSPCON1bits.WCOL = 0;		// Clear any previous write collision
}

void xmit_spi(BYTE c)
{
	unsigned char temp;  
	temp = SSPBUF;				// Clears BF
	PIR1bits.SSPIF = 0;         // Clear interrupt flag
	//SSPCON1bits.WCOL = 0;		// Clear any previous write collision
	SSPBUF = c;					// write byte to SSPBUF register
	//while( !SSPSTATbits.BF );  // wait until bus cycle complete
	while( !PIR1bits.SSPIF );	// wait until bus cycle complete 
}

BYTE rcv_spi (void)
{
	//unsigned char temp;
	//temp = SSPBUF;        // Clear BF
	//PIR1bits.SSPIF = 0;      // Clear interrupt flag
	SSPBUF = 0xFF;           // initiate bus cycle
	while ( !SSPSTATbits.BF );                  // wait until cycle complete
	//while(!PIR1bits.SSPIF);  // wait until cycle complete
	return ( SSPBUF );       // return with byte read 

}

