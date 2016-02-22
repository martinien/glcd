#ifndef CAN_H
#define	CAN_H

#include <p24FV16KM204.h>

#define FCY 16000000UL
#include <libpic30.h>

/*ADC BUFFER WITH SENSOR CONVERTED MEASURE*/


void adc_init();

void adc_launch();

#endif
