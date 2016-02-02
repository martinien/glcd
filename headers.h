#ifndef HEADERS_H
#define	HEADERS_H


#include <p24FV16KM204.h>


#define FCY 16000000UL
#include <libpic30.h>

#ifndef LOGO_H
#include "logo.h"
#endif
//
#define delay_ms __delay_ms
#define delay_us __delay_us

#include "average.h"
#include "twinmaxUI.h"
#include "timer.h"

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* HEADERS_H */

