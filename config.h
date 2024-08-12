/* 
 * All config can happen in their respective libraries, but it got annoying to
 * manage, so here's a centralized configuration file for all editable constants
 * (see the corresponding header files for documentation on exactly what they do)
 */

#include <xc.h>

#ifndef CONFIG_H
#define	CONFIG_H


/// main.c (these constants need to be manually tuned for your application)
#define SCALE_P 1
#define SCALE_I 1
#define SCALE_D 1


/// joystick_api.h

#define K_SAMPLERATE 256

/* conditional compilation defines */
#define GET_ADC_X // X adc conversion will happen
#define GET_ADC_Y // Y adc conversion will happen
#define BUF_ADC_X // X buffer
//#define BUF_ADC_Y // no Y buffer


/// touchpad_api.h

#define TOUCHPAD_CENTER 63
#define CMD_READ_X 0xD8
#define CMD_READ_Y 0x98


/// pid_control.h

#define P_CANCEL 0
#define I_SAMPLES 128
#define D_SAMPLES 8
#define BUFSIZE 1024
#define BUF_T_MIN INT16_MIN
#define BUF_T_MAX INT16_MAX
typedef int16_t buf_t;
typedef int32_t bbuf_t;


// servo_api.h

/* n/a */


// lcd_api.h

#define LCD_CONTRAST 0x00


#endif	/* CONFIG_H */
