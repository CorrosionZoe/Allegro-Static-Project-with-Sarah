#include <allegro5/allegro.h>
#include <stdio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#define pink al_map_rgb(255, 12, 174)
#define green al_map_rgb(106, 100, 96)

int main(int argc, char *argv[]){
    al_init();
    al_install_keyboard();
    ALLEGRO_DISPLAY* disp = al_create_display(1000, 1000);
    ALLEGRO_EVENT_QUEUE * EQ = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();

    if(!disp){
        al_show_native_message_box(disp, "Error", "EEE404", "Fail to display", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return 404;
    }
    if (!al_init_image_addon()) {
    	al_show_native_message_box(disp, "Error", "Error",
    		"Failed to initialize image addon!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return 0;
	}
    if (!EQ) {
		al_show_native_message_box(disp, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(disp);
      	return -1;
	}
    ALLEGRO_BITMAP *image = al_load_bitmap("Forest Truck 1.png");
    if (!image) {
		al_show_native_message_box(disp, "Error", "Error", "Failed to load image!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(disp);
     	return -1;
	}

    al_set_window_title(disp, "Snow Fight");
    al_register_event_source(EQ, al_get_display_event_source(disp));
 	al_register_event_source(EQ, al_get_keyboard_event_source());

    
    ALLEGRO_BITMAP *clip = al_create_sub_bitmap(image, 1000, 1000, 500, 500);
    
    al_convert_mask_to_alpha(clip, green);
    int x = 100, y = 100;
    al_clear_to_color(pink);
    al_draw_bitmap(clip, x, y, 0);
    al_flip_display();
    bool exit = false;
    while(!exit){
        ALLEGRO_EVENT ev;
        al_wait_for_event(EQ, &ev);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        	exit = true;
      	}
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         	switch(ev.keyboard.keycode) {
            	case ALLEGRO_KEY_UP:
               		y -= 20;
               		break;
	            case ALLEGRO_KEY_DOWN:
    		        y += 20;
            		break;
            	case ALLEGRO_KEY_LEFT:
               		x -= 20;
               		break;
	            case ALLEGRO_KEY_RIGHT:
               		x += 20;
               		break;
               	case ALLEGRO_KEY_ESCAPE:
               		exit = true;
               		break;
         	}
         	al_clear_to_color(pink);
		 	al_draw_bitmap(clip, x, y, 0);
		 	al_flip_display();
		}
    }

    al_rest(2);
    al_destroy_display(disp);
    al_destroy_bitmap(image);
    return 0;
}