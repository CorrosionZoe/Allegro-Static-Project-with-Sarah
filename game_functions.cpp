/*Zoe and Sarah*/
#include "winter.h"
// Function for dog's choice of movement
int Dog_Choice(){
    //set bool = true
    bool normal = true;
    // while loop to randomly choose between moving or throwing a snowball.
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

// function to control dog movement
void Dog_Move(Entity Dog[], DogNPC m[], int number, int specie){
    switch(m[number].choice){
        case 1: m[number].x = 0 - Dog[specie].speed; m[number].y = 0; m[number].flag = 1;//Left 
            break;
        case 2: m[number].x = Dog[specie].speed; m[number].y = 0; m[number].flag = 0;//Right
            break;
        case 3: m[number].y = 0 - Dog[specie].speed; m[number].x = 0;//Up
            break;
        case 4: m[number].y = Dog[specie].speed; m[number].x = 0;//Down
            break;
        case 5: m[number].x = 0 - Dog[specie].speed; m[number].y = 0 - Dog[specie].speed; m[number].flag = 1;// can move up and left
            break;
        case 6: m[number].x = 0 - Dog[specie].speed; m[number].y = Dog[specie].speed; m[number].flag = 1;// can move down and left
            break;
        case 7: m[number].x = Dog[specie].speed; m[number].y = 0 - Dog[specie].speed; m[number].flag = 0;// can move up and right
            break;
        case 8: m[number].x = Dog[specie].speed; m[number].y = Dog[specie].speed; m[number].flag = 0;// can move down and right
            break;
    }
}

void Shadows_update(Location XY[], DogNPC m[], int member){
    //Cat
    XY[cat_1].sdx = XY[cat_1].bx + XY[cat_1].W / 2;
    XY[cat_1].sdy = XY[cat_1].by + XY[cat_1].H;
    //Dog
    for(int i = 0; i < member; i++){
        m[i].dog_XY.sdx = m[i].dog_XY.bx + XY[dog_1].W / 2;
        m[i].dog_XY.sdy = m[i].dog_XY.by + XY[dog_1].H;
    }
}

void Boundary_update(Location XY[], DogNPC m[], int member){
    //BB
    XY[cat_1].bx = XY[cat_1].px + 71;  XY[cat_1].by = XY[cat_1].py + 49; //Cat
    for(int i = 0; i < member; i++){
        if(m[i].flag == 1){
            m[i].dog_XY.bx = m[i].dog_XY.px + 63;
            m[i].dog_XY.by = m[i].dog_XY.py + 40;
        }else{
            m[i].dog_XY.bx = m[i].dog_XY.px + 187 - XY[dog_1].W;
            m[i].dog_XY.by = m[i].dog_XY.py + 40;
        } //Dog
    }
}

void Life_update(Location XY[], DogNPC m[], int member){
    XY[cat_1].lx = XY[cat_1].px + 40; XY[cat_1].ly = XY[cat_1].py - 22;
    for(int i = 0; i< member; i++){
        m[i].dog_XY.lx = m[i].dog_XY.bx + 40; m[i].dog_XY.ly = m[i].dog_XY.by - 22;
    }
}

void Collecting_snowball(Location XY[], Entity Player[], int choice, int timer){
    int FPS_timer = FPS * COLLECT_TIME;
    if(timer <= FPS_timer){
        al_draw_line(XY[cat_1].lx, XY[cat_1].ly - 10, (float)XY[cat_1].lx + (180 / FPS_timer) * timer,
         XY[cat_1].ly - 10, red, 10);
    }else{
        timer = 0;
        Player[choice].snowball ++;
    }
}

// function to detect if dog and cat collide.
void Boundary_Detection(Location XY[], Animation ob[], ALLEGRO_FONT *font){
    char b1 = cat_1; //cat_1
    char b2 = dog_1;  // dog_1
    char b3 = snowb_s;//snowb_s
// if Cat gets hit by snowball
       al_clear_to_color(white);
    if (isCollision(XY, b1, b2) == true){
       // printf("You lose a life");
        al_draw_text(font, pink, SCREEN_W/2,(SCREEN_H/4), ALLEGRO_ALIGN_CENTRE, "You lost a life");
        al_flip_display();
//    }else if (isCollision(XY, b2,b1) == true){ // function to detect if snowball collides with dog
  //      al_draw_text(font, pink, SCREEN_W/2, (SCREEN_H/4), ALLEGRO_ALIGN_CENTRE, "Dog lost a life");
    } //else (isCollision(XY,))
    //, (SCREEN_H/4)
}
/*
 //BB
    XY[4].bx = XY[4].px + 0;  XY[4].by = XY[4].py + 55; XY[4].W = 209; XY[4].H = 90;//Cat
    XY[5].bx = XY[5].px + 80; XY[5].by = XY[5].py +75;  XY[5].W = 111; XY[5].H = 268;//Dog
*/
// boundary for display screen
bool isCollision(Location XY[], int b1, int b2) {

    if (XY[b1].py + XY[b1].H < XY[b2].py) {
        return false;
    }
    else if (XY[b1].py > XY[b2].py + XY[b2].H) {
        return false;
    }
    else if (XY[b1].px + XY[b1].W < XY[b2].px) {
        return false;
    }
    else if (XY[b1].px > XY[b2].px + XY[b2].W) {
        return false;
    }
    return true;
}

void Dog_NPC_Function(DogNPC m[], Location XY[], Entity Dog[], Animation ob[], int i){
    if(m[i].dog_choice == true){
		m[i].choice = Dog_Choice();
		m[i].dog_choice = false;
	}

	// //Decide the moving and silent animation
	if(m[i].choice != 0){ //Moving
		if(m[i].dog_pause == true){  //(One time task until the movement is finished)
			m[i].dog_move = rand()%5 + 1;  //How many seconds(1-5)
			Dog_Move(Dog, m, i, 0);  //This is get the dog moving choice and the flag
			m[i].dog_pause = false;
		}

	    m[i].dog_timer ++;

	    if(m[i].dog_timer < FPS * m[i].dog_move){
		    Timer_Part_1_for_Dog(m, ob, XY, dog_1, i);
			Timer_Part_2_for_Dog(m, ob, dog_1, i);
		}else{
			m[i].dog_timer = 0;
			m[i].dog_pause = true; m[i].dog_choice = true;//Reset the bool
		}
	}else{ //Silent
		if(m[i].dog_pause == true){
			m[i].dog_rest = rand()%3 + 3;//(3-5)
			m[i].x = 0; m[i].y = 0;
			m[i].dog_pause = false;
		}

		m[i].dog_timer ++;

		if(m[i].dog_timer < FPS * m[i].dog_rest){
			Timer_Part_1_for_Dog(m, ob, XY, dog_1_s, i);
			Timer_Part_2_for_Dog(m, ob, dog_1_s, i);
		}else{
			m[i].dog_timer = 0;
			m[i].dog_pause = true; m[i].dog_choice = true;//Reset the bool
		}
	}
}