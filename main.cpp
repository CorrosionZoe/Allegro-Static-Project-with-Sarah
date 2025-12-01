#include "winter.h"

int main(int argc, char *argv[]){
    al_init();
    al_install_keyboard();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();
    ALLEGRO_DISPLAY* disp = al_create_display(SCREEN_W, SCREEN_H);

	int error = 0;
	error = addonCheck(disp);

    ALLEGRO_FONT *font = al_load_ttf_font("store/ShortBaby.ttf", 50, 0);
    ALLEGRO_EVENT_QUEUE * EQ = al_create_event_queue();
	ALLEGRO_TIMER * timer = al_create_timer(1.0 / FPS);
    ALLEGRO_BITMAP * frame[aFPS];
    

	//Checking ERROR
    error = ERROR(disp, EQ, timer, font, frame[1]);
	if(error != 0){
		return error;
	}
	
    al_set_window_title(disp, "Winter Squabble");
    al_register_event_source(EQ, al_get_display_event_source(disp));
 	al_register_event_source(EQ, al_get_keyboard_event_source());
	al_register_event_source(EQ, al_get_timer_event_source(timer));

    animation(frame);
    // set current frame and position.
	int curr = 0;
	int posx = 372;
	int posy = 400;
	al_draw_bitmap(frame[0], posx, posy, 0);
	al_flip_display();
	bool doexit = false;

	al_start_timer(timer);		// 4.   Start the timer.

	while (!doexit) {

    	ALLEGRO_EVENT ev;
      	al_wait_for_event(EQ, &ev);

      	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        	doexit = true;
      	}
        else if(ev.type == ALLEGRO_EVENT_TIMER) {
        	curr++;
        	curr %= aFPS;
	      	al_clear_to_color(purple);
            shape();
			al_draw_bitmap(frame[curr], posx, posy, 0);
			al_flip_display();
		}
	}

    text(font);

	// Wait for 2 seconds. . .
	al_rest(5);

	// Release the bitmap data and then exit
	for (int i=0; i<aFPS; i++)
   		al_destroy_bitmap(frame[i]);
	al_destroy_display(disp);
    return 0;
}