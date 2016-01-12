
#include "timer.h"
#include "FRENCH.h"
#define FCY 4000000UL
#include <p24FV16KM202.h>
#include <libpic30.h>
#define delay_ms __delay_ms

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

void engine_initialization() {
  lcd_cls();
  tui_writeAt(1,15,BLUETOOTH,0,0);
  tui_writeAt(5,10,YES,0,0);
  tui_writeAt(5,90,NO,1,0);
  delay_ms(1000);
  tui_writeAt(5,10,YES,1,0);
  tui_writeAt(5,90,NO,0,0);    
  delay_ms(700);   

  lcd_cls();
  
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
  lcd_cls();
}

void engine_start() {
  timer_start();
}