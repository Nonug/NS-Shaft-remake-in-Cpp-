/* ------------------------------------
 *               tile.h
 * ------------------------------------
 * Tile objects that goes up from the bottom.
 * there are different types with different behaviours
 *
 *  Normal tiles:   heal 1 hp, not hostile
 *  Spike  tiles:   -5hp. (= -6hp and heal+1) become more common as score goes up
 *  Spring tiles:   bouncy, +1HP per bounce. rare for higher difficulties
 *  fragile tiles:  just let u stand for ~1s then break
 *  conveyer tiles: constantly pushes u < or >. (maybe change player speed if on it?)
 * ------------------------------------
 */


#include "common.h" // relocate includes and global var

#ifndef _TILE_H_
#define _TILE_H_


class Tile
{
  public:
    Tile(double y_, int x_, double speed_);
    ~Tile();
    virtual void display();
    void move();
    int isDead = 0;
    int x, width = 15, height = 2;
    double y; // decimals for better speed calculation
    WINDOW * boxWin;

  private:

    int type, delay;

    double g = 3, gsum = 0;  // gsum: aggregate g for each frame, if > 1, fall
    double speed;

};

Tile::Tile(double y_, int x_, double speed_)
{
  y = y_;
  x = x_;
  boxWin = newwin(height,width,y,x);
  speed = speed_;
  init_pair(6, COLOR_BLUE, COLOR_BLACK); // set colour
  wattron(boxWin,COLOR_PAIR(6));
  // getmaxyx(curwin, height, width);
}

Tile::~Tile()
{
  wborder(boxWin, ' ', ' ', ' ',' ',' ',' ',' ',' '); // remove outline
  wrefresh(boxWin);
	delwin(boxWin); //deallocate memory
}

void Tile::display()
{
  // box(curwin,y,x);
  mvwin(boxWin, y, x);
  box(boxWin,0,0); // normal tile: display as a box.
  wrefresh(boxWin);

}

void Tile::move()
{
  if (!isDead) y -= speed;
  // if (isDead) y += speed;
  if (y <= YLIMIT){
    isDead = 1; //true
  }
  // if (y >= 50) isDead = 0;

  // y += speed; // goes off screen. wait for destruction
}

#endif
