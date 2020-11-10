#include <iostream>
#include <string>
#include <ncurses.h>
using namespace std;

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
    }
    //start the game if choose P
    else if(c = 'P')
    {
        printw("\nThe game begins in 5 seconds......");
        refresh();
        napms(5000);
        endwin();

    }

    //endwin(); //properly end curses

    return 0; // return value for the shell
}
