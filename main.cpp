#include <allegro5/allegro.h>
#include <stdio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "winter.h"

#define pink al_map_rgb(255, 12, 174)
#define green al_map_rgb(106, 100, 96)

const float FPS = 60.0;

int main(int argc, char *argv[]){
    al_init();
    al_install_keyboard();
    ALLEGRO_DISPLAY* disp = al_create_display(1000, 1000);

	int error = 0;
	error = addonCheck(disp);

    ALLEGRO_EVENT_QUEUE * EQ = al_create_event_queue();
	ALLEGRO_TIMER * timer = al_create_timer(1.0 / FPS);
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_BITMAP *image = al_load_bitmap("Block_of_Diamond_JE6_BE3.png");

	//Checking ERROR
    error = ERROR(disp, EQ, timer, font, image);
	if(error != 0){
		return error;
	}
	
    al_set_window_title(disp, "Winter Squabble");
    al_register_event_source(EQ, al_get_display_event_source(disp));
 	al_register_event_source(EQ, al_get_keyboard_event_source());
	al_register_event_source(EQ, al_get_timer_event_source(timer));

	
	scale(image);
    al_convert_mask_to_alpha(image, green);
    int x = 0, y = 0, posX = 100, posY = 100;
    al_clear_to_color(pink);
    al_draw_bitmap(image, posX, posY, 0);
    al_flip_display();
    bool exit = false;
	al_start_timer(timer);
    while(!exit){
        ALLEGRO_EVENT ev;
        al_wait_for_event(EQ, &ev);
        
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exit = true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {
                // 按键按下时，设置速度（例如 20）
                case ALLEGRO_KEY_UP:    y = -5; x = 0; break;
                case ALLEGRO_KEY_DOWN:  y = 5;  x = 0; break;
                case ALLEGRO_KEY_LEFT:  x = -5; y = 0; break;
                case ALLEGRO_KEY_RIGHT: x = 5;  y = 0; break;
                case ALLEGRO_KEY_ESCAPE: exit = true; break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) { 
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                case ALLEGRO_KEY_DOWN:
                    y = 0; // 释放上下键时，y 速度归零
                    break;
                case ALLEGRO_KEY_LEFT:
                case ALLEGRO_KEY_RIGHT:
                    x = 0; // 释放左右键时，x 速度归零
                    break;
            }
        }
        
        // -----------------------------------------------------
        // 定时器事件 (这是执行移动的引擎)
        // -----------------------------------------------------
        else if (ev.type == ALLEGRO_EVENT_TIMER) {
            // 只要 x 或 y 不为 0，就会在每个定时器滴答时移动
            posX += x;
            posY += y;

            // 绘图
            al_clear_to_color(pink);
            al_draw_bitmap(image, posX, posY, 0);
            al_flip_display();
        }
    }

    al_rest(2);
    al_destroy_display(disp);
    al_destroy_bitmap(image);
    return 0;
}