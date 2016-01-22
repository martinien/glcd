#include "can.h"
#include <libpic30.h>
#include <xc.h>
#include <p24FV16KM202.h>

#define _ISR __attribute__((interrupt))

// interupt handler
void _ISR _T1Interrupt(void);

void timer_start();

// Interrupt callback
void timer_top();