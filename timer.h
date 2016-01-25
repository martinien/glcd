#ifndef TIMER_H
#define	TIMER_H

#include "can.h"

#define _ISR __attribute__((interrupt))

// interupt handler
void _ISR _T1Interrupt(void);

void timer_start();

// Interrupt callback
void timer_top();

#endif
