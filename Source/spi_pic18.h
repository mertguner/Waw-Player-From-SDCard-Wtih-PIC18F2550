#ifndef _SPI_PIC18
#define _SPI_PIC18

#include "integer.h"

#define   SPI_FOSC_64   0b00000010              // SPI Master mode, clock = Fosc/64
#define   SPI_FOSC_TMR2 0b00000011              // SPI Master mode, clock = TMR2 output/2
#define   SSPENB        0b00100000           // Enable serial port and configures SCK, SDO, SDI

/* Port Controls  (Platform dependent) */
//#define SS_TRIS()	TRISBbits.TRISB2 = 0
#define SS_TRIS()	TRISCbits.TRISC6 = 0
//#define SELECT()	LATBbits.LATB2 = 0	/* RB2: MMC CS = L */
#define SELECT()	LATCbits.LATC6 = 0	/* RB2: MMC CS = L */
//#define	DESELECT()	LATBbits.LATB2 = 1	/* RB2: MMC CS = H */
#define	DESELECT()	LATCbits.LATC6 = 1	/* RB2: MMC CS = H */

#define	MMC_SEL		1	/* MMC CS status (true:selected) */	

void init_spi(void);
void xmit_spi (BYTE);	/* Send a byte */
BYTE rcv_spi (void);	/* Send 0xFF and receive a byte */


#endif // _SPI_PIC18