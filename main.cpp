#include <iostream>
#include <string>
#include <curses.h>
using namespace std;
#include "game.h"

int main()
{
    char text[] = "Text based NS-Shaft \n1. Play(P) \n2. Exit(E) \nEnter your choice:";
    char *t;

    //initialize the curses
    initscr();
    t = text;

    //print out the word character by character
    while (*t){
        addch(*t);
        t++;
        refresh();
        //with 1/10th second of pause in between
        napms(100);
    }

    //grab the choice of user
    char c = getch();

    //Exit the game if choose E
    if (c == 'E'){
        printw("\nBye Bye");
        refresh();
        napms(2000);
        endwin();
        return 0; // return value for the shell
    }
    //start the game if choose P
    else if(c = 'P')
    {
        char txt[] = "\nInstructions \nPress a to go left \nPress d to go right \nPress q to quit \nAvoid landing on spikes \nThe game begins in 5 seconds......";
        char *o;
        o = txt;

        while (*o){
            addch(*o);
            o++;
            refresh();
            napms(100);
        }
        refresh();
        napms(5000);
        int init_status = init();
        if (init_status == 0)
              {
                     run();
              }
              close();
              return 0;
    }
}
