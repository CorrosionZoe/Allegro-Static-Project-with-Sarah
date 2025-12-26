/*Zoe and Sarah*/

#include "winter.h"


int main(int argc, char *argv[]){

	/**********⭐**********⭐Set Up⭐************⭐**********/

	//Install and initialize struct//
    al_init();
    al_install_keyboard(); al_init_image_addon(); al_init_ttf_addon(); al_init_font_addon(); al_install_mouse(); // initialize addons
	Animation ob[OB_CONTAINER]; HitBox XY[OB_CONTAINER]; LDog m[OB_CONTAINER];//Animation,Location, and NPC values
	Entity Player[3]; Entity Dog[4]; Entity SB[1];//Entities
      // create two images
	STORE_struct(ob, Player, Dog, SB);

	//First creating display//
    ALLEGRO_DISPLAY* disp = al_create_display(SCREEN_W, SCREEN_H);
	ALLEGRO_BITMAP *icon_32 = al_load_bitmap("Snowball_32.png");
	ALLEGRO_BITMAP *game_buffer = al_create_bitmap(SCREEN_W, SCREEN_H);
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
	al_register_event_source(EQ, al_get_mouse_event_source());
	ARRAY_frame(ob, cat_1); ARRAY_frame(ob, cat_1_s); ARRAY_frame(ob, dog_1); ARRAY_frame(ob, dog_1_s);/*ob*/
	//store frame set
	animation(ob, cat_1); animation(ob, cat_1_s); animation(ob, dog_1); animation(ob, dog_1_s);/*ob*/
	
	//Checking total ERROR//
    error = ERROR(disp, EQ, timer, font, ob, icon_32, game_buffer);
	if(error != 0){
		printf("%d errors", error);
		return error;
	}

	/**********⭐**********⭐Main⭐************⭐**********/
	char ans;
    // set current frame and position.//
	int curr = 0; int currs = 0;
	//Player position
	int x = 0; int y = 0;
	//Px+Py
    XY[cat_1].px = 100; XY[cat_1].py = 300;
	//Dogs position
	int members = 1;
	INIT_location(XY, m, members);
	//curr set
	// memset(curr, -1, sizeof(curr));
	
	
	/***—————————————————Timer———————————————————***/

	//GAME BOOL
	bool game_start = true; bool menu = false; bool throwing; bool showingsnowball = false;
	//KEY BOOL
	bool left = false; bool right = false; bool up = false; bool down = false; bool exit = false; bool showBB = false;
	//FLAG BOOL
	bool flags = 0; 
	//DOG FLAG + DOG INT                                   //BB INT
	int BB_timer = 0;

	//Text file scanning
	int Player_Choice = 0;
	READ_files(disp, Player, Player_Choice, exit);

	al_start_timer(timer);	//Start the timer.

	
	while (!exit) {

    	ALLEGRO_EVENT ev;
      	al_wait_for_event(EQ, &ev);

      	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        	exit = true;
      	}
        else if(ev.type == ALLEGRO_EVENT_TIMER) {
			//Set game buffer to the screen
			al_set_target_bitmap(game_buffer);

			//Clear buffer
			al_clear_to_color(black);

			/***—————————————————Starting Menu———————————————————***/
			if(menu == true){
				printf("game start?(y/n)\n");
				scanf("%c",  &ans);
				if(ans == 'y'){
					game_start = true; menu = false;
			
				}
			}

			/***—————————————————Game_Part———————————————————***/


			if(game_start == true){
				//Background Display
				al_draw_bitmap(ob[0].image, 0, 0, 0);
				
				//Update Boundaries(Hitboxes)
				Boundary_update(XY, m, members);

				//Updating and showing shadows
				Shadows_update(XY, m, members);
				Shadows(ob, XY, m, members);

				//Updating Life
				Life_update(XY, m, members);

				// iNITIALIZE THE BOUNDARY DETECTION FUNCTION
				//Boundary_Detection(XY);

				if(showingsnowball == true){
					al_draw_bitmap(ob[snowb_s].image, 50, 20, 0);
				}

				//------------Cat Moving(Player)-----------
				if(left == true || right == true || up == true || down == true){   //Moving Animation
					Timer_Part_1(curr, ob, XY, cat_1, cat_1, x, y);
					Timer_Part_2(curr, ob, XY, flags, cat_1, cat_1);
				}else{  //Silent Animation
					Timer_Part_1(currs, ob, XY, cat_1_s, cat_1, x, y);
					Timer_Part_2(currs, ob, XY, flags, cat_1_s, cat_1);
				}
			
				//----------------Dog Moving---------------

				//First Step: Dog choosing the movement(One time task until the movement is finished)
				for(int i = 0; i < members; i++){
					if(m[i].dog_choice == true){
					m[i].choice = Dog_Choice();
					m[i].dog_choice = false;
					}

					// //Decide the moving and silent animation
					if(m[i].choice != 0){ //Moving
						if(m[i].dog_pause == true){  //(One time task until the movement is finished)
						m[i].dog_move = rand()%5 + 1;  //How many seconds(1-5)
						Dog_Move(Dog, m, i);  //This is get the dog moving choice and the flag
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
				
				
			} 

			//Show bounderies
			if(showBB == true){
				BounderyBox(XY, m, cat_1, 0);
				for(int i = 0; i< members; i++){
					BounderyBox(XY, m, dog_1, i);
				}
				BB_timer = 1;
			}

			//Showing Life Bars
			LifeBar(ob, XY, m, members);

			//Create Fullscreen functions
			al_set_target_bitmap(al_get_backbuffer(disp));
			scale_buffer(disp, game_buffer);

			//Make the screen
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
				case ALLEGRO_KEY_B:
					if(BB_timer == 0){
						showBB = true;
					}else{
						showBB = false;
						BB_timer = 0;
					}
					break;
            	case ALLEGRO_KEY_ESCAPE:
    		        exit = true;
            		break;
				case ALLEGRO_KEY_SPACE:
				// draw snowball
					showingsnowball = true;
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
		else if(ev.type == 	ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			
		}
	}

	// snowball 
    //ob[snowb_s].image = NULL; ob[snowb_s].image = al_load_bitmap("Image/SnowBall_O.png");

//Snowball for Cat
//al_draw_filled_circle(50, 50, 10, white);



// Snowball for Dog
//for (int i = 0; i < 1000; i++) {
//	al_draw_filled_circle(XY[cat_1].bx, XY[cat_1].by, 10, white);
	
//	(100 + i, 250, 50);
//	al_rest//delay(10);
	//cleardevice();
//}


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

	CLEAR_graphic(ob);
	al_destroy_display(disp);
	al_destroy_bitmap(icon_32);
    return 0;
}