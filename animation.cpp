/*Zoe and Sarah*/
#include "winter.h"
//Function to find the right frame for the animation for each change in movement for cat//
void Timer_Part_1(int &curr, Animation ob[], Location &C, Entity Player[], int aniID, int x, int y){
	//Update the animation frame//
    curr ++;
	curr %= ob[aniID].aFPS;
	
	if (x < 0) { //If the x position of character is next to the left border of the screen, character will stop//
    	if (C.bx + x >= 0) { 
       		C.px += x; 
    	}
	} 
	else if (x > 0) { //If the x position of character is next to the right border of the screen, character will stop//
    	if (C.bx + Player[Ocat].W + x <= SCREEN_W) {
        	C.px += x;
    	}
	}

	if (y < 0) { //If the y position of character is next to the bottom border of the screen, character will stop//
    	if (C.by + y >= 30) {
        	C.py += y;
    	}
	} 
	else if (y > 0) { //If the y position of character is next to the top border of the screen, character will stop//
    	if (C.by + Player[Ocat].H + y <= SCREEN_H) {
        	C.py += y;
    	}
	}
}
//Function to draw the right frame for the animation for each change in movement for dog//
void Timer_Part_2(int &curr, Animation ob[], Location C, int F, int aniID){
	al_draw_bitmap(ob[aniID].frame[curr], C.px, C.py, F);
}

//Function to control the timing of the animation for the dog//
void Timer_Part_1_for_Dog(DogNPC D[], Animation ob[], Entity Dog[], int aniID, int i){
	D[i].curr ++;
	D[i].curr %= ob[aniID].aFPS;

	if (D[i].x < 0) { //If statement to control the x position of the dog if x is less than 0//
    	if (D[i].dog_XY.bx + D[i].x >= 0) { 
       		D[i].dog_XY.px += D[i].x; 
    	}
	} 
	else if (D[i].x > 0) { // if statement to control the x position of the dog if x is greater than 0
    	if (D[i].dog_XY.bx + Dog[Gdog].W + D[i].x <= SCREEN_W) {
        	D[i].dog_XY.px += D[i].x;
    	}
	}
	if (D[i].y < 0) { // if statement to control the y position of the dog if y is less than 0
    	if (D[i].dog_XY.by + D[i].y >= 30) { 
       		D[i].dog_XY.py += D[i].y; 
    	}
	} 
	else if (D[i].y > 0) { // if statement to control the y position of the dog if y is greater than 0
    	if (D[i].dog_XY.by + Dog[Gdog].H + D[i].y <= SCREEN_H) {
        	D[i].dog_XY.py += D[i].y;
    	}
	}
}
// function to control the animation fo the dog
void Timer_Part_2_for_Dog(DogNPC D[], Animation ob[], int aniID, int i){
	al_draw_bitmap(ob[aniID].frame[D[i].curr], D[i].dog_XY.px, D[i].dog_XY.py, D[i].flag);
}

// function to control when the snowball appears animation
void Snowball_thrown(Entity Player[], Entity SB[], Animation ob[], Location &S,
	int x, int x1, int y, int y1, int choice, bool &throwing, bool &Aiming, bool &init){
	//x is target, x1 is starting point
	static float curX, curY; //These are the xy that are used in drawing the snowball
	//Static can stay the same amount of variables each time the 
	static float moveX, moveY; // These are the amount of moving through each frame
	float MAX_distance = (float)SB[Ocat].speed * Player[choice].power;//This is the MAX distance the player can throw


	if (!init) { //One time job
    curX = x1; //Get the same location of the starting point
    curY = y1;
    
    float w = (float)x - x1;//Get the width and the height for the tilted line
    float h = (float)y - y1;
    float distance = sqrt(w * w + h * h);//Calculate distance

	if(distance < MAX_distance){//Compare if the target is too far
		moveX = (w / distance) * SB[Ocat].speed;
    	moveY = (h / distance) * SB[Ocat].speed;
	}else{
		moveX = (w / MAX_distance) * SB[Ocat].speed;
    	moveY = (h / MAX_distance) * SB[Ocat].speed;
	}
    
    init = true;//close the IF until the whole funtion ends
    Player[choice].speed /= 2;//Slow down Player's speed
	}
	
	curX += moveX; //update location
	curY += moveY;
	S.px = curX - 32; S.py = curY - 32;
	
	float dist_left = sqrt(pow(x - curX, 2) + pow(y - curY, 2));//Calculate how much distance left

	if (dist_left < SB[Ocat].speed) {
		//Detect if the snowball location is out of the target, if is, end the function
    	False_snowball(Player, S, choice, throwing, Aiming, init);
	} else {
    	// Drawing the snowball
    	al_draw_bitmap(ob[snowb_s].image, S.px, S.py, 0);
	}
}