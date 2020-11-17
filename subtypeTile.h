/* ------------------------------------
 *               SpikeTile.H
 * ------------------------------------
 * contain subclasses of tile
 * SpikeTile, SpringTile, FragileTile, LConveyerTile, RConveyerTile
 * polymorphism time
 *
 * ------------------------------------
 */


#include "common.h" // relocate incldues and global var
#include "tile.h"

#ifndef _SPIKETILE_H_
#define _SPIKETILE_H_


class SpikeTile : public Tile
{
  public:
    SpikeTile(double y_, int x_, double speed_) : Tile(y_, x_, speed_)
    {
      init_pair(2, COLOR_RED, COLOR_BLACK); // set colour
      wattron(boxWin,COLOR_PAIR(2));
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
      // init_pair(5, COLOR_GREEN, COLOR_GREEN); // set colour
      // wattron(boxWin,COLOR_PAIR(3));
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
