/*Zoe and Sarah*/
#include "winter.h"

int main(int argc, char *argv[]){

	/**********⭐**********⭐Set Up⭐************⭐**********/

	//Install and initialize struct//
    al_init();
    al_install_keyboard(); al_init_image_addon(); al_init_ttf_addon(); al_init_font_addon(); al_install_mouse(); // initialize addons
	Animation ob[OB_CONTAINER]; Location C; Location S; DogNPC D[OB_CONTAINER];//Animation,Location, and NPC values
	Entity Player[3]; Entity Dog[2]; Entity SB[1];//Entities
      //Create two images//
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
	ALLEGRO_FONT *info = al_load_ttf_font("store/BRT.otf", 35, 0); 
	ALLEGRO_FONT *title = al_load_ttf_font("store/Candy.ttf", 80, 0);
    ALLEGRO_EVENT_QUEUE * EQ = al_create_event_queue();
	ALLEGRO_TIMER * timer = al_create_timer(1.0 / FPS);

	//Set Title and events//
    al_set_window_title(disp, "Winter Squabble");
    al_register_event_source(EQ, al_get_display_event_source(disp));
 	al_register_event_source(EQ, al_get_keyboard_event_source());
	al_register_event_source(EQ, al_get_timer_event_source(timer));
	al_register_event_source(EQ, al_get_mouse_event_source());
	ARRAY_frame(ob, cat_1); ARRAY_frame(ob, cat_1_s); ARRAY_frame(ob, dog_1); ARRAY_frame(ob, dog_1_s);/*ob*/
	//Store frame set//
	animation(ob, cat_1); animation(ob, cat_1_s); animation(ob, dog_1); animation(ob, dog_1_s);/*ob*/

	/**********⭐**********⭐Main⭐************⭐**********/
    //Set current frame and position.//
	int curr = 0; int currs = 0;
	//Player position//
	int x = 0; int y = 0; int x1 = 0; int y1 = 0;
	//FLAG BOOL for the player//
	bool flags = 0; int Player_Choice = Ocat;
	//Cat x and y position//                                
    C.px = 100; C.py = 300; 
	//Set coordinates of x and y position of mouse//
	int mx = 0; int my = 0; int target_x = 0; int target_y = 0;
	//Number of dog NPCS//
	int members = 1;
	//Initialize character locations for each game//
	INIT_location(D, Player, Dog, SB, members);
	
	
	/***—————————————————Timer———————————————————***/

	//Bool for game features//
	bool game_start = false; 
	bool game_end = false;
	bool instructions = false;
	bool menu = true; 
	bool first = true;
	//Bool for updating lives//
	bool D_reduce = false;

	//Snowball BOOL
	bool throwing = false; 
	//bool showingsnowball = false; 
	bool Aiming = false;
	bool collecting = false;
	bool is_initialized = false;
	//Bool for keyboard keys//
	bool left = false; bool right = false; bool up = false; bool down = false; bool exit = false; bool showBB = false; 
	//set collect timer//
	int collect_timer = 0;

	//Scan Text file//
	READ_files(disp, Player, Player_Choice);


	//Checking total ERROR//
    error = ERROR(disp, EQ, timer, font, ob, icon_32, game_buffer);
	if(error != 0){
		printf("%d errors", error);
		return error;
	}

	al_start_timer(timer);	//Start the timer.

	//game start, display menu screen (NOT ACTUAL "GAME" START)	
	while (exit == false) {

    	ALLEGRO_EVENT ev;
      	al_wait_for_event(EQ, &ev);
		// if statement controlling mimizing display.
      	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        	exit = true; //If you click quit button or ESC the game will quit
      	}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){ // location of mouse
			mx = ev.mouse.x; my = ev.mouse.y; //Detect location of the mouse
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){ //If one of the mouse bottun is pressed down
			if(game_start == true){ //Only works inside of the game
				if (ev.mouse.button == 1 && Aiming == true && Player[Player_Choice].snowball > 0 && throwing == false){
				throwing = true; //Starts to throw!
				target_x = mx, target_y = my; //Get the location of the target
				x1 = C.bx + Player[Player_Choice].W / 2; y1 = C.by + Player[Player_Choice].H / 2; //Get the location of the Cat
				}
			}else if(menu == true){ //Only works in the starting menu
				if (ev.mouse.button == 1 && mx >= SCREEN_W/2 - 150 && mx <= SCREEN_W/2 + 150 && my >= 430 && my <= 530 && instructions == false){
					game_start = true; first = true; menu = false; //Start the game
				}else if(ev.mouse.button == 1 && mx >= SCREEN_W/2 - 150 && mx <= SCREEN_W/2 + 150 && my >= 310 && my <= 410){
					instructions = true; 
				} else if (ev.mouse.button == 1 && mx >= SCREEN_W - 200 && mx <= SCREEN_W - 20 && my >= SCREEN_H - 80 && my <= SCREEN_H - 10 && instructions == true) {
					instructions = false; 
				} else if (ev.mouse.button == 1 && mx >= SCREEN_W/2 - 150 && mx <= SCREEN_W/2 + 150 && my >= 550 && my <= 650 && instructions == false) {
					exit = true;
				} 
			} else {
				if (ev.mouse.button == 1 && mx >= SCREEN_W/2 - 150 && mx <= SCREEN_W/2 + 150 && my >= 430 && my <= 530) { // play again button
					game_start = true; first = true; game_end = false;
				}
				if (ev.mouse.button == 1 && mx >= SCREEN_W/2 - 150 && mx <= SCREEN_W/2 + 150 && my >= 550 && my <= 650) { // exit button on end display
					menu = true; game_end = false;
				}
			}		
		}
        else if(ev.type == ALLEGRO_EVENT_TIMER) { //Game Starts!
			//Set game buffer to the screen
			al_set_target_bitmap(game_buffer); //Preparation for the fullscreen(Test)

			//Clear buffer
			al_clear_to_color(black);//Clear buffer

			/***—————————————————Starting Menu———————————————————***/
			
			if(menu == true){//Starting Menu Part
				
				//------------------------Starting Menu Page-----------------------//
   				//al_clear_to_color(white);//Background
				
				al_clear_to_color(black);
				al_draw_bitmap(ob[0].image, 0, 0, 0);

   				al_draw_text(title, titleblue, SCREEN_W/2, 100, ALLEGRO_ALIGN_CENTRE, "Winter Squabble!");//Title
				al_draw_text(title, titleblue, SCREEN_W/2, 200, ALLEGRO_ALIGN_CENTRE, "Cat vs. Dog");// sub heading
   				
   				// Button for View Instructions
				al_draw_filled_rectangle(SCREEN_W/2 - 150, 310, SCREEN_W/2 + 150, 410, white); // IDEAL 350
				al_draw_rectangle(SCREEN_W/2 - 150, 310, SCREEN_W/2 + 150, 410, titleblue, 5);
				al_draw_text(font, titleblue, SCREEN_W/2, 340, ALLEGRO_ALIGN_CENTRE, "Instructions"); // IDEAL 380
				
				// Button for Starting game  (x1, y1, x2, y2, colour) - Upper left and lower right points of the rectangle
				al_draw_filled_rectangle(SCREEN_W/2 - 150, 430, SCREEN_W/2 + 150, 530, white);
				al_draw_rectangle(SCREEN_W/2 - 150, 430, SCREEN_W/2 + 150, 530, titleblue, 5);
				al_draw_text(font, titleblue, SCREEN_W/2, 460, ALLEGRO_ALIGN_CENTRE, "Start"); 
				
				// Button for Exit  (x1, y1, x2, y2, colour) - Upper left and lower right points of the rectangle
				al_draw_filled_rectangle(SCREEN_W/2 - 150, 550, SCREEN_W/2 + 150, 650, white);
				al_draw_rectangle(SCREEN_W/2 - 150, 550, SCREEN_W/2 + 150, 650, titleblue, 5);
				al_draw_text(font, titleblue, SCREEN_W/2, 580, ALLEGRO_ALIGN_CENTRE, "Exit");

				//------------------------------------------------------------------//
				if(instructions == true){
				//INSTRUCTIONS
				al_clear_to_color(black);
				al_draw_bitmap(ob[0].image, 0, 0, 0);
				//Print Instructions
				al_draw_text(title, titleblue, SCREEN_W/2, 30, ALLEGRO_ALIGN_CENTRE,"Instructions:");

				//Rectangle box for instructions
				al_draw_filled_rectangle(SCREEN_W/2 - 400, 150, SCREEN_W/2 + 400, 600, infoblue);
				//Instruction Information
				al_draw_text(info, titleblue, SCREEN_W/2, 180, ALLEGRO_ALIGN_CENTRE, "You are the cat player playing against a dog NPC.");
				al_draw_text(info, titleblue, SCREEN_W/2, 250, ALLEGRO_ALIGN_CENTRE, "Both of you only have three lives,");
				al_draw_text(info, titleblue, SCREEN_W/2, 320, ALLEGRO_ALIGN_CENTRE, "whoever survives keys or WDAS keys. Click the");
				al_draw_text(info, titleblue, SCREEN_W/2, 390, ALLEGRO_ALIGN_CENTRE, "left shift to collect snow and drag the blue line ");
				al_draw_text(info, titleblue, SCREEN_W/2, 460, ALLEGRO_ALIGN_CENTRE, "to aim a snowball at the dog.");
				al_draw_text(info, titleblue, SCREEN_W/2, 530, ALLEGRO_ALIGN_CENTRE, "You have unlimited snowballs and time.");
				
				//Next button
				al_draw_filled_rectangle(SCREEN_W - 200, SCREEN_H - 80, SCREEN_W - 20, SCREEN_H - 10, titleblue);
				al_draw_text(font, white, SCREEN_W - 120, SCREEN_H - 65, ALLEGRO_ALIGN_CENTRE, "Okay");
				}
			}

			/***—————————————————Game_Part———————————————————***/
			// If player chooses to play game, initialize game screen.
			if(game_start == true){
				if(first == true){
					curr = 0; currs = 0;
					x = 0; y = 0; x1 = 0; y1 = 0;
					flags = 0;                      
    				C.px = 100; C.py = 300; 
					members = 1;
					D[0].life = Dog[Gdog].life;
					INIT_location(D, Player, Dog, SB, members);
					first = false;
				}
				//Snow Background Display of Game
				al_draw_bitmap(ob[0].image, 0, 0, 0);

				//Updating and showing shadows for each character (Cat and Dog)
				Shadows_update(C, D, Player, Dog, members);
				
				//Updating Life Bars for each character
				Life_update(C, S, D, SB, Player, Dog, members, Player_Choice, D_reduce);
				if(D_reduce == true){
					False_snowball(Player, S, Player_Choice, throwing, Aiming, is_initialized);
					D_reduce = false;
				}

				//Draw Shadows(Layer 1)
				Shadows(ob, C, D, members);

				//----------------Dog Moving---------------
				
				//Draw Dogs(Layer 2)
				//First Step: Dog choosing the movement between moving or throwing snowball (One time task until the movement is finished)
				for(int i = 0; i < members; i++){
					Dog_NPC_Function(D, Dog, ob, i);
				}

				//Draw Dogs(Layer 3)
				//------------Cat Moving(Player)-----------
				if(left == true || right == true || up == true || down == true){   //Moving Animation
					Timer_Part_1(curr, ob, C, Player, cat_1, x, y);
					Timer_Part_2(curr, ob, C, flags, cat_1);
				}else{  //Silent Animation
					Timer_Part_1(currs, ob, C, Player, cat_1_s, x, y);
					Timer_Part_2(currs, ob, C, flags, cat_1_s);
				}

				//Draw snowballs(Layer 4)
				//Collecting the snowball and Show aiming line
				if(Aiming == true){
					if(Player[Player_Choice].snowball == 0){
						collecting = true;	
						collect_timer ++;
						Collecting_snowball(C, Player, Player_Choice, collect_timer);
					}else{
						collecting = false; 
						if(throwing == true){
							Snowball_thrown(Player, SB, ob, S, target_x, x1, target_y, y1, Player_Choice, throwing, Aiming, is_initialized);
						}else{
							Aiming_Line(C, Player, mx, my);
						}
					}
				}
			

				//Update Boundaries(Hitboxes) for Cat, Dog NPC, and potentially for other dogs too.
				Boundary_update(C, S, D, Dog, members);

				//Show bounderies for cat and dog(Layer 5)
				if(showBB == true){
					BounderyBox(C, S, D, Player, Dog, SB, members, throwing);
				}
				
				//Showing Life Bars for cat and dog(Layer 6)
				LifeBar(ob, C, D, Player, Dog, Player_Choice, members);

				if (D[0].life == 0) {       
        			game_start = false; 
        			game_end = true; 
    			}
			}
			
			if(game_end == true){
				al_clear_to_color(black);
				al_draw_bitmap(ob[0].image, 0, 0, 0);
				al_draw_text(title, titleblue, SCREEN_W/2, 180, ALLEGRO_ALIGN_CENTRE, "Game End");
				al_draw_text(font, titleblue, SCREEN_W/2, 290, ALLEGRO_ALIGN_CENTRE, "Thank you for playing");

				//Start again button//
				al_draw_filled_rectangle(SCREEN_W/2 - 150, 430, SCREEN_W/2 + 150, 530, white);
				al_draw_rectangle(SCREEN_W/2 - 150, 430, SCREEN_W/2 + 150, 530, titleblue, 5);
				al_draw_text(font, titleblue, SCREEN_W/2, 460, ALLEGRO_ALIGN_CENTRE, "Play again!"); 
	
				//Exit game button//	
				al_draw_filled_rectangle(SCREEN_W/2 - 150, 550, SCREEN_W/2 + 150, 650, white);
				al_draw_rectangle(SCREEN_W/2 - 150, 550, SCREEN_W/2 + 150, 650, titleblue, 5);
				al_draw_text(font, titleblue, SCREEN_W/2, 580, ALLEGRO_ALIGN_CENTRE, "Back");
			}

			//Create Fullscreen functions
			al_set_target_bitmap(al_get_backbuffer(disp));
			scale_buffer(disp, game_buffer);
			
			//Make the screen
			al_flip_display();
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){// if keyboard keys are pressed
			if(game_start == true){
				switch(ev.keyboard.keycode) {
					case ALLEGRO_KEY_W: // click 'w' to move up
					case ALLEGRO_KEY_UP: // click up to move up 
						if(collecting == false){
							up = true; y = 0 - Player[Player_Choice].speed;
						}
               			break;
					case ALLEGRO_KEY_S: // click 's' to move down
					case ALLEGRO_KEY_DOWN: // click down to move down
						if(collecting == false){
						down = true; y = Player[Player_Choice].speed;
						}
               			break;
					case ALLEGRO_KEY_D: // click 'd' to move right
            		case ALLEGRO_KEY_RIGHT: // click right to move right
						if(collecting == false){
						right = true; x = Player[Player_Choice].speed; flags = 0;
						}
               			break;
					case ALLEGRO_KEY_A: // click 'a' to move left
	            	case ALLEGRO_KEY_LEFT: // click left to move left
						if(collecting == false){
						left = true; x = 0 - Player[Player_Choice].speed; flags = 1;
						}
            			break;
					case ALLEGRO_KEY_B: //Click 'b' to move 
						if(showBB == false){
							showBB = true;
						}else{
							showBB = false;
						}
						break;
					case ALLEGRO_KEY_LSHIFT:
						if(Aiming == false){
							Aiming = true;
						}else{
							Aiming = false;
						}
						break;
				}
			}
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_F11: // click 
					toggleCheck(disp);
					break;
				case ALLEGRO_KEY_ESCAPE:
					if(game_start == true){
						menu = true; game_start = false; 
					}
            		break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP && game_start == true){
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_W:
				case ALLEGRO_KEY_UP:
               		up = false;
					y = 0;
               		break;
				case ALLEGRO_KEY_S:
				case ALLEGRO_KEY_DOWN:
					down = false;
					y = 0;
               		break;
				case ALLEGRO_KEY_D:
            	case ALLEGRO_KEY_RIGHT:
					right = false;
					x = 0;
               		break;
				case ALLEGRO_KEY_A:
	            case ALLEGRO_KEY_LEFT:
					left = false;
					x = 0;
            		break;
			}
		}
	}

	printf("EXIT\n");
	al_rest(1.0);

	// Wait for 0.1 seconds. . .//
	al_rest(.1);
	CLEAR_graphic(ob);
	al_destroy_display(disp);
	al_destroy_bitmap(icon_32);
    return 0;
}