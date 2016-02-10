#include "twinmaxUI.h" 
#include "params.h"
#include "engine.h"



void tui_draw_graph(unsigned char values[4], int referenceIndex){
    lcd_draw_bar(0, values[0], referenceIndex==0);
    lcd_draw_bar(1, values[1], referenceIndex==1);
#ifndef TWO_BARS
    lcd_draw_bar(2, values[2], referenceIndex==2);
    lcd_draw_bar(3, values[3], referenceIndex==3);
#endif
}

void tui_menuItem(int index, const char *string, unsigned char highlighted){
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

void tui_write_at(unsigned char page, unsigned char y, const char* string, int reversed, int width){
    int i = 0;
    unsigned char referenceY = y;
    if(width == 0){
        width = 127;
    }
    while (string[i] != 0){
        //start new line if address is at the end of the screen
        if(y + FONT_WIDTH > width){
            y = referenceY;
            page++;
        }
        if(reversed == 1){
            lcd_draw_reversed_char(page, y, string[i++]);
             y += FONT_WIDTH;
        }
        else{
            lcd_draw_char(page, y, string[i++]);
            y += FONT_WIDTH;
        } 
    }
}

void tui_displayMeasures(unsigned short measures[4],unsigned short reference, unsigned short range, int referenceIndex){    
    unsigned char values[4];
    int i = 0;
    long temp = 0;

    for(i = 0; i < 4; i++){
        // Calculate each values between 0 and 64 to display
        temp = measures[i];
        temp = temp - reference;
        temp = temp + range / 2;
        temp = 63 * temp;
        temp = temp / range;

        // Set to 63 or 0 if the value is out of range
        if(temp>=63){
            temp=63;      
        }
        if(temp<=0){
           temp=0;
        }

        // store the value for display
        values[i] = (unsigned char)temp;
    }

    // draw the graph with the values
    tui_draw_graph(values,referenceIndex);

    // draw the scale on the left
    tui_draw_number(0,0,reference + range/2);   
    tui_draw_number(3,0,reference);   
    tui_draw_number(7,0,reference - range/2);
}

void tui_draw_number(unsigned char page,unsigned char y,unsigned short val){
    char string[5];

    // Convert an unsigned short to a 5 char string
    snprintf(string, 5, "%u", val);

    // Clear the space
    tui_write_at(page, y, "    ", 0, 0);

    // Draw the 5 char string
    tui_write_at(page, y, string, 0, 0);
}

void tui_battery(unsigned char val){
    glcd_smallNumberAt(0,120,val/10,1);
    glcd_smallNumberAt(0,124,val%10,1); 
}