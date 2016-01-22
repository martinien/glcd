#include "timer.h"

// interupt handler
void __attribute__((__interrupt__,__auto_psv__)) _T1Interrupt(void)
 {   
    IFS0bits.T1IF = 0;
    timer_top();
    return;
 }

void timer_start(void){
  //set interrupt
  //    Interrupt Enable Control bit (TxIE)
  //    Interrupt Flag Status bit (TxIF)
  //    Interrupt Priority Control bits (TxIP<2:0>)
  //set timer
  //    TMRx: read timer value
  //    PRx : 16-Bit Timer Period register associated with the timer
  //    
  //    TxCON: 16-Bit Timer Control register associated with the timer
  //      &= 0000000001110110 stop the timer and set it to not stopping when in idle mode
  //      &= 1111111110111111 disable gate Timerx Gated Time Accumulation Enable bit
  //      &= 1111111111001111 set timer prescale to 1:1
  //      &= 1111111111111011 don't use external clock sync
  //      &= 1111111111111101  Internal clock (FOSC/2)
  
    IEC0bits.T1IE = 1; //set timer interuption
    IPC0bits.T1IP = 010; // set timer interuption priority

    T1CON = 0x00; // set the register for timer 1
    PR1 = 0xFFFF; // count 2^16 time
    IFS0bits.T1IF = 0; //clear timer flag
    T1CONbits.TON = 1; //start timer
}

// Interrupt callback
void timer_top(){
    IFS0bits.T1IF = 0; //clear timer flag
    can_launch();
}