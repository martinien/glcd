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
#pragma config FNOSC = FRC           // Oscillator Select (8MHz FRC oscillator With Postscaler (FRCDIV))
#pragma config SOSCSRC = ANA            // SOSC Source Type (Analog Mode for use with crystal)
#pragma config LPRCSEL = HP             // LPRC Oscillator Power and Accuracy (High Power, High Accuracy Mode)
#pragma config IESO = ON                // Internal External Switch Over bit (Internal External Switchover mode enabled (Two-speed Start-up enabled))

// FOSC
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = IO            // CLKO Enable Configuration bit (Port I/O enabled (CLKO disabled))
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary Oscillator configured for high-power operation)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Both Clock Switching and Fail-safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:32768)
#pragma config FWPSA = PR128            // WDT Prescaler bit (WDT prescaler ratio of 1:128)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bits (WDT disabled in hardware; SWDTEN bit disabled)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard WDT selected(windowed WDT disabled))

// FPOR
#pragma config BOREN = BOR3             // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware, SBOREN bit disabled)
#pragma config RETCFG = OFF             //  (Retention regulator is not available)
#pragma config PWRTEN = ON              // Power-up Timer Enable bit (PWRT enabled)
#pragma config I2C1SEL = PRI            // Alternate I2C1 Pin Mapping bit (Use Default SCL1/SDA1 Pins For I2C1)
#pragma config BORV = V18               // Brown-out Reset Voltage bits (Brown-out Reset set to lowest voltage (1.8V))
#pragma config MCLRE = ON               // MCLR Pin Enable bit (RA5 input pin disabled, MCLR pin enabled)

// FICD
#pragma config ICS = PGx1               // ICD Pin Placement Select bits (EMUC/EMUD share PGC1/PGD1)




int main(void)
{
    
    
    // Set up output pin for LED
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA7 = 0;
    
    
    
    TRISA = 0;
    __delay_ms(100);
   // lcd_screenon(1);
  //  __delay_ms(500);
     //lcd_cls();
     _lcd_reset();
     __delay_ms(100);
     RESET=0;
     lcd_screenon(0);
     int i=0;
     int j=0;

    while(1)
    {       
        
       
       
        for(i = 0; i < 128; i++)
        
            for(j=0;j<60;j++){
            lcd_plotpixel(i,j); 
            __delay_ms(200);
          
        
        }
        
                
       
        __delay_ms(20000);
        
        
        
    }
}

