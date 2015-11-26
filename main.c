/********************************************************************
* FileName:     main.c
* Dependencies:    
* Processor:    PIC24FV16KM202
* Hardware:     Microstick for 5V PIC24 K Series
* Compiler:     XC16 v1.1 or later
* Company:      Microchip Technology, Inc.

*
* 
* Change History:
*
* Author        Revision #      Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* B. Ivey       1.00            01-15-2013  Initial code
********************************************************************/

//#include <p24fxxxx.h>
#include <p24FV16KM202.h>
#include <stdint.h>
#include <stdlib.h>
#include "glcd.h"
//#include "lcdTest.c"








// PIC24FV16KM202 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// FBS
#pragma config BWRP = OFF               // Boot Segment Write Protect (Disabled)
#pragma config BSS = OFF                // Boot segment Protect (No boot program flash segment)

// FGS
#pragma config GWRP = OFF               // General Segment Write Protect (General segment may be written)
#pragma config GCP = OFF                // General Segment Code Protect (No Protection)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Select (Fast RC Oscillator (FRC))
#pragma config SOSCSRC = DIG            // SOSC Source Type (Digital Mode for use with external source)
#pragma config LPRCSEL = HP             // LPRC Oscillator Power and Accuracy (High Power, High Accuracy Mode)
#pragma config IESO = OFF               // Internal External Switch Over bit (Internal External Switchover mode disabled (Two-speed Start-up disabled))

// FOSC
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = IO            // CLKO Enable Configuration bit (Port I/O enabled (CLKO disabled))
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary Oscillator configured for high-power operation)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Both Clock Switching and Fail-safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:32768)
#pragma config FWPSA = PR128            // WDT Prescaler bit (WDT prescaler ratio of 1:128)
#pragma config FWDTEN = ON              // Watchdog Timer Enable bits (WDT enabled in hardware)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard WDT selected(windowed WDT disabled))

// FPOR
#pragma config BOREN = BOR3             // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware, SBOREN bit disabled)
#pragma config RETCFG = OFF             //  (Retention regulator is not available)
#pragma config PWRTEN = OFF             // Power-up Timer Enable bit (PWRT disabled)
#pragma config I2C1SEL = PRI            // Alternate I2C1 Pin Mapping bit (Use Default SCL1/SDA1 Pins For I2C1)
#pragma config BORV = V18               // Brown-out Reset Voltage bits (Brown-out Reset set to lowest voltage (1.8V))
#pragma config MCLRE = ON               // MCLR Pin Enable bit (RA5 input pin disabled, MCLR pin enabled)

// FICD
#pragma config ICS = PGx2               // ICD Pin Placement Select bits (EMUC/EMUD share PGC2/PGD2)








int main(void)
{
            // Set up output pin for LED
//    TRISAbits.TRISA0 = 0;
//    TRISAbits.TRISA1 = 0;
//    TRISAbits.TRISA2 = 0;
//    TRISAbits.TRISA3 = 0;
   /* OSCCON =0b
    CLKDIV = 
    OSCTUN = */
    U2MODE = 0b0010000000000000;
    
    
    TRISA = 0;
    TRISB = 0;
   // ODCA = 0b00010000;
    unsigned int i;
//    TRISAbits.TRISA7 = 0;
    while(1)
    {   
      //  LATA = 0b11111000;
      //  PORTB = 0b11111111;
        
      
       // Nop();         
      
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        LATAbits.LATA0 = 0;
        LATAbits.LATA1 = 1; 
        LATAbits.LATA2 = 0;
       LATAbits.LATA3 = 1;
       LATAbits.LATA4 = 1;    
       LATAbits.LATA7=1;       
       
       LATB=0b01010101;

     //  PORTAbits.RA4 = 1;
       // PORTAbits.RA4 = 1;

        
        for(i = 0; i < 65535; i++)
        {
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
        }
        LATAbits.LATA0 = 1;
        LATAbits.LATA1 = 0; 
        LATAbits.LATA2 = 1;
       LATAbits.LATA3 = 0;  
       LATAbits.LATA4 = 0;    
       LATAbits.LATA7 = 0;
       LATB= 0b10101010;

       //PORTAbits.RA4 = 0;

       // PORTB = 0;
         // LATA = 0b00000111;
        // LATAbits.LATA1 = 1;
      //  PORTAbits.RA3 = 0;
       // PORTAbits.RA4 = 0;
        

     /*   PORTAbits.RA0 = 0;
        Nop();
        PORTAbits.RA2 = 1;
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        PORTAbits.RA1 = 1;*/
        
        for(i = 0; i < 65535; i++)
        {
            Nop();
            Nop();            
            Nop();
            Nop();
            
        }
    } 
    

   
}

