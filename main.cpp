#include "winter.h"


int main(int argc, char *argv[]){

	/**********⭐**********⭐Set Up⭐************⭐**********/

	//Install and initialize struct//
    al_init();
    al_install_keyboard();
	al_init_image_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();
	Animation ob[OB_CONTAINER];
	Frame XY[OB_CONTAINER];
	STORE_struct(ob);
	INIT_location(XY);

	//First creating display//
    ALLEGRO_DISPLAY* disp = al_create_display(SCREEN_W, SCREEN_H);

	//Checking addon ERROR//
	int error = 0;
	error = addonCheck(disp);

	//Initializing Allegros//
    ALLEGRO_FONT *font = al_load_ttf_font("store/ShortBaby.ttf", 50, 0);
    ALLEGRO_EVENT_QUEUE * EQ = al_create_event_queue();
	ALLEGRO_TIMER * timer = al_create_timer(1.0 / FPS);
    
	//Checking total ERROR//
    error = ERROR(disp, EQ, timer, font, ob);
	if(error != 0){
		return error;
	}

	//Set Title and events//
    al_set_window_title(disp, "Winter Squabble");
    al_register_event_source(EQ, al_get_display_event_source(disp));
 	al_register_event_source(EQ, al_get_keyboard_event_source());
	al_register_event_source(EQ, al_get_timer_event_source(timer));
	int cat = 4; int cube = 0;
	ARRAY_frame(ob, cat); ARRAY_frame(ob, cube);/*ob*/

	/**********⭐**********⭐Main⭐************⭐**********/
	int moving = 10;
    // set current frame and position.//
	int curr[OB_CONTAINER];
	int x = 0; int y = 0;
	memset(curr, -1, sizeof(curr));
	animation(ob, cat); animation(ob, cube);/*ob*/
	
	
	/***—————————————————Animation———————————————————***/
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
	bool exit = false;
	bool flags = 0;
	al_start_timer(timer);	//Start the timer.
	
	while (!exit) {

    	ALLEGRO_EVENT ev;
      	al_wait_for_event(EQ, &ev);

      	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        	exit = true;
      	}
        else if(ev.type == ALLEGRO_EVENT_TIMER) {
			al_clear_to_color(pink);
			al_draw_bitmap(ob[3].image, 0, 0, 0);//Background
			if(left == true || right == true || up == true || down == true){   //Moving Animation
				Timer_Part_1(curr, x, y, ob, XY, cat);
				Timer_Part_2(curr, ob, XY, flags, cat, cat);
			}else{  //Silent Animation
				Timer_Part_1(curr, x, y, ob, XY, cube);
				Timer_Part_2(curr, ob, XY, flags, cube, cat);
			}
            al_flip_display();
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
               		up = true; y = 0 - moving; flags = 0;
               		break;
				case ALLEGRO_KEY_DOWN:
					down = true; y = moving; flags = 0;
               		break;
            	case ALLEGRO_KEY_RIGHT:
					right = true; x = moving; flags = 0;
               		break;
	            case ALLEGRO_KEY_LEFT:
					left = true; x = 0 - moving; flags = 1;
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


	// Wait for 2 seconds. . .//
	al_rest(.1);

	// Release the bitmap data and then exit//
	for (int i=0; i< ob[cat].aFPS; i++){/*ob*/
		al_destroy_bitmap(ob[cat].frame[i]);/*ob*/
	}
	for (int i=0; i< ob[cube].aFPS; i++){/*ob*/
		al_destroy_bitmap(ob[cube].frame[i]);/*ob*/
	}
	al_destroy_bitmap(ob[3].image);
	al_destroy_display(disp);
    return 0;
}