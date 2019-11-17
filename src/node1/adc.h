#ifndef __ADC_H__
#define __ADC_H__

#define F_CPU 4915200

#include <avr/io.h>
#include <util/delay.h>

#include <stdint.h>

typedef enum
{
    JOY_X = 4,
    JOY_Y = 5,
    SLIDER_L = 6,
    SLIDER_R = 7
} adc_channel_t;

uint8_t adc_read(uint8_t channel);

#endif