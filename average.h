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

// initialize an average array
void average_init(moving_average *, unsigned short);

// add a value to the average array at the specific index.
// return next index to use
void average_add_value(moving_average *, unsigned short);

// return the average
unsigned short average_get_average(moving_average *);

#endif