#include "common.h"

#ifndef _MENU_H_
#define _MENU_H_

WINDOW* men;
WINDOW* ins;
WINDOW* title;

void menu()
{
    // the character array that contains all the choices
    char choice_list[CHOICE][15]={"Play", "Instruction", "Leaderboard", "Exit"};
    // the tempotaty array to store the choice to be printed out at a row
    char choice[15];
    // inp is for input of user
    int inp, i = 0;
    // // initializd the screen
    // initscr();
    // the window for menu
    men = newwin(16, 25, 4, 1);
    box(men, 0, 0);
    // the window for title
    title = newwin(3, 25, 1, 1);
    box(title, 0, 0);
    mvwprintw(title, 1, 1, "NS-SHAFT:C++");
    wrefresh(title);
    // initially, print out the menu with the first box being highlighted
    wattron(men, A_STANDOUT);
    for(int j = 0; j<4; j++)
    {
	       // this puts the item in the choice list into the variable for storing the list of that row
        sprintf(choice, "%s", choice_list[j]);
        mvwprintw(men, j+1, 1, "%s", choice);
        wattroff(men, A_STANDOUT); // turn off the highlight for other choices
    }
    // instructions of the menu usage
    mvwprintw(men, 10, 2, "UP  -> %c ", UP);
    mvwprintw(men, 11, 2, "DOWN -> %c ", DOWN);
    mvwprintw(men, 12, 2, "Select -> %s ", "SPACE");
    wrefresh(men);
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
            case UP:
              i--;
              if(i < 0)  // go back to last choice
              {
                  i = (CHOICE-1);
              }
              break;

            case DOWN:
              i++;
              if(i > (CHOICE-1)) // go back to first choice
              {
                  i = 0;
              }
              break;
	    // the case when player chooses the current choice
            case SELECT:
	    // the choice of play game/ returns 1 to the run() in gameManager
            if(i == 0)
            {
                delwin(men); // delete all 3 windows
                delwin(ins);
                delwin(title);
                return;
            }
            // for the instruction choice the instruction window pops out
            if(i == 1)
            {
                ins = newwin(14 , 56, 4, 27);
                box(ins, 0, 0);
                mvwprintw(ins, 2, 2, "Controls :");
      	        mvwprintw(ins, 3, 2, "Move Left -> Left arrow key");
      	        mvwprintw(ins, 4, 2, "Move Right -> Right arrow key");
      	        mvwprintw(ins, 5, 2, "Quit game -> %c", QUIT);
                mvwprintw(ins, 6, 2, "blue normal tile: +1 hp");
                mvwprintw(ins, 7, 2, "red spike tile: -3 hp");
                mvwprintw(ins, 8, 2, "green spring tile: bouncy, +1 hp");
                mvwprintw(ins, 9, 2, "yellow fragile tile : trap block that breaks, +1 hp");
                mvwprintw(ins, 10, 2, "white left conveyer tile: pushes left, +1 hp ");
                mvwprintw(ins, 11,2, "magenta right conveyer tile: pushes right, +1 hp");
                wrefresh(ins);
            }
            // Leaderboard choice : trigger the function that shows score board
            if(i == 2)
            {
                int n = 0;              // nth score in descending order
                fstream op("Score.txt");

                ins = newwin(14, 56, 4, 27);
                box(ins, 0, 0);
                mvwprintw(ins, 1,2, "Top ten previous highscores");

                // store the scores from file to vector with istream_iterator
                vector<int> scores((istream_iterator<int>(op)), istream_iterator<int>());
                sort(scores.begin(), scores.end(), greater<int>()); // sorts in descending order

                // print top 10 scores from vec
                for (const auto& e: x){
                        if (n >= 9) break; // only output top 10 scores
                        mvwprintw(ins, n+i, 3, "%d.", n+1);
                        mvwprintw(ins, n+i, 6,"%d", e);
                        n++;

                    }
                mvwprintw(ins, 12, 2, "Press s to continue");
                wrefresh(ins);
            }
	    // exit choice : delete the menu windows and return to terminal
            if(i == 3)
            {
                endwin(); // end all windows
                exit(1); //quit game

            }
            break;
        }
	// highlights the next choice which the player is currently on
        wattron(men, A_STANDOUT);
        sprintf(choice, "%s", choice_list[i]);
        mvwprintw(men, i+1, 1, "%s", choice);
        wattroff(men, A_STANDOUT);

    }
    delwin(men); // shouldnt run
    clear();
    refresh();
    return; // this shouldnt run
}


#endif
