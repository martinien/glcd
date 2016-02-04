#ifndef ENGINE_H
#define	ENGINE_H




#ifndef delay_ms
#define delay_ms __delay_ms
#define delay_us __delay_us
#endif



void button_left_interupt();

void button_right_interupt();

void button_select_interupt();

void button_light_interupt();

void button_power_interupt();

void engine_initialization();

void engine_start();

#endif
