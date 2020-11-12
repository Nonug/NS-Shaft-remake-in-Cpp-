#include <string>
#include <curses.h>
#include <iostream>
#include <cstdint>
#include "game.h"
using namespace std;

WINDOW* win;

//player information inside of a struct
struct
{
  vector2d pos;
  char disp_char;
  int health = 10;
}player;

int init()
{
    //initialize the window
    win = initscr();
    resize_term(30, 60);
    cbreak();
    noecho();
    clear();
    refresh();
    //allow ncurses to interpret action keys
    keypad(win, true);
    //disable blocking when getch()
    //allow to animate screen while waiting input
    nodelay(win, true);
    //make cursor invisible
    curs_set(0);
    return 0;
}

void run()
{
    //the appearance of player
    player.disp_char = '0';
    //initial position of the player
    player.pos = {30, 5};
    //create a int to store the input of player
    int input_char;
    //create boolean value to indicate exit of game
    bool exit = false;

    while(1){
        //get the input of player during the game loop
        input_char = getch();
        //remove the previous position the player at as ncurses
        //does not remove the previous position until it is overwritten
        mvaddch(player.pos.y, player.pos.x, ' ');
        //use a switch data type to interpret the type of input
        switch(input_char){
        case 'q':
            exit = true;
            break;
        /*case 'w':
            player.pos.y -= 1;
            break;*/
        case 'a':
            player.pos.x -= 1;
            break;
        /*case 's':
            player.pos.y += 1;
            break;*/
        case 'd':
            player.pos.x += 1;
            break;
        default:
            break;
        }
        //show the play at the screen at initial position
        //and update the new location
        mvaddch(player.pos.y, player.pos.x, player.disp_char);
        //refresh screen to update new location
        refresh();
        if (exit){
        break;
    }
    }


}

void close()
{
    endwin();
}
