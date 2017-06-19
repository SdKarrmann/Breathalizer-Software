/*
Implements the functions defined in DigitalPOT.h.
*/

#include "DigitalPOT.h"

#define BUFFER SSPBUF
#define BUFFER_FULL BF
#define SS RD1

#define _XTAL_FREQ 4000000

#define COMMAND_WRITE_DATA 0x12 // 0001 0010

void InitPOT(void)
{
    TRISC5 = 0;
    TRISC3 = 0;
    TRISC4 = 1;
    TRISD1 = 0;
    CKE = 1;
    CKP = 1;
    SSPEN = 1;
}

void SetResistance(BYTE data)
{
    SS = 0;
    BUFFER = COMMAND_WRITE_DATA;
    while(!BF) {;}
    BYTE temp = BUFFER;
    BUFFER = data;
    while(!BF) {;}
    temp = BUFFER;
    SS = 1;
}

//#define POT_TESTING
#ifdef POT_TESTING

#define TESTING_DELAY 5000

int main()
{
    InitPOT();
    while(1)
    {
        SetResistance(0x003); //1 kOhms
        __delay_ms(TESTING_DELAY);
        SetResistance(0x0D); //5 kOhms
        __delay_ms(TESTING_DELAY);
        SetResistance(0x1A); //10 kOhms
        __delay_ms(TESTING_DELAY);
        SetResistance(0x35); //20 kOhms
        __delay_ms(TESTING_DELAY);
        SetResistance(0x84); //50 kOhms
        __delay_ms(TESTING_DELAY);
    }
}

#endif