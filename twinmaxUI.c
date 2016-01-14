           
#include "headers.h"
#define FONT_WIDTH 6
#define NUMBER_WIDTH 4
//#include "twinmaxUI.h"

void tui_drawGraph(unsigned char values[4]){
    lcd_draw_bar(0, values[0], 0);
     lcd_draw_bar(1, values[1], 0);
     lcd_draw_bar(2, values[2], 0);
    lcd_draw_bar(3, values[3], 0);      
    
   
    
    
      
}

void tui_menuItem(int index,const char *string,unsigned char highlighted){
    char i = 0;
    unsigned char x = index;
    unsigned char y = 0;
    while (string[i] != 0 && i < 10){
        //start new line if address is at the end of the screen
        if(y +FONT_WIDTH > 64){
            return;
        }
        if(highlighted == 1){
           lcd_draw_reversed_char(x, y, string[i++]);
        }
        else{
           lcd_draw_char(x, y, string[i++]);
        }
        y+= FONT_WIDTH;
    }
}


void tui_writeAt(unsigned char x,unsigned char y,const char* string,int reversed,int width){
    char i = 0;
    unsigned char referenceY = y;
    if(width == 0){
        width = 127;
    }
    while (string[i] != 0){
        //start new line if address is at the end of the screen
        if(y + FONT_WIDTH > width){
            y = referenceY;
            x++;
        }
        if(reversed == 1){
            lcd_draw_reversed_char(x, y, string[i++]);
             y += FONT_WIDTH;
        }
        else{
            lcd_draw_char(x, y, string[i++]);
            y += FONT_WIDTH;
        }
        y++;
    }}




void tui_displayMesures(double measures[4], double sensitivity, int referenceIndex){

    double referenceMeasure = measures[referenceIndex];
    unsigned char values[4];
    int i;
    for(i = 0; i < 4; i++){
        values[i]= (unsigned char) sensitivity * (measures[i] * referenceMeasure) + 32;
    }
}


void tui_numberAt(unsigned char x,unsigned char y,unsigned char val){
    
    char string[4];
    sprintf(string, "%d", val);
    tui_writeAt( x, y,string,0,0);   
    
    
}

void tui_test(){
    
    int i = 0;
    int j=0;
    unsigned char values[4]={37,25,14,54};
    lcd_cls();    
    lcd_set_page(2);
    lcd_set_address(90);
    lcd_write(0b01010101);
    lcd_set_address(90);
    lcd_testByte(lcd_read());
    delay_ms(2000);
    lcd_set_page(3);
    lcd_set_address(90);
    lcd_write(0b10101010);
    lcd_set_address(90);
    lcd_testByte(lcd_read());
    delay_ms(2000);
    lcd_cls();
    while(1){
        tui_drawGraph(values);
        for(i=0;i<4;i++){
            values[i]=(values[i] + 1)%64;
        }
//        j=j+1%90;
//        tui_numberAt(0,0,400+j);
//        tui_numberAt(3,0,600+j);
//        tui_numberAt(7,0,800+j);
//      //  delay_ms(25);
        
    
    }


}