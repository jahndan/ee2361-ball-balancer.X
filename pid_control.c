/*
 * Project: ball-balancer
 * Course: EE2361 Spring 2024
 * Created on April 9, 2024, 5:10 AM
 */

#include "config.h"
#include <xc.h>
#include "pid_control.h"

#ifdef BUF_ADC_X
volatile buf_t buffer_x[BUFSIZE] = {0}; // underlying array that stores buffer values
volatile int buf_x_index = 0; // points ahead of latest value, stack-style

void init_pid_buf_x(void) {
    buf_x_index = 0;
    for (int i = 0; i < BUFSIZE; i++) {
        buffer_x[i] = 0;
    }
}

void buf_x_put(buf_t value) {
    // add the value unless it is the cancel (in which case, use zero instead)
    buffer_x[buf_x_index++] = (value != P_CANCEL) ? value : 0; // post-increment
    if (buf_x_index >= BUFSIZE) buf_x_index -= BUFSIZE; // out-of-bounds guard
}

bbuf_t buf_x_getP(void) {
    // grab latest value and promote
    return (bbuf_t) buffer_x[buf_x_index-1];
}

bbuf_t buf_x_getI(void) {
    bbuf_t sum = 0; // avoid losing precision
    buf_t* current = buffer_x + buf_x_index; // get reference after latest value
    // add up the I_SAMPLES latest terms
    for (int i = 0; i < I_SAMPLES; i++) {
        --current; // pre-decrement because it points after latest value
        if (buffer_x - current > 0) current += BUFSIZE; // out-of-bounds guard
        sum += *current;
    }
    return sum;
}

bbuf_t buf_x_getD(void) {
    buf_t* current = buffer_x + buf_x_index;
    --current; // get reference to latest value
    if (buffer_x - current > 0) current += BUFSIZE; // out-of-bounds guard

    buf_t* prev = buffer_x + buf_x_index;
    prev -= D_SAMPLES; // get reference to nth latest value
    if (buffer_x - prev > 0) prev += BUFSIZE; // out-of-bounds guard

    return (bbuf_t) *current - *prev;
}
#endif

#ifdef BUF_ADC_Y
volatile buf_t buffer_y[BUFSIZE] = {0}; // underlying array that stores buffer values
volatile int buf_y_index = 0; // points ahead of latest value, stack-style

void init_pid_buf_y(void) {
    buf_y_index = 0;
    for (int i = 0; i < BUFSIZE; i++) {
        buffer_y[i] = 0;
    }
}

void buf_y_put(buf_t value) {
    // add the value unless it is the cancel (in which case, use zero instead)
    buffer_y[buf_y_index++] = (value != P_CANCEL) ? value : 0; // post-increment
    if (buf_y_index >= BUFSIZE) buf_y_index -= BUFSIZE; // out-of-bounds guard
}

bbuf_t buf_y_getP(void) {
    // grab latest value and promote
    return (bbuf_t) buffer_y[buf_y_index - 1];
}

bbuf_t buf_y_getI(void) {
    bbuf_t sum = 0; // avoid losing precision
    buf_t* current = buffer_y + buf_y_index; // get reference after latest value
    // add up the I_SAMPLES latest terms
    for (int i = 0; i < I_SAMPLES; i++) {
        --current; // pre-decrement because it points after latest value
        if (buffer_y - current > 0) current += BUFSIZE; // out-of-bounds guard
        sum += *current;
    }
    return sum;
}

bbuf_t buf_y_getD(void) {
    buf_t* current = buffer_y + buf_y_index;
    --current; // get reference to latest value
    if (buffer_y - current > 0) current += BUFSIZE; // out-of-bounds guard

    buf_t* prev = buffer_y + buf_y_index;
    prev -= D_SAMPLES; // get reference to nth latest value
    if (buffer_y - prev > 0) prev += BUFSIZE; // out-of-bounds guard

    return (bbuf_t) *current - *prev;
}
#endif

buf_t buf_clamp(bbuf_t value) {
    // safely demote
    if (value < BUF_T_MIN) return BUF_T_MIN;
    if (value > BUF_T_MAX) return BUF_T_MAX;
    return (buf_t) value;
}
