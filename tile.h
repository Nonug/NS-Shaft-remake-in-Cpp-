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
    int type;
    WINDOW * boxWin;

  private:

    int delay;

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
  type = 1;
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

class SpikeTile : public Tile
{
  public:
    SpikeTile(double y_, int x_, double speed_) : Tile(y_, x_, speed_)
    {
      init_pair(2, COLOR_RED, COLOR_BLACK); // set colour
      wattron(boxWin,COLOR_PAIR(2));
      type = 2;
    }

    void display()
    {
      // box(curwin,y,x);
      mvwin(boxWin, y, x); // move boxwin to current xy
      // wattron(boxWin,COLOR_PAIR(2));
      // box(boxWin,0,0);
      wborder(boxWin, 0, 0, '^', 0, 0, 0, 0, 0); //spike box
      // wattroff(COLOR_PAIR(2));
      wrefresh(boxWin);
    }

};

class SpringTile : public Tile
{
  public:
    SpringTile(double y_, int x_, double speed_):Tile(y_, x_, speed_)
    {
      init_pair(3, COLOR_GREEN, COLOR_BLACK); // set colour
      wattron(boxWin,COLOR_PAIR(3));
      type = 3;
    }

    void display()
    {
      // box(curwin,y,x);
      mvwin(boxWin, y, x); // move boxwin to current xy
      box(boxWin,0,0);
      mvwprintw(boxWin,0,0,"_______________");
      mvwprintw(boxWin,1,0,"___Ξ_Ξ_Ξ_Ξ_Ξ___"); //Ϫ Ӿ
      // mvwprintw(boxWin,1,0,"≥≤≥≤≥≤≥≤≥≤≥≤≥≤");
      // mvwprintw(boxWin,2,0,"_______________");
      // wborder(boxWin,0,0,'v','^',0,0,0,0);

      wrefresh(boxWin);

    }


};

class FragileTile : public Tile
{
  public:
    FragileTile(double y_, int x_, double speed_):Tile(y_, x_, speed_)
    {
      init_pair(4, COLOR_YELLOW, COLOR_BLACK); // set colour
      wattron(boxWin,COLOR_PAIR(4));
      type = 4;
    }

    void display()
    {
      // box(curwin,y,x);
      mvwin(boxWin, y, x); // move boxwin to current xy
      // box(boxWin,0,0);
      wborder(boxWin, 0, 0, '-', '-', 0, 0, 0, 0); //spike box
      wrefresh(boxWin);

    }


};

class LConveyerTile : public Tile
{
  public:
    // constructor: super()
    int count = 0;
    LConveyerTile(double y_, int x_, double speed_):Tile(y_, x_, speed_)
    {
      wattroff(boxWin,COLOR_PAIR(6)); // turn off default colour
      init_pair(0, COLOR_BLACK, COLOR_WHITE); // set colour
      wattron(boxWin,COLOR_PAIR(0));
      type = 5;
    }

    void display()
    {
      // box(curwin,y,x);
      mvwin(boxWin, y, x);
      box(boxWin, 0, 0); //left conveyer
      if (count < 5){  // switch sprite every 5 count
        mvwprintw(boxWin,0,1,"⊂--⊂--⊂--⊂--⊂");
        mvwprintw(boxWin,1,1,"-⊃--⊃--⊃--⊃--");
        count++;
      } else if (count < 10){
        mvwprintw(boxWin,0,1,"--⊂--⊂--⊂--⊂-");
        mvwprintw(boxWin,1,1,"--⊃--⊃--⊃--⊃-");
        count++;
      } else {
        mvwprintw(boxWin,0,1,"-⊂--⊂--⊂--⊂--");
        mvwprintw(boxWin,1,1,"⊃--⊃--⊃--⊃--⊃");
        count = (count > 15)? 0 : count + 1;
      }
      wrefresh(boxWin);

    }


};
// subclass of L conveyer
class RConveyerTile : public LConveyerTile
{
  public:
    // constructor: super()
    RConveyerTile(double y_, int x_, double speed_):LConveyerTile(y_, x_, speed_)
    {
      init_pair(5, COLOR_MAGENTA, COLOR_BLACK); // set colour
      wattron(boxWin,COLOR_PAIR(5));
      type = 6;
    }

    void display()
    {
      // box(curwin,y,x);
      mvwin(boxWin, y, x);
      box(boxWin, 0, 0); //right conveyer
      if (count < 5){  // switch sprite every 5 count
        mvwprintw(boxWin,1,1,"⊂--⊂--⊂--⊂--⊂");
        mvwprintw(boxWin,0,1,"-⊃--⊃--⊃--⊃--");
        count++;
      } else if (count < 10){
        mvwprintw(boxWin,1,1,"--⊂--⊂--⊂--⊂-");
        mvwprintw(boxWin,0,1,"--⊃--⊃--⊃--⊃-");
        count++;
      } else {
        mvwprintw(boxWin,1,1,"-⊂--⊂--⊂--⊂--");
        mvwprintw(boxWin,0,1,"⊃--⊃--⊃--⊃--⊃");
        count = (count > 15)? 0 : count + 1;
      }
      wrefresh(boxWin);

    }
};

#endif
