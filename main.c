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
#define FCY 4000000UL
#include <p24FV16KM202.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
//#include "glcd.h"
#include "logo.h"
//#include "twinmaxUI.h"
#include "FRENCH.h"
#include <libpic30.h>
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

#define delay_ms __delay_ms
#define delay_us __delay_us


int main(void) {

    unsigned char status,data;
    int i,j;
    TRISA = 0;
    TRISB = 0;
    ANSB = 0;
    
    
    status = 0;
    
    lcd_on();
   // delay_ms(20);
    int v;
    
    while(1){
    lcd_cls(); 
    lcd_on();
    lcd_bitmap(twinmaxLogo);
    delay_ms(2000);
    lcd_cls();  
    lcd_draw_bar(0, 10, 0);
    lcd_draw_bar(1, 55, 1);
    lcd_draw_bar(2, 35, 0);
    lcd_draw_bar(3, 45, 0);
    delay_ms(4000);
   
    
    while(1){
    lcd_cls();       
    lcd_draw_bar(0, 40, 0);
    lcd_draw_bar(1, 55, 1);
    lcd_draw_bar(2, 35, 0);
    lcd_draw_bar(3, 45, 0);
//    tui_writeAt(0,0,"1000",0,0);
//    tui_writeAt(4,0,"0854",0,0);
//    tui_writeAt(7,0,"0621",0,0);
        for(v=0;v<10;v++){
           // lcd_startLine(0);
            lcd_draw_bar(0,v,0);
            glcd_smallNumberAt(0,0,v,0);
            glcd_smallNumberAt(0,0,5,0);
            delay_ms(500);
        }
        for(v=9;v>=0;v--){            
            lcd_draw_bar(0,v, 0);
            glcd_smallNumberAt(0,0,i,0);
            glcd_smallNumberAt(0,4,i,0);
            delay_ms(500);
        }
    delay_ms(100);
    }
    
//    lcd_cls();
//    lcd_bitmap(twinmaxLogo);
//    delay_ms(2000);
//    lcd_cls();
//    tui_writeAt(1,15,BLUETOOTH,0,0);
//    tui_writeAt(5,10,YES,0,0);
//    tui_writeAt(5,90,NO,1,0);
//    delay_ms(1000);
//    tui_writeAt(5,10,YES,1,0);
//    tui_writeAt(5,90,NO,0,0);
//    
//    delay_ms(700);    
//    lcd_cls();
//    lcd_startLine(0);
//    tui_writeAt(1,15,REFERENCE,0,0);
//    tui_writeAt(5,5,"1",1,0);
//    tui_writeAt(5,35,"2",0,0);
//    tui_writeAt(5,65,"3",0,0);
//    tui_writeAt(5,95,"4",0,0);   
//    delay_ms(1000);    
//    tui_writeAt(5,5,"1",0,0);
//    tui_writeAt(5,35,"2",1,0);
//    delay_ms(300);    
//    tui_writeAt(5,35,"2",0,0);
//    tui_writeAt(5,65,"3",1,0);
//    delay_ms(1000); 
//    lcd_cls();
//   
//    unsigned char a,b,c,d;
//    a=40;
//    b=55;
//    c=35;
//    d=45;
//    
//    unsigned char values[4]={a,b,c,d};    
//    tui_drawGraph(values);
//    lcd_startLine(0);
//    delay_ms(4000);
//    lcd_cls();
//    lcd_draw_bar(0, 40, 0);
//    lcd_draw_bar(1, 55, 0);
//    lcd_draw_bar(2, 35, 0);
//    lcd_draw_bar(3, 45, 1);
//    tui_writeAt(0,0,"1000",0,0);
//    tui_writeAt(4,0,"0854",0,0);
//    tui_writeAt(7,0,"0621",0,0);
//    glcd_smallNumberAt(0,112,8,0);
//    glcd_smallNumberAt(0,116,3,0);
//    tui_writeAt(0,120,"%",0,0);
//    
//    delay_ms(5100);
//    tui_menuItem(0,"Retour",0);
//    tui_menuItem(1,"Precision",1);
//    tui_menuItem(2,"Backlight",0);
    
    
    
   // free(values);
    
    lcd_cls();
    lcd_off();
    }

}