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
#include <stdio.h>
#include "glcd.h"
#include "logo.h"

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






int main(void){

  //  stdout = _H_USART;
    unsigned int x = 0;  
    int y = 0;
    unsigned char s;
    TRISA = 0;
    TRISB = 0;
    ANSB=0;
    RESET = 1 ;
    ENABLE = 1;
    CS1 = 0;
    CS2 = 0 ;         
    lcd_on();    
    delay_us(1000);
    lcd_bitmap(logo);     
    delay_ms(1000);
    lcd_off();    
    delay_ms(1000);
    lcd_on();
    delay_ms(1000);
    lcd_startLine(0);
    int i,j;
    
    for(i=0;i<64;i++){
        for(j=0;j<64;j++){
            lcd_plotpixel(i,j);
            delay_ms(20);
        }
    }
    
    //lcd_draw_bar
    
    
//    lcd_horizontalBar(1,25);
//    delay_ms(200);    
//    lcd_horizontalBar(2,35);
//    delay_ms(200);  
//    lcd_horizontalMainBar(3,45);
//    delay_ms(200);  
//    lcd_horizontalBar(4,55);
//    delay_ms(200);  
//    lcd_horizontalBar(5,65);
    
    lcd_setpage(0);
    lcd_setyaddr(0);
    lcd_off();
    delay_ms(100);
    s = (_lcd_status());    
    delay_ms(100);    
    lcd_on();
    delay_ms(1000);
    lcd_putrs("status:");
    lcd_testByte(s);
    
    delay_ms(100000);
    
    
    
    
    
    delay_ms(2000);
    lcd_setpage(0);
    lcd_setyaddr(0 & 0b00111111);
    lcd_putrs("Lorem ipsum dolor sit amet`\n consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum");
    lcd_cls();
    
 
    lcd_bitmap(road); 
    
    
    while(1){
    while(x<63){
        lcd_startLine(x);
        delay_ms(100);
        x++; 
    }
    x=0;
    
    }
    
    
    delay_ms(1000000);
    //lcd_off();
    while(1)
    {
        
        
       delay_us(1000);
       /* lcd_on();
        lcd_bitmap(isen);
        delay_ms(5000);
        lcd_cls();
        delay_ms(500);
        
        for(x = 40; x < 120; x++){
            for(y = 0; y < 10; y++){
            lcd_plotpixel(x,y); 
            delay_ms(5);                       
            }
            delay_ms(100);
        }*/
    }  
 }