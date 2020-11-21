/* ------------------------------------
 *               tile.h
 * ------------------------------------
 * Tile objects that goes up from the bottom.
 * there are different types with different behaviours
 *
 *  Normal tiles:   heal 1 hp, not hostile
 *  Spike  tiles:   -3hp. become more common as score goes up
 *  Spring tiles:   bouncy, +1HP per bounce. rare for higher difficulties
 *  fragile tiles:  just let u stand for ~1s then break
 *  conveyer tiles: constantly pushes u < or > and + 1 hp. 
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
    virtual void display(); // display tile with sprite. virtual: polymorphism for subclasses
    void move();

    bool isDead = 0;        // toggled when out-of-bound, or when fragile is stepped on
    bool isTouched = 0;     // whether the tile has been touched, for hp/score calculation
    int touchCount = 0;     // for spring and fragile tile effect delay
    int x, width = 15, height = 2;
    double y;               // decimals for better speed calculation
    int type;               // type of tile. defined in common.h
    WINDOW * boxWin;        // the window of box


  private:

    double g = 3;         // gravity constant
    double speed;         // speed of tile

};

Tile::Tile(double y_, int x_, double speed_)
{
  y = y_;
  x = x_;
  boxWin = newwin(height,width,y,x); // create window for tiles
  speed = speed_;
  init_pair(6, COLOR_BLUE, COLOR_BLACK); // set colour
  wattron(boxWin,COLOR_PAIR(6));
  type = 1;
  
}

Tile::~Tile()
{
  wborder(boxWin, ' ', ' ', ' ',' ',' ',' ',' ',' '); // remove outline
  wrefresh(boxWin);
	delwin(boxWin); //deallocate memory
}

void Tile::display()
{
  
  mvwin(boxWin, y, x); // move tile to current location
  box(boxWin,0,0); // normal tile: display as a box.
  wrefresh(boxWin);

}

void Tile::move()
{
  if (!isDead) y -= speed; // make the tiles go up
  
  if (y <= YLIMIT + 1){
    isDead = 1; //true, will be deconstructed
  }
  
}

class SpikeTile : public Tile     // inherite properties from the Tile class  
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
      
      mvwin(boxWin, y, x); // move boxwin to current xy
      
      wborder(boxWin, 0, 0, '^', 0, 0, 0, 0, 0); //spike box
      
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
      
      mvwin(boxWin, y, x); // move boxwin to current xy
      box(boxWin,0,0);
      mvwprintw(boxWin,0,0,"_______________");
      mvwprintw(boxWin,1,0,"___Ξ_Ξ_Ξ_Ξ_Ξ___"); //Spring box 
      

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
      
      mvwin(boxWin, y, x); // move boxwin to current xy
      
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
