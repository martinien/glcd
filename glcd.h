#ifndef GLCD_H
#define	GLCD_H

#define CSLOW 0
#define CSHIGH 1
#define FCY 4000000UL
#include "myFont.h"
#include <p24FV16KM202.h>
#include <libpic30.h>


#define LCD_TRIS      TRISB
#define LCD_DATA      PORTB
#define ENABLE        LATAbits.LATA4
#define RW            LATAbits.LATA3
#define DI            LATAbits.LATA2
#define RESET         LATAbits.LATA7
#define CS1           LATAbits.LATA0
#define CS2           LATAbits.LATA1



 

#define LEFT          0b01

#define RIGHT         0b10

#define BOTH          0b11

#define NONE          0b00


/*void _lcd_enable(void);

unsigned char _lcd_status(void);

void _lcd_reset(void);

void _lcd_waitbusy(void);

// public function prototypes

//

// call these all you want !

void lcd_screenon(int on);

void lcd_on();

void lcd_off();

void lcd_clear_screen(void);



void lcd_selectside(unsigned char sides);

void lcd_write (unsigned char data);

unsigned char lcd_read (void);

void lcd_plotpixel(unsigned char rx, unsigned char ry);

void lcd_putchar(char c);

void lcd_puts(char *string);

void lcd_putrs(const char *string);

void lcd_bitmap(const char *bmp);
 

void lcd_char(char c);

void lcd_testChar(char c);

void lcd_longString(const char *string);

void lcd_charAt(char c, int x,int y);

void lcd_startLine(unsigned int z);

void lcd_horizontalBar(unsigned char index,unsigned char val);

void lcd_draw_bar(unsigned char index, unsigned char value, int handling);

void lcd_draw_reversed_char(unsigned char x, unsigned char y, char c);

void lcd_draw_char(unsigned char x, unsigned char y, char c);
*/

#endif