#include "winter.h"

// function to store animation images into an array
void animation(Animation ob[], int number){
    char location[FILE_NAME];
    for(int i = 0; i< ob[number].aFPS; i++){
        snprintf(location, FILE_NAME, "Animation/%s/%d.png", ob[number].name, i);
        ob[number].frame[i] = al_load_bitmap(location);
    }
}
/* code for just a template to make a shape
void shape(){
    // paint rectangle  (x1, y1, x2, y2, colour) - Upper left and lower right points of the rectangle
	al_draw_filled_rectangle(0, 0, 100, 50, pink);
	al_draw_filled_circle(SCREEN_W-60, 60, 50, pink);
	al_draw_circle(SCREEN_W-90, SCREEN_H -90, 80, pink, 10);		// last parameter is thickness of line
	al_draw_line(0, SCREEN_H, 110, 550, pink, 25);
}
*/

// function to make the text appear 
void text(ALLEGRO_FONT* font){
    al_draw_text(font, pink, SCREEN_W/2, (SCREEN_H/4), ALLEGRO_ALIGN_CENTRE, "Everything is Awesome!");
    al_flip_display();
    al_rest(1);
    al_draw_text(font, pink, SCREEN_W/2, (300), ALLEGRO_ALIGN_CENTRE, "When you are part of a team");
    al_flip_display();
}
// function to make the frame an image
void image_to_frame(Animation ob[], int number){
    float o_width = al_get_bitmap_width(ob[number].image);
	float o_height = al_get_bitmap_height(ob[number].image);
    for (int i = 0; i < 4; i++){
        for(int j = 0; j< 4; j++){
            ob[number].frame[i *4 + j] = al_create_sub_bitmap(ob[number].image, j* (o_width /4), i *(o_height /4), (o_width /4), (o_height /4));
        }
    }
}