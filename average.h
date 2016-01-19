
// initialize an average array
unsigned short* average_init(int nb_values);


// add a value to the average array at the specific index.
// return next index to use
int average_add_value(unsigned short values[], int nb_values, unsigned short val, int index);


// return the average if the array is full
unsigned short average_get_average(unsigned short* values, int nb_values);


// return 1 if all values as been set in the array at least once
// (ie check if the last value is different from init value (0xFFFF))
// return 0 otherwise
int average_is_average_ready(unsigned short* values, int nb_values);

