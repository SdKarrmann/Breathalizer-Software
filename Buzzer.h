/*
This file declares the methods used to interface with the magnetic transducer.
This "buzzer" is able to emit a range of tones and can be turned on or off.
*/

#ifndef _BUZZER_H
#define _BUZZER_H

#include "htc.h"

#define HIGH_TONE       58      // Length of period, from 0-255
#define LOW_TONE        239

#define HIGH_TONE_HZ    1048
#define LOW_TONE_HZ     262

/*
Initializes settings for interfacing with the buzzer.
*/
void InitBuzzer();

/*
Stops buzzer from emitting sound.
*/
void TurnBuzzerOff();

/*
Starts buzzer emitting sound at the last used frequency.
*/
void TurnBuzzerOn();

/*
Sets the frequency that will be emitted by the buzzer.
params: IN freq - frequency to be emitted in Hz
*/
void SetTone(unsigned int period);

void PlayHighTone();

void PlayLowTone();

void PlayTone(int period);

#endif