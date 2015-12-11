
#include "glcd.h"
#include <libpic30.h>
#include "myFont.h"
//#define FCY 8000000UL

/*const char font[]= { 


 

};*/

void _lcd_enable(void)

{
 
    ENABLE=0;
    __delay_us(.2);
    ENABLE=1;   
    __delay_us(0.6);
    ENABLE=0;
    __delay_us(.5);
 
  //  __delay_us(.6);
    
}

unsigned char _lcd_status(void)
{
    // returns the lcd status & maintains the TRIS state of the lcd data port

    unsigned char _lcd_tris, _status;
    
    // save values
    _lcd_tris = LCD_TRIS;
    int cs1 = CS1;
    int cs2 = CS2;
    
    // read the status
    LCD_TRIS=0xFF; // all inputs

    DI=0; RW=1; // command/read
    CS1 = 0;
    CS2 = 0;

    __delay_us(.2);
    _lcd_enable();
    __delay_us(.2);

    _status = LCD_DATA;
    __delay_us(.2);
    
    // restore values
    LCD_TRIS = _lcd_tris;
    CS1 = cs1;
    CS2= cs2;

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

void lcd_on(){
    int data;
    ENABLE=0; 
    __delay_us(.1);
    CS1=0;
    CS2=0;
    RW = 0;
    DI=0;
    data = 0x3F;
    LCD_TRIS = 0;
    LCD_DATA = data;
    __delay_us(.5); 
    ENABLE=1;
    __delay_us(.5);
    ENABLE=0;
    __delay_us(.1);    
}

void lcd_off(){
    
    int data;
    ENABLE=0;    
    CS1=0;
    CS2=0;
    RW = 0;
    DI=0;
    data = 0x3E;
    LCD_TRIS = 0;
    LCD_DATA = data;
    __delay_us(.5); 
    ENABLE=1;
    __delay_us(.5);
    ENABLE=0;
    __delay_us(.1);
}

void lcd_cls(void){
    unsigned char x,y;

    CS1 = 0;
    CS2 = 0;
    for (x=0; x<8; x++){
        // set the page (x)
        lcd_setpage(x);
        // set the y address to 0
        lcd_setyaddr(0);
        // setup for data
        LCD_DATA=0; RW=0; DI=1;
        // clear the row
        for (y=0; y<64; y++){
            _lcd_enable(); 
            //Delay10TCYx(1);
        }
    }
}

void lcd_setpage(unsigned char page){
    unsigned int cs1,cs2;
    cs1 = CS1;
    cs2 = CS2;
    _lcd_waitbusy();

    DI=0; RW=0;         
    CS1= 0;
    CS2=0;
    LCD_DATA = 0b10111000 | page;
    
    _lcd_enable();

    CS1=  cs1;
    CS2 = cs2;
}

void lcd_setyaddr(unsigned char y){
    _lcd_waitbusy();
    DI=0; RW=0;
    LCD_DATA = 0b01000000 | (y & 0b00111111);
    _lcd_enable();
}

void _lcd_waitbusy(void){
    while (_lcd_status() & 0b10000000){
        __delay_ms(.5); // .5 ms
    }
}

void lcd_write (unsigned char data){
    _lcd_waitbusy();
    DI=1; RW=0;
    LCD_TRIS=0; 
    LCD_DATA = data;
    _lcd_enable();
}

void lcd_selectside(unsigned char sides){
    if (sides & LEFT)
        CS1 = 0;
    else
        CS1 = 1;
    if (sides & RIGHT)
        CS2 = 0;
    else
        CS2 = 1;
}

/*unsigned char lcd_read (void){
    unsigned char _data;
    LCD_TRIS=0xFF;

    RW = 1;
    DI=1;

    _lcd_enable();
    _data = LCD_DATA;
    LCD_TRIS=0x00;

    return _data;
}*/

unsigned char lcd_read(void)
{
    unsigned char _lcd_tris, _data;
    _lcd_tris = LCD_TRIS;
    LCD_TRIS=0xFF; // all inputs
    DI=1; RW=1;
    
    __delay_us(.2);
    _lcd_enable();
    __delay_us(.2);
    _data = LCD_DATA;
    __delay_us(.2);
    
    // restore the tris value
    LCD_TRIS = _lcd_tris;
    return _data;
}

void lcd_plotpixel(unsigned char rx, unsigned char ry){
    unsigned char data;

    _lcd_waitbusy();
    
    // select the correct side
    lcd_setpage( ry >> 3);    
    if (rx & 64)
        lcd_selectside(RIGHT);
    else
        lcd_selectside(LEFT);

    lcd_setyaddr( rx & 0b00111111);
    data = lcd_read();
    lcd_setyaddr( rx & 0b00111111); 
    lcd_write (data | (1 << (ry & 0b111)));
}



void lcd_char(char c)
{
    unsigned char page, y;
    int i,charIndex;
      
    lcd_selectside(LEFT);    
    charIndex = c;
    //charIndex -= 32; 
    for(i = 0; i < 6; i++){
        lcd_write(myfont[charIndex][i]);
    //printf('%c',myfont[base][i]);    }
    }
}
 

/*void lcd_putchar(char c)

{

    int base;

    base = c - 32;

    base *= 3;

    lcd_write(font[base]);

    lcd_write(font[base + 1]);

    lcd_write(font[base + 2]);

    lcd_write(0);

}*/

void lcd_putrs(const char *string)

{

    char i=0;

    while (string[i] != 0)

        lcd_char(string[i++]);

} 
/*
void lcd_puts(char *string)

{

    char i=0;

    while (string[i] != 0)

        lcd_putchar(string[i++]);

} */


void lcd_bitmap(const char * bmp)
{
    unsigned char i, j;
    
    for(i = 0; i < 8; i++){   
       lcd_selectside(LEFT);  
       
       for(j = 0; j < 64 ; j++){
         lcd_setpage(i);  
         lcd_setyaddr(j & 0b00111111);
         lcd_write(bmp[(i*128)+j]);
       }
       
       lcd_selectside(RIGHT);    
       for(j = 64 ; j < 128 ; j++){
          lcd_setpage(i);  
          lcd_setyaddr(j & 0b00111111);
          lcd_write(bmp[(i*128)+j]);
       }  
    }
}


/*void lcd_longString(const char *string){

    unsigned char i, j;    
    for(i = 0; i < 8; i++){   
       lcd_selectside(LEFT);  
       
       for(j = 0; j < 64 ; j++){
         lcd_setpage(i);  
         lcd_setyaddr(j & 0b00111111);
         lcd_write(bmp[(i*128)+j]);
       }
       
       lcd_selectside(RIGHT);    
       for(j = 64 ; j < 128 ; j++){
          lcd_setpage(i);  
          lcd_setyaddr(j & 0b00111111);
          lcd_write(bmp[(i*128)+j]);
       }  
    }
    */
    
    









int is_busy()
{
    int status = 0;        //Read data here
    
    ENABLE = 0;                 //Low Enable
    __delay_us(1);            //tf
    RW = 1;                 //Read
    DI = 0;                 //Status         
    __delay_us(1);            //tasu
    ENABLE = 1;                 //High Enable
    __delay_us(5);            //tr + max(td,twh)->twh
    
    //Dummy read
    ENABLE = 0;                 //Low Enable
    __delay_us(5);            //tf + twl + chineese error    
    
    ENABLE = 1;                 //High Enable
    __delay_us(1);            //tr + td        
                                  
    status = LCD_DATA;    //Input data
    ENABLE = 0;                 //Low Enable
    __delay_us(1);            //tdhr
    /*#ifdef DEBUG_READ
        printf("S:%x\n\r",status);
    #endif*/
    return (status & 0x80);           
}




