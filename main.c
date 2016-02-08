/********************************************************************
 * FileName:     main.c
 * Dependencies:    
 * Processor:    PIC24FV16KM204
 * 
 */

#include "headers.h"

// PIC24FV16KM204 Configuration Bit Settings

// 'C' source line config statements


// FBS
#pragma config BWRP = OFF               // Boot Segment Write Protect (Disabled)
#pragma config BSS = OFF                // Boot segment Protect (No boot program flash segment)

// FGS
#pragma config GWRP = OFF               // General Segment Write Protect (General segment may be written)
#pragma config GCP = OFF                // General Segment Code Protect (No Protection)

// FOSCSEL
#pragma config FNOSC = FRCPLL           // Oscillator Select (Fast RC Oscillator with Postscaler and PLL Module (FRCDIV+PLL))
#pragma config SOSCSRC = DIG            // SOSC Source Type (Digital Mode for use with external source)
#pragma config LPRCSEL = HP             // LPRC Oscillator Power and Accuracy (High Power, High Accuracy Mode)
#pragma config IESO = OFF               // Internal External Switch Over bit (Internal External Switchover mode disabled (Two-speed Start-up disabled))

// FOSC
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = IO          // CLKO Enable Configuration bit (Port I/O enabled (CLKO disabled))
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary Oscillator configured for high-power operation)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Both Clock Switching and Fail-safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPS = PS1              // Watchdog Timer Postscale Select bits (1:1)
#pragma config FWPSA = PR128            // WDT Prescaler bit (WDT prescaler ratio of 1:128)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bits (WDT disabled in hardware; SWDTEN bit disabled)
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

    volatile struct movingAverage a1;
    volatile struct movingAverage * avg1;
    volatile unsigned short range ;
 
int main(void) {
    
    unsigned long oldAvg = 0; //Use to store the previous displayed average
    unsigned long newAvg = 0; //Use to store the current displayed average
    
    CLKDIV = 0; // No clock prescaler

    //Initialise pointers and arrays for the average
    avg1 = &a1;
    average_init(avg1, 0);
    
    INTCON2 = 0; // Use standard vector table, DISI is not active, Every Interrupts on positive edge
    INTCON1bits.NSTDIS = 0; // Interrupt Nesting Disabled  
 

    init_button_interrupt();
    
    // Set outputs / inputs
    TRISA = 0b0000110001111111;
    TRISB = 0b1111001000000000;
    TRISC = 0b0000000001000011;

    
    //engine_initialization();
    engine_splash();
    adc_init();
    engine_start();
    
    int count = 0;
    int range =  4097;
    int reference = 2047;
    unsigned short testVals[4];
    while(1){
        
        newAvg = average_get_average(avg1);
        oldAvg = (newAvg * 50 + oldAvg * 50) / 100;
        
        testVals[0] = 2047;
        testVals[1] = 2047;
        testVals[2] = (unsigned long)2047;
        testVals[3] = count * 64;
        
//        lcd_draw_bar(0,2047 / 64,0);
//        lcd_draw_bar(0,2047 / 64,1);
//        lcd_draw_bar(0,2047 / 64,2);
//        lcd_draw_bar(0,2047 / 64,3);
//        
        tui_displayMeasures(testVals,reference,range,1);

        delay_ms(100);
        if(count > 64){
            count = 0;
            range = range / 2;
        }else{
            count = count + 1;
        }
    }

    return 1;
}
