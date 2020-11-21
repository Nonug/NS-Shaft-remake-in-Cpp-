#include "common.h"
#include "tile.h"

#ifndef _MENU_H_
#define _MENU_H_

WINDOW* men;
WINDOW* ins;
WINDOW* til;

int menu()
{
    char choice_list[CHOICE][15]={"Play", "Instruction", "Leaderboard", "Exit"};
    char choice[15];
    int inp, i = 0;
    
    initscr();
    men = newwin(16, 25, 4, 1);
    box(men, 0, 0);
    til = newwin(3, 25, 1, 1);
    box(til, 0, 0);
    mvwprintw(til, 1, 1, "NS-SHAFT:C++");
    wrefresh(til);
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
        sprintf(choice, "%s", choice_list[i]);
        mvwprintw(men, i+1, 1, "%s", choice);
    }
    mvwprintw(men, 10, 2, "Up  -> '%c' ", up);
    mvwprintw(men, 11, 2, "Down -> '%c' ", down);
    mvwprintw(men, 12, 2, "Select -> '%c' ", control_choose);
    wrefresh(men);
    noecho();
    keypad(men, true);
    curs_set(0);
    while(inp = wgetch(men))
    {
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
            case control_choose:
            if(i == 0)
            {
                return 1;
            }
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
            if(i == 2)
            {
                //display the score
            }
            if(i == 3)
            {
                delwin(men);
                endwin();
                return 2;
            }
            break;
        }
        wattron(men, A_STANDOUT);
        sprintf(choice, "%s", choice_list[i]);
        mvwprintw(men, i+1, 1, "%s", choice);
        wattroff(men, A_STANDOUT);
        
    }
    delwin(men);
    endwin();
}


#endif