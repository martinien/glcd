unsigned short* average_init(int nb_values){
    unsigned short * array;
    array = MALLOC(nb_values * sizeof(unsigned short));
    array[nb_values - 1] = 0xFFFF;
}

int average_add_value(unsigned short values[], int nb_values, unsigned short val, int index){
    values[index] = val;
    return index + 1 % nb_values;
}

unsigned short average_get_average(unsigned short* values, int nb_values){
    int i = 0;
    unsigned long sum = 0;
    if(!is_average_ready()){
      return 0;
    }
    for(i = 0; i < nb_values; i++){
        sum += values[i];
    }
    return sum / nb_values;
}

bool average_is_average_ready(){
    if(array[nb_values - 1] == 0xFFF){
        return false;
    }else{
        return true;
    }
}
