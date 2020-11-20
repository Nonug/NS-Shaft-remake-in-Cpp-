#include "common.h"
#include "tile.h"
#include "player.h"
#ifndef _MANAGER_H_
#define _MANAGER_H_

// main: game.run()
//
// game: create player, create tile,
//      constructor: call create funct
//      run(): running = 1;
//            while running
//                start time count
//                inputPhase, update, drawphase
//                calculate elasped time, set fps
//
//
//  physics: collisionsCheck, movePlayer
//  entity control: addTile, clearDeadTiles
//  main game control: display, run, getInput
//
//
// event/entity/physics manager?
class Manager
{
  public:
    double tileSpawnY = MAX_Y - BHEIGHT + 5; // y of spawnpt of tile
    int tileSpawnX = rand() % 60 + 1; //random xpos for tiles
    double speed = 0.15; // speed of tiles
    double spawnTileDelay = 0.8 ;

    bool running = 1; // while game run



    WINDOW* playwin;
    WINDOW* statwin; //!
    WINDOW* instwin;
    vector<unique_ptr<Tile>> tiles;
    Player* p;
    int diff = 1;
    int difficulty = 100;

    Manager(){
      playwin = newwin(MAX_Y,MAX_X, 5 , 1); // playing window
      statwin = newwin(9,24,5,MAX_X+4); //statistics window!
      instwin = newwin(14,55,15, MAX_X+4);
       nodelay(playwin, true);
      p = new Player(playwin,6,20);
    }


    void display(){

      clear();

      refresh();
      wrefresh(playwin);
      wrefresh(statwin); //!
      wrefresh(instwin);
      // wrefresh(playwin);

      getInput(); //read user input
      p->gravity();
      effect();
      movePlayer();
      p->display();

      for (const auto& tile : tiles){
        tile->move();
        tile->display();
        p->display();
      }

      box(playwin,0,0);
      box(statwin,0,0);//!
      box(instwin,0,0);

      // for (int i = 0 ; i < 4;i++)
      // mvprintw(4,1+i*15,"|23456789abced|");


      refresh();
      usleep(DELAY); // Shorter delay between movements
    }

    void update_stat(int level, int health, int diff) {
      box(statwin, 0, 0);
	    mvwprintw(statwin, 2, 5, "HEALTH : %i", health);
      // wmove(statwin, 3, 5);                // HP bar
      // for (int i = 0; i < health; i++){
      //   waddch(statwin, 'o');
      // }
	    mvwprintw(statwin, 4, 5, "LEVEL : %i", level);
      mvwprintw(statwin, 6, 5, "DIFFICULTY : %i", diff);
	    mvwprintw(statwin, 0, 6 , "# STATS #");
    }

    void update_inst(){
      box(instwin,0,0);
      mvwprintw(instwin, 2, 2, "Controls :");
	    mvwprintw(instwin, 3, 2, "Move Left -> Left arrow key");
	    mvwprintw(instwin, 4, 2, "Move Right -> Right arrow key");
	    mvwprintw(instwin, 5, 2, "Quit game -> %c", control_quit);
      mvwprintw(instwin, 6, 2, "blue normal tile:");
      mvwprintw(instwin, 7, 2, "red spike tile: -3 hp");
      mvwprintw(instwin, 8, 2, "green spring tile: bouncy");
      mvwprintw(instwin, 9, 2, "yellow fragile tile : trap block that breaks");
      mvwprintw(instwin, 10, 2, "white left conveyer tile: pushes left");
      mvwprintw(instwin, 11,2, "magenta right conveyer tile: pushes right");
    }


    void run(){

      using clock = chrono::system_clock;
      using sec = chrono::duration<double>;
      auto before = clock::now();
      auto timelimit = spawnTileDelay * chrono::seconds{1};
      srand(time(0)); //set rand seed
      while(running)
      {
        first_tile();
        if (clock::now() - before > timelimit)
        {
          before = clock::now();
          addTile();

        }
        clearDeadTiles();
        display();
        healthupdate();
        update_stat(p->level, p->health, diff);
        update_inst();
        checkseed(p->level);
        if (p->health <= 0)
        {
          running = 0;
        }

      }
      //deconstructor here
    }

    // generates the first tile under player
    // so that player don't fall out of the screen at the beginning
    void first_tile(){
      if (p->first_tile != 1){
        tiles.emplace_back(new Tile(tileSpawnY, 17, speed));
        p->first_tile = 1;
      }

    }
    // generate tiles psuedo-randomly
    void addTile(){
      // chance of hostile tiles spawning increases as time goes on

      int seed = rand() % difficulty; // rand from 0 to 99, upperbound drops over time
      tileSpawnX = rand() % (MAX_X - BWIDTH); //random xpos for platforms
      if (seed > 50){         // 50% Normal
        tiles.emplace_back(new Tile(tileSpawnY,tileSpawnX,speed));
      } else if (seed > 40){  // 10% Spring
        tiles.emplace_back(new SpringTile(tileSpawnY,tileSpawnX,speed));
      } else if (seed > 25){  // 15% Fragile
        tiles.emplace_back(new FragileTile(tileSpawnY,tileSpawnX,speed));
      } else if (seed > 20){  // 5% RConveyerTile
        tiles.emplace_back(new RConveyerTile(tileSpawnY,tileSpawnX,speed));
      } else if (seed > 15){  // 5% LConveyerTile
        tiles.emplace_back(new LConveyerTile(tileSpawnY,tileSpawnX,speed));
      } else {                // 0 - 14 : Spike (15%)
        tiles.emplace_back(new SpikeTile(tileSpawnY,tileSpawnX,speed));
      }

    }

    void clearDeadTiles(){
      // remove dead tiles
      // with an iterator using Erase-Remove Idiom
      tiles.erase(remove_if(tiles.begin(), tiles.end(),
                  [](auto& tile) // C++14: auto in lambda
                  {return tile->isDead;}),
                  tiles.end());
    }


    Tile* collisionsCheck(){
      for (auto& tile: tiles){
        double tileMaxY = tile->y + tile->height;
        double tileMaxX = tile->x + tile->width;
        if (p->y >= tileMaxY || // player Top is LOWER than tile bottom
            p->x >= tileMaxX || // player LEFT > tile RIGHT
            tile->y >= (p->y+p->height) || // Tile top is UNDER player bottom
            tile->x >= (p->x + p->width))
            continue; // no collision
        else {
          p->inAir = 0; // has collision
          // tile->isTouched = 1; relocated to hpupdate
          return tile.get(); // return RAW pointer to tile
        }
      }
      p->inAir = 1; // collisions at all
      return NULL;
    }


    // change the difficulty as the level increases
    // as the random function works as follow
    // rand() % (max - min + 1) + min
    // where the generated number would be in range min <= x <= max
    void checkseed(int level){
      if (level%10 == 0 && level/10 == 1 && p->diff2 != 1){
        p->diff2 = 1;
        difficulty = 91;  // rand from 0 to 90
        diff += 1;
      }
      if (level%20 == 0 && level/10 == 2 && p->diff3 != 1){
        p->diff3 = 1;
        difficulty = 86; // rand from 0 to 85
        diff += 1;
      }
      if (level%30 == 0 && level/10 == 3 && p->diff4 != 1){
        p->diff4 = 1;
        difficulty = 81; // rand from 0 to 80
        diff += 1;
      }
      if (level%40 == 0 && level/10 == 4 && p->diff5 != 1){
        p->diff5 = 1;
        difficulty = 76; // ramd from 0 to 75
        diff += 1;
      }
    }

    // effects of the tiles
    void effect(){
      Tile* t = collisionsCheck();
      if (t != NULL){
        // spring tile bounces upwards by 3 after some delay
        if (t -> type == SPRING && t->touchCount >= 10){
          p->velocity[Y] -= 3;
          t->touchCount = 0; // reset delay
        }
        // fragile tile are trap blocks that breaks after some delay
        if (t -> type == FRAGILE && t->touchCount >= 20){
            t -> isDead = 1;
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



    void healthupdate()
    {
      Tile* t= collisionsCheck();

      // kill player if out of bound
      if (p -> y > MAX_Y + 10){
        p->health = 0;
      }

      if (t == NULL) return;

      // increment delay for spring and fragile tiles effect activation
      if (t->type == SPRING || t->type == FRAGILE) t->touchCount += 2;

      // if player standing on a tile and the tile is not being standed on previously
      if (t->isTouched != 1){

        t->isTouched = 1;       // mark as touched
        p->level += 1;          // add score

        if (t -> type == SPIKE){// spike tiles
            p->health -= 3;
        } else {                // other tiles
          if (p->health < MAX_HEALTH){
            (p->health)++;         // heal
          }
        }

      }

    }



    void movePlayer(){
      p->x += p->velocity[X];
      Tile* t= collisionsCheck();
      if (t != NULL){
          if (p->velocity[X] > 0){
            // playerR = tileL
            // playerX + playerW = tileX
            //p->x = t->x - p->width;

          }
          if (p->velocity[X] < 0){
            // playerL = tileR
            // p->x = t->x + t->width;
          }
      }

      p->y += p->velocity[Y];
      t = collisionsCheck();
      if (t != NULL){
          // if fall down
        if (p->velocity[Y] > 0){
          // playerDown = tileTop
          // playerY + playerH = tileY
          p->y = t->y - p->height;
        }

      //   if (p->velocity[Y] < 0)
      //     // playerTop = tileDown
      //     y = tile->y + tile->height;
      // }
      // p->velocity[X] = 0;
      // p->velocity[Y] = 0;
      }
    }

    int getInput(){
      int choice = getch();
      switch(choice)
      {
        case KEY_LEFT:
          p->mvleft();
          break;
        case KEY_RIGHT:
          p->mvright();
          break;
        case 'q':
          running = 0; //TODO define and call destructors
          break;
        default:
          // p->velocity[X] = 0;
          break;
      }
      return choice;
    }
};




#endif
