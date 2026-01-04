/*Zoe and Sarah*/
#include "winter.h"

//Function to check errors (Display, buffer, event queue, font, snow background, cat animation, dog animation, snowball image, timer, icon)//
int ERROR(ALLEGRO_DISPLAY *disp, ALLEGRO_EVENT_QUEUE * EQ, ALLEGRO_TIMER * timer, ALLEGRO_FONT* font, Animation ob[], ALLEGRO_BITMAP *icon_32, ALLEGRO_BITMAP *game_buffer){
    //ALL//
    int Enum = 0;
    if(!disp){ //If statement to print error if the display is not loaded properly//
        al_show_native_message_box(disp, "Error", "EEE404", "Fail to display", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        Enum ++;
    }
    if(!game_buffer){ //If statement to print error if the buffer is not loaded properly//
        al_show_native_message_box(disp, "Error", "EEE404", "Fail to load the buffer", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        Enum ++;
    }
    if (!EQ) { //If statement to print error if the event queue is not loaded properly//
		al_show_native_message_box(disp, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(disp);
      	Enum ++;
	}
    if (!font){ //If statement to print error if the shortbaby font is not loaded properly//
      al_show_native_message_box(disp, "Error", "Error", "Could not load ShortBaby font",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      Enum ++;
    }
    if (!font){ //If statement to print error if the brt font is not loaded properly//
      al_show_native_message_box(disp, "Error", "Error", "Could not load brt font",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      Enum ++;
      }
    if (!ob[0].image) { //If statement to print error if the background is not loaded properly//
		al_show_native_message_box(disp, "Error", "Error", "Failed to load background image!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(disp);
     	Enum ++;
	}
    if (!ob[cat_1].frame || !ob[cat_1_s].frame) { //If statement to print error if the cat animation is not loaded properly//
		al_show_native_message_box(disp, "Error", "Error", "Failed to load cat animation!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(disp);
     	Enum ++;
	}
    if (!ob[dog_1].frame || !ob[dog_1_s].frame) { //If statement to print error if the dog animation is not loaded properly//
		al_show_native_message_box(disp, "Error", "Error", "Failed to load dog animation!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(disp);
     	Enum ++;
	}
    if (!ob[snowb_s].image) { //If statement to print error if the snowball is not loaded properly//
		al_show_native_message_box(disp, "Error", "Error", "Failed to load snowball image!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(disp);
     	Enum ++;
	}
    if (!timer) { //If statement to print error if the timer is not loaded properly//
   		al_show_native_message_box(disp, "Error", "Error", "Failed to create timer!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        Enum ++;
    }
    if (!icon_32) { //If statement to print error if the icon is not loaded properly//
   		al_show_native_message_box(disp, "Error", "Error", "Failed to load icon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        Enum ++;
    }
    return Enum;
}

//Function to ensure no error in addon//
int addonCheck(ALLEGRO_DISPLAY *disp){
    //If statement to print error if the primitives is not loaded properly//
    if (!al_init_primitives_addon()) {
    	al_show_native_message_box(disp, "Error", "Error", "Failed to initialize primitives addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}
    if (!al_init_image_addon()) { //If statement to print error if the addon image is not loaded properly//
    	al_show_native_message_box(disp, "Error", "Error",
    		"Failed to initialize image addon!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}
    if (!al_install_keyboard()) { //If statement to print error if the keyboard feature does not work properly//
	    al_show_native_message_box(disp, "Error", "Error", "failed to initialize the keyboard!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	return -1;
   	}
    if (!al_install_mouse()) { //If statement to print error if the mouse feature does not work properly//
	    al_show_native_message_box(disp, "Error", "Error", "failed to initialize the mouse!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	return -1;
   	}
    return 0;
}

//Function to store image frames for animation in an array//
void ARRAY_frame(Animation ob[], int number){
    int store = ob[number].aFPS;
    ob[number].frame = (ALLEGRO_BITMAP**)malloc(store * sizeof(ALLEGRO_BITMAP*));
}

//Function to switch between small and full window screen//
void toggleCheck(ALLEGRO_DISPLAY *disp){
    int flags = al_get_display_flags(disp); 
    bool is_fullscreen = (flags & ALLEGRO_FULLSCREEN_WINDOW);
    int new_state = is_fullscreen ? 0 : 1;
    al_set_display_flag(disp, ALLEGRO_FULLSCREEN_WINDOW, new_state);
}

//Function to check the location of the dog//
void INIT_location(DogNPC D[], Entity Player[], Entity Dog[], Entity SB[], int member){
    Player[Ocat].W = 55; Player[Ocat].H = 129;
    Dog[Gdog].W = 50; Dog[Gdog].H = 160;
    SB[Ocat].W = 33; SB[Ocat].H = 38;

    srand(time(0));
    for(int i = 0; i < member; i++){ //For loop for dog to randomly move//
        D[i].dog_XY.px = rand()%700+1;
        D[i].dog_XY.py = rand()%370+31;
    }
}

//Function to adjust display screen from small size to big size and vice versa//
void scale_buffer(ALLEGRO_DISPLAY *disp, ALLEGRO_BITMAP *game_buffer){
    int screen_w = al_get_display_width(disp);
    int screen_h = al_get_display_height(disp);

    float option1 = (float)screen_w / SCREEN_W;
    float option2 = (float)screen_h / SCREEN_H;
    float scale = (option1 < option2) ? option1 : option2;

    float scaled_w = SCREEN_W * scale;
    float scaled_h = SCREEN_H * scale;

    float CX = (screen_w - scaled_w) / 2.0f;
    float CY = (screen_h - scaled_h) / 2.0f;

    al_draw_scaled_bitmap(
        game_buffer,
        0, 0, SCREEN_W, SCREEN_H,
        CX, CY,
        scaled_w, scaled_h,
        0
    );
    
    al_flip_display();
}

//Function to store the images of the animation, cat, and dog//
void STORE_struct(Animation ob[], Entity Player[], Entity Dog[], Entity SB[]){
    /*              Animation Structure                 */
    //Game Begin: 0 ----- Background//
    ob[0].image = NULL; ob[0].image = al_load_bitmap("Image/SnowBG.jpeg");
    //1 ----- Cat staying(original)//
    ob[cat_1_s].aFPS = 13; strcpy(ob[cat_1_s].name, "Cat_S"); ob[cat_1_s].frame = NULL;
    //2----- Cat moving(original)//
    ob[cat_1].aFPS = 8; strcpy(ob[cat_1].name, "Cat"); ob[cat_1].frame = NULL;
    //4
    //10 ----- Dog NPC staying(original)//
    ob[dog_1_s].aFPS = 11; strcpy(ob[dog_1_s].name, "Dog_S"); ob[dog_1_s].frame = NULL;
    //11 ----- Dog NPC moving(original)//
    ob[dog_1].aFPS = 9; strcpy(ob[dog_1].name, "Dog"); ob[dog_1].frame = NULL;
    //20 ----- Snowball!(original)//
    ob[snowb_s].image = NULL; ob[snowb_s].image = al_load_bitmap("Image/SnowBall_O.png");
    //22 ----- Character Shadow//
    ob[shadow].image = NULL; ob[shadow].image = al_load_bitmap("Image/GShadow.png");
    //23 ----- Red Heart(Alive)//
    ob[heart_r].image = NULL; ob[heart_r].image = al_load_bitmap("Image/Heart.png");
    //24 ----- Gray Heart(Dead)//
    ob[heart_g].image = NULL; ob[heart_g].image = al_load_bitmap("Image/GrayHeart.png");


    //-----------------------------------------------------------
    
    /*                 Entity Structure                 */
    //Entity Speed//
    Player[Ocat].speed = 7; Player[Bcat].speed = 15; Player[Gcat].speed = 5;
    Dog[Gdog].speed = 5;
    SB[Ocat].speed = 20;   
    //Entity power//
    Player[Ocat].power = 15; Player[Bcat].power = 10; Player[Gcat].power = 20;
    Dog[Gdog].power = 15;
    SB[Ocat].power = 1;
}