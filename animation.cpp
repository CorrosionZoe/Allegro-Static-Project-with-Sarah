/*Zoe and Sarah*/
#include "winter.h"
// function to find the right frame for the animation for each change in movement
void Timer_Part_1(int cur[], int x, int y, Animation ob[], Frame XY[], int aniID, int posID){
	//Update the animation frame
    cur[aniID] ++;
	cur[aniID] %= ob[aniID].aFPS;
	//Update the location
	XY[posID].px += x; 
    XY[posID].py += y;
	//Limit the movement of the players.
	if(XY[posID].px > SCREEN_W || XY[posID].px < 0 || XY[posID].px + XY[posID].W < 0 || XY[posID].px + XY[posID].W > SCREEN_W){
		XY[posID].px -= x;
	}
	if(XY[posID].py > SCREEN_H || XY[posID].py < 0 || XY[posID].py + XY[posID].H < 0 || XY[posID].py + XY[posID].H > SCREEN_H){
		XY[posID].py -= y;
	}
}
// function to draw the right frame for the animation for each change in movement
void Timer_Part_2(int cur[], Animation ob[], Frame XY[], int F, int aniID, int posID){
	al_draw_bitmap(ob[aniID].frame[cur[aniID]], XY[posID].px, XY[posID].py, F);
}