/*Zoe and Sarah*/
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

void CLEAR_graphic(Animation ob[]){
    // Release the bitmap data and then exit//
	for (int i=0; i< ob[cat_1].aFPS; i++){/*ob*/
		al_destroy_bitmap(ob[cat_1].frame[i]);/*ob*/
	}
	for (int i=0; i< ob[cat_1_s].aFPS; i++){/*ob*/
		al_destroy_bitmap(ob[cat_1_s].frame[i]);/*ob*/
	}
	for (int i=0; i< ob[dog_1].aFPS; i++){/*ob*/
		al_destroy_bitmap(ob[dog_1].frame[i]);/*ob*/
	}
	for (int i=0; i< ob[dog_1_s].aFPS; i++){/*ob*/
		al_destroy_bitmap(ob[dog_1_s].frame[i]);/*ob*/
	}
	al_destroy_bitmap(ob[0].image);
    al_destroy_bitmap(ob[snowb_s].image);
    al_destroy_bitmap(ob[shadow].image);
    al_destroy_bitmap(ob[heart_r].image);
    al_destroy_bitmap(ob[heart_g].image);
}

void BounderyBox(HitBox XY[], LDog m[], int num, int i){
    if(num < 10){//Cat colour
        al_draw_rectangle(XY[num].bx, XY[num].by, 
            XY[num].bx + XY[num].W, XY[num].by + XY[num].H, pink, 5);
    }else{//Dog colour
        al_draw_rectangle(m[i].dog_hitbox.bx, m[i].dog_hitbox.by, 
            m[i].dog_hitbox.bx + XY[num].W, m[i].dog_hitbox.by + XY[num].H, purple, 5);
    }
}

void Shadows(Animation ob[], HitBox XY[], LDog m[], int member){
    al_draw_bitmap(ob[shadow].image, XY[cat_1].sdx - 48, XY[cat_1].sdy - 20, 0);//For Cat
    for(int i = 0; i< member; i++){
        al_draw_bitmap(ob[shadow].image, m[i].dog_hitbox.sdx - 48, m[i].dog_hitbox.sdy - 20, 0);//For Dog
    }
}

void LifeBar(Animation ob[], HitBox XY[], LDog m[], int member){
    //First Life
    al_draw_bitmap(ob[heart_r].image, XY[cat_1].lx, XY[cat_1].ly, 0);//For Cat
    al_draw_bitmap(ob[heart_r].image, XY[cat_1].lx + 42, XY[cat_1].ly, 0);
    al_draw_bitmap(ob[heart_r].image, XY[cat_1].lx + 84, XY[cat_1].ly, 0);
    for(int i = 0; i< member; i++){
        al_draw_bitmap(ob[heart_r].image, m[i].dog_hitbox.lx, m[i].dog_hitbox.ly, 0);//For Dog
        al_draw_bitmap(ob[heart_r].image, m[i].dog_hitbox.lx + 42, m[i].dog_hitbox.ly, 0);
        al_draw_bitmap(ob[heart_r].image, m[i].dog_hitbox.lx + 84, m[i].dog_hitbox.ly, 0);
    }
}