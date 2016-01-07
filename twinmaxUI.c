            
#define FONT_WIDTH 6
//#include "twinmaxUI.h"

void tui_drawGraph(unsigned char values[4] ){
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

//void tui_question(int index,const char *question,const char*A1,const char* A2,int highlighted){
//
//    char i=0;
//    unsigned char x=index;
//    unsigned char y=0;
//    while (question[i] != 0 && i<10){
//        //start new line if address is at the end of the screen
//        if(y +FONT_WIDTH > 64){
//            return;
//        }
//        if(reversed==1){
//           lcd_draw_reversed_char(x,y,string[i++]);
//        }
//        else{
//           lcd_draw_char(x,y,string[i++]);
//        }
//        y+= FONT_WIDTH;
//    }
//
//
//
//}

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