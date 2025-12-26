/*Zoe and Sarah*/
#include "winter.h"
// function to find the right frame for the animation for each change in movement for CAT
void Timer_Part_1(int &curr, Animation ob[], HitBox XY[], int aniID, int posID, int x, int y){
	//Update the animation frame
    curr ++;
	curr %= ob[aniID].aFPS;

	if (x < 0) { 
    	if (XY[posID].bx + x >= 0) { 
       		XY[posID].px += x; 
    	}
	} 
	else if (x > 0) {
    	if (XY[posID].bx + XY[posID].W + x <= SCREEN_W) {
        	XY[posID].px += x;
    	}
	}

	if (y < 0) {
    	if (XY[posID].by + y >= 30) {
        	XY[posID].py += y;
    	}
	} 
	else if (y > 0) {
    	if (XY[posID].by + XY[posID].H + y <= SCREEN_H) {
        	XY[posID].py += y;
    	}
	}
}
// function to draw the right frame for the animation for each change in movement for DOG
void Timer_Part_2(int &curr, Animation ob[], HitBox XY[], int F, int aniID, int posID){
	al_draw_bitmap(ob[aniID].frame[curr], XY[posID].px, XY[posID].py, F);
}

void Timer_Part_1_for_Dog(LDog m[], Animation ob[], HitBox XY[], int aniID, int i){
	m[i].curr ++;
	m[i].curr %= ob[aniID].aFPS;

	if (m[i].x < 0) { 
    	if (m[i].dog_hitbox.bx + m[i].x >= 0) { 
       		m[i].dog_hitbox.px += m[i].x; 
    	}
	} 
	else if (m[i].x > 0) {
    	if (m[i].dog_hitbox.bx + XY[dog_1].W + m[i].x <= SCREEN_W) {
        	m[i].dog_hitbox.px += m[i].x;
    	}
	}

	if (m[i].y < 0) { 
    	if (m[i].dog_hitbox.by + m[i].y >= 30) { 
       		m[i].dog_hitbox.py += m[i].y; 
    	}
	} 
	else if (m[i].y > 0) {
    	if (m[i].dog_hitbox.by + XY[dog_1].H + m[i].y <= SCREEN_H) {
        	m[i].dog_hitbox.py += m[i].y;
    	}
	}
}

void Timer_Part_2_for_Dog(LDog m[], Animation ob[], int aniID, int i){
	al_draw_bitmap(ob[aniID].frame[m[i].curr], m[i].dog_hitbox.px, m[i].dog_hitbox.py, m[i].flag);
}

//void Timer_Snowball_thrown(Main m[], Animation ob[], int aniID, int i){
//	bool showingsnowball = true;
//}