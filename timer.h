#ifndef TIMER_H
#define	TIMER_H

#include "can.h"

#include <p24FV16KM204.h>
#define FCY 16000000UL
#include <libpic30.h>

#define _ISR __attribute__((interrupt))

// interupt handler
void _ISR _T1Interrupt(void);

// Init and start the timer
void timer_start();

// Timer Interrupt callback
// Launch the adc
void timer_top();

#endif
