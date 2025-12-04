#include <allegro5/allegro.h>
#include <stdio.h>
#include <string.h>
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
#define FPS 16.0
#define FILE_NAME 100
#define OB_CONTAINER 50

//Structures
struct Animation{
    int aFPS;
    char name[50];
    ALLEGRO_BITMAP **frame;
    ALLEGRO_BITMAP * image;
};

struct Frame{
    int px; int py;
};

//Storing Animation Information(allegro.cpp)
void STORE_struct(Animation ob[]);
void ARRAY_frame(Animation ob[], int number);
void INIT_location(Frame XY[]);

//Check the ERROR(allegro.cpp)
int ERROR(ALLEGRO_DISPLAY *disp, ALLEGRO_EVENT_QUEUE * EQ, ALLEGRO_TIMER * timer, ALLEGRO_FONT* font, Animation ob[]);
int addonCheck(ALLEGRO_DISPLAY *disp);

//Graphic Part(graphic.cpp)
void scale_image(Animation ob[], int number); //rescale the image
void animation(Animation ob[], int number); //scan images and put them into frame array
void shape();//Some Shapes Templates
void text(ALLEGRO_FONT* font);//font Templates
void image_to_frame(Animation ob[], int number);//Cut image into pieces and turn them to frame array

//Main Animation Functions(animation.cpp)
void Timer_Part_1(int cur[], int x, int y, Animation ob[], Frame XY[], int number);
void Timer_Part_2(int cur[], Animation ob[], Frame XY[], int F, int aniID, int posID);
