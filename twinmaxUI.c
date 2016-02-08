#include "twinmaxUI.h" 




void tui_drawGraph(unsigned char values[4],int referenceIndex){
    lcd_draw_bar(0, values[0], referenceIndex==0);
    lcd_draw_bar(1, values[1], referenceIndex==1);
    lcd_draw_bar(2, values[2], referenceIndex==2);
    lcd_draw_bar(3, values[3], referenceIndex==3);
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

void tui_writeAt(unsigned char page,unsigned char y,const char* string,int reversed,int width){
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
        temp = measures[i];
        temp = temp - reference;
        temp = temp + range / 2;
        temp = 63 * temp;
        temp = temp / range;
        //temp = 2047 / 64;
         if(temp>=63){
            temp=63;
        }
        if(temp<=0){
            temp=0;
        }
        values[i] = (unsigned char)temp;
        
        //values[i]= (unsigned char)(63*(measures[i]-reference + range/2))/range;
       
       
    }
            
    char string[4];
    
    tui_drawGraph(values,referenceIndex);
    
    tui_numberAt(0,0,reference + range/2);   
    tui_numberAt(3,0,reference);   
    tui_numberAt(7,0,reference - range/2);
    
}

void tui_numberAt(unsigned char page,unsigned char y,unsigned short val){
    char string[5]="coucou";
    //tui_writeAt(page,y,"coucou",0,0);
    snprintf(string,5, "%u", val);
    tui_writeAt(page,y,"    ",0,0);
    tui_writeAt(page,y,string,0,0);
}

void tui_battery(unsigned char val){
    glcd_smallNumberAt(0,120,val/10,1);
    glcd_smallNumberAt(0,124,val%10,1);
    
}



void tui_m_capron(){
    unsigned char i = 0;
    unsigned char values[4]={0,5,14,54};
    lcd_clear_screen();       
       
    while(1){
        values[0] = (values[0] - 1)%64 ;
        values[1] = (values[1] - 1)%64 ;
        values[2] = (values[2] - 1)%64 ;
        values[3] = (values[3] - 1)%64 ;
        tui_drawGraph(values,1);
        i=(i-1)%63;
        tui_battery(values[1]);
    }
}

void tui_test(){
    unsigned short i = 0;
    unsigned short values[4]={1,5,14,54};
    double sens = 1;
    
       
    while(1){
        values[0] = i ;
        values[1] = i ;
        values[2] = 20; ;
        values[3] = i;
  
        tui_displayMeasures(values,32,sens,2);
       
        i=(i+1)%64;
        tui_battery(values[0]);
        /****END code for M. Capron*/
        
        //tui_displayMeasures(values,sens,2);
//        delay_ms(500);
        
       // delay_ms(100);
//
//        
//        tui_displayMeasures(values,sens,0);
//        tui_battery(83);
//        values[0] = values[0] - 2 ;
//        values[1] = values[1] - 2 ;
//        values[2] = values[2] - 2 ;
//        values[3] = values[3] - 2 ;
//
//        
//        
//        values[0] = values[0] + 2 ;
//        values[1] = values[1] + 2 ;
//        values[2] = values[2] + 2 ;
//        values[3] = values[3] + 2 ;
//
//        
//        tui_displayMeasures(values,sens,0);
//        values[0] = values[0] - 20 ;
//        values[1] = values[1] - 20 ;
//        values[2] = values[2] - 20 ;
//        values[3] = values[3] - 20 ;
//
//        
//        tui_displayMeasures(values,sens,0);
//        values[0] = values[0] + 12 ;
//        values[1] = values[1] + 12 ;
//        values[2] = values[2] + 12 ;
//        values[3] = values[3] + 12 ;
//
//        
//        tui_displayMeasures(values,sens,0);
//        values[0] = values[0] - 1 ;
//        values[1] = values[1] - 1 ;
//        values[2] = values[2] - 1 ;
//        values[3] = values[3] - 1 ;
//
//        
//        tui_displayMeasures(values,sens,0);
//        values[0] = values[0] - 1 ;
//        values[1] = values[1] - 1 ;
//        values[2] = values[2] - 1 ;
//        values[3] = values[3] - 1 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] - 2 ;
//        values[1] = values[1] - 2 ;
//        values[2] = values[2] - 2 ;
//        values[3] = values[3] - 2 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] + 1 ;
//        values[1] = values[1] + 1 ;
//        values[2] = values[2] + 1 ;
//        values[3] = values[3] + 1 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] + 1 ;
//        values[1] = values[1] + 1 ;
//        values[2] = values[2] + 1 ;
//        values[3] = values[3] + 1 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] + 1 ;
//        values[1] = values[1] + 1 ;
//        values[2] = values[2] + 1 ;
//        values[3] = values[3] + 1 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] + 1 ;
//        values[1] = values[1] + 1 ;
//        values[2] = values[2] + 1 ;
//        values[3] = values[3] + 1 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] + 1 ;
//        values[1] = values[1] + 1 ;
//        values[2] = values[2] + 1 ;
//        values[3] = values[3] + 1 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] + 1 ;
//        values[1] = values[1] + 1 ;
//        values[2] = values[2] + 1 ;
//        values[3] = values[3] + 1 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] + 1 ;
//        values[1] = values[1] + 1 ;
//        values[2] = values[2] + 1 ;
//        values[3] = values[3] + 1 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] - 3 ;
//        values[1] = values[1] - 3 ;
//        values[2] = values[2] - 3 ;
//        values[3] = values[3] - 3 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] - 2 ;
//        values[1] = values[1] - 2 ;
//        values[2] = values[2] - 2 ;
//        values[3] = values[3] - 2 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] - 0 ;
//        values[1] = values[1] - 0 ;
//        values[2] = values[2] - 0 ;
//        values[3] = values[3] - 0 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] - 0 ;
//        values[1] = values[1] - 0 ;
//        values[2] = values[2] - 0 ;
//        values[3] = values[3] - 0 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] + 1 ;
//        values[1] = values[1] + 1 ;
//        values[2] = values[2] + 1 ;
//        values[3] = values[3] + 1 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] + 1 ;
//        values[1] = values[1] + 1 ;
//        values[2] = values[2] + 1 ;
//        values[3] = values[3] + 1 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] - 5 ;
//        values[1] = values[1] - 5 ;
//        values[2] = values[2] - 5 ;
//        values[3] = values[3] - 5 ;
//
//        
//        tui_displayMeasures(values,sens,2);
//        values[0] = values[0] + 1 ;
//        values[1] = values[1] + 1 ;
//        values[2] = values[2] + 1 ;
//        values[3] = values[3] + 1 ;
//
//
//        tui_displayMeasures(values,sens,2);
    }
}