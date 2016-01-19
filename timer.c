#include "can.h"

void timer_start(){
  //set interupt
  //    Interrupt Enable Control bit (TxIE)
  //    Interrupt Flag Status bit (TxIF)
  //    Interrupt Priority Control bits (TxIP<2:0>)
  //set timer
  //    TMRx: read timer value
  //    PRx : 16-Bit Timer Period register associated with the timer
  //    
  //    TxCON: 16-Bit Timer Control register associated with the timer
  //      &= 0000000001110110 stop the timer and set it to not stoping when in idel mode
  //      &= 1111111110111111 disable gate Timerx Gated Time Accumulation Enable bit
  //      &= 1111111111001111 set timer prescale to 1:1
  //      &= 1111111111111011 don't use external clock sync
  //      &= 1111111111111101  Internal clock (FOSC/2)
  
    IEC0BITS.T1IE = 1; //set timer interuption
    IPC0BITS.T1IP = 001; // set timer interuption priority

    T1CON = 0x00; // set the register for timer 1
    PR1 = 0xFFFF; // count 2^16 time
  
    IFS0BITS.T1IF = 0; //clear timer flag
    T1CONBITS.TON = 1; //start timer
}



void timer_top(){
    IFS0BITS.T1IF = 0; //clear timer flag
    can_launch();
}