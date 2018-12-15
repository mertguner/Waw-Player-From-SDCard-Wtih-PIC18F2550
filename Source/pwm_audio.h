#ifndef _PWM_AUDIO
#define _PWM_AUDIO

#define WAV_BUFFER_SIZE		256

void pwm_audio_init(void);
void set_sampling_rate(unsigned long rate);
void wav_putc(unsigned char c);

#define enable_audio()		TRISC &= 0b11111001
#define disable_audio()		TRISC |= 0b00000110


#endif	// _PWM_AUDIO
