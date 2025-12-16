/*Zoe and Sarah*/
#include "winter.h"

void READ_files(ALLEGRO_DISPLAY *disp, int &Cat_Specie, bool &exit){
    FILE *Cat = fopen("Player.txt", "r");//Open PLayer Text

    if (!Cat){
		al_show_native_message_box(disp, "Error", "EEE404", "FAIL to open Player.txt", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        exit = true;
    }

    //Scan Player Text
    fscanf(Cat, "Cat-Specie: %d", &Cat_Specie);
    printf("%d", Cat_Specie);
    if(Cat_Specie > 2 || Cat_Specie < 0){
        al_show_native_message_box(disp, "Error", "EEE404", "INVALID Cat >=(", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        exit = true;
    }

    //Close txts
    fclose(Cat);
}