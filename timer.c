#include "timer.h"

// interupt handler
void __attribute__((__interrupt__,__auto_psv__)) _T1Interrupt(void)
 {   
    can_launch();
//    IFS0bits.T1IF = 0;
 }

void timer_start(void){
  //set timer 1
  //    
  //    TxCON: 16-Bit Timer Control register associated with the timer
  //      &= 0000000001110110 stop the timer and set it to not stopping when in idle mode
  //      &= 1111111110111111 disable gate Timerx Gated Time Accumulation Enable bit
  //      &= 1111111111001111 set timer prescale to 1:1
  //      &= 1111111111111011 don't use external clock sync
  //      &= 1111111111111101  Internal clock (FOSC/2)
    
    // count 9600 time, with f_osc = 32Mhz that make every 600ns
//    PR1 = 0b0010010110000000; 
//    
//    T1CON = 0b00;
//    
//    IEC0bits.T1IE = 1; //set timer interruption
//    IPC0bits.T1IP = 100; // set timer interruption priority
//
//   
//    IFS0bits.T1IF = 0; //clear timer flag
//    T1CONbits.TON = 1; //start timer
}
