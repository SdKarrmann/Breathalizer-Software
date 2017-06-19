/*
File for smoothing the ADC values read from the
temperature sensor and the MQ3 gas count sensor.
This reveals functionality to add a new value to
be smoothed, set the alpha value used when
calculating the smoothed values, and to retrieve
the current smoothed value.
*/

#ifndef SMOOTHING_H
#define SMOOTHING_H

typedef unsigned int smooth_type;
// larger data type to avoid overflows during calculations
typedef long calc_type;

/*
Sets the alpha value used when smoothing temperature
readings.

Param1: in - A BYTE with a value of [0, 100] representing
	the percent used in smoothing calculations.
*/
void SetTempAlpha(smooth_type);

/*
Sets the alpha value used when smoothing gas count
readings.

Param1: in - A BYTE with a value of [0, 100] representing
	the percent used in smoothing calculations.
*/
void SetGasAlpha(smooth_type);

/*
Stores a new temperature reading after smoothing the value.
Smoothing is handled using the equation:
	V = a * P + (1 - a) * X
where V is the value that is stored, a is the alpha value,
P is the previous smoothed value that was stored, or zero
if this is the first value read, and X is the temperature
value passed in as a parameter.

Param1: in - A BYTE value to be smoothed and stored as the
	current temperature.
*/
void AddNewTemp(smooth_type);

/*
Stores a new gas count reading after smoothing the value.
Smoothing is handled using the equation:
	V = a * P + (1 - a) * X
where V is the value that is stored, a is the alpha value,
P is the previous smoothed value that was stored, or zero
if this is the first value read, and X is the gas count
value passed in as a parameter.

Param1: in - A BYTE value to be smoothed and stored as the
	current gas count.
*/
void AddNewGas(smooth_type);

/*
Returns the current smoothed temperature reading.

Return: BYTE - the current temperature value after
	smoothing.
*/
smooth_type GetTemp(void);

/*
Returns the current smoothed gas count reading.

Return: BYTE - the current gas count value after smoothing.
*/
smooth_type GetGasCount(void);

#endif