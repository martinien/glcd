#include "can.h"

void can_init(){
    
    AD1CON1bits.ADON = 1; //Enbale CAN
    AD1CON1bits.ADSIDL = 1; //Stop when in idle mode
    AD1CON1bits.MODE12 = 1; // 12 BITS CAN
    AD1CON1bits.FORM = 0b00; //Absolute decimal, unsigned, right-justified
    AD1CON1bits.SSRC = 0b0111; //Auto-Convertion mode
    AD1CON1bits.ASAM = 0; //Wait for timer to start
    AD1CON1bits.SAMP = 0; //Wait for timer and ASSAM
    AD1CON1bits.DONE = 0; // Clear CAN flag
    
    AD1CON2bits.PVCFG = 0b00; //Set AVdd as reference
    AD1CON2bits.NVCFG0 = 0; //Set AVSS as reference
    AD1CON2bits.OFFCAL= 0; //Connect to normal inputs
    AD1CON2bits.BUFREGEN = 1; //No FIFO buffering
    AD1CON2bits.SMPI = 0b00111; // Interruption occurs after 8 convertions
    AD1CON2bits.ALTS = 0; // Always use sample A chanel
    
    AD1CON3bits.ADRC = 0; //Use internal clock
    AD1CON3bits.SAMC = 0b00010; // Set as 2 * T_AD
    AD1CON3bits.ADCS = 0b00001001; // Set as 10 T_AD
    
    AD1CON5bits.ASEN = 0; //Auto-scan disable
    AD1CON5bits.LPEN = 0; // Full power enabled after scan
    AD1CON5bits.CTMREQ = 0; // CTMU disable
    AD1CON5bits.BGREQ = 0; //Band gap is not enable
    //AD1CON5bits.VRSREQ = 0; // On-chip regulator is not enable by the ADC
    AD1CON5bits.ASINT = 0b00; // No interrupt 
    AD1CON5bits.WM = 0b00; //Classic buffering
    AD1CON5bits.CM = 0b00; //Less than mode
    
    AD1CHS = 0b0001111000011110; //Set Vss and AVdd as references
    
    //TODO => add CNx to CAN 
    //  AD1CSSH = 
}

void can_launch(){
  // set assam to 1
}

// _ADC1Interrupt  _AltADC1Interrupt ADC 1 convert completed
void can_top(){
    
    //set assam to 0
    //send bluetooth
}