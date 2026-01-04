/*Zoe and Sarah*/
#include "winter.h"
// function to read files
int READ_files(ALLEGRO_DISPLAY *disp, Entity Player[], int &Cat_Specie){
    FILE *Cat = fopen("Player.txt", "r");//Open player text file
    if (!Cat){ // if statement to print error if player text file failed to open
		al_show_native_message_box(disp, "Error", "EEE404", "FAIL to open Player.txt", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return 4;
    }

    //Scan Player Text file
    fscanf(Cat, "Cat-Specie %d\n", &Cat_Specie);
    printf("%d", Cat_Specie);
    if(Cat_Specie > 2 || Cat_Specie < 0){ //print error if cat is not loaded properly
        al_show_native_message_box(disp, "Error", "EEE404", "INVALID Cat >=(", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return 4;
    }
    // fscanf(Cat, "%d %d %d", &Player[0].speed, &Player[1].speed, &Player[2].speed);
    // printf("%d, %d, %d", Player[0].speed, Player[1].speed, Player[2].speed);
    // if(Player[0].speed + Player[1].speed + Player[2].speed >= SCREEN_H){
    //     al_show_native_message_box(disp, "Error", "EEE404", "INVALID Cat Speed >=(", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    //     exit = true;
    // }

    //Closes player text file
    fclose(Cat);
    return 0;
}