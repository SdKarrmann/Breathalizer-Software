/*
This is the main file for our Breathalizer program.
This handles collecting input from the MQ3 alcohol
sensor, the temperature sensor, and the DIP switch,
and then determining the appropriate output for the
buzzer, LCD, and digital POT.
*/

#include "htc.h"
#include "LCD.h"
#include "BreathalizerDipHandler.h"
#include "ADConverter.h"
#include "Buzzer.h"
#include "DigitalPOT.h"
#include "Smoothing.h"

// Osc = XT, Watchdog off, everthing else off or disabled
__CONFIG( 0x3F39 );

#define TEMP_CHANNEL    1
#define ALCOHOL_CHANNEL 2

// Temperature Constants
#define CEL_TO_FAHR     18
#define FAHR_OFFSET     32
#define SENSOR_OFFSET   -2
#define TMP_ADJ_BAC     -1  // a value in linear adjustment of BAC
#define TMP_SHIFT_BAC   120 // b value in linear adjustment of BAC
#define DECIMAL_SHIFT   100
#define ADC_MAX_VALUE   1023
#define Vc              5
#define DECIMAL_FORMAT  2
#define TEMP_PRECISION  10  // 10^n, n is number of decimal places desired

#define RL1             0x03
#define RL2             0x0D
#define RL3             0x1A
#define RL4             0x35
#define RL5             0x84
#define RL              RL3

#define LCD_WIDTH       16
#define _XTAL_FREQ      4000000
#define MAIN_LOOP_DELAY 250
#define BAC_THRESHOLD   750     //0.075
#define LEN_BAC_TABLE   11
#define TABLE_STEP      10      // 0.01 multiplied by 1000
/*
Called to handle initialization of the components
necessary for this program, including the LCD, the
DIP switch, the digital POT, and the buzzer.
*/
void InitMain()
{
    nRBPU = 0;
    InitLCD();
    InitDip();
    InitPOT();
    InitBuzzer();
}

/*
Converts the raw input from the temperature sensor and
converts it into units of Fahrenheit.

Param1: in - The raw data read from the temperature sensor.
Return: The temperature measured in units of Fahrenheit.
*/
signed int RawADCToFahrenheit(unsigned int adcData)
{
    //return (double)adcData * .48876 - 2;
    return ((signed long)adcData * 880 + 28400) / 100;
}

/*
Converts the raw input from the temperature sensor and
converts it into units of Celsius.

Param1: in - The raw data from the temperature sensor.
Return: The temperature measured in units of Celcius.
*/
signed int RawADCToCelsius(unsigned int adcData)
{
    //return (double)adcData * .87977 + 28.4;
    return (((signed long)adcData * 489) / 100) - 20;
}

/*
Clears the first characters of the array param, up to the
given length. No checks are made to ensure that the length
is less than the number of elements in the array.

Param1: in/out - An array of chars to be cleared.
Param2: in - The length of the array to be cleared.
*/
void ClearString(char str[], BYTE length)
{
    for(BYTE i = 0; i < length; i++)
    {
        str[i] = ' ';
    }   
}

/*
Prints the given char array to the LCD, with a decimal point
inserted at the (length - decPlaces) position. No checks are
made to see if decPlaces is less than length or if length is
less then the number of elements in the array.

Param1: in - The array of chars to be written to the LCD.
Param2: in - A BYTE determining how long the array is.
Param3: in - A BYTE determining how many decimal places from
    the end of the array to place the decimal point.
*/
void SendDecimal(char dataStr[], BYTE length, BYTE decPlaces)
{
    signed char missingDigits = (signed char)decPlaces - (signed char)length;
    if(missingDigits >= 0)
    {   
        SendString("0.");
        for(BYTE j = 0; j < missingDigits; j++)
            SendData('0');
    }
    
    SendData(dataStr[0]);
    BYTE i = 1;
    while(dataStr[i])
    {
        if(i == (length - decPlaces))
            SendData('.');
        SendData(dataStr[i++]);
    }
}

/*
Takes raw ADC data, converts it to a string, and then prints
it to the LCD.

Param1: in - The raw data to convert to a string.
Param2: in - The char array to store the string while printing.
Param3: in - A byte determining the location to place the decimal
    point.
*/
void PrintData(unsigned int input, char dataStr[], BYTE decPlaces)
{
    SetCursor(1,0);
    ClearString(dataStr, LCD_WIDTH);
    BYTE length = IntToString(input, dataStr);
    if(decPlaces == 0)
        SendString(dataStr);
    else
        SendDecimal(dataStr, length, decPlaces);
}

/*
Returns the cursor to the home position of the second line and clears
the string that is currently printed.
*/
void ClearLineTwo()
{
    SetCursor(1, 0);
    SendString("                "); 
}

/*

*/
unsigned int TempAdjustADC(unsigned int inputADC)
{
    unsigned int tempC = GetTemp();
    return (inputADC * ((tempC * TMP_ADJ_BAC) + TMP_SHIFT_BAC) / DECIMAL_SHIFT);
}

const unsigned int BAC_ADC_COUNTS[] = 
{ 
   783, 805, 828, 851, 874, 897, 919, 942, 965, 988, 1011 
};

unsigned int GetBAC(unsigned int data)
{
    unsigned int lower = 0, higher = BAC_ADC_COUNTS[0];
    BYTE count = 0;
    while(count + 1 < LEN_BAC_TABLE && higher < data)
    {
        lower = higher;
        higher = BAC_ADC_COUNTS[count + 1];
        count++;
    }
    --count;
    return count * TABLE_STEP + ((data - lower) * TABLE_STEP / (higher - lower));
}

/*
Updates the state of the program based on the DIP input.
This changes the value printed to the LCD, handles the
buzzer outputs, calls the functions to handle any conversions
from raw data, and sets the digital POT to the required
settings.

Param1: in - A byte that designates the mode.
Param2: in/out - A reference to an integer. The int is 
    incremented every .25 seconds while in LCD testing mode.
*/
void UpdateBasedOnMode(BYTE mode, unsigned int* counter)
{
    char dataString[LCD_WIDTH] = {0};
    signed int data = 0;
    BYTE decPlaces = 0;
    switch(mode)
    {
        case BAC_PCT_RL:
            decPlaces = 4;
            data = GetGasCount();
            data = TempAdjustADC(data);
            BYTE bac = GetBAC(data);
            if(data > BAC_THRESHOLD)
                PlayTone(HIGH_TONE);
            else
                PlayTone(LOW_TONE);
            break;
        case ADC_RAW_GAS_RL:
            SetResistance(RL);
            data = GetGasCount();
            break;
        case ADC_RAW_GAS_RL1:
            SetResistance(RL1); // 1K Ohm
            data = GetGasCount();
            break;
        case ADC_RAW_GAS_RL2:
            SetResistance(RL2); // 5K Ohm
            data = GetGasCount();
            break; 
        case ADC_RAW_GAS_RL3:
            SetResistance(RL3); // 10K Ohm
            data = GetGasCount();
            break;
        case ADC_RAW_GAS_RL4:
            SetResistance(RL4); // 20K Ohm
            data = GetGasCount();
            break;
        case ADC_RAW_GAS_RL5:
            SetResistance(RL5); // 50K Ohm
            data = GetGasCount();
            break;
        case TEMP_FAHRENHEIT:
            data = GetTemp();
            data = RawADCToFahrenheit(data);
            decPlaces = 1;
            break;
        case TEMP_CELSIUS:
            data = GetTemp();;
            data = RawADCToCelsius(data);
            decPlaces = 1;
            break;
        case ADC_RAW_TEMP:
            data = GetTemp();;
            break;
        case LCD_TEST:
            (*counter)++;
            data = *counter;
            break;
        case BUZZER_LOW:
            data = LOW_TONE_HZ;
            PlayTone(LOW_TONE);
            break;
        case BUZZER_HIGH:
            data = HIGH_TONE_HZ;
            PlayTone(HIGH_TONE);
            break;  
    }
    PrintData(data, dataString, decPlaces);
}
 
/*
Reads the raw data from all of the ADC inputs and passes the
input to a smoothing function for later reference.
*/
void UpdateADCReadings()
{
    unsigned int data = GetAnalogInput(ALCOHOL_CHANNEL);// Update ADC values
    AddNewGas(data);
    data = GetAnalogInput(TEMP_CHANNEL);
    AddNewTemp(data);                      // End update ADC values
}

/*
Determines whether the buzzer should be activated. This does
not actually activate the buzzer.

Param1: in - The current input from the DIP switches to determine
    the state of the program.
Return: True if the buzzer should play in this state of the program,
    false otherwise.
*/
BYTE BuzzerShouldPlay(BYTE mode)
{
    if(mode == BUZZER_HIGH)
        return 1;
    if(mode == BUZZER_LOW)
        return 1;
    if(mode == BAC_PCT_RL)
        return 1;
    return 0;
}

/*
The main loop for the program. Calls functions to update ADC input,
update the program state based on DIP switch input, update the LCD
text, and handles the program delay.
*/
int main()
{
    InitMain();
    unsigned int testCounter = 0;
    ClearDisplay();
    while(1)
    {
        UpdateADCReadings();
        ClearLineTwo();
        BYTE mode = GetSwitchInput();
        const char * modeString = GetLCDString(mode);
        ReturnHome();
        SendString(modeString);
        if(!BuzzerShouldPlay(mode))
            TurnBuzzerOff();
        UpdateBasedOnMode(mode, &testCounter);
        __delay_ms(MAIN_LOOP_DELAY);
        /*signed int temp = RawADCToFahrenheit(100);
        char name[16] = {0};
        ClearDisplay();
        SendData('F');
        PrintData(temp, name, 1);
        __delay_ms(1000);
        ClearDisplay();
        SendData('C');
        temp = RawADCToCelsius(100);
        PrintData(temp, name, 1);
        __delay_ms(1000);*/

    }
    return 0;
}