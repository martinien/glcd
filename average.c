#include "average.h"




void average_init(mavg movingAvg,unsigned short defaultValue){
    int i;    
    for(i=0;i<AVGSIZE;i++){
        movingAvg.values[i]=defaultValue;
    }
    movingAvg.index = 0;
    movingAvg.currentSum = AVGSIZE * defaultValue;        
}

void average_add_value(mavg movingAvg,unsigned short value){
    movingAvg.currentSum += value - movingAvg.values[movingAvg.index] ;
    movingAvg.values[movingAvg.index] = value;
    movingAvg.index = (movingAvg.index + 1)%AVGSIZE;      
    
}

unsigned short average_get_average(mavg movingAvg){
    
    return ((unsigned short)(movingAvg.currentSum/AVGSIZE));
    
    
}






