#ifndef GAME_H
#define GAME_H

int init();
void run();
void close();

//define data type for 2D vectors
typedef struct
{
    //for the x y coordinate of player
    int x;
    int y;
}vector2d;



#endif // GAME_H_INCLUDED
