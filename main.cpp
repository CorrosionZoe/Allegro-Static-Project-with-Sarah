#include <allegro5/allegro.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

const int SCREEN_W = 1920;
const int SCREEN_H = 1080;

int main(){
al_init();
al_init_primitives_addon();
al_install_mouse();

ALLEGRO_DISPLAY *display = nullptr;
display = al_create_display(SCREEN_W, SCREEN_H);
al_set_window_title(display, "mouse test");

ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
bool select = false;

event_queue = al_create_event_queue();
al_register_event_source(event_queue, al_get_mouse_event_source());

al_clear_to_color(al_map_rgb(0, 0, 0));\
al_draw_rectangle(500, 500, 800, 800,al_map_rgb(200, 200, 0) , 10);
al_flip_display();


while(!select){
ALLEGRO_EVENT ev;
al_wait_for_event(event_queue, &ev);
if(ev.mouse.x >= 500 && ev.mouse.y >= 500 && ev.mouse.x <= 800 && ev.mouse.y <= 800 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
printf("Hooray!(%d, %d)", ev.mouse.x, ev.mouse.y);
select = true;
}
else if(ev.mouse.x >= 500 && ev.mouse.y >= 500 && ev.mouse.x <= 800 && ev.mouse.y <= 800)
printf("(%d, %d)", ev.mouse.x, ev.mouse.y);
}

return 0;
}