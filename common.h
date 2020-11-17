
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
using namespace std;
// using namespace std::chrono;

// init_pair(1, COLOR_RED, COLOR_BLACK);
#define DELAY 20000 //delay between frame
// Tile dimensions
#define BWIDTH 15
#define BHEIGHT 2
// Playwin dimensions
#define MAX_X 60
#define MAX_Y 37
// y of Ceiling of playwin
#define YLIMIT 5


#endif