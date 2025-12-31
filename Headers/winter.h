/*Zoe and Sarah*/
#include <allegro5/allegro.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>


//ALL GLOBAL VARIABLES
//define COLOUR
#define pink al_map_rgb(255, 12, 174)
#define purple al_map_rgb(105, 56, 255)
#define white al_map_rgb(255, 255, 255)
#define black al_map_rgb(0, 0, 0)
#define blue al_map_rgba(0, 185, 230, 128)
#define red al_map_rgb(37, 150, 190)

//Basic Settings
#define SCREEN_W 1000
#define SCREEN_H 700
#define FPS 16.0
#define FILE_NAME 100
#define OB_CONTAINER 30
#define COLLECT_TIME 3

//Animation define
#define cat_1_s 1 // cat is still
#define cat_1 2 // cat is moving
#define dog_1_s 10 //  dog is still
#define dog_1 11 // dog is moving
#define snowb_s 20 //snowball is still
#define shadow 22 //Shadow
#define heart_r 23 //Red Heart
#define heart_g 24 //Gray Heart

//Define speices(Expirimental)
#define Ocat 0 
#define Bcat 1
#define Gcat 2
#define Gdog 0

//ALL Structures
struct Animation{
    int aFPS;
    char name[50];
    ALLEGRO_BITMAP **frame;
    ALLEGRO_BITMAP * image;
};

struct Location{
    int W; int H; //Width and Hight for the hitbox
    int px; int py; //the location that draws the image
    int bx; int by; //the location that draws the hitbox
    int sdx; int sdy; //the middle location of the shadow
    int lx; int ly; // The location of the first life
};

struct Entity{
    char name[50];
    int speed;
    int power;
    int snowball = 0;
    int life = 3;
    int specie;
    // bool left = false; bool right = false; bool up = false; bool down = false;
};

struct DogNPC{
    int curr = 0;
    int x = 0; int y = 0;
    int choice = 0;
    bool dog_pause = true; bool dog_choice = true;
    int flag = 0;
    int dog_rest = 0; int dog_move = 0; int dog_timer = 0; int BB_timer = 0;
    Location dog_XY;
};


// ALL PROTYPES
//Storing Animation Information(allegro.cpp)🔉
void STORE_struct(Animation ob[], Entity Player[], Entity Dog[], Entity SB[]);
void ARRAY_frame(Animation ob[], int number);
void INIT_location(Location C[], DogNPC m[], int member);

// Check the ERROR(allegro.cpp)❌
int ERROR(ALLEGRO_DISPLAY *disp, ALLEGRO_EVENT_QUEUE * EQ, ALLEGRO_TIMER * timer, ALLEGRO_FONT* font, Animation ob[], ALLEGRO_BITMAP *icon_32, ALLEGRO_BITMAP *game_buffer);
int addonCheck(ALLEGRO_DISPLAY *disp);
void toggleCheck(ALLEGRO_DISPLAY *disp);
void scale_buffer(ALLEGRO_DISPLAY *disp, ALLEGRO_BITMAP *game_buffer);

//Read Files📄
void READ_files(ALLEGRO_DISPLAY *disp, Entity Player[], int &Cat_Specie, bool &exit);

//Graphic Part(graphic.cpp)🖼️
void animation(Animation ob[], int number); //scan images and put them into frame array
void Aiming_Line(Location C[], int x, int y); // Drawing the aiming line
void text(ALLEGRO_FONT* font);//font Templates
void CLEAR_graphic(Animation ob[]);//Clearing all the graphic
void image_to_frame(Animation ob[], int number);//Cut image into pieces and turn them to frame array
void BounderyBox(Location C[], DogNPC m[], int num, int i);
void Shadows(Animation ob[], Location C[], DogNPC m[], int member); //Prototype for showing shadows
void LifeBar(Animation ob[], Location C[], DogNPC m[], int member); //Prototype for showing life

//Main Animation Functions(animation.cpp)🏃‍♂️
void Timer_Part_1(int &curr, Animation ob[], Location C[], int aniID, int posID, int x, int y);
void Timer_Part_2(int &curr, Animation ob[], Location C[], int F, int aniID, int posID);
void Timer_Part_1_for_Dog(DogNPC m[], Animation ob[], Location C[], int aniID, int i);
void Timer_Part_2_for_Dog(DogNPC m[], Animation ob[], int aniID, int i);

//Entity Functions(game_functions.cpp)🐶
int Dog_Choice();
void Dog_Move(Entity Dog[], DogNPC m[], int number, int specie);
void Dog_NPC_Function(DogNPC m[], Location C[], Entity Dog[], Animation ob[], int i);
void Shadows_update(Location C[], DogNPC m[], int member);
void Life_update(Location C[], DogNPC m[], int member);
void Collecting_snowball(Location C[], Entity Player[], int choice, int timer);
//Prototype for Boundary Detection Function
void Boundary_update(Location C[], DogNPC m[], int member);
void Boundary_Detection(Location C[], Animation ob[], ALLEGRO_FONT *font);
bool isCollision(Location C[], int b1, int b2);

/*
int initializeAllegro(int width, int height, const char title[]);
bool loadBitmap(Image &image, const char *filename);
void setPosition(Image &image, int xPos, int yPos);
void calcBounds(Image & image);
void drawBoundingBox(Image & image);
bool isCollision(Image &a, Image &b);*/