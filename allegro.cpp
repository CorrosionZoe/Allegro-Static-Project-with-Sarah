/*Zoe and Sarah*/
#include "winter.h"

// Function to check errors.
int ERROR(ALLEGRO_DISPLAY *disp, ALLEGRO_EVENT_QUEUE * EQ, ALLEGRO_TIMER * timer, ALLEGRO_FONT* font, Animation ob[], ALLEGRO_BITMAP *icon_32, ALLEGRO_BITMAP *game_buffer){
    //AL
    int Enum = 0;
    if(!disp){
        al_show_native_message_box(disp, "Error", "EEE404", "Fail to display", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        Enum ++;
    }
    if(!game_buffer){
        al_show_native_message_box(disp, "Error", "EEE404", "Fail to load the buffer", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        Enum ++;
    }
    if (!EQ) {
		al_show_native_message_box(disp, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(disp);
      	Enum ++;
	}
    if (!font){
      al_show_native_message_box(disp, "Error", "Error", "Could not load ShortBaby.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      Enum ++;
    }
    if (!ob[0].frame) {
		al_show_native_message_box(disp, "Error", "Error", "Failed to load Cube0 animation!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(disp);
     	Enum ++;
	}
    if (!ob[6].frame) {
		al_show_native_message_box(disp, "Error", "Error", "Failed to load Cube1 animation!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(disp);
     	Enum ++;
	}
    if (!ob[4].frame || !ob[5].frame) {
		al_show_native_message_box(disp, "Error", "Error", "Failed to load Animal animation!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(disp);
     	Enum ++;
	}
    if (!ob[3].image) {
		al_show_native_message_box(disp, "Error", "Error", "Failed to load image!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(disp);
     	Enum ++;
	}
    if (!timer) {
   		al_show_native_message_box(disp, "Error", "Error", "Failed to create timer!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        Enum ++;
    }
    if (!icon_32) {
   		al_show_native_message_box(disp, "Error", "Error", "Failed to load icon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        Enum ++;
    }
    return Enum;
}

// function to ensure no error in addon
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
//function for animation
void ARRAY_frame(Animation ob[], int number){
    int store = ob[number].aFPS;
    ob[number].frame = (ALLEGRO_BITMAP**)malloc(store * sizeof(ALLEGRO_BITMAP*));
}
// function to switch between small and full window screen.
void toggleCheck(ALLEGRO_DISPLAY *disp){
    int flags = al_get_display_flags(disp); //
    bool is_fullscreen = (flags & ALLEGRO_FULLSCREEN_WINDOW);
    int new_state = is_fullscreen ? 0 : 1;
    al_set_display_flag(disp, ALLEGRO_FULLSCREEN_WINDOW, new_state);
}
// function to store the images of the animation, cat, and dog.
void STORE_struct(Animation ob[], Entity Player[], Entity Dog[]){
    /*              Animation Structure                 */
    //0
    ob[0].aFPS = 7;
    strcpy(ob[0].name, "Cube"); 
    ob[0].frame = NULL;
    //1
    //2
    /////////////////////////////////////////////////////////////////Game Begin: 3 ----- Background
    ob[3].image = NULL;
    strcpy(ob[3].name, "Snow_Background");
    ob[3].image = al_load_bitmap("Image/SnowBG.jpeg");
    //4 ----- Cat moving
    ob[4].aFPS = 6;
    strcpy(ob[4].name, "Cat");
    ob[4].frame = NULL;
    //5 ----- Dog NPC moving
    ob[5].aFPS = 4;
    strcpy(ob[5].name, "Dog");
    ob[5].frame = NULL;
    //6 ----- Dog NPC staying
    ob[6].aFPS = 7;
    strcpy(ob[6].name, "Cube");
    ob[6].frame = NULL;
    //-----------------------------------------------------------
    
    /*                 Entity Structure                 */
    Player[0].speed = 20; Dog[5].speed = 5;
}
// function to check the location of the dog
void INIT_location(Frame XY[]){
    srand(time(0));
    //Px
    XY[4].px = 100;
    XY[5].px = rand()%901 + 50;
    //Py
    XY[4].py = 300;
    XY[5].py = rand()%601 + 50;
    //BB
    XY[4].W = 200; XY[4].H = 200;
    XY[5].W = 300; XY[5].H = 300;
}


