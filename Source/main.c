/***************************************************

PIC18F SD/MMC WAV Audio Player
yus	- http://projectproto.blogspot.com/
May 2010

*****************************************************/
#include <htc.h>
#include <string.h>


#define _XTAL_FREQ 48000000

#pragma config FOSC     = HSPLL_HS
#pragma config PLLDIV   = 5				// (20 MHz crystal on PICDEM FS USB board)
#pragma config CPUDIV   = OSC1_PLL2		// Clock source from 96MHz PLL/2

#pragma config PWRT = ON
#pragma config BOR = ON
#pragma config BORV = 2
#pragma config WDT = OFF
#pragma config DEBUG = OFF
#pragma config LVP = OFF




#include "pff.h"
#include "wave_file.h"
#include "pwm_audio.h"
#include "button.h"
FATFS Fs;			/* File system object */
DIR Dir;			/* Directory object */
FILINFO Fno;		/* File information */

void delay(void);

void main(void)
{
int sayi = 0;
ADCON0bits.ADON = 0;
ADCON1 = 0x0F;
CMCON = 0x07;
CVRCON = 0x00;


TRISAbits.TRISA0 = 1;
TRISBbits.TRISB3 = 1;
TRISAbits.TRISA1 = 1;
TRISBbits.TRISB2 = 1;
TRISAbits.TRISA2 = 1;
TRISAbits.TRISA3 = 1;
TRISAbits.TRISA4 = 1;
TRISAbits.TRISA5 = 1;

TRISCbits.TRISC0 = 1;

TRISBbits.TRISB4 = 0;
TRISCbits.TRISC1 = 0;
LATBbits.LATB4 = 0;

SwitchState1 = sw1;
SwitchState2 = sw2;
SwitchState3 = sw3;
SwitchState4 = sw4;
SwitchState5 = sw5;
SwitchState6 = sw6;
SwitchState7 = sw7;
SwitchState8 = sw8;

_delay(65000);
	pwm_audio_init();

	while(1){
		delay();
		if (pf_mount(&Fs) ) continue;	/* Initialize FS */
Fno.fname[0] = 'S';
Fno.fname[1] = 'E';
Fno.fname[2] = 'S';
Fno.fname[3] = '1';
Fno.fname[4] = '.';
Fno.fname[5] = 'W';
Fno.fname[6] = 'A';
Fno.fname[7] = 'V';
		while(1){
sayi = (8*Buton8())+(7*Buton7())+(6*Buton6())+(5*Buton5())+(4*Buton4())+(3*Buton3())+(2*Buton2())+(Buton1());

_delay(5000);

if(sayi != 0)
{
			if (pf_opendir(&Dir, "")) break;				// open root directory
		//	while (!pf_readdir(&Dir, &Fno) && Fno.fname[0]) {
				
Fno.fname[3] = sayi + 48;
LATBbits.LATB4 = 1;
play_wave_file(Fno.fname);
LATBbits.LATB4 = 0;
sayi=0;

}				
		//	}
		}
		
	}
}

void delay(void)
{
	long i=0x7FFFF;
	while(--i);
}