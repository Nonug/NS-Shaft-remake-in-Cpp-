# NS-Shaft remake in Cpp
This a text-based game for the COMP2113 project

## Team 
Group 4 
Nonug: Chan Tsz Hei 3035692060  
ChanChakSum3035708534: Chan Chak Sum 3035708534

## Game description
From [Wikipedia](https://en.wikipedia.org/wiki/NS-Shaft):
> NS-Shaft is a shareware computer game that was originally produced in the late 1990s by Nagi-P Software for the Macintosh.  

> NS-Shaft is a platform game in which the player attempts to descend into a cave. There are two controls, which move the player to the left and the right. The platforms move up the screen at a slowly accelerating rate. A ceiling of spikes hovers at the top of the screen. The goal is to fall from platform to platform rapidly enough to not be hit by the spikes, but slowly enough not to fall off the bottom of the screen.  

## Basic Game Rules
> The player controls the character with 'a' and 'd'. The max health point of the player is 9.
There are 6 types of tiles in the game and the player will desend onto the tiles. As the game progresses, the hostile spike tile will become more and more common. Here's a brief introduction of the 6 tiles. 

Tiles | Effect
------------ | -------------
Blue normal tiles | add one health point
Red spike tiles | minus three health points
Green spring tiles | add one health point and bounces the player upwards
Yellow fragile tiles | add one health point and breaks after ~1 second
Left/Right conveyer tiles | add one health point and pushes player to respective directions   

## Showcase:

Our remake

[![](http://img.youtube.com/vi/mfsU_nKl2wI/0.jpg)](https://www.youtube.com/watch?v=mfsU_nKl2wI "showcase")

Original

[![](http://img.youtube.com/vi/-SksNwLmSSE/0.jpg)](https://youtu.be/-SksNwLmSSE?t=32 "Original")

## Code Requirements:
Requirement | Implementation
------------ | -------------
Generation of random game sets or events | Procedural generation of different types of tiles randomly (types, location)
Data structures for storing game status | Using classes to store corrisponding game status such as player health. Using vectors to store highscores and on-screen tiles 
Dynamic memory management | Setting up pointers with "new" type to create dynamic variables in the heap instead of regular memory (e.g. player)
File input/output (e.g., for loading/saving game status) | Storing/retrieving high scores in the leaderboard
Program codes in multiple files | header files for game components(gameManager.h/tile.h/menu.h, etc)   

## Libraries used:
- `ncurses.h` for drawing the frames in the terminal

## Compile
by following https://stackoverflow.com/questions/60325432/using-ncurses-without-installing-it , clone ncurses mirror from github.

`g++ -I ~/local/include -I ~/local/include/ncursestw -L ~/local/lib -o main main.cpp -lncursestw -ldl -pthread`

## Run
`./main`

## Todo
- [X] Proper indentation and naming styles
- [X] In-code documentation
- [X] Tile generation, physics.
- [x] Player collision physics
- [X] Score calculation (floor)
- [X] Player HP
- [X] Difficulty
- [X] leaderboard
