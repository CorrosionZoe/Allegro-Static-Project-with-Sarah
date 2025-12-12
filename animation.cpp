#include "winter.h"
// function to find the right frame for the animation for each change in movement
void Timer_Part_1(int cur[], int x, int y, Animation ob[], Frame XY[], int aniID, int posID){
    cur[aniID] ++;
	cur[aniID] %= ob[aniID].aFPS;
	XY[posID].px += x; 
    XY[posID].py += y;
}
// function to draw the right frame for the animation for each change in movement
void Timer_Part_2(int cur[], Animation ob[], Frame XY[], int F, int aniID, int posID){
	al_draw_bitmap(ob[aniID].frame[cur[aniID]], XY[posID].px, XY[posID].py, F);
}