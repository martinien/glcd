#define FCY 4000000UL
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

/*#define GLCD_EN       PORTAbits.RA1 
#define GLCD_Data     PORTB
#define GLCD_Dir      TRISB

#define GLCD_CS1      PORTAbits.RA7
#define GLCD_CS2      PORTAbits.RA0
#define GLCD_RS       PORTAbits.RA3
#define GLCD_RW       PORTAbits.RA2
#define GLCD_RST      PORTAbits.RA4

#define GLCD_CS1_Direction  TRISABITS.TRISA7
#define GLCD_CS2_Direction  TRISABITS.TRISA0
#define GLCD_RS_Direction   TRISABITS.TRISA3
#define GLCD_RW_Direction   TRISABITS.TRISA2
#define GLCD_RST_Direction  TRISABITS.TRISA4
#define GLCD_EN_Direction   TRISABITS.TRISA1*/

 

#define LEFT          0b01

#define RIGHT         0b10

#define BOTH          0b11

#define NONE          0b00
// Glcd module connections

// End Glcd module connections

// internal function prototypes

// 

// you would not normally call these directly. but you can 

// if you like.

void _lcd_enable(void);

unsigned char _lcd_status(void);

void _lcd_reset(void);

void _lcd_waitbusy(void);

// public function prototypes

//

// call these all you want !

void lcd_screenon(int on);

void lcd_on();

void lcd_off();

void lcd_cls(void);

void lcd_setpage(unsigned char page);

void lcd_setyaddr(unsigned char y);

void lcd_selectside(unsigned char sides);

void lcd_write (unsigned char data);

unsigned char lcd_read (void);

void lcd_plotpixel(unsigned char rx, unsigned char ry);

void lcd_putchar(char c);

void lcd_puts(char *string);

void lcd_putrs(const char *string);

 

 