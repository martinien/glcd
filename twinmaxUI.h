#include "headers.h"
#include "glcd.h"
#define FONT_WIDTH 6
#define NUMBER_WIDTH 4

void tui_drawGraph(unsigned char values[4], int referenceIndex);

void tui_writeAt(unsigned char x,unsigned char y,const char* string,int reversed,int width);

void tui_menuItem(int index,const char *string,unsigned char highlighted);

void tui_displayMesures(double measures[4],double sensitivity,int referenceIndex);
