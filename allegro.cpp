#include "winter.h"

int ERROR(ALLEGRO_DISPLAY *disp, ALLEGRO_EVENT_QUEUE * EQ, ALLEGRO_TIMER * timer, ALLEGRO_FONT* font, ALLEGRO_BITMAP *image){
    //AL
    if(!disp){
        al_show_native_message_box(disp, "Error", "EEE404", "Fail to display", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return 404;
    }
    if (!EQ) {
		al_show_native_message_box(disp, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(disp);
      	return -1;
	}
    if (!font){
      al_show_native_message_box(disp, "Error", "Error", "Could not load ShortBaby.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
    }
    if (!image) {
		al_show_native_message_box(disp, "Error", "Error", "Failed to load image!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(disp);
     	return -1;
	}
    if (!timer) {
   		al_show_native_message_box(disp, "Error", "Error", "Failed to create timer!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    return 0;
}

int addonCheck(ALLEGRO_DISPLAY *disp){
    //al
    if (!al_init_primitives_addon()) {
    	al_show_native_message_box(disp, "Error", "Error", "Failed to initialize primatives addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}
    if (!al_init_image_addon()) {
    	al_show_native_message_box(disp, "Error", "Error",
    		"Failed to initialize image addon!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}
    if (!al_install_keyboard()) {
	    al_show_native_message_box(disp, "Error", "Error", "failed to initialize the keyboard!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	return -1;
   	}
    return 0;
}

