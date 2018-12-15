#include <htc.h>

int SwitchState1,SwitchState2,SwitchState3,SwitchState4,SwitchState5,SwitchState6,SwitchState7,SwitchState8;

#define sw1 PORTAbits.RA0
#define sw2 PORTBbits.RB3
#define sw3 PORTAbits.RA1
#define sw4 PORTBbits.RB2
#define sw5 PORTAbits.RA2
#define sw6 PORTAbits.RA3
#define sw7 PORTAbits.RA4
#define sw8 PORTAbits.RA5

#define Mod PORTCbits.RC0

int Buton1(void);
int Buton2(void);
int Buton3(void);
int Buton4(void);
int Buton5(void);
int Buton6(void);
int Buton7(void);
int Buton8(void);
