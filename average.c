#include "average.h"



void averages_init(){
    // Initialise 4 averages
    extern struct movingAverage avgs[4];
    extern struct movingAverage * movingAverages[4];
    int i;
    for(i = 0; i < 4; ++i){
        movingAverages[i] = &avgs[i];
        average_init(movingAverages[i], 0);
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

unsigned short average_get_average(struct movingAverage * average){
    
    return ((unsigned short)(average->sum / AVERAGE_SIZE));
}

void average_update_weighted_averages(){
    extern struct movingAverage * movingAverages[4];
    extern unsigned short weightedAverages[4];
    long tmp;
    int i=0;
    for(i=0;i<4;i++){
        tmp =  average_get_average(movingAverages[i]);
        weightedAverages[i]= (unsigned short)tmp;
    }      
}
unsigned short averages_get_average(int i){
    extern struct movingAverage * movingAverages[4];
    return average_get_average(movingAverages[i]);
}




void average_add_values(unsigned short value1, unsigned short value2, unsigned short value3, unsigned short value4){
    extern struct movingAverage * movingAverages[4];
    average_add_value(movingAverages[0], value1);
    average_add_value(movingAverages[1], value2);
    average_add_value(movingAverages[2], value3);
    average_add_value(movingAverages[3], value4);
}
