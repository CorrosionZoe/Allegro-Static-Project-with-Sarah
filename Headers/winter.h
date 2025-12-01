#include <allegro5/allegro.h>
#include <stdio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#define pink al_map_rgb(255, 12, 174)
#define purple al_map_rgb(105, 56, 255)
#define white al_map_rgb(255, 255, 255)
#define green al_map_rgb(106, 100, 96)
#define black al_map_rgb(0, 0, 0)

#define SCREEN_W 1000
#define SCREEN_H 700
#define FPS 6.0
#define aFPS 6
#define FILE_NAME 100


int ERROR(ALLEGRO_DISPLAY *disp, ALLEGRO_EVENT_QUEUE * EQ, ALLEGRO_TIMER * timer, ALLEGRO_FONT* font, ALLEGRO_BITMAP *image);
int addonCheck(ALLEGRO_DISPLAY *disp);

void scale_image(ALLEGRO_BITMAP *image);
void animation(ALLEGRO_BITMAP * frame[]);
void shape();
void text(ALLEGRO_FONT* font);