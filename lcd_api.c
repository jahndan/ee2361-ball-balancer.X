/*
 * Project: ball-balancer
 * Course: EE2361 Spring 2024
 * Created on April 15, 2024, 2:20 PM
 */

#include "config.h"
#include <xc.h>
#include "lcd_api.h"

/** implementation detail: helper function used in others' implementations */
void lcd_cmd(char package) {
    // start sequence
    I2C2CONbits.SEN = 1;
    while (I2C2CONbits.SEN == 1); // wait
    // chip address/write
    _MI2C2IF = 0; // clear flag
    I2C2TRN = 0x7c;
    while (_MI2C2IF == 0); // wait
    // control byte
    _MI2C2IF = 0; // clear flag
    I2C2TRN = 0x00;
    while (_MI2C2IF == 0); // wait
    // command byte
    _MI2C2IF = 0; // clear flag
    I2C2TRN = package;
    while (_MI2C2IF == 0); // wait
    // stop sequence
    _MI2C2IF = 0; // clear flag
    I2C2CONbits.PEN = 1;
    while (I2C2CONbits.PEN == 1); // wait
}

void delay_ms(unsigned int num) {
    while (num-- > 0) {
        asm("repeat #15998");
        asm("nop");
    }
}

void init_baud_gen(void) {
    I2C2CONbits.I2CEN = 0;
    I2C2BRG = 0x9d; // 100kHz, 16MHz; Table 16-1
    I2C2CONbits.I2CEN = 1;
    I2C2CONbits.I2CSIDL = 0; // no idling
    _MI2C2IF = 0;
}

void init_lcd(void) {
    delay_ms(50);
    lcd_cmd(0x38); // function set, normal instruction mode
    lcd_cmd(0x39); // function set, extended instruction mode
    lcd_cmd(0x14); // interval osc
    lcd_cmd(0x70 | LCD_CONTRAST); // contrast C3-C0
    lcd_cmd(0x56); // Ion, Bon, C5-C4
    lcd_cmd(0x6c); // follower control
    delay_ms(200);
    lcd_cmd(0x38); // function set, normal instruction mode
    lcd_cmd(0x0c); // Display On
    lcd_cmd(0x01); // Clear Display
    delay_ms(2);
}

void lcd_printChar(char package) {
    // start sequence
    I2C2CONbits.SEN = 1;
    while (I2C2CONbits.SEN == 1); // wait
    // chip address/write
    _MI2C2IF = 0; // clear flag
    I2C2TRN = 0x7c;
    while (_MI2C2IF == 0); // wait
    // control byte
    _MI2C2IF = 0; // clear flag
    I2C2TRN = 0x40;
    while (_MI2C2IF == 0); // wait
    // command byte
    _MI2C2IF = 0; // clear flag
    I2C2TRN = package;
    while (_MI2C2IF == 0); // wait
    // stop sequence
    _MI2C2IF = 0; // clear flag
    I2C2CONbits.PEN = 1;
    while (I2C2CONbits.PEN == 1); // wait
}

void lcd_printStr(char* package) {
    // start sequence
    I2C2CONbits.SEN = 1;
    while (I2C2CONbits.SEN == 1); // wait
    // chip address/write
    _MI2C2IF = 0; // clear flag
    I2C2TRN = 0x7c;
    while (_MI2C2IF == 0); // wait
    // stop before the last non-null character
    while (*(package + 1) != 0) {
        // control byte
        _MI2C2IF = 0; // clear flag
        I2C2TRN = 0xc0; // co = 1, rs = 1
        while (_MI2C2IF == 0); // wait
        // command byte
        _MI2C2IF = 0; // clear flag
        I2C2TRN = *package;
        while (_MI2C2IF == 0); // wait
        ++package;
    }
    // send the last non-null character
    {
        // control byte
        _MI2C2IF = 0; // clear flag
        I2C2TRN = 0x40; // co = 0, rs = 1
        while (_MI2C2IF == 0); // wait
        // command byte
        _MI2C2IF = 0; // clear flag
        I2C2TRN = *package;
        while (_MI2C2IF == 0); // wait
    }
    // stop sequence
    _MI2C2IF = 0; // clear flag
    I2C2CONbits.PEN = 1;
    while (I2C2CONbits.PEN == 1); // wait
}

void lcd_setCursor(char row, char col) {
    char address = col | row << 6 | 0x80;
    lcd_cmd(address);
}
