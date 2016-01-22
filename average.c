#include "average.h"

unsigned short* average_init(int nb_values){
    unsigned short * array;
    array = malloc(nb_values * sizeof(unsigned short));
    array[nb_values - 1] = 0xFFFF;
}

int average_add_value(unsigned short values[], int nb_values, unsigned short val, int index){
    values[index] = val;
    return index + 1 % nb_values;
}

unsigned short average_get_average(unsigned short* values, int nb_values){
    int i = 0;
    unsigned long sum = 0;
    if(!average_is_average_ready(values, nb_values)){
      return 0;
    }
    for(i = 0; i < nb_values; i++){
        sum += values[i];
    }
    return sum / nb_values;
}

int average_is_average_ready(unsigned short* values, int nb_values){
    if(values[nb_values - 1] == 0xFFF){
        return 0;
    }else{
        return 1;
    }
}

int average_free(unsigned short* values){
    return free(values);
}
