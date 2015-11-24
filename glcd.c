
#include "glcd.h"
#include <libpic30.h>
//#define FCY 8000000UL

const char font[]= { 

 /* add your own font data

    each char is 3x8 pixels. 3 bytes per char. left column, middle column, right column

 */

};

void _lcd_enable(void)

{

  
    ENABLE=1;

    __delay_us(5);

    ENABLE=0;

    __delay_us(5);

}

unsigned char _lcd_status(void)

{

    // returns the lcd status & maintains the TRIS state of the

    // lcd data port

    unsigned char _lcd_tris, _status;

    // save the tris value

    _lcd_tris = LCD_TRIS;

    // read the status
    LCD_TRIS=0xFF; // all inputs

    DI=0; RW=1; // command/read

    _lcd_enable();

    _status = LCD_DATA;

    // restore the tris value
    LCD_TRIS = _lcd_tris;

    

    return _status;

}

void _lcd_reset(void)

{

    // reset the lcd module
    // datasheet says reset must be low for minimum of 1us

    // after Vdd clears 4.5v. 

    // from experimentation, this is bullshit. this seems to
    // work though.

    __delay_ms(.5); // actually .5 ms

    RESET=1;
    __delay_ms(.5); // actually .5 ms

    RESET=0;

    // check status, and wait if necessary

    while (_lcd_status() & 0b00010000)

    {
        __delay_us(5); // .5 ms

    }

}

void lcd_screenon(unsigned char on)

{

    // turn the display on or off

    LCD_TRIS=0; // all outputs

    RW=0; DI=0;

    LCD_DATA = 0b00111110 | (on & 0b00000001); // main screen turn on!
    _lcd_enable();

}

void lcd_cls(void)

{

    unsigned char x,y;

    for (x=0; x<8; x++)

    {

        // set the page (x)

        lcd_setpage(x);

        // set the y address to 0

        lcd_setyaddr(0);

        // setup for data

        LCD_DATA=0; RW=0; DI=1;

        // clear the row

        for (y=0; y<64; y++)

        {

            _lcd_enable(); 

            //Delay10TCYx(1);

        }

    }

}

void lcd_setpage(unsigned char page)

{

    _lcd_waitbusy();

    DI=0; RW=0; 

    LCD_DATA = 0b10111000 | page;

    _lcd_enable();

}

void lcd_setyaddr(unsigned char y)

{
    _lcd_waitbusy();

    DI=0; RW=0;

    LCD_DATA = 0b01000000 | (y & 0b00111111);

    _lcd_enable();

}

void _lcd_waitbusy(void)

{
    while (_lcd_status() & 0b10000000)

    {

        __delay_ms(.5); // .5 ms

    }

}

void lcd_write (unsigned char data)

{

    _lcd_waitbusy();

    DI=1; RW=0;

    LCD_TRIS=0; 

    LCD_DATA = data;

    _lcd_enable();

}

void lcd_selectside(unsigned char sides)

{

    // set a CS pin low to enable it

    if (sides & LEFT)

        CS1 = 0;

    else

        CS1 = 1;

    if (sides & RIGHT)

        CS2 = 0;

    else

        CS2 = 1;

}

unsigned char lcd_read (void)

{

    unsigned char _data;

    

    LCD_TRIS=0xFF;

    RW = 1;
    DI=1;

    _lcd_enable();

    _data = LCD_DATA;

    LCD_TRIS=0x00;

    return _data;

}

void lcd_plotpixel(unsigned char rx, unsigned char ry)

{

    unsigned char data;

    _lcd_waitbusy();

    // select the correct side

    if (rx & 64)

        lcd_selectside(RIGHT);

    else

        lcd_selectside(LEFT);

 

    lcd_setpage( ry >> 3);
    lcd_setyaddr( rx & 0b00111111);

    data = lcd_read(); // dummy read needed here

    data = lcd_read();

    lcd_setyaddr( rx & 0b00111111); 

    lcd_write (data | (1 << (ry & 0b111)));

}

 

void lcd_putchar(char c)

{

    int base;

    base = c - 32;

    base *= 3;

    lcd_write(font[base]);

    lcd_write(font[base + 1]);

    lcd_write(font[base + 2]);

    lcd_write(0);

}

void lcd_putrs(const char *string)

{

    char i=0;

    while (string[i] != 0)

        lcd_putchar(string[i++]);

} 

void lcd_puts(char *string)

{

    char i=0;

    while (string[i] != 0)

        lcd_putchar(string[i++]);

} 



/**************************/
/*
 * Project name: Testing GLCD with PIC16F887
 * Copyright:
     (c) Embedded-Lab.com, 2011.

 * Description:
     This routine demonstrates how to initialize a KS0108 based GLCD and 
     activate the pixels on display. A sub-routine is written to draw a point on
     the GLCD at a given coordinates.
      * Test configuration:
     MCU:             PIC16F887
     Dev.Board:       UNI-DS6
     Oscillator:      HS, 10.0000 MHz
     Ext. Modules:    GLCD 128x64, KS108/107 controller

*/




void delay_us(int t){
    __delay_us(t);
}

/*
void Enable_Pulse()
{
   GLCD_EN=1; //EN high
   delay_us(5);
   GLCD_EN=0; //EN low
   delay_us(5);
}

void GLCD_ON()
{
    //Activate both chips
    GLCD_CS1 = 0;
    GLCD_CS2 = 0;
    GLCD_RS = 0;          //RS low --> command
    GLCD_RW = 0;          //RW low --> write
    GLCD_Data = 0x3F;         //ON command
    Enable_Pulse();
}

void Set_Start_Line(unsigned short line)
{
    GLCD_RS = 0;             //RS low --> command
    GLCD_RW = 0;             //RW low --> write
    //Activate both chips
    GLCD_CS1 = 0;
    GLCD_CS2 = 0;
    GLCD_Data = 0xC0 | line;     //Set Start Line command
    Enable_Pulse();
}

void GOTO_COL(unsigned int x)
{
   unsigned short Col_Data;
   GLCD_RS = 0;              //RS low --> command
   GLCD_RW = 0;              //RW low --> write
   if(x<64)             //left section
   {
      GLCD_CS1 = 0;          //select chip 1
      GLCD_CS2 = 1;          //deselect chip 2
      Col_Data = x;              //put column address on data port
   }
   else                 //right section
   {

      GLCD_CS2 = 0;
      GLCD_CS1 = 1;
      Col_Data = x-64;   //put column address on data port
   }
   Col_Data = (Col_Data | 0x40 ) & 0x7F;  //Command format
   GLCD_Data = Col_Data;
   Enable_Pulse();
}

void GOTO_ROW(unsigned int y)
{
   unsigned short Col_Data;
   GLCD_RS = 0;                  //RS low --> command
   GLCD_RW = 0;                  //RW low --> write
   Col_Data = (y | 0xB8 ) & 0xBF; //put row address on data port set command
   GLCD_Data = Col_Data;
   Enable_Pulse();
}

void GOTO_XY(unsigned int x,unsigned int y)
{
    GOTO_COL(x);
    GOTO_ROW(y);
}

void GLCD_Write(unsigned short b)
{
   GLCD_RS = 1;          //RS high --> data
   GLCD_RW = 0;          //RW low --> write
   GLCD_Data = b;            //put data on data port
   delay_us(1);
   Enable_Pulse();
}

unsigned short GLCD_Read(unsigned short column)
{
    unsigned short read_data = 0; //Read data here
    GLCD_Dir = 0xFF;     //PORTD as Input
    GLCD_RW = 1;             //Read
    GLCD_RS = 1;             //Data
    GLCD_CS1 = (column>63);
    GLCD_CS2 = !GLCD_CS1;         //Disable/Enable CS2
    delay_us(1);        //tasu
    GLCD_EN = 1;             //Latch RAM data into ouput register
    delay_us(1);        //twl + tf

    //Dummy read
    GLCD_EN = 0;             //Low Enable
    delay_us(5);
    GLCD_EN = 1;             //latch data from output register to data bus
    delay_us(1);             //tr + td(twh)

    read_data = GLCD_Data;    //Input data
    GLCD_EN = 0;             //Low Enable to remove data from the bus
    delay_us(1);        //tdhr
    GLCD_Dir = 0x00;     //Output again
    return read_data;
}

 void GLCD_Clrln(unsigned short ln)
 {
    int i;
    GOTO_XY(0,ln);      //At start of line of left side
    GOTO_XY(64,ln);     //At start of line of right side (Problem)
    GLCD_CS1 = 0;
    for(i=0;i<65;i++)
    GLCD_Write(0);
 }

//-------------------------

void GLCD_CLR()
{
   unsigned short m;
   for(m=0;m<8;m++){
    GLCD_Clrln(m);
   }
}

void Draw_Point(unsigned short x,unsigned short y, unsigned short color)
{
    unsigned short Col_Data;;
    GOTO_XY(x,(y/8));
    switch (color)
    {
        case 0:         //Light spot
            Col_Data = ~(1<<(y%8)) & GLCD_Read(x);
        break;
        case 1:         //Dark spot
            Col_Data = (1<<(y%8)) | GLCD_Read(x);
        break;
    }
    GOTO_XY(x,(y/8));
    GLCD_Write(Col_Data);
}

void test() {
  unsigned short u, v;
 
  GLCD_CS1 = 1;                // De-Activate both chips
  GLCD_CS2 = 1;
  GLCD_RST = 1;
  GLCD_ON();
  GLCD_CLR();
  Set_Start_Line(0);
  do {
     
     for(u=0; u<64; u+=6)
      for (v=0; v<128; v+=2)
      Draw_Point(v, u, 1);
      __delay_ms(1000);
      GLCD_CLR();
      __delay_ms(1000);

  } while(1);
}*/
