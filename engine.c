#include <p24FV16KM204.h>



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
    RUN,
    SLEEP
};

volatile int is_blueetooth_enable;
volatile enum engine_phase phase = INIT;




void __attribute__((__interrupt__, __auto_psv__)) _CNInterrupt(void){

    delay_ms(100);
    
    if(LEFT_BUTTON == 1 && RIGHT_BUTTON == 1){
     button_calibration_interrupt();   
    }
    else if(LEFT_BUTTON == 1){
        button_left_interupt();
    }else if(RIGHT_BUTTON == 1){
        button_right_interupt();
    }else if(SELECTION_BUTTON == 1){
        button_select_interupt();
    }else if(POWER_BUTTON == 1){
        button_power_interupt();
    }else if(BACKLIGHT_BUTTON == 1){
        button_light_interupt();
    }

    delay_ms(100);
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
     * RA9 = CN34  => LEFT
     * RA10 = CN35 =>SELECT
     * RA11 = CN36 <>RIGHT
     * RA2 = CN30   => power button 
     * RA3 = CN29 => backlight
     * 
    */
    
    CNEN1 = 0b0000000000000000; 
    CNEN2 = 0b0110000000000000;
    CNEN3 = 0b0000000000011100;     
    
}

void set_scale(unsigned short new_reference, unsigned short new_range){
    extern unsigned short pression_range;
    extern unsigned short pression_reference;
    int new_reference_pressure = measure_to_pressure(new_reference);
    int new_range_pressure = measure_to_pressure(new_range);

    if(new_reference_pressure - new_range_pressure / 2 <= 0){
        new_reference = new_range / 2;
    }

    pression_reference = new_reference;

    if(new_range <= MAX_RANGE && new_range >= MIN_RANGE){
        pression_range = new_range;
    }
    return;
}

void button_left_interupt(){
    extern unsigned short reference_sensor;
    extern unsigned short weightedAverages[4];
    extern unsigned short pression_range;
    set_scale(weightedAverages[reference_sensor], pression_range * RANGE_STEP);
    delay_ms(200);
    return;
}

void button_right_interupt(){
    extern unsigned short reference_sensor;
    extern unsigned short weightedAverages[4];
    extern unsigned short pression_range;
    set_scale(weightedAverages[reference_sensor], pression_range / RANGE_STEP);
    delay_ms(200);
    return;
}

void button_select_interupt(){
    extern unsigned short reference_sensor;
    extern unsigned short weightedAverages[4];
    extern unsigned short pression_range;
    set_scale(weightedAverages[reference_sensor], pression_range);
    delay_ms(200);
    return;
}

void button_light_interupt(){
    extern int backlight_level;
    backlight_level = (backlight_level + 1)%3 ;
    pwm_set(backlight_level);
    return;
}

void button_power_interupt(){
     if(phase == SLEEP){
         phase = INIT;
     }else{
         //TODO changer les registres ECN pour désactiver les interruptions autres que le buton pwoer
         CNEN1 =0;
         CNEN2 = 0b0100000000000000; // Only keep power button interrupt
         CNEN3 = 0 ;         
         phase = SLEEP;
         timer_stop();
         lcd_clear_screen();
         tui_write_at(3,40,BYE,0,0);
         delay_ms(2000);
//         PORTA = 0;
//         PORTB = 0;
//         LATC = 0;
         //lcd_off();
         POWER_CIRCUIT_ENABLE = 0;

         IFS1bits.CNIF = 0;
         
         //OSCCONbits.CLKLOCK;

         Sleep();
        }
    return;
}

void button_calibration_interrupt(){
    delay_ms(500);
    average_update_weighted_averages();
    extern unsigned short reference_sensor;
    extern unsigned short weightedAverages[4];
    extern int sensor_offsets[4];
    int i;
    
//    sensor_offsets[0] = 0;
//    sensor_offsets[1] = SENSOR1AVGBUF - SENSOR2AVGBUF;
//    sensor_offsets[2] = SENSOR1AVGBUF - SENSOR3AVGBUF;
//    sensor_offsets[3] = SENSOR1AVGBUF - SENSOR4AVGBUF;
    
    for(i=0;i<4;i++){
        sensor_offsets[i]= weightedAverages[reference_sensor] - weightedAverages[i];
            
        }
          
    
}

void pwm_init(){
    CCP5CON1Lbits.CCSEL = 0; //MCCP operting mode
    CCP5CON1Lbits.MOD = 0b0101;   // Set mode (Buffered Dual-Compare/PWM mode)
    
    CCP5CON1Lbits.TMR32 = 0;      // Set timebase width (16-bit)
    CCP5CON1Lbits.TMRSYNC = 0;    // Set timebase synchronization (Synchronized) 
    CCP5CON1Lbits.CLKSEL = 0b000; // Set the clock source (Tcy)
    CCP5CON1Lbits.TMRPS = 0b00;   // Set the clock pre-scaler (1:1)

    CCP5CON1Hbits.TRIGEN = 0;     // Set Sync/Triggered mode (Synchronous)
    CCP5CON1Hbits.SYNC = 0b00000; // Select Sync/Trigger source (Self-sync)
    
    CCP5CON2Hbits.OCAEN = 1;    
    CCP5CON3Hbits.POLACE = 0;
    CCP5CON3Hbits.PSSACE = 0b10;   //pins driven inactive on shutdown
    
    CCP5TMRL = 0x0000;
    CCP5PRL = 0xFFFF;
    CCP5RA = 0x0000;
    CCP5RB = 0x0000;
    CCP5CON1Lbits.CCPON = 1;      // Turn on MCCP module
}

void pwm_set(int level){
    if(level == 0){        
        CCP5RB = 0xFFFF;
    }
    if(level == 1){
        CCP5RB = 0x8888;        
    }
    if(level == 2){
        CCP5RB = 0x00; 
    }
}
void engine_splash(){
    lcd_on();
    lcd_clear_screen();
    lcd_on();
    lcd_bitmap(twinmaxLogo);    
    delay_ms(4000);
    lcd_clear_screen();
    lcd_on();
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
    // Temporaly disable button interruption
    IEC1bits.CNIE = 0;
    extern unsigned short reference_sensor;

     if(engine_ask_for_bluetooth() == 1){
         ble_init();
     }

     lcd_clear_screen();
     reference_sensor = engine_ask_for_reference_sensor();

    lcd_clear_screen();
}

void engine_initialization() {
   
    POWER_CIRCUIT_ENABLE = 1 ; //ALMIENTATION ENABLE
    delay_ms(1500);
   engine_splash();    
    // Initialise sleeping options
    RCONbits.RETEN = 1;
    RCONbits.PMSLP = 0;
    pwm_init();   
    
    
    
    engine_menu();
    delay_ms(650);
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
    extern int sensor_offsets[4];
    pression_range = MAX_RANGE;             
    unsigned short vals[4];
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
        for(i=0;i<4;i++){
            vals[i]= weightedAverages[i] + sensor_offsets[i];
        }
        tui_displayMeasures(vals, pression_reference, pression_range, reference_sensor);
        delay_ms(100);
    }
}
