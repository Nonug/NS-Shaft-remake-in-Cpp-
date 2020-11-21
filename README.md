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
[![](http://img.youtube.com/vi/-SksNwLmSSE/0.jpg)](https://youtu.be/-SksNwLmSSE?t=32 "")

## Code Requirements:
Requirement | Implementation
------------ | -------------
Generation of random game sets or events | Procedural generation of different types of tiles randomly (types, location)
Data structures for storing game status | Setting up different types of data for the storage of game status such as player health 
Dynamic memory management | Setting up pointers with "new" type to create dynamic variables in the heap instead of regular memory (e.g. player)
File input/output (e.g., for loading/saving game status) | Storing high scores in the leader board
Program codes in multiple files | header files for game components(gameManager.h/tile.h/menu.h, etc)   

## Libraries used:
- `ncurses.h` for drawing the frames in the terminal

## Compile
`g++ -std=c++14 main.cpp -lncursesw`

## Run
`./a.out`

## Todo
- [X] Proper indentation and naming styles
- [X] In-code documentation
- [X] Tile generation, physics.
- [x] Player collision physics
- [X] Score calculation (floor)
- [X] Player HP
- [X] Difficulty
- [X] leaderboard
