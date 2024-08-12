/*
 * Project: ball-balancer
 * Course: EE2361 Spring 2024
 * Created on April 9, 2024, 5:01 AM
 */

#include "config.h"
#include <xc.h>

#ifndef TOUCHPAD_API_H
#define	TOUCHPAD_API_H

//#define TOUCHPAD_CENTER 63
//#define CMD_READ_X 0xD8
//#define CMD_READ_Y 0x98

/** Initializes the PIC24 for SPI communication with the TSC2046 to read touchpad position data */
void init_touchpad(void);

/** Sends a command over SPI to read the X position and returns that X value */
uint8_t SPI_ReadX(void);

/** Sends a command over SPI to read the Y position and returns that Y value */
uint8_t SPI_ReadY(void);

#endif	/* TOUCHPAD_API_H */
