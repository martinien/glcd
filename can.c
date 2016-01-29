#include "can.h"


void adc_init(){
    
    AD1CON1bits.ADON = 1; //Enable CAN
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
    
    //select input pins
    /*
     * RB12 = capteur1 =         AN12
     RB13 = capteur moyenne 1 = an11
     RB14 = capteur 2 =         an10
     RB15 = capteur 2 moyenne =  an9
     RA0 = capteur 3  =          an0
     RA1 = capteur 3 moyenne =   an1
     RC0 = capteur 4  =          an6
     RA4 = capteur 4 moyenne =   an16
     */
     
    
    AD1CSSL = 0b000111001000011;
    AD1CSSH = 0b000000000000001;
    
    IFS0bits.AD1IF = 0 ; //reset interrupt falg
    IEC0bits.AD1IE = 1; //enable interrupt
    
    IPC3bits.AD1IP = 0b100; //interrupt priority set to 4
    //TODO => add CNx to CAN 
   
}

void adc_launch(){
    AD1CON1bits.ASAM = 1;
    
  // set assam to 1
}

void __attribute__((__interrupt__,__auto_psv__)) _ADC1Interrupt(void){
    
    
    AD1CON1bits.ASAM = 0;
        
        
    IFS0bits.AD1IF = 0 ; //reset interrupt falg
    
    return;
        
}


// _ADC1Interrupt  _AltADC1Interrupt ADC 1 convert completed
