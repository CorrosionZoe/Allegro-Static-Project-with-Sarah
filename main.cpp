#include "winter.h"


int main(int argc, char *argv[]){

	/**********⭐**********⭐Set Up⭐************⭐**********/

	//Install and initialize struct//
    al_init();
    al_install_keyboard(); al_init_image_addon(); al_init_ttf_addon(); al_init_font_addon(); // initialize addons
	Animation ob[OB_CONTAINER]; Frame XY[OB_CONTAINER];
	INIT_location(XY);
	Entity Player[3]; Entity Dog[4];
      // create two images
	STORE_struct(ob, Player, Dog);

	//First creating display//
    ALLEGRO_DISPLAY* disp = al_create_display(SCREEN_W, SCREEN_H);
	ALLEGRO_BITMAP *icon_32 = al_load_bitmap("Snowball_32.png");
	al_set_display_icon(disp, icon_32);

	//Checking addon ERROR//
	int error = 0;
	error = addonCheck(disp);

	//Initializing Allegros//
    ALLEGRO_FONT *font = al_load_ttf_font("store/ShortBaby.ttf", 50, 0);
    ALLEGRO_EVENT_QUEUE * EQ = al_create_event_queue();
	ALLEGRO_TIMER * timer = al_create_timer(1.0 / FPS);

	//Set Title and events//
    al_set_window_title(disp, "Winter Squabble");
    al_register_event_source(EQ, al_get_display_event_source(disp));
 	al_register_event_source(EQ, al_get_keyboard_event_source());
	al_register_event_source(EQ, al_get_timer_event_source(timer));
	int cat = 4; int cube = 0; int dog = 5; int cube2 = 6;//Animations
	ARRAY_frame(ob, cat); ARRAY_frame(ob, cube); ARRAY_frame(ob, dog); ARRAY_frame(ob, cube2);/*ob*/
	//store frame set
	animation(ob, cat); animation(ob, cube); animation(ob, dog); animation(ob, cube2);/*ob*/
	
	//Checking total ERROR//
    error = ERROR(disp, EQ, timer, font, ob, icon_32);
	if(error != 0){
		printf("%d errors", error);
		return error;
	}

	/**********⭐**********⭐Main⭐************⭐**********/
	int Player_Choice = 0;
    // set current frame and position.//
	int curr[OB_CONTAINER];
	//Player position
	int x = 0; int y = 0;
	//Dogs position
	int dx = 0; int dy = 0;
	int choice = 0; int members = 1;
	//curr set
	memset(curr, -1, sizeof(curr));
	
	
	/***—————————————————Animation———————————————————***/
	bool left = false; bool right = false; bool up = false; bool down = false; bool exit = false;
	bool dog_pause = true; bool dog_choice = true;
	bool flags = 0; 
	int dflags = 0;
	int dog_rest = 0; int dog_move = 0; int dog_timer = 0;
	al_start_timer(timer);	//Start the timer.

	
	while (!exit) {

    	ALLEGRO_EVENT ev;
      	al_wait_for_event(EQ, &ev);

      	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        	exit = true;
      	}
        else if(ev.type == ALLEGRO_EVENT_TIMER) {
			al_clear_to_color(black);
			al_draw_bitmap(ob[3].image, 0, 0, 0);//Background

			//------------Cat Moving(Player)-----------
			if(left == true || right == true || up == true || down == true){   //Moving Animation
				Timer_Part_1(curr, x, y, ob, XY, cat, cat);
				Timer_Part_2(curr, ob, XY, flags, cat, cat);
			}else{  //Silent Animation
				Timer_Part_1(curr, x, y, ob, XY, cube, cat);
				Timer_Part_2(curr, ob, XY, flags, cube, cat);
			}

			//----------------Dog Moving---------------

			//First Step: Dog choosing the movement(One time task until the movement is finished)
			/*
			if(dog_choice == true){
				choice = Dog_Choice();
				dog_choice = false;
			}
			
			//Decide the moving and silent animation
			if(choice != 0){ //Moving
				if(dog_pause == true){  //(One time task until the movement is finished)
					dog_move = rand()%2 + 2;  //How many seconds
					Dog_Move(Dog, dx, dy, dog, dflags);  //This is get the dog moving choice and the flag
					dog_pause = false;
				}
				dog_timer ++;
				if(dog_timer < FPS * dog_move){
					Timer_Part_1(curr, dx, dy, ob, XY, dog, dog);
					Timer_Part_2(curr, ob, XY, dflags, dog, dog);
				}else{
					dog_timer = 0;
					dog_pause = true; dog_choice = true;//Reset the bool
				}
			}else{ //Silent
				if(dog_pause == true){
					dog_rest = rand()%3 + 1;
					dog_pause = false;
				}
				dog_timer ++;
				if(dog_timer < FPS * dog_rest){
					Timer_Part_1(curr, dx, dy, ob, XY, cube2, dog);
					Timer_Part_2(curr, ob, XY, dflags, cube2, dog);
				}else{
					dog_timer = 0;
					dog_pause = true; dog_choice = true;//Reset the bool
				}
			}There's some issues with the code about the dog NPC*/
            al_flip_display();
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
               		up = true; y = 0 - Player[Player_Choice].speed; flags = 0;
               		break;
				case ALLEGRO_KEY_DOWN:
					down = true; y = Player[Player_Choice].speed; flags = 0;
               		break;
            	case ALLEGRO_KEY_RIGHT:
					right = true; x = Player[Player_Choice].speed; flags = 0;
               		break;
	            case ALLEGRO_KEY_LEFT:
					left = true; x = 0 - Player[Player_Choice].speed; flags = 1;
            		break;
				case ALLEGRO_KEY_F11:
					toggleCheck(disp);
					break;
            	case ALLEGRO_KEY_ESCAPE:
    		        exit = true;
            		break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
               		up = false;
					y = 0;
               		break;
				case ALLEGRO_KEY_DOWN:
					down = false;
					y = 0;
               		break;
            	case ALLEGRO_KEY_RIGHT:
					right = false;
					x = 0;
               		break;
	            case ALLEGRO_KEY_LEFT:
					left = false;
					x = 0;
            		break;
			}
		}
	}
	/***——————————————————————————————————————————————***/

	/*if (show_bbox) {
		// draw images bounding box
		drawBoundingBox(cat);
		drawBoundingBox(dog);
	
	}

	// message to apepar if collision occurs
	if (isCollision(cat, dog)){
		al_draw_text(arial, BLUE, 0, 0, 0, "You loose a life!");
	}

	// do the normal writing to the screen
	al_flip_display();*/

	// Wait for 2 seconds. . .//
	al_rest(.1);

	// Release the bitmap data and then exit//
	for (int i=0; i< ob[cat].aFPS; i++){/*ob*/
		al_destroy_bitmap(ob[cat].frame[i]);/*ob*/
	}
	for (int i=0; i< ob[cube].aFPS; i++){/*ob*/
		al_destroy_bitmap(ob[cube].frame[i]);/*ob*/
	}
	for (int i=0; i< ob[dog].aFPS; i++){/*ob*/
		al_destroy_bitmap(ob[dog].frame[i]);/*ob*/
	}
	for (int i=0; i< ob[cube2].aFPS; i++){/*ob*/
		al_destroy_bitmap(ob[cube2].frame[i]);/*ob*/
	}
	al_destroy_bitmap(ob[3].image);
	al_destroy_display(disp);
	al_destroy_bitmap(icon_32);
    return 0;
}