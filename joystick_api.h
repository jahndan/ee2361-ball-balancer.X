/*
 * Project: ball-balancer
 * Course: EE2361 Spring 2024
 * Created on April 26, 2024, 4:42 PM
 */

#include "config.h"
#include <xc.h>

#ifndef JOYSTICK_API_H
#define	JOYSTICK_API_H

/** how many times a second ADC happens (samplerate)**/
// #define K_SAMPLERATE 125 // set this in config.h

/*** defines for conditional compiling ***/
// #define GET_ADC_X // define this in config.h and the X adc conversion will happen
// #define GET_ADC_Y // define this in config.h and the Y adc conversion will happen
// #define BUF_ADC_X // define this in config.h and X values will have their own buffer
// #define BUF_ADC_Y // define this in config.h and Y values will have their own buffer

#ifdef GET_ADC_X
/** accessor for volatile adc X value (extern variables are janky) */
uint16_t get_adc_x(void);
#endif  /* GET_ADC_X */

#ifdef GET_ADC_Y
/** accessor for volatile adc Y value (extern variables are janky) */
uint16_t get_adc_y(void);
#endif  /* GET_ADC_Y */

/** Initializes the PIC24 to interface with the joystick by conditionally setting up ADC
 * conversion on the necessary pins. (AN0 aka RA0 is configured if GET_ADC_X is set;
 * AN1 aka RA1 is configured if GET_ADC_Y is set) */
void init_joystick(void);

/** Interrupt Service Routine that actually updates the current ADC values for X and Y
 * (if the corresponding GET_ADC_* is set), and pushes their values to the corresponding
 * buffer if it exists (i.e. the corresponding BUF_ADC_* is set) */
void __attribute__((interrupt, auto_psv)) _ADC1Interrupt(void);

#endif	/* JOYSTICK_API_H */
