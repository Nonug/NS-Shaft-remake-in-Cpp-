/* ------------------------------------
 *            gameManager.h
 * ------------------------------------
 *  Controls the flow of the game,
 *  entities and physics
 *
 * ------------------------------------
 *
 */

#include "common.h"
#include "tile.h"
#include "player.h"
#include "end.h"
#ifndef _MANAGER_H_
#define _MANAGER_H_

// Manager Object:
//
//  main game control:  run, getInput
//
//  window control:     update_stat, update_inst, display
//
//  physics:            collisionsCheck, movePlayer, effect, movePlayer
//
//  entity control:     addTile, clearDeadTiles, healthupdate
//

class Manager
{
  public:
    double tileSpawnY = MAX_Y - BHEIGHT + 5; // y of spawnpt of tile
    int tileSpawnX = rand() % 60 + 1;        // random xpos for tiles
    double speed = 0.15;                     // speed of tiles
    double spawnTileDelay;      // delay between each tile spawn = 0.12 / speed

    bool running = 1;               // is game running? after game ends, =1 if go main screen, else exit

    WINDOW* playwin;                // game window, with tiles and player
    WINDOW* statwin;                // show curent level, HP
    WINDOW* instwin;                // show instruction
    vector<unique_ptr<Tile>> tiles; // store generated alive tiles.
    Player* p;                      // Player obj pointer

    int levelCoeff = 100; // As game progress, it decreases.
                          // this will increases tile speed and hostile tile spawn rate

    // class constructor, initialize windows and player
    Manager(){
      playwin = newwin(MAX_Y,MAX_X, 5 , 1); // playing window
      statwin = newwin(9,24,5,MAX_X+4);     // statistics window (score, hp)
      instwin = newwin(14,55,15, MAX_X+4);  // instructions window
      nodelay(playwin, true);               // no delay for getch()
      p = new Player(playwin,10,30);        // create a player obj
    }

    // Class Destructor: release memory
    ~Manager(){
      delete p;
      delwin(playwin);
      delwin(statwin);
      delwin(instwin);
    }

    // Heart of the game, call other member functions
    void run(){

      using clock = chrono::system_clock;
      using sec = chrono::duration<double>;
      auto before = clock::now();           // set timestamp before each loop
      spawnTileDelay = 120 / speed;         // delay between tile spawn
      auto timelimit = spawnTileDelay * chrono::milliseconds{1};// convert to ms
      srand(time(0));                       // set rand seed
      update_inst();                        // draw the instruction once

      // add a safety tile
      tiles.emplace_back(new Tile(tileSpawnY, 30, speed));

      while(running) // when not dead/ quit game
      {
        // Add a tile if time elapsed > spawnTileDelay
        if (clock::now() - before > timelimit)
        {
          before = clock::now();
          addTile();
        }


        clearDeadTiles(); // remove dead tiles
        display();    // main physics function, perform actions then display it


        // end the game if HP below 0
        if (p->health <= 0)
        {
          running = 0;
        }

      }

      // when dead or quit, wipe the screen and show end screen
      clear();
      refresh();
      running = endscr(p->level); // call end screen, running becomes true if choose return main screen

    }

    // get input, then call player member function to move it L/R
    void getInput(){
      int choice = getch();
      switch(choice)
      {
        case 'a':
          p->mvleft();
          break;
        case 'd':
          p->mvright();
          break;
        case QUIT: // defined in common.h, default = 'q'
          running = 0;
          break;
        default:
          break;
      }
      return;
    }

    // call the physics functions, refresh the frame and entities
    void display(){

      clear(); // clear previous frames (not shown yet)

      // refresh all frames (show empty)
      refresh();
      wrefresh(playwin);
      wrefresh(statwin);
      wrefresh(instwin);


      getInput();     // read user input
      p->gravity();   // gravity move player down
      effect();       // interactions with tiles
      healthupdate(); // update player HP
      movePlayer();   // update player location
      p->display();   // show player
      update_stat(p->level, p->health); // update stat window data

      // move and show every alive tiles, and show the player too
      for (const auto& tile : tiles){
        tile->move();
        tile->display();
        p->display();
      }

      // game box with spikes from ceiling
      wborder(playwin, 0, 0, 'V', 0, 0, 0, 0, 0);
      // box for other windows
      box(statwin,0,0);
      box(instwin,0,0);

      refresh();
      usleep(DELAY); // delay between movements, defined in common.h
    }

    // update stat window with player lvl and hp
    void update_stat(int level, int health) {

      box(statwin, 0, 0);
      mvwprintw(statwin, 0, 6 , "# STATS #");
	    mvwprintw(statwin, 2, 5, "HEALTH : %i", health);
	    mvwprintw(statwin, 4, 5, "LEVEL : %i", level);
      // mvwprintw(statwin, 6, 5, "DIFFICULTY : %i", diff);

    }

    // Draw the instruction window
    void update_inst(){
      box(instwin,0,0);
      mvwprintw(instwin, 2, 2, "Controls :");
	    mvwprintw(instwin, 3, 2, "Move Left -> Left arrow key");
	    mvwprintw(instwin, 4, 2, "Move Right -> Right arrow key");
	    mvwprintw(instwin, 5, 2, "Quit game -> %c", QUIT);
      mvwprintw(instwin, 6, 2, "blue normal tile:");
      mvwprintw(instwin, 7, 2, "red spike tile: -3 hp");
      mvwprintw(instwin, 8, 2, "green spring tile: bouncy");
      mvwprintw(instwin, 9, 2, "yellow fragile tile : trap block that breaks");
      mvwprintw(instwin, 10, 2, "white left conveyer tile: pushes left");
      mvwprintw(instwin, 11,2, "magenta right conveyer tile: pushes right");
    }



    // generate tiles psuedo-randomly
    void addTile(){
      // chance of hostile tiles spawning increases as time goes on

      // f(x) = 59 e^{-\frac{x}{100}}\ +40
      levelCoeff = 59 * exp(-(p->level)/100) + 40; // from 99 to 40
      speed = 0.002 * p->level + 0.15;        // speed from 0.15 to 0.3
      int seed = rand() % levelCoeff;         // rand from 99 to 40, upperbound drops over time
      tileSpawnX = rand() % (MAX_X - BWIDTH); //random xpos for platforms

      if (seed > 50){         // 50% Normal
        tiles.emplace_back(new Tile(tileSpawnY,tileSpawnX,speed));
      } else if (seed > 40){  // 10% Spring
        tiles.emplace_back(new SpringTile(tileSpawnY,tileSpawnX,speed));
      } else if (seed > 25){  // 5% RConveyerTile
        tiles.emplace_back(new RConveyerTile(tileSpawnY,tileSpawnX,speed));
      } else if (seed > 20){  // 5% LConveyerTile
        tiles.emplace_back(new LConveyerTile(tileSpawnY,tileSpawnX,speed));
      } else if (seed > 15){  // 15% Fragile
        tiles.emplace_back(new FragileTile(tileSpawnY,tileSpawnX,speed));
      } else {                // 15% Spike
        tiles.emplace_back(new SpikeTile(tileSpawnY,tileSpawnX,speed));
      }

    }

    // remove dead tiles
    void clearDeadTiles(){
      // delete all dead tiles an iterator using Erase-Remove Idiom
      tiles.erase(remove_if(tiles.begin(), tiles.end(),
                  [](auto& tile) // C++14: auto in lambda
                  {return tile->isDead;}),
                  tiles.end());
    }

    // Check player and tile collisions
    // return the first tile in collision with player, else return NULL
    Tile* collisionsCheck(){

      if (p->invincibleCount > 0){// player invincible, no collision allowed
        p->invincibleCount -= 1;
        return NULL; // no collisions at all
      }


      for (auto& tile: tiles){
        double tileMaxY = tile->y + tile->height;
        double tileMaxX = tile->x + tile->width;
        if (p->y >= tileMaxY || // player Top is LOWER than tile bottom
            p->x >= tileMaxX || // player LEFT > tile RIGHT
            tile->y >= (p->y+p->height) || // Tile top is UNDER player bottom
            tile->x >= (p->x + p->width))
            continue; // no collision
        else {
          return tile.get(); // return RAW pointer to tile
        }
      }
      return NULL;
    }




    // mechanics of the tiles
    void effect(){
      Tile* t = collisionsCheck();
      // constansts defined from common.h
      if (t != NULL ){
        // spring tile bounces player upwards by 3 after some delay
        if (t -> type == SPRING && t->touchCount >= 10){
          p->velocity[Y] -= 3;
          t->touchCount = 0; // reset delay
        }
        // fragile tile breaks after some delay
        if (t -> type == FRAGILE && t->touchCount >= 20){
            t -> isDead = 1; // dies after breaking
        }
        // left conveyer tile sets velocity to 0.2 units leftwards
        if (t -> type == LCONVEYER){
          p->velocity[X] -= 0.2;
        }
        // right conveyer tile sets velocity to 0.2 unit rightwards
        if (t -> type == RCONVEYER){
          p->velocity[X] += 0.2;
        }
      }
    }


    // update health of player
    void healthupdate()
    {
      Tile* t= collisionsCheck();

      // kill player if out of bound
      if (p -> y > MAX_Y + 10){
        p->health = 0;
      }


      // end function if no collision
      if (t == NULL) return;

      // Increment delay for spring and fragile tiles effect activation
      if (t->type == SPRING || t->type == FRAGILE) t->touchCount += 2;

      // if player standing on a tile which was not stood on previously
      if (t->isTouched != 1){

        t->isTouched = 1;       // mark as touched
        p->level += 1;          // add score

        if (t -> type == SPIKE){// spike tiles
            p->hurtFlashCount += 30; // indicate hurt, player will change color for 10 counts
            p->health -= 3;     // damage
        } else {                // other tiles
          if (p->health < MAX_HEALTH){
            (p->health)++;      // heal
          }
        }

      }

    }


    // set player new coordinates from velocity
    void movePlayer(){
      p->x += p->velocity[X];
      p->y += p->velocity[Y];
      Tile* t = collisionsCheck();
      if (t != NULL){
          // if falling down
        if (p->velocity[Y] > 0){
          // set playerDown = tileTop
          // i.e. playerY + playerH = tileY
          // move player back to tile top
          p->y = t->y - p->height;
        }

      }
    }


};




#endif
