           
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
    unsigned char values[4]={37,25,14,54};
    lcd_cls();
    while(1){
        values[0] = 37;
        values[1] = 25;
        values[2] = 14;
        values[3] = 54;
  
        tui_drawGraph(values);
        values[0] = values[0] + 4 ;
        values[2] = values[2] + 4 ;
        values[3] = values[3] + 4 ;

        
        tui_drawGraph(values);
        values[0] = values[0] - 2 ;
        values[2] = values[2] - 2 ;
        values[3] = values[3] - 2 ;

        
        tui_drawGraph(values);
        values[0] = values[0] + 2 ;
        values[2] = values[2] + 2 ;
        values[3] = values[3] + 2 ;

        
        tui_drawGraph(values);
        values[0] = values[0] - 20 ;
        values[2] = values[2] - 20 ;
        values[3] = values[3] - 20 ;

        
        tui_drawGraph(values);
        values[0] = values[0] + 12 ;
        values[2] = values[2] + 12 ;
        values[3] = values[3] + 12 ;

        
        tui_drawGraph(values);
        values[0] = values[0] - 1 ;
        values[2] = values[2] - 1 ;
        values[3] = values[3] - 1 ;

        
        tui_drawGraph(values);
        values[0] = values[0] - 1 ;
        values[2] = values[2] - 1 ;
        values[3] = values[3] - 1 ;

        
        tui_drawGraph(values);
        values[0] = values[0] - 2 ;
        values[2] = values[2] - 2 ;
        values[3] = values[3] - 2 ;

        
        tui_drawGraph(values);
        values[0] = values[0] + 1 ;
        values[2] = values[2] + 1 ;
        values[3] = values[3] + 1 ;

        
        tui_drawGraph(values);
        values[0] = values[0] + 1 ;
        values[2] = values[2] + 1 ;
        values[3] = values[3] + 1 ;

        
        tui_drawGraph(values);
        values[0] = values[0] + 1 ;
        values[2] = values[2] + 1 ;
        values[3] = values[3] + 1 ;

        
        tui_drawGraph(values);
        values[0] = values[0] + 1 ;
        values[2] = values[2] + 1 ;
        values[3] = values[3] + 1 ;

        
        tui_drawGraph(values);
        values[0] = values[0] + 1 ;
        values[2] = values[2] + 1 ;
        values[3] = values[3] + 1 ;

        
        tui_drawGraph(values);
        values[0] = values[0] + 1 ;
        values[2] = values[2] + 1 ;
        values[3] = values[3] + 1 ;

        
        tui_drawGraph(values);
        values[0] = values[0] + 1 ;
        values[2] = values[2] + 1 ;
        values[3] = values[3] + 1 ;

        
        tui_drawGraph(values);
        values[0] = values[0] - 3 ;
        values[2] = values[2] - 3 ;
        values[3] = values[3] - 3 ;

        
        tui_drawGraph(values);
        values[0] = values[0] - 2 ;
        values[2] = values[2] - 2 ;
        values[3] = values[3] - 2 ;

        
        tui_drawGraph(values);
        values[0] = values[0] - 0 ;
        values[2] = values[2] - 0 ;
        values[3] = values[3] - 0 ;

        
        tui_drawGraph(values);
        values[0] = values[0] - 0 ;
        values[2] = values[2] - 0 ;
        values[3] = values[3] - 0 ;

        
        tui_drawGraph(values);
        values[0] = values[0] + 1 ;
        values[2] = values[2] + 1 ;
        values[3] = values[3] + 1 ;

        
        tui_drawGraph(values);
        values[0] = values[0] + 1 ;
        values[2] = values[2] + 1 ;
        values[3] = values[3] + 1 ;

        
        tui_drawGraph(values);
        values[0] = values[0] - 5 ;
        values[2] = values[2] - 5 ;
        values[3] = values[3] - 5 ;

        
        tui_drawGraph(values);
        values[0] = values[0] + 1 ;
        values[2] = values[2] + 1 ;
        values[3] = values[3] + 1 ;


        tui_drawGraph(values);
    }
}