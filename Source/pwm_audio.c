/****************************************************
PIC18 PWM Audio

PIC18F SD/MMC WAV Audio Player
yus	- http://projectproto.blogspot.com/
May 2010

PIC PWM Calculator
http://www.micro-examples.com/public/microex-navig/doc/097-pwm-calculator.html

PIC Timer Calculator
http://eng-serve.com/pic/pic_timer.html
*****************************************************/
#include <htc.h>
#include "pwm_audio.h"

#define WAV_BUFFER_MASK		(WAV_BUFFER_SIZE-1)

/*** private variables ***/
unsigned char TMR1H_preload, TMR1L_preload;
unsigned char WAV_L_BUFF[WAV_BUFFER_SIZE];
//unsigned char WAV_R_BUFF[WAV_BUFFER_SIZE];
volatile unsigned int pWAVIN, pWAVOUT;
//unsigned int pWAV_R_IN, pWAV_R_OUT;

/*** private functions ***/
void pwm_init(void)	//187.5kHz PWM @ 48MHz Fosc
{
	PR2 = 0b00111111 ;	// Freq = Fosc / [4*(PR2+1)]	:T2 prescaler = 1
	T2CON = 0b00000100 ;	// Timer2 on; prescaler = 1

	// PWM1
	CCPR1L = 0b00011111 ;	// 50% initial duty
	CCP1CON = 0b00111100 ;

	// PWM2
	CCPR2L = 0b00011111 ;	// 50% initial duty
	CCP2CON = 0b00111100 ;

	//TRISC &= 0b11111001;	// CCP1(RC2) and CCP2(RC1)
}

void set_pwm1_duty(unsigned char duty1)
{
	CCPR1L = duty1>>2;
	CCP1CON &= 0b11001111;
	CCP1CON |= (duty1<<4)&0b00110000;
}

void set_pwm2_duty(unsigned char duty2)
{
	CCPR2L = duty2>>2;
	CCP2CON &= 0b11001111;
	CCP2CON |= 0b00110000&(duty2<<4);
}

void timer1_init(void)
{
	T1CONbits.RD16 = 1;		// 16-bit operation

	T1CONbits.TMR1CS = 0;	// internal clock (Fosc/4) as source

	TMR1H = 0;
	TMR1L = 0;

	INTCONbits.GIE = 1; 	// Global Interrupt Enable
	INTCONbits.PEIE = 1; 	// Peripheral Interrupt Enable
	//IPR1bits.TMR1IP = 1;	// TMR1 Overflow Interrupt Priority bit ( 1 = high priority)
	PIR1bits.TMR1IF = 0;	// clear interrupt flag
	//PIE1bits.TMR1IE = 1;	// TMR1 Overflow Interrupt Enable bit

	T1CONbits.TMR1ON = 1; 	// enable timer 1
}

// High-priority service
void interrupt isr(void)
{
	/***** Timer 1 Code *****/
	if((PIE1bits.TMR1IE)&&(PIR1bits.TMR1IF))//&&(TMR1IP))
	{
LATCbits.LATC1 = !LATCbits.LATC1;
		TMR1H = TMR1H_preload;	// preset for timer1 MSB register
    	TMR1L = TMR1L_preload;	// preset for timer1 LSB register

    	set_pwm1_duty ( WAV_L_BUFF[pWAVOUT] );
		//set_pwm2_duty ( WAV_L_BUFF[pWAVOUT] );
		++pWAVOUT;
		pWAVOUT &= WAV_BUFFER_MASK;                    

    	if(pWAVOUT == pWAVIN)		// if buffer is empty
    	{
      		/* Disable the timer1 interrupt */
			PIE1bits.TMR1IE = 1;
    	} 

		PIR1bits.TMR1IF=0;	// clear event flag
	}
	
}



/***** Exported functions *******/
void pwm_audio_init(void)
{
	pwm_init();
	timer1_init();

	pWAVIN = pWAVOUT = 0;	// reset buffer
}
/*
static const unsigned char sampling_rates_tmr1[][2] =
{
// TMR1H preload	TMR1L preload	// @ Fosc = 48MHz
	250,			36,				// 8000.00 Hz
	251,			192,			// 11029.41 Hz
	252,			24,				// 12000.00 Hz
	253,			18,				// 16000.00 Hz
	253,			224,			// 22058.82 Hz
	254,			12,				// 24000.00 Hz
	254,			137,			// 32000.00 Hz
	254,			240,			// 44117.65 Hz
	255,			6				// 48000.00 Hz
};
*/

void set_sampling_rate(unsigned long rate)
{
	unsigned long preload;
	//preload = 65536 - (48000000 / (4 * rate) );
	preload = 65536 - ( 12000000 / rate );
    preload+=45;
	TMR1H_preload = (unsigned char)(preload>>8);
	TMR1L_preload = (unsigned char)(preload & 0x00FF);

}

void wav_putc(unsigned char c)
{
	// wait until buffer has an empty slot.
	while (((pWAVIN+1) & WAV_BUFFER_MASK)==pWAVOUT);
	WAV_L_BUFF[pWAVIN] = c;
	pWAVIN = (pWAVIN + 1) & WAV_BUFFER_MASK;	// increment input WAV buffer pointer

	PIE1bits.TMR1IE = 1;
}

