/*Zoe and Sarah*/
#include "winter.h"
//Function for dog's choice of movement//
int Dog_Choice(){
    //Set bool = true//
    bool normal = true;
    //While loop to randomly choose between moving or throwing a snowball.//
    while(normal){
        int choice = rand()% 3 + 1;
        if(choice != 1){
            int choice2 = rand()% 8 + 1;
            return choice2;
        }else{
            return 0;
        }
    }
    return 0;
}

//Function to control dog movement//
void Dog_Move(Entity Dog[], DogNPC D[], int number, int specie){
    switch(D[number].choice){
        case 1: D[number].x = 0 - Dog[specie].speed; D[number].y = 0; D[number].flag = 1; //Move left//
            break;
        case 2: D[number].x = Dog[specie].speed; D[number].y = 0; D[number].flag = 0; //Move right//
            break;
        case 3: D[number].y = 0 - Dog[specie].speed; D[number].x = 0; //Move up//
            break;
        case 4: D[number].y = Dog[specie].speed; D[number].x = 0; //Move down//
            break;
        case 5: D[number].x = 0 - Dog[specie].speed; D[number].y = 0 - Dog[specie].speed; D[number].flag = 1; //Move up and left//
            break;
        case 6: D[number].x = 0 - Dog[specie].speed; D[number].y = Dog[specie].speed; D[number].flag = 1; //Move down and left//
            break;
        case 7: D[number].x = Dog[specie].speed; D[number].y = 0 - Dog[specie].speed; D[number].flag = 0; //Move up and right//
            break;
        case 8: D[number].x = Dog[specie].speed; D[number].y = Dog[specie].speed; D[number].flag = 0; //Move down and right//
            break;
    }
}
//Function to make the shadow follow each character when they move//
void Shadows_update(Location &C, DogNPC D[], Entity Player[], Entity Dog[], int member){
    //Control shadow of cat//
    C.sdx = C.bx + Player[Ocat].W / 2;
    C.sdy = C.by + Player[Ocat].H;
    //Control shadow of dog//
    for(int i = 0; i < member; i++){
        D[i].dog_XY.sdx = D[i].dog_XY.bx + Dog[Gdog].W / 2;
        D[i].dog_XY.sdy = D[i].dog_XY.by + Dog[Gdog].H;
    }
}
//Function to make boundary box for the characters//
void Boundary_update(Location &C, Location &S, DogNPC D[], Entity Dog[], int member){
    //Boundary box//
    C.bx = C.px + 71;  C.by = C.py + 49; //Cat
    for(int i = 0; i < member; i++){ 
        if(D[i].flag == 1){
            D[i].dog_XY.bx = D[i].dog_XY.px + 63;
            D[i].dog_XY.by = D[i].dog_XY.py + 40;
        }else{
            D[i].dog_XY.bx = D[i].dog_XY.px + 187 - Dog[Gdog].W;
            D[i].dog_XY.by = D[i].dog_XY.py + 40;
        } 
    }
    S.bx = S.px + 15; S.by = S.py + 15;
}
//Function for life bars// 
void Life_update(Location &C, Location S, DogNPC D[], Entity SB[], Entity Player[], Entity Dog[], int member, int choice, bool &D_reduce){
    C.lx = C.px + 40; C.ly = C.py - 22;
    for(int i = 0; i< member; i++){
        D[i].dog_XY.lx = D[i].dog_XY.bx + 40; D[i].dog_XY.ly = D[i].dog_XY.by - 22;
    }
    //For loop to control life function and minus dog life when hit by snowball// 
    for(int i = 0; i< member; i++){
        if(S.bx + SB[Ocat].W > D[i].dog_XY.bx && S.bx < D[i].dog_XY.bx + Dog[Gdog].W
             && S.by + SB[Ocat].H > D[i].dog_XY.by && S.by < D[i].dog_XY.by + Dog[Gdog].H){
            D_reduce = true;
        }
        if(D_reduce == true){
            D[i].life --;
            printf("Dog lost 1 life\n");
            printf("Remain: %d\n", D[i].life);

        }

    }  
     
}

//Function to collect snowball// 
void Collecting_snowball(Location C, Entity Player[], int choice, int &timer){
    int FPS_timer = FPS * COLLECT_TIME; 
    if(timer <= FPS_timer){
        al_draw_line(C.lx, C.ly - 10, (float)C.lx + (180 / FPS_timer) * timer,
         C.ly - 10, red, 10);
    }else{
        timer = 0;
        Player[choice].snowball ++;
    }
}

void False_snowball(Entity Player[], Location &S, int C, bool &T, bool &A, bool &I){
    Player[C].snowball--; //Reduce 1 snowball
   	Player[C].speed *= 2; //Player's Speed turns back to normal
    T = false;
    A = false;
    I = false;
    S.px = -1000; S.py = -1000;
}

// function to detect if dog and cat collide.
/*
void Boundary_Detection(Location C, DogNPC D[], Animation ob[], ALLEGRO_FONT *font){
    char b1 = cat_1; //cat_1
    char b2 = dog_1;  // dog_1
    char b3 = snowb_s;//snowb_s
// if Cat gets hit by snowball
       al_clear_to_color(white);
    if (isCollision(C, D, b1, b2) == true){
       // printf("You lose a life");
        al_draw_text(font, pink, SCREEN_W/2,(SCREEN_H/4), ALLEGRO_ALIGN_CENTRE, "You lost a life");
        al_flip_display();
//    }else if (isCollision(C, b2,b1) == true){ // function to detect if snowball collides with dog
  //      al_draw_text(font, pink, SCREEN_W/2, (SCREEN_H/4), ALLEGRO_ALIGN_CENTRE, "Dog lost a life");
    } //else (isCollision(C,))
    //, (SCREEN_H/4)
}
/*
 //BB
    C[4].bx = C[4].px + 0;  C[4].by = C[4].py + 55; C[4].W = 209; C[4].H = 90;//Cat
    C[5].bx = C[5].px + 80; C[5].by = C[5].py +75;  C[5].W = 111; C[5].H = 268;//Dog
*/
// boundary for display screen
/*
bool isCollision(Location C, DogNPC D[], int b1, int b2) {
    
    if (C.py + C.H < D[0].dog_XY.py) {
        return false;
    }
    else if (C[b1].py > C[b2].py + C[b2].H) {
        return false;
    }
    else if (C[b1].px + C[b1].W < C[b2].px) {
        return false;
    }
    else if (C[b1].px > C[b2].px + C[b2].W) {
        return false;
    }
    return true;
    */

/*
void onMouse(int event, int x, int y, int flags, void *userdata) {
    if (event == cv::Event_LBUTTONDOWN) {
        cv::imshow(EVENT_L)
    }
}
    */
// function for the dog NPC
void Dog_NPC_Function(DogNPC D[], Entity Dog[], Animation ob[], int i){
    if(D[i].dog_choice == true){
		D[i].choice = Dog_Choice();
		D[i].dog_choice = false;
	}

	// //Decide the moving and silent animation
	if(D[i].choice != 0){ //Moving
		if(D[i].dog_pause == true){  //(One time task until the movement is finished)
			D[i].dog_move = rand()%5 + 1;  //How many seconds(1-5)
			Dog_Move(Dog, D, i, 0);  //This is get the dog moving choice and the flag
			D[i].dog_pause = false;
		}
        //Dog timer//
	    D[i].dog_timer ++;

	    if(D[i].dog_timer < FPS * D[i].dog_move){ //If statement to make the animation frame match the dog's movement.
		    Timer_Part_1_for_Dog(D, ob, Dog, dog_1, i);
			Timer_Part_2_for_Dog(D, ob, dog_1, i);
		}else{ //Dog is still
			D[i].dog_timer = 0;
			D[i].dog_pause = true; D[i].dog_choice = true;//Reset the bool
		}
	}else{ //If statement to control animation of dog breathing when dog is not moving//
		if(D[i].dog_pause == true){
			D[i].dog_rest = rand()%3 + 3;//(3-5)
			D[i].x = 0; D[i].y = 0;
			D[i].dog_pause = false;
		}
        //Calculate how long dog moves in seconds//
		D[i].dog_timer ++;

		if(D[i].dog_timer < FPS * D[i].dog_rest){//If statement to make animation frame match the dog's movement for being still (breathing).
			Timer_Part_1_for_Dog(D, ob, Dog, dog_1_s, i);
			Timer_Part_2_for_Dog(D, ob, dog_1_s, i);
		}else{ //Dog would be moving so it stops running the breathing function.
			D[i].dog_timer = 0;
			D[i].dog_pause = true; D[i].dog_choice = true;//Reset the bool
		}
	}
}