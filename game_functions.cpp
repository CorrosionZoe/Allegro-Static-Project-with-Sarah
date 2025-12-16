/*Zoe and Sarah*/
#include "winter.h"
// Function for dog's choice of movement
int Dog_Choice(){
    //set bool = true
    bool normal = true;
    // while loop to randomly choose between moving or throwing a snowball.
    while(normal){
        int choice = rand()% 3 + 1;
        if(choice != 1){
            int choice2 = rand()% 8 + 1;
            return choice2;
        }else{
            return 0;
        }
    }
    return 0;
}

// function to control dog movement
void Dog_Move(Entity Dog[], int &x, int &y, int number, int &f, int choice){
    switch(choice){
        case 1: x = 0 - Dog[number].speed; y = 0; f = 1;//Left 
            break;
        case 2: x = Dog[number].speed; y = 0; f = 0;//Right
            break;
        case 3: y = 0 - Dog[number].speed; x = 0;//Up
            break;
        case 4: y = Dog[number].speed; x = 0;//Down
            break;
        case 5: x = 0 - Dog[number].speed; y = 0 - Dog[number].speed; f = 1;// can move up and left
            break;
        case 6: x = 0 - Dog[number].speed; y = Dog[number].speed; f = 1;// can move down and left
            break;
        case 7: x = Dog[number].speed; y = 0 - Dog[number].speed; f = 0;// can move up and right
            break;
        case 8: x = Dog[number].speed; y = Dog[number].speed; f = 0;// can move down and right
            break;
    }
}


// function to detect if dog and cat collide.

/*
    calcBounds, calculate border locations of boundary box

void calcBounds(Image &cat) {
    cat.bbLeft = cat.x;
	cat.bbTop  = cat.y;
	cat.bbRight = cat.bbLeft + al_get_bitmap_width(cat.bitmap);
	cat.bbBottom = cat.bbTop + al_get_bitmap_height(cat.bitmap);
}


void drawBoundingBox(Image &cat) {
    calcBounds(image);
	al_draw_line(image.bbLeft, image.bbTop, image.bbRight, image.bbTop, RED, 1);
    al_draw_line(image.bbLeft, image.bbBottom, image.bbRight, image.bbBottom, RED, 1);
	al_draw_line(image.bbLeft, image.bbTop, image.bbLeft, image.bbBottom, RED, 1);
	al_draw_line(image.bbRight, image.bbTop, image.bbRight, image.bbBottom, RED,1);
}*/

bool isCollision(Frame XY[], int b1, int b2) {

    if (XY[b1].py + XY[b1].H < XY[b2].py) {
        return false;
    }
    else if (XY[b1].py > XY[b2].py + XY[b2].H) {
        return false;
    }
    else if (XY[b1].px + XY[b1].W < XY[b2].px) {
        return false;
    }
    else if (XY[b1].px > XY[b2].px + XY[b2].W) {
        return false;
    }
    return true;
}