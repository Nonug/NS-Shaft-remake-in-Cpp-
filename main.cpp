/* ------------------------------------
 *            main.cpp
 * ------------------------------------
 *  Text-based NS-Shaft remake
 *  based on ncurses
 *
 * ------------------------------------
 *
 */

#include "common.h" // contain library includes and global var
#include "player.h" // player class
#include "tile.h"   // tile class
#include "menu.h"   // start menu
#include "end.h"    // end menu
#include "gameManager.h" // game controller class

// Initialize ncurses standard screen, start colour
void game_init(){
  setlocale(LC_ALL, ""); // set locale to draw unicode characters
  initscr();             // Initialize the window

  // start colour if its supported
  if(has_colors() == FALSE)
  {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  }

  start_color();		    	/* Start color 			*/

  raw();			           	/* Line buffering disabled	*/
  keypad(stdscr, TRUE);		/* We get F1, F2 , arrow keys etc..		*/
  noecho();               // Don't echo any keypresses
  curs_set(FALSE);        // Don't display a cursor
  nodelay(stdscr, true);  //allow to animate screen while waiting input
}

// Main game loop.
int main(int argc, char** argv) {

    game_init();                        // Initialize the screen
    while (1){
      menu();                           // start screen
      Manager* manager = new Manager(); // create the game manager and run
      manager->run();                   // main game phase
      delete manager;                   // release memory
    }
    endwin();                           // end ncurses terminal
 }
