#include "engine.h"
#ifndef LOGO_H
#include "logo.h"
#endif
#include "timer.h"
#include "FRENCH.h"
#include "glcd.h"
#include "twinmaxUI.h"

enum phase{
    INIT,
    BLUETOOTHMENU,
    REFERENCEMENU
    
};
volatile short blueetooth;
volatile short referenceCarburator;
volatile enum phase phase;

void __attribute__((__interrupt__, __auto_psv__)) _CNInterrupt(void){

    //todo : reset interruption flag
    delay_ms(40);
    IFS1bits.CNIF = 0;
//    if(PORTAbits.RA6 == 1){
//        
//        button_left_interupt();
//    }else if(PORTAbits.RA10 == 1){
//        
//        button_left_interupt();
//    }else if(PORTAbits.RA11 == 1){
//        
//        button_left_interupt();
//    }else if(PORTAbits.RA2 == 1){
//        
//        button_left_interupt();
//    }else if(PORTAbits.RA3 == 1){
//        
//        button_left_interupt();
//    }
    button_left_interupt();
    
}

void init_interrupt(){
    /*
     * The CNEN1 and CNEN3 registers contain the interrupt enable control
     * 
     * RA6 = CN8 <= !!!!!!!! WHERE THE FUCK IS CN8IE ?????????
     * RA10 = CN35
     * RA11 = CN36
     * RA2 = CN30
     * RA3 = CN29
     * 
    */
    
    CNEN1 = 0b0000000100000000; // <= here CN8 is acctually missing in the datasheet
    CNEN2 = 0b0110000000000000;
    CNEN3 = 0b0000000000011000;
    
    
}

void button_left_interupt(){
    tui_battery(10);
  return;
}

void button_right_interupt(){
  return;
}

void button_select_interupt(){
  return;
}

void button_light_interupt(){
  return;
}

void button_power_interupt(){
  return;
}

void engine_splash(){
    lcd_on();
    lcd_clear_screen();
    lcd_on();
    lcd_bitmap(twinmaxLogo);    
    delay_ms(5000);
    lcd_clear_screen();
}

void engine_menu(){
    tui_writeAt(1,15,BLUETOOTH,0,0);
    
    
    tui_writeAt(5,10,YES,0,0);
    tui_writeAt(5,90,NO,1,0);
    delay_ms(1000);
    tui_writeAt(5,10,YES,1,0);
    tui_writeAt(5,90,NO,0,0);    
    delay_ms(700);   

    lcd_clear_screen();

    tui_writeAt(1,15,REFERENCE,0,0);
    tui_writeAt(5,5,"1",1,0);
    tui_writeAt(5,35,"2",0,0);
    tui_writeAt(5,65,"3",0,0);
    tui_writeAt(5,95,"4",0,0);   
    delay_ms(800);    
    tui_writeAt(5,5,"1",0,0);
    tui_writeAt(5,35,"2",1,0);
    delay_ms(300);    
    tui_writeAt(5,35,"2",0,0);
    tui_writeAt(5,65,"3",1,0);
    delay_ms(1000); 
    lcd_clear_screen();
    
}

void engine_initialization() {
  lcd_clear_screen();
  
}

void engine_start() {
  timer_start();
}