/*
This file implements the methods declared in ADConverter.h.
*/

#include "ADConverter.h"

#define AD_REGISTER_0       ADCON0
#define CONVERSION_START    GO_nDONE
#define ACQUISITION_TIME     25

#define RADIX               10
#define ASCII_FOR_ZERO      '0'

#define _XTAL_FREQ          4000000

unsigned int GetAnalogInput(BYTE channelSelect)
{
    AD_REGISTER_0 = (channelSelect << 3) | 0x81; // 0100 0001, clock select and ON bit

    __delay_us(ACQUISITION_TIME);
    CONVERSION_START = 1;
    while(CONVERSION_START)
        ;
    return (ADRESH << 2) | (ADRESL >> 6);
}

#include "LCD.h"
BYTE IntToString(signed int value, char string[])
{
    long placeValue = 1;
    BYTE length = 0;
    while (value >= placeValue)
    {
        length++;
        placeValue *= 10;    
    }

    BYTE i;
    for(i = 0; i < length; i ++)
    {
        placeValue /= RADIX;
        BYTE currentDigit = (value % (RADIX * placeValue)) / placeValue;
        string[i] = currentDigit + ASCII_FOR_ZERO;
    }
    string[i] = 0;
    return length;
}