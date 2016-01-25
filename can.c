#include "can.h"

void can_init(){
    //AD1CON1bits.ADSIDL = 1; //continue on idle mode
    //AD1CON1bits.MODE12 = 1; //12-bits converstions
    //AD1CON1bits.FORM = 0b00; //absolute descimal result, unsigned, left-justified
    //AD1CON1bits.SSRC = 0b
            //clear flag
}

void can_launch(){
  // set assam to 1
//    AD1CON1bits.ADON = 1;
  //set assan bit to 1
  // set number of continuous concvertion
  //convert values
}

// _ADC1Interrupt  _AltADC1Interrupt ADC 1 convert completed
void can_top(){
    
    //set assam to 0
  //send bluetooth
}