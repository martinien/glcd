/* 
 * File:   inputs.h
 * Author: martinien
 *
 * Created on 4 février 2016, 11:52
 */

#ifndef INPUTS_H
#define	INPUTS_H

/*ADC BUFFER WITH SENSOR CONVERTED MEASURE*/
    /*
     * RB12 = capteur1 =         AN12
     RB13 = capteur moyenne 1 = an11
     RB14 = capteur 2 =         an10
     RB15 = capteur 2 moyenne =  an9
     RA0 = capteur 3  =          an0
     RA1 = capteur 3 moyenne =   an1
     RC0 = capteur 4  =          an6
     RA4 = capteur 4 moyenne =   an16
     */
#define SENSOR1BUF       ADC1BUF12
#define SENSOR1AVGBUF    ADC1BUF11
#define SENSOR2BUF       ADC1BUF10
#define SENSOR2AVGBUF    ADC1BUF9
#define SENSOR3BUF       ADC1BUF0
#define SENSOR3AVGBUF    ADC1BUF1
#define SENSOR4BUF       ADC1BUF6
#define SENSOR4VAGBUF    ADC1BUF16


/*BUTTONS*/
#define TESTBUTTON PORTAbits.RA10
#define LEFTBUTTON 
#define RIGHTBUTTON



#endif	/* INPUTS_H */

