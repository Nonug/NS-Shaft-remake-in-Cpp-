
#include "common.h"
#include "tile.h"
#include "player.h"
#include "spikeTile.h"

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
    vector<unique_ptr<Tile>> tiles;
    Player* p;

    Manager(){
      playwin = newwin(37,MAX_X, 5 , 1); // playing window
       nodelay(playwin, true);
      p = new Player(playwin,6,20);
    }

    void display(){

      clear();

      refresh();
      wrefresh(playwin);
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

      // for (int i = 0 ; i < 4;i++)
      // mvprintw(4,1+i*15,"|23456789abced|");


      refresh();
      usleep(DELAY); // Shorter delay between movements
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

      }
      //call destructor here, game ending screen
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
                  [](auto& tile)
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

    void movePlayer(){
      p->x += p->velocity[X];
      Tile* t= collisionsCheck();
      if (t != NULL){                  // TODO: fix the clipping issues
          if (p->velocity[X] > 0){
            // playerR = tileL
            // playerX + playerW = tileX
            // p->x = t->x - p->width;

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
