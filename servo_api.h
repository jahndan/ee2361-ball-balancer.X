/*
 * Project: ball-balancer
 * Course: EE2361 Spring 2024
 * Created on April 9, 2024, 5:05 AM
 */

#include "config.h"
#include <xc.h>

#ifndef SERVO_API_H
#define	SERVO_API_H

/** Initialize the PIC24 to interface with two PWM-controlled servos,
 * using pin RB6 and RB7 to output PWM to drive each servo */
void init_servos(void);

/** Set the angle (in tenths of degrees, between -900 and 900) of
 * the servos (calculates and sets the appropriate pulse width) */
void set_servos(int angle);

/** Utility clamp function to keep values between -900 and 900 */
int angular_clamp(int x);

#endif	/* SERVO_API_H */
