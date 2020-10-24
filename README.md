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

> There are two ways to die: by hitting too many spikes and running out of health, or falling off the bottom of the screen. Hitting spikes (either on the ceiling, or on a platform) reduces the player's amount of health by five, while landing on an ordinary platform increases the player's health by one.

## Showcase:
[![](http://img.youtube.com/vi/-SksNwLmSSE/0.jpg)](https://youtu.be/-SksNwLmSSE?t=32 "")

## Code Requirements:
Requirement | Implementation
------------ | -------------
Generation of random game sets or events | Procedural generation of different types of tiles randomly (types, location)
Data structures for storing game status | 
Dynamic memory management | 
File input/output (e.g., for loading/saving game status) | Leaderboard
Program codes in multiple files | Class 

## Libraries used:
- `ncurses.h` for drawing the frames in the terminal

## Compile
`g++ main.cpp -lncurses`

## Todo
- [ ] Proper indentation and naming styles
- [ ] In-code documentation
- [ ] Tile generation, physics.
- [ ] Player collision physics
- [ ] Score calculation (floor)
- [ ] Player HP
- [ ] Difficulty
- [ ] leaderboard
- [ ] Soundeffect and music
- [ ] Local Multiplayer
