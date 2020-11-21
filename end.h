#include "common.h"
#include <fstream>

#ifndef _END_H_
#define _END_H_

WINDOW* endw;
WINDOW* scr;

int endscr(int level)
{

    // save the score to text file
    fstream file;
    file.open("Score.txt",ios_base::app);
    file << level << endl;
    /*vector<int> x(istream_iterator<int>(file),{});
    sort(x.begin(), x.end());
    for(const auto& elem: x){
        file << elem << "\n ";
    } */
    file.close();

    // the character array that contains all the choices
    char choice_list[ECHOICE][15]={"Back to menu", "Exit"};
    // the tempotaty array to store the choice to be printed out at a row
    char choice[15];
    // inp is for input of user
    int inp, i = 0;

    // the window for game over message
    endw = newwin(15, 40, 14, 10);
    box(endw, 0, 0);
    // the window for title
    scr = newwin(6, 40, 5, 10);
    box(scr, 0, 0);
    mvwprintw(scr, 1, 1, "Game over");
    mvwprintw(scr, 2, 1, "Your level : %i", level);
    mvwprintw(scr, 3, 1, "Score saved to leaderboard");
    wrefresh(scr);
    // initially, print out the menu with the first box being highlighted
    for(int j=0; j<ECHOICE; j++)
    {
        if(j==0)
        {
            wattron(endw , A_STANDOUT);
        }
        else
        {
            wattroff(endw , A_STANDOUT);
        }
	// this puts the item in the choice list into the variable for storing the list of that row
        sprintf(choice, "%s", choice_list[j]);
        mvwprintw(endw, j+1, 1, "%s", choice);
    }
    // instructions of the end screen usage
    mvwprintw(endw, 10, 2, "UP  -> '%c' ", UP);
    mvwprintw(endw, 11, 2, "DOWN -> '%c' ", DOWN);
    mvwprintw(endw, 12, 2, "Select -> '%c' ", "SPACE");
    wrefresh(endw);
    noecho();
    keypad(endw, true);
    curs_set(0);
    // obtain user input from the end screen
    while(inp = wgetch(endw))
    {
	// this reprints the previous choice after the highlight is turned off
        sprintf(choice, "%s", choice_list[i]);
        mvwprintw(endw, i+1, 1, "%s", choice);
        switch(inp)
        {
            case UP:
            i--;
            if(i < 0)
            {
                i = (ECHOICE-1);
            }
            break;
            case DOWN:
            i++;
            if(i > (ECHOICE-1))
            {
                i = 0;
            }
            break;
	        // the case when player chooses the current choice
            case SELECT:
            // return to menu
            if(i == 0)
            {
                bool r = 1;
                delwin(endw);
                clear();
                refresh();
                return r;
            }
            // the choice of returning to
            if(i == 1)
            {

                endwin();

            }
            break;
        }
	    // highlights the next choice which the player is currently on
        wattron(endw, A_STANDOUT);
        sprintf(choice, "%s", choice_list[i]);
        mvwprintw(endw, i+1, 1, "%s", choice);
        wattroff(endw, A_STANDOUT);

    }
    delwin(endw);
    clear();
    refresh();
    return 0;
}


#endif
