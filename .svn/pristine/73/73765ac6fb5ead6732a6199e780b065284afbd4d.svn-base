/*
Grants access to helper functions for use with the
MQ3 alcohol sensor. These functions calculate the
resistance and voltage across the sensor unit.
*/

#ifndef ALCOHOL_SENSOR_H
#define ALCOHOL_SENSOR_H

#include "htc.h"

#define BYTE unsigned char

/*
Returns the resistance across the gas sensor in the
MQ3 alcohol sensor. The two values needed for this
calculation are the voltage Vrl across the load Rl
and the load resistance Rl.

Param1: In - The voltage across the load, in Volts.
Param2: In - The resistance of the load, in Ohms.
Return: The resistance of the gas sensor.
*/
BYTE GetSensorResistance(const BYTE, const BYTE);

/*
Returns the voltage across the load Rl of the MQ3
alcohol sensor. The two values needed for this
calculation are the resistance Rl and the resistance
across the gas sensor Rs.

Param1: In - The sensor resistance, in Ohms.
Param2: In - The load resistance, in Ohms.
Return: The voltage across Rl, in Volts.
*/
BYTE GetSensorVoltage(const BYTE, const BYTE);

#endif