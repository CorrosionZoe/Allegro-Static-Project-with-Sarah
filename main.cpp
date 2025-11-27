#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

int main(int argc, char *argv[]){
    al_init();
    al_install_keyboard();
    ALLEGRO_DISPLAY* disp = al_create_display(1000, 700);
    ALLEGRO_FONT* font = al_create_builtin_font();

    if(!disp){
        al_show_native_message_box(disp, "Error", "EEE404", "Fail to display", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return 404;
    }
    if (!al_init_image_addon()) {
    	al_show_native_message_box(disp, "Error", "Error",
    		"Failed to initialize image addon!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}
    al_set_window_title(disp, "Snow Fight");
    ALLEGRO_BITMAP *image = al_load_bitmap("Forest Truck 1.png");
    if (!image) {
		al_show_native_message_box(disp, "Error", "Error", "Failed to load image!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(disp);
     	return -1;
	 }
    al_draw_bitmap(image, 0,  0, 0);
    al_flip_display();
    al_rest(5);
    al_destroy_display(disp);
    al_destroy_bitmap(image);
    return 0;
}