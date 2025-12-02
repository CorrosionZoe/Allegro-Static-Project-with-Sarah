#include "winter.h"


void scale_image(ALLEGRO_BITMAP *image){
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

void animation(Animation ob[], int number){
    char location[FILE_NAME];
    for(int i = 0; i< ob[number].aFPS; i++){
        snprintf(location, FILE_NAME, "Animation/%s/%d.png", ob[number].name, i);
        ob[number].frame[i] = al_load_bitmap(location);
    }
}

void shape(){
    // paint rectangle  (x1, y1, x2, y2, colour) - Upper left and lower right points of the rectangle
	al_draw_filled_rectangle(0, 0, 100, 50, pink);
	al_draw_filled_circle(SCREEN_W-60, 60, 50, pink);
	al_draw_circle(SCREEN_W-90, SCREEN_H -90, 80, pink, 10);		// last parameter is thickness of line
	al_draw_line(0, SCREEN_H, 110, 550, pink, 25);
}

void text(ALLEGRO_FONT* font){
    al_draw_text(font, pink, SCREEN_W/2, (SCREEN_H/4), ALLEGRO_ALIGN_CENTRE, "Everything is Awesome!");
    al_flip_display();
    al_rest(1);
    al_draw_text(font, pink, SCREEN_W/2, (300), ALLEGRO_ALIGN_CENTRE, "When you are part of a team");
    al_flip_display();
}

void loading_image(Animation ob[], int number){
    for (int i = 0; i < 4; i++){
        for(int j = 0; j< 4; j++){
            ob[number].frame[i *4 + j] = al_create_sub_bitmap(ob[number].image, j* 75, i *75, 75, 75);
        }
    }
}