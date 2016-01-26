#include "timer.h"

// interupt handler
void __attribute__((__interrupt__,__auto_psv__)) _T1Interrupt(void)
 {   
    //can_launch();
    // Clear timer interruption flag
    if(PORTBbits.RB0 == 1){
     
    PORTBbits.RB0 = 0;   
    }else{
     
    PORTBbits.RB0 = 1;   
    }
     
    IFS0bits.T1IF = 0;
    return;
 }

void timer_start(void){
  //    Set timer 1
  //    
  //    TxCON: 16-Bit Timer Control register associated with the timer
  //      set timer to stop when in idle mode
  //      disable gate Timerx Gated Time Accumulation
  //      set timer prescaler to 1:1
  //      don't use external clock sync
  //      Internal clock (FOSC/2)
    
    // count 9600 time, with f_osc = 32Mhz that make every 600ns
    INTCON1bits.NSTDIS = 0;
    PR1 = 0b0010010110000000; 
    
    T1CON = 0b0010000000000000;
    
    IEC0bits.T1IE = 1; //set timer interruption
    IPC0bits.T1IP = 0b100; // set timer interruption priority

    IFS0bits.T1IF = 0; //clear timer flag
    T1CONbits.TON = 1; //start timer
}
