#include <allegro5/allegro.h>
#include <stdio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

//define COLOUR
#define pink al_map_rgb(255, 12, 174)
#define purple al_map_rgb(105, 56, 255)
#define white al_map_rgb(255, 255, 255)
#define green al_map_rgb(106, 100, 96)
#define black al_map_rgb(0, 0, 0)

//Basic Settings
#define SCREEN_W 1000
#define SCREEN_H 700
#define FPS 6.0
#define FILE_NAME 100

//Structures
struct Animation{
    int aFPS;
    char name[50];
    ALLEGRO_BITMAP **frame;
    ALLEGRO_BITMAP * image;
};

//Storing Animation Information
void STORE_struct(Animation ob[]);
void STORE_frame(Animation ob[], int number);

//Check the ERROR
int ERROR(ALLEGRO_DISPLAY *disp, ALLEGRO_EVENT_QUEUE * EQ, ALLEGRO_TIMER * timer, ALLEGRO_FONT* font, Animation ob[]);
int addonCheck(ALLEGRO_DISPLAY *disp);

//Graphic Part
void scale_image(ALLEGRO_BITMAP *image);
void animation(Animation ob[], int number);
void shape();
void text(ALLEGRO_FONT* font);
void loading_image(Animation ob[], int number);