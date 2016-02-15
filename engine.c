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
#include "headers.h"


enum engine_phase{
    INIT,
    BLUETOOTHMENU,
    REFERENCEMENU,
    RUN,
    SLEEP
};

volatile int is_blueetooth_enable;
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

    delay_ms(500);
    IFS1bits.CNIF = 0;
    button_power_interupt();

    delay_ms(150);

    // Reset flag
    
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
    
    CNEN1 = 0b0000000000000000; // 
    //CNEN2 = 0b0110000000000000; //TODO RESTORE
    CNEN2 = 0b0000000000000000;
    CNEN3 = 0b0000000000011000; 
}

void button_left_interupt(){
    extern unsigned short pression_reference;
    extern unsigned short pression_range;
    extern unsigned short weightedAverages[4];
    extern unsigned short reference_sensor;
    pression_reference = weightedAverages[reference_sensor];
    if(pression_range*RANGE_STEP <= MAX_RANGE){
        pression_range = pression_range*RANGE_STEP;
    }
    return;
    delay_ms(200);
    return;
}

void button_right_interupt(){
    extern unsigned short pression_reference;
    extern unsigned short pression_range;
    extern unsigned short weightedAverages[4];
    extern unsigned short reference_sensor;
    pression_reference = weightedAverages[reference_sensor];
    if(pression_range/RANGE_STEP >= MIN_RANGE){
        pression_range = pression_range/RANGE_STEP;
    }
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
     if(phase == SLEEP){
         phase == INIT ;        
     }        
         
     else{
         phase = SLEEP;
         RCONbits.RETEN = 1; 
         RCONbits.PMSLP = 0;
         timer_stop();
         lcd_clear_screen();
         lcd_off();
         delay_ms(10);
         Sleep();
  
        }
            
     
    return;
}



void engine_splash(){
    lcd_on();
    lcd_clear_screen();
    lcd_on();
    lcd_bitmap(twinmaxLogo);    
    delay_ms(4000);
    lcd_clear_screen();
}

void engine_display_bluetooth_question(){
    tui_write_at(1, 15, BLUETOOTH, 0, 0);      
    tui_write_at(5, 10, YES, is_blueetooth_enable==0, 0);
    tui_write_at(5, 90, NO, is_blueetooth_enable==1, 0);
}

void engine_display_reference_question(int reference_sensor){
    tui_write_at(1, 15, REFERENCE, 0, 0);
    tui_write_at(5, 5, "1", reference_sensor==0, 0);
    tui_write_at(5, 35, "2", reference_sensor==1, 0);
#ifndef TWO_BARS
    tui_write_at(5, 65, "3", reference_sensor==2, 0);
    tui_write_at(5, 95, "4", reference_sensor==3, 0); 
#endif
}

int engine_ask_for_bluetooth(){
    int selected = 0;
    
    while(selected == 0){
        engine_display_bluetooth_question(is_blueetooth_enable);
        while((LEFT_BUTTON || SELECTION_BUTTON || RIGHT_BUTTON) == 0){  
        }
        if(LEFT_BUTTON == 1){
            is_blueetooth_enable = (is_blueetooth_enable + 1) % 2;
        }else if(RIGHT_BUTTON == 1){
            is_blueetooth_enable = (is_blueetooth_enable + 1) % 2;
        }else{
            selected = 1;
        }
        delay_ms(200);
    }

    return is_blueetooth_enable;
}

int engine_ask_for_reference_sensor(){
    int selected = 0;
    unsigned int reference = 0;

    while(selected == 0){
        engine_display_reference_question(reference);
        while((LEFT_BUTTON || RIGHT_BUTTON || SELECTION_BUTTON) == 0){
        }
        if (LEFT_BUTTON == 1){
            reference = (reference - 1) % 4;
            selected = 1;
        }else if(RIGHT_BUTTON == 1){
            reference = (reference + 1) % 4;
        }else if(SELECTION_BUTTON == 1){
            selected = 1;
        }
        delay_ms(200);
    }
    return (int)reference;
}

void engine_menu(){ 
    //TODO (julien 10/02/2016) don't disable all interruption because we want to be interrupted if user press sleep button
    
    // Temporaly disable button interruption
    IEC1bits.CNIE = 0;

    // if(engine_ask_for_bluetooth()){
    //     //ble_init();
    // }

    // reference_sensor = engine_ask_for_reference_sensor();

    lcd_clear_screen();
}

void engine_initialization() {
    engine_splash();
    engine_menu();
    init_button_interrupt();
    averages_init();
    adc_init();
    lcd_clear_screen();
    engine_start();
}

void engine_start() {
    extern unsigned short weightedAverages[4];
    extern unsigned short pression_range;
    extern unsigned short pression_reference;
    extern unsigned short reference_sensor;    
    pression_range = MAX_RANGE;   
    reference_sensor = 3;           
    unsigned short testVals[4];
    int i = 0;
    phase = RUN;
    timer_start();    
    for(i=0;i<10;i++){
        average_update_weighted_averages();
        delay_ms(10)
    };
    average_update_weighted_averages();
    pression_reference = weightedAverages[reference_sensor];
    
    while(phase == RUN){
       
        
            
        average_update_weighted_averages();    
        
//        testVals[0] = SENSOR4BUF;
//        testVals[1] = weightedAverages[3];
//        testVals[2] = averages_get_average(3);
//        testVals[3] = weightedAverages[3];
//        count = (count +10)%4000;
        tui_displayMeasures(weightedAverages, pression_reference, pression_range, reference_sensor);
        
//        delay_ms(20);
//        count = (count+1)%101;
//        tui_battery(count);
        
       
        delay_ms(100);

    }
}
