/*
This file declares the methods used to interface with the LCD. The user is able
to clear the screen, send a string to be displayed, and set the position of the
cursor (where text will be written next).
*/

#ifndef _LCD_H
#define _LCD_H

#define BYTE unsigned char

/*  Runs initialization sequence for LCD so that data and commands
    can be sent and received.
*/
void InitLCD(void);

/*  Clears all characters that were previously displayed and returns the
    cursor to the home position.
*/
void ClearDisplay(void);

/*  Sends the given BYTE to the LCD, which will display it. This function will
    automatically advance the cursor.
    params: (in) BYTE data - byte to be sent
*/
void SendData (const BYTE data);

/*  Sends the given string to the LCD, which will display it. This function
    will advance the cursor to the next position after the end of the displayed
    string.
    params: (in) BYTE* string - null terminated string to be sent
*/
void SendString (const BYTE* string);

/*  Sets the position of the cursor to the given indices, does not change
    the characters displayed on the LCD. Both row and column index are
    0-based.
    params: (in) BYTE row - row index cursor will move to
            (in) BYTE col - column index cursor will move to
*/
void SetCursor (const BYTE row, const BYTE col);

/*  Sets the position of the cursor to row 0 and column 0, does not change
    the characters displayed on the LCD.
*/
void ReturnHome(void);

#endif