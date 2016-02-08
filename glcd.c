#include "glcd.h"
#include "myFont.h"

int currentPage;
int currentY;


int BAR_WIDTH=20;
int BAR_SPAN=24;
int MENU_WIDTH=28;
unsigned char BLANK_BIT=0b00000000;
unsigned char FULL_BIT=0b11111111;

/*Pulse to enable command/data on the display*/
void _lcd_enable(void){  
    ENABLE=0;
    __delay_us(.2);
    ENABLE=1;   
    __delay_us(.5);
    ENABLE=0;
    __delay_us(.5);
 }


/*TODO time optimisation*/
unsigned char _lcd_status(void){
    unsigned char status,_lcd_tris;
    _lcd_tris = LCD_TRIS;           // stores the state of tris, CS1 and CS2
    int cs1 = CS1;
    int cs2 = CS2; 
    CS1 = CSHIGH;
    CS2 = CSHIGH;
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
    status = LCD_DATA & 0b11111111;    //Input data
    ENABLE = 0;                 //Low Enable
    __delay_us(1);            //tdhr    
    LCD_TRIS = _lcd_tris;           // restores the initial state of tris, CS1 and CS2
    CS1 = cs1;
    CS2= cs2;
    
    return (status);        
   
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
    RESET = 1;
    int data;
    ENABLE=0; 
    __delay_us(.1);
    CS1=CSHIGH;
    CS2=CSHIGH;
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
    CS1=CSHIGH;
    CS2=CSHIGH;
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

/*Clear scran*/
void lcd_clear_screen(void){
    //lcd clear screen
    unsigned char x,y;

    lcd_set_address(0);
    lcd_set_address(64);
    CS1 = CSHIGH;
    CS2 = CSHIGH;
    for (x=0; x<8; x++){
        // set the page (x)
        lcd_set_page(x);
        // set the y address to 0
        
        // setup for data
        LCD_DATA=0; RW=0; DI=1;
        // clear the row
        for (y=0; y<64; y++){
            lcd_write(0); 
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
    CS1= CSHIGH;
    CS2=CSHIGH;
    LCD_DATA = 0b10111000 | page;
    
    _lcd_enable();

    CS1=  cs1;
    CS2 = cs2;
    currentPage=page;
}

/*Waits for busy flag to be low*/
void _lcd_waitbusy(void){
    while (_lcd_status() & 0b10000000){
        __delay_us(.1); // .5 us
    }
}

/*write a byte to the display ram - data will be written at the active X and Y - the display increments its y register  */
void lcd_write(unsigned char data){
    _lcd_waitbusy();
    DI=1; RW = 0;
    LCD_TRIS = 0;
    LCD_DATA = data;
    _lcd_enable();
    currentY++;
    
}

/*Handles the case when writing cause y register to reach midle of screen*/
void lcd_continuous_write(unsigned char data){
    if(currentY == 64)
        lcd_set_address(64);
    lcd_write(data);
}

/*Select left or right side*/
void lcd_selectside(unsigned char sides){
    if (sides & LEFT)
        CS1 = CSHIGH;
    else
        CS1 = CSLOW;
    if (sides & RIGHT)
        CS2 = CSHIGH;
    else
        CS2 = CSLOW;
}

/*Reads a byte from the display ram - data will be read from the active X and Y - the display increments its y register  */
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
    _data = LCD_DATA & 0b11111111;
    __delay_us(.3);
    ENABLE = 0;       
    
    // restore the tris value
    LCD_TRIS = _lcd_tris;
    currentY++;
    return _data;
}

/*Plot a unique pixel on the screen */
void lcd_plotpixel(unsigned char x, unsigned char y){
    unsigned char data;

    _lcd_waitbusy();
    lcd_set_page(x>>3);
    lcd_set_address(y);
    data = lcd_read();
    lcd_set_address(y);
    lcd_write(data); //| (1<<(x%8))
    //lcd_write (data | (1 << (rx)));
}

/*Selects a side of the screen and write the correct address*/
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

/*Write a byte iat the spe*/
void lcd_draw(unsigned char page, unsigned char y, unsigned char symbol){
    //TODO (julien 16/12/2015) check if set address is necessary when y == currentY
    lcd_set_page(page);
    lcd_set_address(y);
    lcd_write(symbol);
}

void lcd_reversed_draw(unsigned char page, unsigned char y, unsigned char symbol){
    //TODO (julien 16/12/2015) check if set address is necessary when y == currentY
    lcd_set_page(page);
    lcd_set_address(y);
    lcd_write(~symbol);
}

//optimized with navie y incrementation
void lcd_draw_n_times(unsigned char page, unsigned char y, unsigned char nb_repeat, unsigned char symbol){
    // draw the symbol passed in argumet nb_repeat times at the selected page and y
    int i;
    // unsigned char limit =  y +nb_repeat()
    if(nb_repeat>0){
        lcd_draw(page, y, symbol);        
    }           
    //draw the sybmbole nb_repeat times
    for ( i = 1; i < nb_repeat; ++i){
        lcd_continuous_write(symbol);
    }
}

void lcd_prepare_bars(){
    lcd_draw_bar(0, 30, 0);
    lcd_draw_bar(1, 30, 0);
    lcd_draw_bar(2, 30, 0);
    lcd_draw_bar(3, 30, 0);
}

void lcd_draw_bar(unsigned char index, unsigned char value, int isReference){
    int nb_blank_pages, nb_full_pages, nb_blank_pixel_in_transition_page;
    int x,y,y_start;
    int i;
    int arrow_drawn = 0;
    unsigned char transition_page_bit;
    
    
    nb_full_pages = value/8;
    nb_blank_pages = 8 - nb_full_pages - 1;
    nb_blank_pixel_in_transition_page = 8 - (value % 8);
    transition_page_bit = FULL_BIT << nb_blank_pixel_in_transition_page;

    y_start = MENU_WIDTH + index * BAR_SPAN;
    y = y_start;
    x = 0;

    for (i = 0; i < nb_blank_pages; ++i){
        lcd_draw_n_times(x, y, BAR_SPAN, BLANK_BIT);
        if(i==nb_blank_pages - 1 && isReference==1){ //Reference bar
         lcd_draw_char(x,12+y,0);   
         arrow_drawn = 1;
        }
        x++;
    }

    y = y_start;
    // lcd_draw_n_times(x, y, BAR_SPAN - BAR_WIDTH, BLANK_BIT);
    y += BAR_SPAN - BAR_WIDTH;
    lcd_draw_n_times(x, y, BAR_WIDTH, transition_page_bit);

    y = y_start;
    x++;

    for (i = 0; i < nb_full_pages; ++i){
        y = y_start;
        // lcd_draw_n_times(x, y, BAR_SPAN - BAR_WIDTH, BLANK_BIT);
        y += BAR_SPAN - BAR_WIDTH;
        lcd_draw_n_times(x, y, BAR_WIDTH, FULL_BIT);

        y = y_start;
        x++;
    }
}

//optimized 
void lcd_draw_char(unsigned char page, unsigned char y, char c){
    int i,charIndex;    
    charIndex = c;
    lcd_draw(page,y,myfont[charIndex][0]);
    y++;
    for(i = 1; i <= FONT_WIDTH; i++){ 
        lcd_draw(page,y,myfont[charIndex][i]);
        y++;
    }
}

void lcd_draw_reversed_char(unsigned char page, unsigned char y, char c){
    int i,charIndex;    
    charIndex = c;
    lcd_draw(page,y,~myfont[charIndex][0]);
    for(i = 1; i <= FONT_WIDTH; i++){ 
        lcd_draw(page,y,~myfont[charIndex][i]);
        y++;
    }
}

unsigned char* lcd_testByte(unsigned char page, unsigned short b){
    unsigned short mask = 0b1000000000000000;
    int i = 0;
    unsigned char result[17];
    
    for(i = 0; i < 16; i++){
        result[i] = "A";
    }
    result[16] = 0;
    return result;
    
}

void glcd_smallNumberAt(unsigned char page,unsigned char y,unsigned char value,int reversed){
    int i=0;  
    lcd_draw(page,y,SmallNumbers[value][i]);
    for(i = 1; i < NUMBER_WIDTH; i++){ 
        lcd_write(SmallNumbers[value][i] );    
        
    }

}

void lcd_startLine(unsigned int z){
    int cs1,cs2;
    cs1 = CS1;
    cs2 = CS2;
    CS1 = CSHIGH;
    CS2 = CSHIGH;
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
        lcd_draw(i,0,bmp[(i*128)]);
       for(j = 0; j < 64 ; j++){
           lcd_write(bmp[(i*128)+j]);          
       }  
        lcd_draw(i,64,bmp[(i*128)]);
       for(j = 65; j < 124 ; j++){
           lcd_write(bmp[(i*128)+j]);          
       }  
    }
}

void lcd_bitmap_plus(const char * bmp,unsigned char y,unsigned char width,unsigned char reversed){
    unsigned char i, j;
    for(i = 0; i < 8; i++){   
        lcd_draw(i,0,bmp[(i*width)]);
       for(j = y; j < width ; j++){
           lcd_write(bmp[(i*width)+j]);          
       }  
    }
}


