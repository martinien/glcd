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
    
    // if(PORTAbits.RA6 == 1){
    //     button_left_interupt
    // }else if(PORTAbits.RA10 == 1){
        
    // }else if(PORTAbits.RA11 == 1){
        
    // }else if(PORTAbits.RA2 == 1){
        
    // }else if(PORTAbits.RA3 == 1){
        
    // }
    
}


// TODO julien le 19/01
// The CNEN1 and CNEN3 registers contain the interrupt enable control
void button_left_interupt(){
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

void_engine_splash(){
    lcd_on();
    lcd_clear_screen();
    lcd_on();
    lcd_bitmap(twinmaxLogo);    
    delay_ms(5000);
    lcd_clear_screen();
}

void_engine_menu(){
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