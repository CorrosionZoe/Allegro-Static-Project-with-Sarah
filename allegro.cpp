#include <allegro5/allegro.h>
#include <stdio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

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

void scale(ALLEGRO_BITMAP *image){
    float original_width = al_get_bitmap_width(image); // 假设是 100
	float original_height = al_get_bitmap_height(image); // 假设是 100

	// 将图片缩小 50% (从 100x100 缩放到 50x50)，并绘制到 (100, 100)
	al_draw_scaled_bitmap(
    	image, 
    	0, 0, original_width, original_height, // 绘制整个源图片
    	100, 100, 500, 500,                      // 目标位置 (100, 100)，目标尺寸 50x50
    	0
	);
}
