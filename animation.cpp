#include "winter.h"

void Timer_Part_1(int cur[], int x, int y, Animation ob[], Frame XY[], int number){
    cur[number] ++;
	cur[number] %= ob[number].aFPS;
	XY[number].px += x; 
    XY[number].py += y;
}

void Timer_Part_2(int cur[], Animation ob[], Frame XY[], int F, int aniID, int posID){
	al_draw_bitmap(ob[aniID].frame[cur[aniID]], XY[posID].px, XY[posID].py, F);
}