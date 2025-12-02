#include "winter.h"


int main(int argc, char *argv[]){

	/**********⭐**********⭐Set Up⭐************⭐**********/

	//Install and initialize struct//
    al_init();
    al_install_keyboard();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();
	Animation ob[2];
	printf("Test\n");
	STORE_struct(ob);
	printf("Is it OK?");

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
	printf("\nTest 2");
	//Set Title and events//
    al_set_window_title(disp, "Winter Squabble");
    al_register_event_source(EQ, al_get_display_event_source(disp));
 	al_register_event_source(EQ, al_get_keyboard_event_source());
	al_register_event_source(EQ, al_get_timer_event_source(timer));

	/**********⭐**********⭐Main⭐************⭐**********/

	STORE_frame(ob, 0);
    animation(ob, 0);
	loading_image(ob, 1);
    // set current frame and position.//
	int cur0 = 0, cur1 = 0;
	int x0 = 372, x1 = 100;
	int y0 = 400, y1 = 100;
	al_draw_bitmap(ob[0].frame[0], x0, y0, 0);
	al_flip_display();

	/***—————————————————Animation———————————————————***/
	bool doexit = false;
	bool directionRight = true;
	int flags = 0;
	al_start_timer(timer);		//Start the timer.
	while (!doexit) {

    	ALLEGRO_EVENT ev;
      	al_wait_for_event(EQ, &ev);

      	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        	doexit = true;
      	}
        else if(ev.type == ALLEGRO_EVENT_TIMER) {
        	//cur0++;
			cur1++;
        	//cur0 %= ob[0].aFPS;
			cur1 %= ob[1].aFPS;
	      	al_clear_to_color(purple);
            //shape();
			if (!directionRight){
				flags = 0;
			}else{
				flags = ALLEGRO_FLIP_HORIZONTAL;
				al_draw_bitmap(ob[1].frame[cur1], x1, y1, flags);
				al_flip_display();
			}	
			//al_draw_bitmap(ob[0].frame[cur0], x0, y0, 0);
			//al_flip_display();
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode) {
            	case ALLEGRO_KEY_RIGHT:
               		directionRight = true;
               		break;
	            case ALLEGRO_KEY_LEFT:
    		        directionRight = false;
            		break;
            	case ALLEGRO_KEY_ESCAPE:
    		        doexit = true;
            		break;
			}
		}
	}
	/***——————————————————————————————————————————————***/

    text(font);

	// Wait for 2 seconds. . .//
	al_rest(5);

	// Release the bitmap data and then exit//
	for (int i=0; i< ob[0].aFPS; i++)
   		al_destroy_bitmap(ob[0].frame[i]);
	al_destroy_display(disp);
    return 0;
}