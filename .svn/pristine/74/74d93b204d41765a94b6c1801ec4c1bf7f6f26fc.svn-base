/*
Grants access to functions used when operating
the digital potentiometer.
*/

#ifndef DIGITAL_POT_H
#define DIGITAL_POT_H

#include "htc.h"

#define BYTE unsigned char

/*
Initializes the TRIS' and registers necessary for
using the SPI interface to access the digital
potentiometer.
*/
void InitPOT(void);

/*
Sets the digital potentiometer's data to the given
BYTE. This varies the resistance of the potentiometer
when run in rheostatic mode.
*/
void SetResistance(BYTE);

#endif