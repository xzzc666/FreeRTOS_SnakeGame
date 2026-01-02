#include "MyFunctions.h"


void SetBigPixiv(int x,int y,int state)
{
	x = 2*x;
	y = 2*y;
	ssd1306_DrawPixel(x,y+16,state);
	ssd1306_DrawPixel(x,y+17,state);
	ssd1306_DrawPixel(x+1,y+16,state);
	ssd1306_DrawPixel(x+1,y+17,state);
}


