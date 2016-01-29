#ifndef AVERAGE_H
#define	AVERAGE_H
#define AVGSIZE 200


typedef struct movingAverage {
   unsigned short values[AVGSIZE] ;
   unsigned short index;
   unsigned long currentSum;   
}mavg;

// initialize an average array
void average_init(mavg *,unsigned short);


// add a value to the average array at the specific index.
// return next index to use
void average_add_value(mavg * , unsigned short );


// return the average if the array is full
unsigned short average_get_average(mavg *);


// return 1 if all values as been set in the array at least once
// (ie check if the last value is different from init value (0xFFFF))
// return 0 otherwise

#endif
