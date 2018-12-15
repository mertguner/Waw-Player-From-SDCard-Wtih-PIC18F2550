

#include "button.h"

int Buton1(void)
{
    int sw1_state;

    sw1_state = sw1;
  
    if( sw1_state != SwitchState1)
    {
        SwitchState1 = sw1_state;
_delay(5000);
        if(SwitchState1 == Mod)
            return 1;             
    }

    return 0;                      

}

int Buton2(void)
{
    int sw2_state;

    sw2_state = sw2;
  
    if( sw2_state != SwitchState2)
    {
        SwitchState2 = sw2_state;
_delay(5000);
        if(SwitchState2 == Mod)
            return 1;                
    }

    return 0;                       

}

int Buton3(void)
{
    int sw3_state;

    sw3_state = sw3;
  
    if( sw3_state != SwitchState3)
    {
        SwitchState3 = sw3_state;
_delay(5000);
        if(SwitchState3 == Mod)
            return 1;                
    }

    return 0;                       

}

int Buton4(void)
{
    int sw4_state;

    sw4_state = sw4;
  
    if( sw4_state != SwitchState4)
    {
        SwitchState4 = sw4_state;
_delay(5000);
        if(SwitchState4 == Mod)
            return 1;                
    }

    return 0;                       

}

int Buton5(void)
{
    int sw5_state;

    sw5_state = sw5;
  
    if( sw5_state != SwitchState5)
    {
        SwitchState5 = sw5_state;
_delay(5000);
        if(SwitchState5 == Mod)
            return 1;                
    }

    return 0;                       

}

int Buton6(void)
{
    int sw6_state;

    sw6_state = sw6;
  
    if( sw6_state != SwitchState6)
    {
        SwitchState6 = sw6_state;
_delay(5000);
        if(SwitchState6 == Mod)
            return 1;                
    }

    return 0;                       

}

int Buton7(void)
{
    int sw7_state;

    sw7_state = sw7;
  
    if( sw7_state != SwitchState7)
    {
        SwitchState7 = sw7_state;
_delay(5000);
        if(SwitchState7 == Mod)
            return 1;                
    }

    return 0;                       

}

int Buton8(void)
{
    int sw8_state;

    sw8_state = sw8;
  
    if( sw8_state != SwitchState8)
    {
        SwitchState8 = sw8_state;
_delay(5000);
        if(SwitchState8 == Mod)
            return 1;                
    }

    return 0;                       

}