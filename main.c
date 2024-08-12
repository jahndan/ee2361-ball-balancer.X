/*
 * Project: ball-balancer
 * Course: EE2361 Spring 2024
 * Created on April 9, 2024, 4:03 AM
 */

#include "boilerplate.h"
#include "config.h"
#include "touchpad_api.h" // main input
// #include "joystick_api.h" // alternative input for testing
#include "pid_control.h"
#include "servo_api.h"
#include "lcd_api.h"
#include <xc.h>
#include <stdio.h>

void init_all(void) {
    // pic24 general stuff
    CLKDIVbits.RCDIV = 0; // set frequency to 16MHz
    AD1PCFG = 0xffff; // all pins digital
    TRISA = 0; // reset i/o directions
    TRISB = 0; // reset i/o directions

    init_touchpad(); // main input
    // init_joystick(); // alternative input for testing
    init_baud_gen();
    init_lcd();
    init_pid_buf_x();
    init_servos();
}

int main(void) {
    init_all();
    char wStr[16] = {0};
    int tempx = 0;
    int tempy = 0;

    while (1) {
        // read coordinates directly
        // tempx = get_adc_x(); // unused since this configuration uses the buffer
        tempy = get_adc_y(); // read directly but only output to LCD

        // put X value in buffer
        buf_x_put(temp);
        // buf_y_put(temp); // unused for this configuration

        // using buffer with PID weights to calculate X'
        tempx = (buf_x_getD() / SCALE_D) + (buf_x_getP() * SCALE_P) + (buf_x_getI() / SCALE_I);
        // tempy = (buf_y_getD() / SCALE_D) + (buf_y_getP() * SCALE_P) + (buf_y_getI() / SCALE_I);

        // process PID output accordingly
        // write X' to LCD
        sprintf(wStr, "X': %d    ", tempx);
        lcd_setCursor(0, 0);
        lcd_printStr(wStr);

        // move servo accordingly
        set_servos(angular_clamp(tempx));

        // write raw Y to LCD
        sprintf(wStr, "Y : %d    ", tempy);
        lcd_setCursor(1, 0);
        lcd_printStr(wStr);
    }
    return 0;
}
