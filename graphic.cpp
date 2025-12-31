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

void Aiming_Line(Location XY[], int x, int y){
    al_draw_filled_circle(x, y, 10, blue);
    // draw line  (x1, y1, x2, y2, colour, thickness) - Upper left and lower right points
	al_draw_line(XY[cat_1].bx + XY[cat_1].W / 2, XY[cat_1].by + XY[cat_1].H / 2, x, y, blue, 5);
}

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

void BounderyBox(Location XY[], DogNPC m[], int num, int i){
    if(num < 10){//Cat colour
        al_draw_rectangle(XY[num].bx, XY[num].by, 
            XY[num].bx + XY[num].W, XY[num].by + XY[num].H, pink, 5);
    }else{//Dog colour
        al_draw_rectangle(m[i].dog_XY.bx, m[i].dog_XY.by, 
            m[i].dog_XY.bx + XY[num].W, m[i].dog_XY.by + XY[num].H, purple, 5);
    }
}

void Shadows(Animation ob[], Location XY[], DogNPC m[], int member){
    al_draw_bitmap(ob[shadow].image, XY[cat_1].sdx - 48, XY[cat_1].sdy - 20, 0);//For Cat
    for(int i = 0; i< member; i++){
        al_draw_bitmap(ob[shadow].image, m[i].dog_XY.sdx - 48, m[i].dog_XY.sdy - 20, 0);//For Dog
    }
}

void LifeBar(Animation ob[], Location XY[], DogNPC m[], int member){
    int distense = 42;
    //First Life
    al_draw_bitmap(ob[heart_r].image, XY[cat_1].lx, XY[cat_1].ly, 0);//For Cat
    al_draw_bitmap(ob[heart_r].image, XY[cat_1].lx + distense, XY[cat_1].ly, 0);
    al_draw_bitmap(ob[heart_r].image, XY[cat_1].lx + distense * 2, XY[cat_1].ly, 0);
    for(int i = 0; i< member; i++){
        al_draw_bitmap(ob[heart_r].image, m[i].dog_XY.lx, m[i].dog_XY.ly, 0);//For Dog
        al_draw_bitmap(ob[heart_r].image, m[i].dog_XY.lx + distense, m[i].dog_XY.ly, 0);
        al_draw_bitmap(ob[heart_r].image, m[i].dog_XY.lx + distense * 2, m[i].dog_XY.ly, 0);
    }
}