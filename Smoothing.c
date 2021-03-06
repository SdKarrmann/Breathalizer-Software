/*
Implements the methods declared in Smoothing.h. This
also handles the memory required for smoothing inputs.
*/

#include "Smoothing.h"

#define PERCENT_TOTAL 100
#define TEMP_ALPHA 50
#define GAS_ALPHA 30

/*
A structure that holds the memory necessary to smooth
input.
*/
struct smoother
{
    smooth_type Yn; // previous value
    smooth_type Yn1; // current value
    smooth_type alpha; // value between 0 and 100, represents a percent
};

struct smoother temperature = {0, 0, TEMP_ALPHA};
struct smoother gasCount = {0, 0, GAS_ALPHA};

void SetTempAlpha(smooth_type alpha)
{
    temperature.alpha = alpha;
}

void SetGasAlpha(smooth_type alpha)
{
    gasCount.alpha = alpha;
}

void AddNewTemp(smooth_type temp)
{
    if(!temperature.Yn1)
        temperature.Yn1 = temp;
    else
    {
        smooth_type temporary = temperature.Yn1;
        // operands are casted to calc_type to prevent overflow in the middle
        // of the calculation, but final result will always be able to be
        // stored in a smooth_type since alpha <= PERCENT_TOTAL
        temperature.Yn1 = ((calc_type)temperature.alpha * temperature.Yn) / PERCENT_TOTAL;
        temperature.Yn1 += ((calc_type)(100 - temperature.alpha) * temp) / PERCENT_TOTAL;
        temperature.Yn = temporary;
    }
    
}

void AddNewGas(smooth_type count)
{
    if(!gasCount.Yn1)
        gasCount.Yn1 = count;
    else
    {
        smooth_type temporary = gasCount.Yn1;
        // operands are casted to calc_type to prevent overflow in the middle
        // of the calculation, but final result will always be able to be
        // stored in a smooth_type since alpha <= PERCENT_TOTAL
        gasCount.Yn1 = ((calc_type)gasCount.alpha * gasCount.Yn) / PERCENT_TOTAL;
        gasCount.Yn1 += ((calc_type)(100 - gasCount.alpha) * count) / PERCENT_TOTAL;
        gasCount.Yn = temporary;
    }

}

smooth_type GetTemp(void)
{
    return temperature.Yn1;
}

smooth_type GetGasCount(void)
{
    return gasCount.Yn1;
}

//#define SMOOTHING_TEST
#ifdef SMOOTHING_TEST

#include "LCD.h"

int main()
{
    InitLCD();
    SetTempAlpha(80);
    if(temperature.alpha == 80) // Test that the alpha is set correctly
        SendData('P');
    else
        SendData('F');
    AddNewTemp(26);
    if(temperature.Yn1 == 26) // Test that initial value is not smoothed
        SendData('P');
    else
        SendData('F');
    AddNewTemp(26);
    if(temperature.Yn1 == 26) // Test that adding an equal value has no change
        SendData('P');
    else
        SendData('F');
    AddNewTemp(34);
    if(temperature.Yn1 == 27) // Test adding a non-equal value.
        SendData('P');
    else
        SendData('F');
    return 0;
}

#endif