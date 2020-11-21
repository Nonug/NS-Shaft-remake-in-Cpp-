#include "common.h"
#include "tile.h"

#ifndef _MENU_H_
#define _MENU_H_

WINDOW* men;
WINDOW* ins;
WINDOW* til;

int menu()
{
    // the character array that contains all the choices
    char choice_list[CHOICE][15]={"Play", "Instruction", "Leaderboard", "Exit"};
    // the tempotaty array to store the choice to be printed out at a row
    char choice[15];
    // inp is for input of user
    int inp, i = 0;
    
    // initializd the screen
    initscr(); 
    // the window for menu
    men = newwin(16, 25, 4, 1);
    box(men, 0, 0);
    // the window for title
    til = newwin(3, 25, 1, 1);
    box(til, 0, 0);
    mvwprintw(til, 1, 1, "NS-SHAFT:C++");
    wrefresh(til);
    // initially, print out the menu with the first box being highlighted
    for(i=0; i<CHOICE; i++)
    {
        if(i==0)
        {
            wattron(men, A_STANDOUT);
        }
        else
        {
            wattroff(men, A_STANDOUT);
        }
	// this puts the item in the choice list into the variable for storing the list of that row
        sprintf(choice, "%s", choice_list[i]);
        mvwprintw(men, i+1, 1, "%s", choice);
    }
    // instructions of the menu usage
    mvwprintw(men, 10, 2, "Up  -> '%c' ", up);
    mvwprintw(men, 11, 2, "Down -> '%c' ", down);
    mvwprintw(men, 12, 2, "Select -> '%c' ", control_choose);
    wrefresh(men);
    noecho();
    keypad(men, true);
    curs_set(0);
    // obtain user input from the menu screen
    while(inp = wgetch(men))
    {
	// this reprints the previous choice after the highlight is turned off
        sprintf(choice, "%s", choice_list[i]);
        mvwprintw(men, i+1, 1, "%s", choice);
        switch(inp)
        {
            case up:
            i--;
            if(i < 0)
            {
                i = (CHOICE-1);
            }
            break;
            case down:
            i++;
            if(i > (CHOICE-1))
            {
                i = 0;
            }
            break;
	    // the case when player chooses the current choice
            case control_choose:
	    // the choice of play game/ returns 1 to the run() in gameManager
            if(i == 0)
            {
                return 1;
            }
            // for the instruction choice the instruction window pops out
            if(i == 1)
            {
                ins = newwin(14 , 55, 4, 27);
                box(ins, 0, 0);
                mvwprintw(ins, 2, 2, "Controls :");
	        mvwprintw(ins, 3, 2, "Move Left -> Left arrow key");
	        mvwprintw(ins, 4, 2, "Move Right -> Right arrow key");
	        mvwprintw(ins, 5, 2, "Quit game -> %c", control_quit);
                mvwprintw(ins, 6, 2, "blue normal tile: +1 hp");
                mvwprintw(ins, 7, 2, "red spike tile: -3 hp");
                mvwprintw(ins, 8, 2, "green spring tile: bouncy, +1 hp");
                mvwprintw(ins, 9, 2, "yellow fragile tile : trap block that breaks");
                mvwprintw(ins, 10, 2, "white left conveyer tile: pushes left, +1 hp ");
                mvwprintw(ins, 11,2, "magenta right conveyer tile: pushes right, +1 hp");
                wrefresh(ins);
            }
	    // Leaderboard choice : trigger the function that shows score board
            if(i == 2)
            {
                //display the score
            }
	    // exit choice : delete the menu windows and return to terminal
            if(i == 3)
            {
                delwin(men);
                endwin();
                return 2;
            }
            break;
        }
	// highlights the next choice which the player is currently on
        wattron(men, A_STANDOUT);
        sprintf(choice, "%s", choice_list[i]);
        mvwprintw(men, i+1, 1, "%s", choice);
        wattroff(men, A_STANDOUT);
        
    }
    delwin(men);
    endwin();
}


#endif
