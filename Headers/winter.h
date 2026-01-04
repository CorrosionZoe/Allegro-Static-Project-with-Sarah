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
/*                 ALL GLOBAL VARIABLES                 */
//define COLOUR
#define pink al_map_rgb(255, 12, 174)
#define purple al_map_rgb(105, 56, 255)
#define white al_map_rgb(255, 255, 255)
#define black al_map_rgb(0, 0, 0)
#define blue al_map_rgba(0, 185, 230, 128)
#define red al_map_rgb(37, 150, 190)
#define green al_map_rgb(107, 242, 208)
#define titleblue al_map_rgb(29, 63, 89)
#define titlegreen al_map_rgb(29, 89, 69)
#define infoblue al_map_rgb(174, 239, 255)

//Basic Settings
#define SCREEN_W 1000
#define SCREEN_H 700
#define FPS 16.0
#define FILE_NAME 100
#define OB_CONTAINER 30
#define COLLECT_TIME 3

//Define Animation
#define cat_1_s 1 // cat is still
#define cat_1 2 // cat is moving
#define dog_1_s 10 //  dog is still
#define dog_1 11 // dog is moving
#define snowb_s 20 //snowball is still
#define shadow 22 //Shadow
#define heart_r 23 //Red Heart
#define heart_g 24 //Gray Heart

//Define species(Experimental)
#define Ocat 0 
#define Bcat 1
#define Gcat 2
#define Gdog 0

/*-----ALL STRUCTURES -----*/
// Structure for Animation
struct Animation{
    int aFPS;
    char name[50];
    ALLEGRO_BITMAP **frame;
    ALLEGRO_BITMAP * image;
};

//Structure for information for each character Cat and Dog
struct Entity{
    char name[50]; // Character name
    float speed; //Character speed
    int power; // Character power
    int snowball = 0; // number of snowball
    int life = 3; // number of life
    int specie; // specie type
    int W; int H; //Width and Height for the hitbox
    // bool left = false; bool right = false; bool up = false; bool down = false;
};

//Structure for location of images
struct Location{
    int px; int py; //the location that draws the image
    int bx; int by; //the location that draws the hitbox
    int sdx; int sdy; //the middle location of the shadow
    int lx; int ly; // The location of the first life
    int life = 3;
};


//Structure to control the movement of the Dog NPC
struct DogNPC{
    int curr = 0;
    int x = 0; int y = 0;
    int choice = 0;
    bool dog_pause = true; bool dog_choice = true;
    int flag = 0;
    int dog_rest = 0; int dog_move = 0; int dog_timer = 0; int BB_timer = 0;
    int life = 3;
    Location dog_XY;
};

/*-----ALL PROTOTYPES -----*/
//Storing Animation Information(allegro.cpp)🔉
void STORE_struct(Animation ob[], Entity Player[], Entity Dog[], Entity SB[]);
void ARRAY_frame(Animation ob[], int number);
void INIT_location(DogNPC D[], Entity Player[], Entity Dog[], Entity SB[], int member);

// Check the ERROR(allegro.cpp)❌
int ERROR(ALLEGRO_DISPLAY *disp, ALLEGRO_EVENT_QUEUE * EQ, ALLEGRO_TIMER * timer, ALLEGRO_FONT* font, Animation ob[], ALLEGRO_BITMAP *icon_32, ALLEGRO_BITMAP *game_buffer);
int addonCheck(ALLEGRO_DISPLAY *disp);
void toggleCheck(ALLEGRO_DISPLAY *disp);
void scale_buffer(ALLEGRO_DISPLAY *disp, ALLEGRO_BITMAP *game_buffer);

//Read Files📄
int READ_files(ALLEGRO_DISPLAY *disp, Entity Player[], int &Cat_Specie);

//Graphic Part(graphic.cpp)🖼️
void animation(Animation ob[], int number); //scan images and put them into frame array
void Aiming_Line(Location C, Entity Player[], int x, int y); // Drawing the aiming line
void text(ALLEGRO_FONT* font);//font Templates
void CLEAR_graphic(Animation ob[]);//Clearing all the graphic
void image_to_frame(Animation ob[], int number);//Cut image into pieces and turn them to frame array
void BounderyBox(Location C, Location S, DogNPC D[], Entity Player[], Entity Dog[], Entity SB[], int members, bool snowball);
void Shadows(Animation ob[], Location C, DogNPC D[], int member); //Prototype for showing shadows
void LifeBar(Animation ob[], Location C, DogNPC D[], Entity Player[], Entity Dog[], int c, int member); //Prototype for showing life

//Main Animation Functions(animation.cpp)🏃‍♂️
void Timer_Part_1(int &curr, Animation ob[], Location &C, Entity Player[], int aniID, int x, int y);
void Timer_Part_2(int &curr, Animation ob[], Location C, int F, int aniID);
void Timer_Part_1_for_Dog(DogNPC D[], Animation ob[], Entity Dog[], int aniID, int i);
void Timer_Part_2_for_Dog(DogNPC D[], Animation ob[], int aniID, int i);
void Snowball_thrown(Entity Player[], Entity SB[], Animation ob[], Location &S,
	int x, int x1, int y, int y1, int choice, bool &throwing, bool &Aiming, bool &init);


//Entity Functions(game_functions.cpp)🐶
int Dog_Choice();
void Dog_Move(Entity Dog[], DogNPC D[], int number, int specie);
void Dog_NPC_Function(DogNPC D[], Entity Dog[], Animation ob[], int i);
void Shadows_update(Location &C, DogNPC D[], Entity Player[], Entity Dog[], int member);
void Life_update(Location &C, Location S, DogNPC D[], Entity SB[], Entity Player[], Entity Dog[], int member, int choice, bool &D_reduce);
void Collecting_snowball(Location C, Entity Player[], int choice, int &timer);
void False_snowball(Entity Player[], Location &S, int C, bool &T, bool &A, bool &I);

//Prototype for Boundary Detection Function
void Boundary_update(Location &C, Location &S, DogNPC D[], Entity Dog[], int member);
//void Boundary_Detection(Location C, DogNPC D[], Animation ob[], ALLEGRO_FONT *font);
//bool isCollision(Location C, DogNPC D[], int b1, int b2);

/*
int initializeAllegro(int width, int height, const char title[]);
bool loadBitmap(Image &image, const char *filename);
void setPosition(Image &image, int xPos, int yPos);
void calcBounds(Image & image);
void drawBoundingBox(Image & image);
bool isCollision(Image &a, Image &b);*/