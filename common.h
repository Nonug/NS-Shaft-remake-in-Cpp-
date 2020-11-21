
#ifndef _COMMON_H_
#define _COMMON_H_

#include <string>
#include <ncurses.h>
#include <algorithm>  // remove and remove_if
// #include <iostream>
#include <unistd.h>
// #include <cstring>
#include <locale.h> //for sprites
#include <cstdlib> // rand
#include <vector>
#include <chrono>  // calc time pass
#include <memory>  // unique_ptr
#include <cmath> // for exp()
using namespace std;
// using namespace std::chrono;


#define DELAY 20000 //delay between frame
// Tile dimensions
#define BWIDTH 15
#define BHEIGHT 2
// Playwin dimensions
#define MAX_X 60
#define MAX_Y 37
// y of Ceiling of playwin
#define YLIMIT 5
// max health is 10
#define MAX_HEALTH 9
#define control_quit 'q'
// constants for types of tile
#define NORMAL 1
#define SPIKE 2
#define SPRING 3
#define FRAGILE 4
#define LCONVEYER 5
#define RCONVEYER 6
//for menu
#define CHOICE 4
#define control_choose ' '
#define up 'w'
#define down 's'




#endif
