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

    Manager(){
      playwin = newwin(MAX_Y,MAX_X, 5 , 1); // playing window
      statwin = newwin(9,21,5,MAX_X+4); //statistics window!
      instwin = newwin(14,50,15, MAX_X+4);
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

    void update_stat(int level, int health) {
      box(statwin, 0, 0);
	    mvwprintw(statwin, 2, 5, "HEALTH : %d", health);
	    mvwprintw(statwin, 4, 5, "LEVEL : %d", level);
	    mvwprintw(statwin, 0, 6 , "# STATS #");
    }

    void update_inst(){
      box(instwin,0,0);
      mvwprintw(instwin, 2, 2, "Controls :");
	    mvwprintw(instwin, 3, 2, "Move Left -> Left arrow key");
	    mvwprintw(instwin, 4, 2, "Move Right -> Right arrow key");
	    mvwprintw(instwin, 5, 2, "Quit game -> %c", control_quit);
      mvwprintw(instwin, 6, 2, "blue normal tile: +1 hp");
      mvwprintw(instwin, 7, 2, "red spike tile: -5 hp");
      mvwprintw(instwin, 8, 2, "green spring tile: bouncy, +1 hp");
      mvwprintw(instwin, 9, 2, "yellow fragile tile: breaks after 1 second");
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

        if (clock::now() - before > timelimit)
        {
          before = clock::now();
          addTile();

        }
        clearDeadTiles();
        display();
        healthupdate();
        update_stat(stats.LEVEL, stats.HEALTH);
        update_inst();
        effect();
        if (stats.HEALTH == 0)
        {
          running = 0;
        }

      }
      //deconstructor here
    }

    // generate tiles psuedo-randomly
    void addTile(){
      // maybe seed shrinks for higher difficulties/when score is high?

      int seed = rand() % 100; // rand from 0 to 99
      tileSpawnX = rand() % (MAX_X - BWIDTH); //random xpos for platforms
      if (seed > 50){
        tiles.emplace_back(new Tile(tileSpawnY,tileSpawnX,speed));
      } else if (seed > 40){
        tiles.emplace_back(new SpikeTile(tileSpawnY,tileSpawnX,speed));
      } else if (seed > 30){
        tiles.emplace_back(new FragileTile(tileSpawnY,tileSpawnX,speed));
      } else if (seed > 20){
        tiles.emplace_back(new RConveyerTile(tileSpawnY,tileSpawnX,speed));
      } else if (seed > 10){
        tiles.emplace_back(new LConveyerTile(tileSpawnY,tileSpawnX,speed));
      } else {
        tiles.emplace_back(new SpringTile(tileSpawnY,tileSpawnX,speed));
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
            continue;
        else {
          p->inAir = 0;
          return tile.get();
        }
      }
      p->inAir = 1;
      return NULL;
    }

    // effects of the tiles, fragile tiles not added yet
    void effect(){
      Tile* t = collisionsCheck();
      if (t != NULL){
        // spring tile bounces upwards by 10 
        if (t -> type == 3){
          p -> y -= 10;
        }
        if (t -> type == 4){
            t -> isDead = 1;
        }
        // left conveyer tile pushes 6 units to left
        if (t -> type == 5){
          p -> x -= 6;
        }
        // right conveyer pushes 6 units to right
        if (t -> type == 6){
          p -> x += 6;
        }
      }
    }


    // count the players health and increase a level when landing on a tile
    // haven't made the level stop increasing constantly on one tile yet
    // haven't solved the instant dying issue
    void healthupdate()
    {
      bool ontile = 0;
      Tile* t= collisionsCheck();
      if (t != NULL){
        ontile = 1;
      }
      if(ontile == 1){
        //normal tile
         if (t -> type == 1)
        {
          if (stats.HEALTH < MAX_HEALTH){
            stats.HEALTH++;
          }
          stats.LEVEL += 1;
        }
        //spike tile
        if (t -> type == 2)
        {
          stats.HEALTH -= 5;
          stats.LEVEL += 1;
        }
        //spring tile
        if (t -> type == 3)
        {
          if (stats.HEALTH < MAX_HEALTH){
            stats.HEALTH++;
          }
          stats.LEVEL += 1;
        }
        //right conveyer tile
        if (t -> type == 5)
        {
          if (stats.HEALTH < MAX_HEALTH){
            stats.HEALTH++;
          }
          stats.LEVEL += 1;
        }
        //left conveyer tile
        if (t -> type == 6)
        {
          if (stats.HEALTH < MAX_HEALTH){
            stats.HEALTH++;
          }
          stats.LEVEL += 1;
        }
      }
      /*if (p -> y > MAX_Y){
        stats.HEALTH = 0;
      }*/
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
          p->velocity[X] = 0;
          break;
      }
      return choice;
    }
};




#endif
