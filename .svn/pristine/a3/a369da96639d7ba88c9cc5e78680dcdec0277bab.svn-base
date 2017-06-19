/*
Implements the functions defined in AlcoholSensor.h.
*/

#include "AlcoholSensor.h"

#define Vc 5

BYTE GetSensorResistance(const BYTE Vrl, const BYTE Rl)
{
    BYTE Il = (BYTE)(Vrl / Rl);
    BYTE Rs = (BYTE)((Vc - Vrl) / Il);
    return Rs;
}

BYTE GetSensorVoltage(const BYTE Rs, const BYTE Rl)
{
    BYTE totalRes = Rs + Rl;
    BYTE Vrl = (Vc * Rl) / totalRes;
    return Vrl;
}