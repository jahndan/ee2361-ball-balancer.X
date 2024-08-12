/*
 * Project: ball-balancer
 * Course: EE2361 Spring 2024
 * Created on April 15, 2024, 2:21 PM
 */

#include "config.h"
#include <xc.h>

#ifndef LCD_H
#define	LCD_H

/** contrast value for LCD initialization */
// #define LCD_CONTRAST 0x00 // set this in config.h

/** utility function used in implementations, made available for convenience */
void delay_ms(unsigned int num);

/** first part of initialization, sets up baud rate clock */
void init_baud_gen(void);

/** second part of initialization, sets up the actual lcd display */
void init_lcd(void);

/** self-explanatory: prints singular character */
void lcd_printChar(char package);

/** self-explanatory: prints string terminated by null character */
void lcd_printStr(char* package);

/** sets the start position - where on the display to write to */
void lcd_setCursor(char row, char col);

#endif	/* LCD_H */
