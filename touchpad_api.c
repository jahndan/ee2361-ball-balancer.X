/*
 * Project: ball-balancer
 * Course: EE2361 Spring 2024
 * Created on April 9, 2024, 5:09 AM
 */

#include "config.h"
#include <xc.h>
#include "touchpad_api.h"

void init_touchpad(void) {
    TRISBbits.TRISB8 = 1; // SDI (Input)
    TRISBbits.TRISB5 = 0; // SDO (Output)
    TRISBbits.TRISB4 = 0; // SCK (Output)
    TRISBbits.TRISB7 = 0; // CS (Output)

    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPOR2bits.RP5R = 7; // RB5->SPI1:SDO1;
    RPOR2bits.RP4R = 8; // RB4->SPI1:SCK1OUT;
    RPOR3bits.RP7R = 9; // chip select (CS)
    RPINR20bits.SDI1R = 8; // master input
    __builtin_write_OSCCONL(OSCCON | 0x40);

    SPI1CON1bits.SSEN = 1; // Chip Select is controlled by software
    SPI1CON1bits.CKP = 0; // Idle state for clock is low
    SPI1CON1bits.CKE = 1; // Data is transmitted on the falling edge of the clock
    SPI1CON1bits.SMP = 0; // Input data sampled at middle of data output time
    SPI1CON1bits.MODE16 = 0; // 8-bit SPI mode
    SPI1CON1bits.MSTEN = 1; // Master mode enable
    SPI1STATbits.SPIEN = 1; // Enable SPI module
}

uint8_t SPI_ReadX(void) {
    uint8_t xVal;
    PORTBbits.RB7 = 0; // Enable CS

    SPI1BUF = CMD_READ_X; // Transmit command byte
    while (SPI1STATbits.SPITBF); // Wait for transmit buffer to be empty
    while (!SPI1STATbits.SPIRBF); // Wait for receive buffer to be full
    xVal = SPI1BUF; // Discard received byte (dummy read)

    SPI1BUF = 0x00; // Initiate another SPI transfer to receive actual data   
    while (!SPI1STATbits.SPIRBF); // Wait for receive buffer to be full
    xVal = SPI1BUF; // Read received X value

    PORTBbits.RB7 = 1; // Disable CS
    return xVal;
}

uint8_t SPI_ReadY(void) {
    uint8_t yVal;
    PORTBbits.RB7 = 0; // Enable CS

    SPI1BUF = CMD_READ_Y; // Transmit command byte
    while (SPI1STATbits.SPITBF); // Wait for transmit buffer to be empty
    while (!SPI1STATbits.SPIRBF); // Wait for receive buffer to be full
    yVal = SPI1BUF; // Discard received byte (dummy read)

    SPI1BUF = 0x00; // Initiate another SPI transfer to receive actual data   
    while (!SPI1STATbits.SPIRBF); // Wait for receive buffer to be full
    yVal = SPI1BUF; // Read received Y value

    PORTBbits.RB7 = 1; // Disable CS
    return yVal;
}
