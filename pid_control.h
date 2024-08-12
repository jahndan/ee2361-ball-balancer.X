/*
 * Project: ball-balancer
 * Course: EE2361 Spring 2024
 * Created on April 9, 2024, 5:03 AM
 */

#include "config.h"
#include <xc.h>

#ifndef PID_CONTROL_H
#define	PID_CONTROL_H


// configs (update in config.h)

/** The value the touchpad idles at (not physically achievable), will be 
 * substituted by zero to avoid slant when nothing is on the touchpad. */
// #define P_CANCEL -63

/** The number of samples used to calculate the integral term */
// #define I_SAMPLES 512

/** The number of samples apart that the two samples used to calculate should
 * be, for the derivative term */
// #define D_SAMPLES 8

/** The size of the underlying array used for the PID buffers */
// #define BUFSIZE 1024

// These should be updated to use the stdint constants that correspond to buf_t
// #define BUF_T_MIN INT8_MIN
// #define BUF_T_MAX INT8_MAX

/** data type for values stored in the buffer */
// typedef int8_t buf_t; // as in buffer type

/** data type used in calculations (buf_t can be used, but may have overflow) */
// typedef int16_t bbuf_t; // as in bigger buffer type


/** Utility function for safely demoting the larger data type to the smaller */
buf_t buf_x_clamp(bbuf_t value);


// functions for the x buffer
#ifdef BUF_ADC_X
/** Initializes the empty buffer to zeros (can be used to reset the buffer) */
void init_pid_buf_x(void);

/** Adds a new value to the buffer, replacing the oldest value */
void buf_x_put(buf_t value);

/** Calculates the latest proportional term */
bbuf_t buf_x_getP(void);

/** Calculates the latest "integral-like" term */
bbuf_t buf_x_getI(void);

/** Calculates the latest "derivative-like" term */
bbuf_t buf_x_getD(void);
#endif

// functions for the y buffer
#ifdef BUF_ADC_Y
/** Initializes the empty buffer to zeros (can be used to reset the buffer) */
void init_pid_buf_y(void);

/** Adds a new value to the buffer, replacing the oldest value */
void buf_y_put(buf_t value);

/** Calculates the latest proportional term */
bbuf_t buf_y_getP(void);

/** Calculates the latest "integral-like" term */
bbuf_t buf_y_getI(void);

/** Calculates the latest "derivative-like" term */
bbuf_t buf_y_getD(void);
#endif

#endif	/* PID_CONTROL_H */
