#include "engine.h"
#ifndef LOGO_H
#include "logo.h"
#endif
#include "timer.h"
#include "FRENCH.h"
#include "glcd.h"
#include "twinmaxUI.h"
#include "params.h"
#include "inputs.h"


enum engine_phase{
    INIT,
    BLUETOOTHMENU,
    REFERENCEMENU,
    RUN,
    SLEEP
};

volatile short blueetooth;
volatile enum engine_phase phase = INIT;

void __attribute__((__interrupt__, __auto_psv__)) _CNInterrupt(void){

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

    button_left_interupt(phase);

    delay_ms(150);

    // Reset flag
    IFS1bits.CNIF = 0;
    return;
}

void init_button_interrupt(){

    /*
    * INTCON1, INTCON2 Registers
    * IFSn: Interrupt Flag Status Registers
    * IECn: Interrupt Enable Control Registers
    * IPCn: Interrupt Priority Control Registers
    */
    
    // Use standard vector table
    // DISI is not active
    // Every Interrupts on positive edge
    INTCON2 = 0;
    
    // Interrupt Nesting Disabled
    INTCON1bits.NSTDIS = 0;
    
    //Reset all flags
    IFS0 = 0;
    IFS1 = 0;
    IFS2 = 0;
    IFS3 = 0;
    IFS4 = 0;
    IFS5 = 0;
    IFS6 = 0;
    
    // Enable Change Notification(CN) Interrupts.
    IEC1bits.CNIE = 1;

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
    // extern enum engine_phase phase;
    // extern unsigned short range;
    // unsigned short reference;

    // if(phase == RUN){
    //     zoom_in();
    //     return;
    // }else if(phase == BLUETOOTHMENU || phase == REFERENCEMENU){
    //     menu_right_command();
    // }
    if(phase == RUN){
        extern unsigned short range;
        unsigned short reference;
        if(range>20){
            range=range/2;
        }
        else{
            range = 2560;
        }
        extern unsigned short oldAvg1;
        set_scale(reference,range);
        reference = oldAvg1;
        delay_ms(200);
        return;
    }
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
    // extern enum engine_phase phase;
    // if(phase == SLEEP){
    //     wake();
    // }else{
    //     sleep();
    // }
    return;
}

void set_scale(unsigned short ref , unsigned short rg ){
    extern unsigned short reference;
    extern unsigned short range;
    reference = ref;
    range = rg;
}

void engine_splash(){
    lcd_on();
    lcd_clear_screen();
    lcd_on();
    lcd_bitmap(twinmaxLogo);    
    delay_ms(1000);
    lcd_clear_screen();
}

void engine_display_bluetooth_question(int is_bluetooth_activated){
    tui_write_at(1, 15, BLUETOOTH, 0, 0);      
    tui_write_at(5, 10, YES, is_bluetooth_activated==0, 0);
    tui_write_at(5, 90, NO, is_bluetooth_activated==1, 0);
}

void engine_ask_for_bluetooth(){
    int selected = 0;
    int is_bluetooth_activated = 0;

    // Temporaly disable button interruption
    IEC1bits.CNIE = 0;
    
    engine_display_bluetooth_question(is_bluetooth_activated);
    
    while(selected == 0){
        while((LEFT_BUTTON || SELECTION_BUTTON || RIGHT_BUTTON) == 0){  
        }
        if(LEFT_BUTTON == 1){
            is_bluetooth_activated = (is_bluetooth_activated + 1) % 2;
        }else if(RIGHT_BUTTON == 1){
            is_bluetooth_activated = (is_bluetooth_activated + 1) % 2;
        }else{
            selected = 1;
        }
        engine_display_bluetooth_question(is_bluetooth_activated);
        delay_ms(200);
    }

    if(is_bluetooth_activated == 0){
        //ble_init();
    }
    return;
}

void engine_ask_for_reference(){
    int selected = 0;
    int reference = 0;
    
    // Temporaly disable button interruption
    IEC1bits.CNIE = 0;

    while(selected == 0){
        while((LEFT_BUTTON || ))
    }
}

void engine_menu(){ 
    
    engine_ask_for_bluetooth();
    engine_ask_for_reference();

    delay_ms(200);
    lcd_clear_screen();

    tui_write_at(1, 15, REFERENCE, 0, 0);
    tui_write_at(5, 5, "1", 1, 0);
    tui_write_at(5, 35, "2", 0, 0);

#ifndef TWO_BARS
    tui_write_at(5, 65, "3", 0, 0);
    tui_write_at(5, 95, "4", 0, 0); 
#endif
    
    while(LEFT_BUTTON == 0){    
    }

    delay_ms(200);    
    lcd_clear_screen();
    
}

void engine_initialization() {
    engine_splash();
    engine_menu();
    init_button_interrupt();
    adc_init();
    lcd_clear_screen();
}

void engine_start() {
    phase = RUN;
    timer_start();
}
