/*Zoe and Sarah*/
#include "winter.h"

// function to store animation images into an array
void animation(Animation ob[], int number){
    char location[FILE_NAME];
    for(int i = 0; i< ob[number].aFPS; i++){ // for loop to upload each image from the particular frame
        snprintf(location, FILE_NAME, "Animation/%s/%d.png", ob[number].name, i);
        ob[number].frame[i] = al_load_bitmap(location);
    }
}
// function to draw aiming line 
void Aiming_Line(Location C, Entity Player[], int x, int y){
    al_draw_filled_circle(x, y, 10, blue);
    // draw line  (x1, y1, x2, y2, colour, thickness) - Upper left and lower right points
	al_draw_line(C.bx + Player[Ocat].W / 2, C.by + Player[Ocat].H / 2, x, y, blue, 5);
}

// function to make the text appear 
void text(ALLEGRO_FONT* font){
    al_draw_text(font, pink, SCREEN_W/2, (SCREEN_H/4), ALLEGRO_ALIGN_CENTRE, "Everything is Awesome!");
    al_flip_display();
    al_rest(1);
    al_draw_text(font, pink, SCREEN_W/2, (300), ALLEGRO_ALIGN_CENTRE, "When you are part of a team");
    al_flip_display();
}
// function to make the frame for the image
void image_to_frame(Animation ob[], int number){
    float o_width = al_get_bitmap_width(ob[number].image);
	float o_height = al_get_bitmap_height(ob[number].image);
    for (int i = 0; i < 4; i++){
        for(int j = 0; j< 4; j++){
            ob[number].frame[i *4 + j] = al_create_sub_bitmap(ob[number].image, j* (o_width /4), i *(o_height /4), (o_width /4), (o_height /4));
        }
    }
}
// function to clear images
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
// function to make a boundary box for each character
void BounderyBox(Location C, Location S, DogNPC D[], Entity Player[], Entity Dog[], Entity SB[], int members, bool snowball){
    //Draw cat boundary box
        al_draw_rectangle(C.bx, C.by, 
            C.bx + Player[Ocat].W, C.by + Player[Ocat].H, pink, 5);
    //for loop to draw dog boundary box
    for(int i = 0; i< members; i++){
        al_draw_rectangle(D[i].dog_XY.bx, D[i].dog_XY.by, 
            D[i].dog_XY.bx + Dog[Gdog].W, D[i].dog_XY.by + Dog[Gdog].H, purple, 5);
	}
    if(snowball == true){
        al_draw_rectangle(S.bx, S.by, 
            S.bx + SB[Ocat].W, S.by + SB[Ocat].H, blue, 5);
    }
}
// function to draw the shadows for the characters
void Shadows(Animation ob[], Location C, DogNPC D[], int member){
    al_draw_bitmap(ob[shadow].image, C.sdx - 48, C.sdy - 20, 0);//For Cat
    for(int i = 0; i< member; i++){
        al_draw_bitmap(ob[shadow].image, D[i].dog_XY.sdx - 48, D[i].dog_XY.sdy - 20, 0);//For Dog
    }
}
// function to draw the life bars for the characters
void LifeBar(Animation ob[], Location C, DogNPC D[], Entity Player[], Entity Dog[], int c, int member){
    int distance = 42;
    //For loop to print red heart lives for characters
    for(int i = 0; i < Player[c].life; i++){
        al_draw_bitmap(ob[heart_r].image, C.lx + distance * i, C.ly, 0);//For Cat lives
    }
    for(int i = 0; i< member; i++){
        for(int j = 0; j < D[i].life; j++) {
            al_draw_bitmap(ob[heart_r].image, D[i].dog_XY.lx + distance * j, D[i].dog_XY.ly, 0); //For dog hearts
        }
        for(int j = D[i].life; j < Dog[Gdog].life; j++) {
            al_draw_bitmap(ob[heart_g].image, D[i].dog_XY.lx + distance * j, D[i].dog_XY.ly, 0); //For dog lose heart
        }
    }
}