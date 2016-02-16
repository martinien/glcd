#ifndef AVERAGE_H
#define	AVERAGE_H
#define AVERAGE_SIZE 200

// Average structure
typedef struct movingAverage{
  
  // Olds the value
  unsigned short values[AVERAGE_SIZE];
  
  // Index of the next value to pop out
  unsigned short index;

  // Keep the sum of the values updated at each changes
  unsigned long sum;
} moving_average;

void averages_init();

void average_init(struct movingAverage * average, unsigned short default_value);

void average_add_value(struct movingAverage * average, unsigned short value);

unsigned short average_get_average(struct movingAverage * average);

void average_update_weighted_averages();

unsigned short averages_get_average(int i);

void average_add_values(unsigned short value1, unsigned short value2, unsigned short value3, unsigned short value4);

#endif