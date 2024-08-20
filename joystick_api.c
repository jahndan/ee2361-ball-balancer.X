/*
 * Project: ball-balancer
 * Course: EE2361 Spring 2024
 * Created on April 26, 2024, 4:42 PM
 */

#include "config.h"
#include <xc.h>
#include "joystick_api.h"
#include "pid_control.h"

#ifdef GET_ADC_X
volatile uint16_t adc_x;
uint16_t get_adc_x(void) { return adc_x; }
#endif  /* GET_ADC_X */

#ifdef GET_ADC_Y
volatile uint16_t adc_y;
uint16_t get_adc_y(void) { return adc_y; }
#endif  /* GET_ADC_Y */

void init_joystick(void) {
#ifdef GET_ADC_X
    TRISAbits.TRISA0 = 1;
    AD1PCFGbits.PCFG0 = 0;
#endif  /* GET_ADC_X */

#ifdef GET_ADC_Y
    TRISAbits.TRISA1 = 1;
    AD1PCFGbits.PCFG1 = 0;
#endif  /* GET_ADC_Y */

#if defined(GET_ADC_X) || defined(GET_ADC_Y)
    AD1CON2bits.VCFG = 0; // AVDD & AVSS min-max
    AD1CON3bits.ADCS = 1; // clock = 2*Tcy
    AD1CON1bits.SSRC = 0b010; // sample/convert on TMR3 overflow
    AD1CON3bits.SAMC = 10; // ?? the reference manual does not elaborate on this whatsoever
    AD1CON1bits.FORM = 0; // unsigned integer
    AD1CON1bits.ASAM = 1; // automatic sampling
    AD1CON2bits.SMPI = 0; // interrupt every sample
    _AD1IF = 0; // clear
    _AD1IE = 1; // enable
    AD1CON1bits.ADON = 1;

    T3CON = 0;
    TMR3 = 0;
    T3CONbits.TCKPS = 0b11;
    PR3 = (62500 / K_SAMPLERATE) - 1;
    T3CONbits.TON = 1;
#endif  /* GET_ADC_X or GET_ADC_Y */
}

void __attribute__((interrupt, auto_psv)) _ADC1Interrupt(void) {
    // conditional compiling the parts

#ifdef GET_ADC_X
    // read X
    AD1CHSbits.CH0SA = 0;
    AD1CON1bits.SAMP = 1; // start sampling
    while (!AD1CON1bits.DONE); // wait until conversion completes
    adc_x = ADC1BUF0;
#ifdef BUF_ADC_X
    buf_x_put(adc_x);
#endif  /* BUF_ADC_X */
    while (AD1CON1bits.SAMP); // wait for sampling to complete
#endif  /* GET_ADC_X */

#ifdef GET_ADC_Y
    // read Y
    AD1CHSbits.CH0SA = 1;
    AD1CON1bits.SAMP = 1; // start sampling
    while (!AD1CON1bits.DONE); // wait until conversion completes
    adc_y = ADC1BUF0;
#ifdef BUF_ADC_Y
    buf_y_put(adc_y);
#endif  /* BUF_ADC_Y */
    while (AD1CON1bits.SAMP); // wait for sampling to complete
#endif  /* GET_ADC_Y */

#if defined(GET_ADC_X) || defined(GET_ADC_Y)
    // it doesn't work without this small delay
    asm("repeat #15");
    asm("nop");
#endif  /* GET_ADC_X or GET_ADC_Y */

    _AD1IF = 0; // clear interrupt flag
}
