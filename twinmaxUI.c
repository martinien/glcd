
#define FONT_WIDTH 6

void tui_drawGraph(int * values )
{
    lcd_draw_bar(0, values[0], 0);
    lcd_draw_bar(1, values[1], 0);
    lcd_draw_bar(2, values[2], 0);
    lcd_draw_bar(3, values[3], 1);    
    
}




void tui_menuItem(int index,const char *string){
    char i=0;
    unsigned char x=index;
    unsigned char y=0;
    while (string[i] != 0 && i<10){
        //start new line if address is at the end of the screen
        if(y +6 /*FONT_WIDTH*/ > 64){
            return;
        }
        lcd_draw_char(x,y,string[i++]);
        y++;
    }
}
