/*
This file implements the methods declared in LCD.h.
*/

// LCD commands
#define CLEAR_DISPLAY               0x01
#define DISPLAY_ON_CURSOR_BLINKING  0x0D
#define FUNCTION_SET_4BIT_2LINES    0x28
#define FUNCTION_SET_8BIT_2LINES    0x38
#define ENTRY_MODE_INC_RIGHT        0x06
#define DISPLAY_OFF                 0x08
#define RETURN_HOME                 0x02
#define SET_DD_RAM                  0x80

// LCD ports and pins
#define CHIP_ENABLE                 RC7//RC5 
#define REGISTER_SELECT             RC6//RC4
#define DATA_LINE                   PORTD//PORTB
#define DATA_LINE_IO_MASK           0x00//0xCF
#define SETTINGS_LINE_IO_MASK       0x00//0xE1
#define DATA_LINE_TRIS				TRISD
#define SETTINGS_LINE_TRIS			TRISC

#define COMMAND_MODE                0
#define DATA_MODE                   1
#define DISABLED                    0
#define ENABLED                     1

#define HIGH_NIBBLE_OFFSET          0
#define LOW_NIBBLE_OFFSET           4
#define ROW_ADDRESS_MULT            64

// Delays
#define DATA_PULSE_WIDTH            1000
#define SHORT_CMD_DELAY_US          60
#define SHORT_STARTUP_DELAY_MS      5
#define LONG_STARTUP_DELAY_MS       15
#define LONG_CMD_DELAY_MS           3
#define _XTAL_FREQ                  4000000

#include "LCD.h"
#include "htc.h"

void EnableTransmission()
{
    CHIP_ENABLE = ENABLED;
    __delay_us(DATA_PULSE_WIDTH);
    CHIP_ENABLE = DISABLED;
}

void SendCommandByNibble(const BYTE command)
{
    REGISTER_SELECT = COMMAND_MODE;

    DATA_LINE = command >> HIGH_NIBBLE_OFFSET;
    EnableTransmission();

    DATA_LINE = command << LOW_NIBBLE_OFFSET;
    EnableTransmission();
}

void SendData (const BYTE data)
{
    REGISTER_SELECT = DATA_MODE;

    DATA_LINE = data >> HIGH_NIBBLE_OFFSET;
    EnableTransmission();
    
    DATA_LINE = data << LOW_NIBBLE_OFFSET;
    EnableTransmission();
}

void InitLCD(void)
{
	DATA_LINE_TRIS = DATA_LINE_TRIS & DATA_LINE_IO_MASK;
	SETTINGS_LINE_TRIS = SETTINGS_LINE_TRIS & SETTINGS_LINE_IO_MASK;
    
    __delay_ms(LONG_STARTUP_DELAY_MS);

    REGISTER_SELECT = COMMAND_MODE;
    DATA_LINE = FUNCTION_SET_8BIT_2LINES >> HIGH_NIBBLE_OFFSET;
    EnableTransmission();
    __delay_ms(SHORT_STARTUP_DELAY_MS);

    DATA_LINE = FUNCTION_SET_8BIT_2LINES >> HIGH_NIBBLE_OFFSET;
    EnableTransmission();
    __delay_us(SHORT_CMD_DELAY_US);

    DATA_LINE = FUNCTION_SET_8BIT_2LINES >> HIGH_NIBBLE_OFFSET;
    EnableTransmission();
    __delay_us(SHORT_CMD_DELAY_US);

    DATA_LINE = FUNCTION_SET_4BIT_2LINES >> HIGH_NIBBLE_OFFSET;
    EnableTransmission();
    __delay_us(SHORT_CMD_DELAY_US);
    
    // LCD now knows that only 4 bits are being sent
    
    SendCommandByNibble(FUNCTION_SET_4BIT_2LINES);
    __delay_us(SHORT_CMD_DELAY_US);

    SendCommandByNibble(DISPLAY_OFF);
    __delay_us(SHORT_CMD_DELAY_US);

    SendCommandByNibble(DISPLAY_ON_CURSOR_BLINKING);
    __delay_ms(LONG_CMD_DELAY_MS);

    SendCommandByNibble(ENTRY_MODE_INC_RIGHT);
    __delay_us(SHORT_CMD_DELAY_US);
}

void ClearDisplay(void)
{
    SendCommandByNibble(CLEAR_DISPLAY);
    __delay_ms(LONG_CMD_DELAY_MS);
}

void SendString (const char * s)
{
    while(*s != 0)
    {
        SendData(*s++);
    }
}

void SetCursor (const BYTE row, const BYTE col)
{
    BYTE address = col + (row * ROW_ADDRESS_MULT);
    SendCommandByNibble(address | SET_DD_RAM);
    __delay_us(SHORT_CMD_DELAY_US);
}

void ReturnHome(void)
{
    SendCommandByNibble(RETURN_HOME);
    __delay_ms(LONG_CMD_DELAY_MS);
}