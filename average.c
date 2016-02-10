#include "average.h"



void averages_init(){
    // Initialise 4 averages
    extern struct movingAverage avgs[4];
    extern struct movingAverage * averages[4];
    int i;
    for(i = 0; i < 4; ++i){
        averages[i] = &avgs[i];
        average_init(averages[i], 0);
    }
}

void average_init(struct movingAverage * average, unsigned short default_value){
    int i;    
    for(i = 0; i < AVERAGE_SIZE; i++){
        average->values[i] = default_value;
    }
    average->index = 0;
    average->sum = AVERAGE_SIZE * default_value;        
}

void average_add_value(struct movingAverage * average, unsigned short value){
    // change the sum by adding the new value and removing the old one
    average->sum = average->sum + value - average->values[average->index];

    // change the value in the array (FIFO mode)
    average->values[average->index] = value;

    // move the index
    average->index = (average->index + 1) % AVERAGE_SIZE;
}

unsigned short average_get_average(int index){
    extern struct movingAverage * averages[4];
    return ((unsigned short)(averages[index]->sum / AVERAGE_SIZE));
}

unsigned short average_get_average_when_in_interrupt(int index){
//    extern struct movingAverage * averages[4];
    extern struct movingAverage * averages[4];
    return ((unsigned short)(averages[index]->sum / AVERAGE_SIZE));
}

void average_add_values(unsigned short value1, unsigned short value2, unsigned short value3, unsigned short value4){
    extern struct movingAverage * averages[4];
    average_add_value(averages[0], value1);
    average_add_value(averages[1], value2);
    average_add_value(averages[2], value3);
    average_add_value(averages[3], value4);
}
