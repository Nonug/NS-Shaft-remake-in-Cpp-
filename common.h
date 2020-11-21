/* ------------------------------------
 *               common.h
 * ------------------------------------
 *  contain library includes and global
 *  variables
 *
 * ------------------------------------
 *
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#include <string>
#include <ncurses.h>  // for drawing windows in console
#include <algorithm>  // vec remove_if, sort
#include <unistd.h>
#include <iterator>   // for iterating vector
#include <locale.h>   // for unicode sprites
#include <cstdlib>    // random number
#include <vector>
#include <chrono>     // calculate time elapsed
#include <memory>     // unique_ptr
#include <cmath>      // for exp()
#include <fstream>
using namespace std;


//delay between frames
#define DELAY 20000

// Playwin dimensions
#define MAX_X 60
#define MAX_Y 37
// y of Ceiling of playwin
#define YLIMIT 5

// Tile dimensions
#define BWIDTH 15
#define BHEIGHT 2
// constants for types of tile
#define NORMAL 1
#define SPIKE 2
#define SPRING 3
#define FRAGILE 4
#define LCONVEYER 5
#define RCONVEYER 6

// max player health
#define MAX_HEALTH 9

//for menu controls
#define CHOICE 4    // menu choices
#define ECHOICE 3   // end choice
#define QUIT 'q'
#define SELECT ' ' //
#define UP 'w'
#define DOWN 's'

#endif
