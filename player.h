/* ------------------------------------
 *               PLAYER.H
 * ------------------------------------
 *  Player class for the game.
 *
 *
 * ------------------------------------
 *
 */

 // TODO: HP, isDead, destructor
 //       onStepBlock (trigger for +HP/-HP)
 //       count score (maybe do that on manager. every second = 1 score?)

#include "common.h" // relocate includes and global var

#ifndef _PLAYER_H_
#define _PLAYER_H_

const int X = 1;
const int Y = 0;

class Player
{
  public:
    // too lazy to make setters and getters instead of making variables public
    // these are public for manager
    double x, y;
    double velocity[2] = {0,0}; // (y,x) velocity
    bool inAir = 0;             // is player in air? (maybe useful for defining onStepBlock)
    int height = 2, width = 2;  // size of the player
    int health = MAX_HEALTH;            // default hp   TODO: fix double digit issue
    int level = 0;              // default lv
    bool diff2 = 0;            //indicator of difficulty 2
    bool diff3 = 0;            //indicator of difficulty 3
    bool diff4 = 0;            //indicator of difficulty 4
    bool diff5 = 0;            //indicator of difficulty 5, which is the maximum
    bool first_tile = 0;       //indicator of whether the first tile is created

    Player(WINDOW * win, double yc, double xc);
    ~Player();

    void mvleft();
    void mvright();
    void display();
    void gravity();
    void move();


  private:
    // sprites
    string init[2]  = {"┏(^o^)┓","┃┃"};
    string stopL[2] = {"┏(^o^ )┓","┃┃"};
    string stopR[2] = {"┏( ^o^)┓","┃┃"};
    string movingLUp[2] = {"┏(^o^ )┛","┛┏"};
    string movingLDown[2] = {"┗(^o^ )┓","┏┗"};
    string movingRUp[2] = {"┗( ^o^)┓","┓┗"};
    string movingRDown[2] = {"┏( ^o^)┛","┛┓"};
    // string jumpL[2] = {"┗(^o^ )┛","┗┃"};    TODO: maybe implement this if have spare time
    // string jumpR[2] = {"┗( ^o^)┛","┃┛"};
    string *currentSprite = init;   // current sprite. for display()


    int offset = 2;   // render the sprite 2 units to the left
    double g = 0.5;   // gravity
    double speed = 1; // horizontal speed
    WINDOW * curwin;  // the window that player is drawn on

};

//Constructor for player.
Player::Player(WINDOW * win, double yc, double xc)
{
  curwin = win;
  y = yc;
  x = xc;
  // keypad(curwin, true); // is this necessary?
}

// Destructor TODO
Player::~Player()
{
  // currentSprite->NULL;
  // curwin->NULL;
}

void Player::mvleft()
{
  velocity[X] = -speed;

  // maybe relocate this to manager (physics control)
  // Stops the player from going pass the playwin
  if(x - speed < 1 + offset) // offset: adjust for shift of sprite
  {
    x = 1 + offset;
    velocity[X] = 0; // reset velocity (is this necessary?)
  }
  // currentSprite = (inAir)? jumpL : stopL; // this aint working properly
  if (currentSprite == movingLUp){ // alternate between 2 moving spirtes
    currentSprite = movingLDown;
  } else {
    currentSprite = movingLUp;
  }
}

void Player::mvright()
{
  velocity[X] = speed;

  // maybe relocate this to manager (physics control)
  // Stops the player from going pass the playwin
  if (x + speed + width > MAX_X - offset - 1) // offset: adjust for shift of sprite
  {
    x = MAX_X - width - offset - 1;
    velocity[X] = 0; // reset velocity (is this necessary?)
  }

  // currentSprite = (inAir)? jumpR : stopR; // this aint working properly
  if (currentSprite == movingRUp){
    currentSprite = movingRDown;
  } else {
    currentSprite = movingRUp;
  }

  // display(stopR);
  // if(x > xMax-1)
  //   x = xMax-1;
}

void Player::gravity()
{
    velocity[Y] = g;
}



// display the player in its current position
void Player::display()
{
  // mvwaddch(curwin, y, x, spite);

  if (y < YLIMIT) y = YLIMIT + 1;    // Prevent clipping out of ceiling
  /*if (y > MAX_Y + 2) y = YLIMIT + 1;*/ // falls out of scrn: teleport back
                                     // maybe relocate this to manager
                                     // placeholder for testing. TODO: trigger dead

  init_pair(1, COLOR_RED, COLOR_BLACK); // TODO: make player flash colour if hurt
  attron(COLOR_PAIR(1));
  mvprintw(y,x-offset,(*currentSprite).c_str());
  mvprintw(y+1,x+3-offset,(*++currentSprite).c_str()); // point sprite[1]
  attroff(COLOR_PAIR(1));
  currentSprite--;  // point sprite[0]
  velocity[X] = 0;
  velocity[Y] = 0;
}


#endif
