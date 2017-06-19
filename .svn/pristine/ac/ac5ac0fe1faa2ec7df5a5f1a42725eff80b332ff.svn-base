/*
This file declares the methods given to interface with the ADC component.
Includes methods for converting analog input to digital as well as converting
that value to a string representation.
*/

#ifndef _ADCONVERTER_H
#define _ADCONVERTER_H

#include "htc.h"

#define BYTE unsigned char

/*
Converts the analog voltage value on the given channel into a binary number.
params: IN channel - the pin whose voltage should be read
*/
unsigned int GetAnalogInput(BYTE channel);

/*
Takes an integer value, and puts into str the decimal representation of that
number as characters. E.g. for value 0x0100, str will be "256". Returns the
length of the resulting string.
params: IN value - the number to be converted
		OUT str - the character array to store value's representation
*/
BYTE IntToString(signed int value, char str[]);

/*
Takes an integer value, and puts into str the decimal representation of that
number as characters. The last 'decPlaces' will be shown after a decimal point.
E.g. for value 0x0100, str will be "256".
params: IN value - the number to be converted
		OUT str - the character array to store value's representation
		IN decPlaces - number of digits to put after the decimal point
*/
void DecimalToString(unsigned int value, char str[], BYTE decPlaces);

#endif