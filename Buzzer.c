/*
This file implements the methods declared in Buzzer.h.
*/

#include "Buzzer.h"

#define _XTAL_FREQ      4000000
#define TONE_LENGTH     250

void InitBuzzer(void)
{
    PR2 = 58;
    CCPR1L = PR2 >> 1;
    TRISC &= ~(1<<2);
    T2CON |= 0x07;
    CCP1CON = 0x0C;
    TurnBuzzerOff();
}

void TurnBuzzerOff(void)
{
    T2CON &= ~(1<<2);       
}

void TurnBuzzerOn(void)
{
    T2CON |= 1<<2;  
}

void SetTone(unsigned int period)
{
    PR2 = period;
}

void PlayTone(int period)
{
    PR2 = period;
    TurnBuzzerOn();
    //__delay_ms(TONE_LENGTH);
    //TurnBuzzerOff();
}