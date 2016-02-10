#include "average.h"

void average_init(moving_average * average, unsigned short default_value){
    int i;    
    for(i = 0; i < AVERAGE_SIZE; i++){
        average->values[i] = default_value;
    }
    average->index = 0;
    average->sum = AVERAGE_SIZE * default_value;        
}

void average_add_value(moving_average * average, unsigned short value){
    // change the sum by adding the new value and removing the old one
    average->sum = average->sum + value - average->values[average->index];

    // change the value in the array (FIFO mode)
    average->values[average->index] = value;

    // move the index
    average->index = (average->index + 1) % AVERAGE_SIZE;
}

unsigned short average_get_average(moving_average * average){
    return ((unsigned short)(average->sum / AVERAGE_SIZE));
}
