/* 
 * File:   params.h
 * Author: martinien
 *
 * Created on 8 février 2016, 16:30
 */

#ifndef PARAMS_H
#define	PARAMS_H

#define MAX_RANGE 2560
#define MIN_RANGE 20
#define RANGE_STEP 2

// #define TWO_BARS
#ifdef TWO_BARS
#define BAR_WIDTH 40
#define BAR_SPAN 48
#else
#define BAR_WIDTH 20
#define BAR_SPAN 24
#endif
#define MENU_WIDTH 28

#endif	/* PARAMS_H */

