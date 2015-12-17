
#include "glcd.h"
#include <libpic30.h>
#include "myFont.h"

int currentX;
int currentY;
int currentPage;

int BAR_WIDTH=14;
int BAR_SPAWN=16;
int MENU_WIDHT=64;
unsigned char BLANK_BIT=0b00000000;
unsigned char FULL_BIT=0b11111111;

void _lcd_enable(void){
    ENABLE=0;
    __delay_us(.2);
    ENABLE=1;   
    __delay_us(0.6);
    ENABLE=0;
    __delay_us(.5);
 }

unsigned char _lcd_status(void){
    unsigned char status,_lcd_tris;
    _lcd_tris = LCD_TRIS;
    int cs1 = CS1;
    int cs2 = CS2; 
    CS1 = 0;
    CS2 = 0;
    ENABLE = 0;                 //Low Enable
    __delay_us(1);            //tf
    RW = 1;                 //Read
    DI = 0;                 //Status  
    LCD_TRIS=0b11111111;
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
    
    LCD_TRIS = _lcd_tris;
    CS1 = cs1;
    CS2= cs2;
    
    return (status);           
    /*unsigned char _lcd_tris, _status;    
    // save values
    _lcd_tris = LCD_TRIS;
    int cs1 = CS1;
    int cs2 = CS2;    
    // read the status
    LCD_TRIS=0b0000000011111111; // all inputs    
    __delay_us(.2);
    ENABLE=0;
    DI=0; RW=1; // command/read
    CS1 = 0;
    CS2 = 0;
    __delay_us(.5);
    ENABLE=1;   
    __delay_us(0.4);
    _status = PORTB ;
    __delay_us(.3);
    ENABLE=0;
    
    
    //_status = 0b00101011; //TODO REMOVE
    __delay_us(.1);
    
    // restore values
    LCD_TRIS = _lcd_tris;
    CS1 = cs1;
    CS2= cs2;

    return _status;*/
}

void _lcd_reset(void){
    __delay_ms(.5); // actually .5 ms
    RESET=1;
    __delay_ms(.5); // actually .5 ms
    RESET=0;
    // check status, and wait if necessary
    while (_lcd_status() & 0b00010000){
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
    //lcd clear screen
    unsigned char x,y;

    lcd_set_address(0);
    lcd_set_address(64);
    CS1 = 0;
    CS2 = 0;
    for (x=0; x<8; x++){
        // set the page (x)
        lcd_set_page(x);
        // set the y address to 0
        
        // setup for data
        LCD_DATA=0; RW=0; DI=1;
        // clear the row
        for (y=0; y<64; y++){
            _lcd_enable(); 
            //Delay10TCYx(1);
        }
    }
}

void lcd_set_page(unsigned char page){
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



void _lcd_waitbusy(void){
    while (_lcd_status() & 0b10000000){
        __delay_ms(.5); // .5 ms
    }
}

void lcd_write(unsigned char data){
    _lcd_waitbusy();
    DI=1; RW=0;
    LCD_TRIS=0; 
    LCD_DATA = data;
    _lcd_enable();
    currentY++;
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

unsigned char lcd_read(void){
    unsigned char _lcd_tris, _data;
    ENABLE = 0;
    _lcd_tris = LCD_TRIS;
    LCD_TRIS=0xFF; // all inputs
    DI=1; RW=1;    
    __delay_us(.5);
    ENABLE=1;
    __delay_us(.5);
    ENABLE=0; 
    __delay_us(.5);
    ENABLE=1;
    __delay_us(.3);
    _data = LCD_DATA;
    __delay_us(.3);
    ENABLE = 0;       
    
    // restore the tris value
    LCD_TRIS = _lcd_tris;
    currentY++;
    return _data;
}

void lcd_plotpixel(unsigned char x, unsigned char y){
    unsigned char data;

    _lcd_waitbusy();
    lcd_set_page(x>>3);
    lcd_set_address(y);
    data = lcd_read();
    lcd_set_address(y);
    lcd_write(data | (1<<(x%8)));
    //lcd_write (data | (1 << (rx)));
}

void lcd_set_address(unsigned char y){
    if (y < 64){
        lcd_selectside(LEFT);
        currentY = y;
    }else{
        lcd_selectside(RIGHT);
        currentY = y - 64;
    }
    
    _lcd_waitbusy();
    DI=0; RW=0;
    LCD_DATA = 0b01000000 | (y & 0b00111111);
    _lcd_enable();
}

void lcd_draw(unsigned char x, unsigned char y, unsigned char symbol){
    //TODO (julien 16/12/2015) check if set address is necessary when y == currentY
    lcd_set_page(x);
    lcd_set_address(y);
    lcd_write(symbol);
}

void lcd_draw_n_times(unsigned char x, unsigned char y, unsigned char nb_repeat, unsigned char symbol){
    // draw the symbol passed in argumet nb_repeat times at the selected page and y
    int i;
    unsigned char address = 0;

    //draw the sybmbole nb_repeat times
    for ( i = 0; i < nb_repeat; ++i){
        address = y + i;
        lcd_draw(x, address, symbol);
    }
}

void lcd_draw_bar(unsigned char index, unsigned char value, int handeling){
    //TODO (julien 17/12/2015) add reference bar handeling
    int nb_blank_pages, nb_full_pages, nb_blank_pixel_in_transition_page;
    int x,y,y_start;
    int i;
    unsigned char transition_page_bit;
    
    nb_full_pages = value/8;
    nb_blank_pages = 8 - nb_full_pages - 1;
    nb_blank_pixel_in_transition_page = 8 - (value % 8);
    transition_page_bit = FULL_BIT >> nb_blank_pixel_in_transition_page;

    y_start = MENU_WIDHT + index * BAR_WIDTH;
    y = y_start;

    for (i = 0; i < nb_blank_pages; ++i){
        lcd_draw_n_times(x, y, BAR_SPAWN, BLANK_BIT);
        x++;
    }

    y = y_start;
    lcd_draw_char(x, y++, BLANK_BIT);
    lcd_draw_n_times(x, y, BAR_WIDTH, transition_page_bit);
    y += BAR_WIDTH;
    lcd_draw_char(x, y, BLANK_BIT);

    y = y_start;
    x++;

    for (i = 0; i < nb_full_pages; ++i){
        y = y_start;
        lcd_draw_char(x, y++, BLANK_BIT);
        lcd_draw_n_times(x, y, BAR_WIDTH, FULL_BIT);
        y += BAR_WIDTH;
        lcd_draw_char(x, y++, BLANK_BIT);
        x++;
    }


}

void lcd_draw_char(unsigned char x, unsigned char y, char c){
    int i,charIndex;    
    charIndex = c;

    for(i = 0; i <= FONT_WIDTH; i++){ 
        lcd_draw(x,y,myfont[charIndex][i]);
        y++;
    }
}

void lcd_putrs(const char *string){
    char i=0;
    unsigned char x=0;
    unsigned char y=0;
    while (string[i] != 0){
        //start new line if address is at the end of the screen
        if(y + FONT_WIDTH > 127){
            y = 0;
            x++;
        }
        lcd_draw_char(x,y,string[i++]);
        y++;
    }
}

void lcd_testByte(unsigned char b){
    unsigned char mask= 0b10000000;
    int i = 0;
    while(i<8){
        if(b&mask){
            lcd_draw_char(currentX,currentY,'1');
        }
        else{
            (lcd_draw_char(currentX,currentY,'0'));
        }
        i++;
        mask>>=1;
    }
}


void lcd_startLine(unsigned int z){
    int cs1,cs2;
    cs1 = CS1;
    cs2 = CS2;
    CS1 = 0;
    CS2 = 0;
    LCD_TRIS = 0;
    _lcd_waitbusy();
    DI=0; RW=0;
    LCD_DATA = 0b11000000 | (z & 0b00111111);
    _lcd_enable();    
    CS1 = cs1;
    CS2 = cs2;
}
    
void lcd_bitmap(const char * bmp){
    unsigned char i, j;
    for(i = 0; i < 8; i++){   
       for(j = 0; j < 124 ; j++){
          lcd_draw(i,j,bmp[(i*128)+j]);
       }  
    }
}

int is_busy(){
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
