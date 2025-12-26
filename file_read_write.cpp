/*Zoe and Sarah*/
#include "winter.h"

void READ_files(ALLEGRO_DISPLAY *disp, Entity Player[], int &Cat_Specie, bool &exit){
    FILE *Cat = fopen("Player.txt", "r");//Open PLayer Text
    if (!Cat){
		al_show_native_message_box(disp, "Error", "EEE404", "FAIL to open Player.txt", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        exit = true;
    }

    //Scan Player Text
    fscanf(Cat, "Cat-Specie %d\n", &Cat_Specie);
    printf("%d", Cat_Specie);
    if(Cat_Specie > 2 || Cat_Specie < 0){
        al_show_native_message_box(disp, "Error", "EEE404", "INVALID Cat >=(", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        exit = true;
    }
    // fscanf(Cat, "%d %d %d", &Player[0].speed, &Player[1].speed, &Player[2].speed);
    // printf("%d, %d, %d", Player[0].speed, Player[1].speed, Player[2].speed);
    // if(Player[0].speed + Player[1].speed + Player[2].speed >= SCREEN_H){
    //     al_show_native_message_box(disp, "Error", "EEE404", "INVALID Cat Speed >=(", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    //     exit = true;
    // }

    //Close txts
    fclose(Cat);
}