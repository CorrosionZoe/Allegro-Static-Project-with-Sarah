#include <allegro5/allegro.h>
#include <stdio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

int ERROR(ALLEGRO_DISPLAY *disp, ALLEGRO_EVENT_QUEUE * EQ, ALLEGRO_TIMER * timer, ALLEGRO_FONT* font, ALLEGRO_BITMAP *image);
int addonCheck(ALLEGRO_DISPLAY *disp);
void scale(ALLEGRO_BITMAP *image);