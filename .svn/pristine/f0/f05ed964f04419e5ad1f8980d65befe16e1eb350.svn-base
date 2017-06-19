/*
This file declares the methods used when dealing with the DIP switch.
*/

#ifndef _BREATHALIZER_DIP_HANDLER_H
#define _BREATHALIZER_DIP_HANDLER_H

/*===================================*/
#define BAC_PCT_RL      0x00
#define ADC_RAW_GAS_RL  0x01
#define ADC_RAW_GAS_RL1 0x21
#define ADC_RAW_GAS_RL2 0x11
#define ADC_RAW_GAS_RL3 0x31
#define ADC_RAW_GAS_RL4 0x09
#define ADC_RAW_GAS_RL5 0x29
#define TEMP_FAHRENHEIT 0x03
#define TEMP_CELSIUS    0x23
#define ADC_RAW_TEMP    0x13
#define LCD_TEST        0x07
#define BUZZER_LOW      0x27
#define BUZZER_HIGH     0x17
/*===================================*/

#include "htc.h"

#define BYTE unsigned char

/*
Returns a string that describes the mode specified by 'mode' 
params: IN mode - mode to describe 
*/
const char* GetLCDString(BYTE mode);

/*
Initializes settings for the DIP switch
*/
void InitDip(void);

/*
Returns the current state of the DIP switch. The lower 6 bits each represent
whether a switch is open or closed.
*/
BYTE GetSwitchInput(void);

#endif