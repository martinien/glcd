#ifndef CAN_H
#define	CAN_H

#include <p24FV16KM204.h>

#define FCY 16000000UL
#include <libpic30.h>

/*ADC BUFFER WITH SENSOR CONVERTED MEASURE*/
#define SENSOR1BUF       ADC1BUF12
#define SENSOR1AVGBUF    ADC1BUF11
#define SENSOR2BUF       ADC1BUF10
#define SENSOR2AVGBUF    ADC1BUF9
#define SENSOR3BUF       ADC1BUF0
#define SENSOR3AVGBUF    ADC1BUF1
#define SENSOR4BUF       ADC1BUF6
#define SENSOR4VAGBUF    ADC1BUF16

void adc_init();

void adc_launch();

#endif
