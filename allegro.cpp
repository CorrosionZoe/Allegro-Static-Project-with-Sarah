#include "winter.h"

int ERROR(ALLEGRO_DISPLAY *disp, ALLEGRO_EVENT_QUEUE * EQ, ALLEGRO_TIMER * timer, ALLEGRO_FONT* font, Animation ob[]){
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
    if (!ob[1].image) {
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

void ARRAY_frame(Animation ob[], int number){
    int store = ob[number].aFPS;
    ob[number].frame = (ALLEGRO_BITMAP**)malloc(store * sizeof(ALLEGRO_BITMAP*));
}

void STORE_struct(Animation ob[]){
    //0
    ob[0].aFPS = 6;
    strcpy(ob[0].name, "Cube");
    ob[0].frame = NULL;
    //1
    ob[1].aFPS = 16;
    strcpy(ob[1].name, "Diamond");
    ob[1].frame = NULL;
    ob[1].image = NULL;
    ob[1].image = al_load_bitmap("Image/Block_of_Diamond.png");
    //2
    ob[2].aFPS = 16;
    ob[2].frame = NULL;
    ob[2].image = NULL;
    ob[2].image = al_load_bitmap("Image/runningMotion.png");
    //Game Begin: 3 ----- Background
    ob[3].image = NULL;
    strcpy(ob[3].name, "Snow_Background");
    ob[3].image = al_load_bitmap("Image/R.jpeg");
    //4 ----- Cat
    ob[4].aFPS = 6;
    
}


