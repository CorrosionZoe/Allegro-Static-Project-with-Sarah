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
	Charactor player[1];
	Charactor NPC[4];
	STORE_struct(ob);

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
	ARRAY_frame(ob, 0);

	/**********⭐**********⭐Main⭐************⭐**********/
	int moving = 2;
    // set current frame and position.//
	int curr[OB_CONTAINER];
	int x[OB_CONTAINER];
	int px[OB_CONTAINER];
	int y[OB_CONTAINER];
	int py[OB_CONTAINER];
	curr[0] = 0, px[0] = 100, x[0] = 0;
	py[0] = 100, y[0] = 0;
	animation(ob, 0);
	al_draw_bitmap(ob[0].frame[0], x[0], y[0], 0);
	al_flip_display();
	printf("2");
	/***—————————————————Animation———————————————————***/
	bool exit = false;
	al_start_timer(timer);	//Start the timer.
	
	while (!exit) {

    	ALLEGRO_EVENT ev;
      	al_wait_for_event(EQ, &ev);

      	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        	exit = true;
      	}
        else if(ev.type == ALLEGRO_EVENT_TIMER) {
			curr[0] ++;
			curr[0] %= ob[0].aFPS;
        	px[0] += x[0];
            py[0] += y[0];
			al_clear_to_color(pink);
			al_draw_bitmap(ob[3].image, 0, 0, 0);
            al_draw_bitmap(ob[0].frame[curr[0]], px[0], py[0], 0);
            al_flip_display();
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
               		y[0] = 0 - moving;
					x[0] = 0;
               		break;
				case ALLEGRO_KEY_DOWN:
               		y[0] = moving;
					x[0] = 0;
               		break;
            	case ALLEGRO_KEY_RIGHT:
               		x[0] = moving;
					y[0] = 0;
               		break;
	            case ALLEGRO_KEY_LEFT:
    		        x[0] = 0 - moving;
					y[0] = 0;
            		break;
            	case ALLEGRO_KEY_ESCAPE:
    		        exit = true;
            		break;
			}
		}
	}
	/***——————————————————————————————————————————————***/


	// Wait for 2 seconds. . .//
	al_rest(5);

	// Release the bitmap data and then exit//
	for (int i=0; i< ob[2].aFPS; i++)
   		al_destroy_bitmap(ob[2].frame[i]);
	al_destroy_display(disp);
    return 0;
}