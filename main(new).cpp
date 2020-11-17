// square (y,x) = (2,3)
// playwin: h,w = 22*2,24*3
// player: 2*2, 2*3
#include "common.h" // relocate incldues and global var
#include "player.h"
#include "tile.h"
#include "gameManager.h"
#include "subtypeTile.h"
// #include <functional> // for unary_function


void game_init(){
  setlocale(LC_ALL, ""); // set locale to draw utf-8 characters
  initscr(); // Initialize the window

  // start colour if its supported
  if(has_colors() == FALSE)
  {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  }
  start_color();			/* Start color 			*/
  // init_pair(1, COLOR_RED, COLOR_BLACK);
  // init_pair(tile_color, COLOR_YELLOW, COLOR_GREEN);
  // init_pair(blank_color, COLOR_BLACK, COLOR_BLACK);
  // init_pair(b_and_w, COLOR_WHITE, COLOR_BLACK);

  raw();				/* Line buffering disabled	*/
  keypad(stdscr, TRUE);		/* We get F1, F2 , arrow keys etc..		*/
  noecho(); // Don't echo any keypresses
  curs_set(FALSE); // Don't display a cursor
  // //allow to animate screen while waiting input
  nodelay(stdscr, true);
}
int main(int argc, char** argv) {
    game_init(); // Initialize the screen
    Manager manager; // create the game manager and run
    manager.run(); // main game phase, TODO: (include start screen, end screen)
    endwin(); // end the process TODO: kill playwin, player etc...
 }
