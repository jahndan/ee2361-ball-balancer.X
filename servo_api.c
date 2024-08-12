/*
 * Project: ball-balancer
 * Course: EE2361 Spring 2024
 * Created on April 9, 2024, 5:12 AM
 */

#include "config.h"
#include <xc.h>
#include "servo_api.h"

void init_servos(void) {
    TRISBbits.TRISB6 = 0; // pin B6 as output
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock PPS
    RPOR3bits.RP6R = 18; // b6 to output compare
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS

    TRISBbits.TRISB7 = 0; // pin B7 as output
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock PPS
    RPOR4bits.RP9R = 19; // b7 to output compare
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS

    T2CON = 0; // turn off T2
    T2CONbits.TCKPS = 0b01; // prescaler: 8
    PR2 = 39999; // period: 20ms
    TMR2 = 0; // reset timer to 0
    T2CONbits.TON = 1; // turn on timer

    OC1CON = 0; // turn off OC1
    OC1R = 3000; // servo start position (register)
    OC1RS = 3000; // servo start position (shadow register)
    OC1CONbits.OCTSEL = 0b0; // use timer 2 for output compare
    OC1CONbits.OCM = 0b110; // output compare PWM w/o faults

    OC2CON = 0; // turn off OC1
    OC2R = 3000; // servo start position (register)
    OC2RS = 3000; // servo start position (shadow register)
    OC2CONbits.OCTSEL = 0b0; // use timer 2 for output compare
    OC2CONbits.OCM = 0b110; // output compare PWM w/o faults
}

void set_servos(int angle) {
    int pulseWidth = 3000 + angle * 2; // rough conversion
    OC1RS = pulseWidth; // set pwm width
    OC2RS = pulseWidth; // set pwm width
}

int angular_clamp(int x) {
    return (x > 900) ? 900 : (
        (x < -900) ? -900 : x
    );
}
