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
    // these are public for manager
    double x, y;
    double velocity[2] = {0,0}; // (y,x) velocity
    
    int height = 2, width = 2;  // size of the player
    int health = MAX_HEALTH;    // default hp   
    int level = 0;              // default lv
    int invincibleCount = 0;    // increased if hit ceiling, allow phasing through tiles and count down back to 0
    int hurtFlashCount = 0;     // increased when hurt, change colour to red until count back to 0
    int spriteCount = 0;     // count down to alternate between walking sprites

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
  
}

// Destructor : release memory
Player::~Player()
{
  delwin(curwin);
}

void Player::mvleft()
{ // set to negative speed so player moves to the left
  velocity[X] = -speed;

  // Stops the player from going pass the playwin
  if(x - speed < 1 + offset) // offset: adjust for shift of sprite
  {
    x = 1 + offset;
    velocity[X] = 0; // reset velocity (is this necessary?)
  }
  
  spriteCount--;
  if (spriteCount > 5){ // alternate between 2 moving spirtes
    currentSprite = movingLDown;
  } else {
    currentSprite = movingLUp;
    if (spriteCount <= 0) spriteCount = 10;
  }
}

void Player::mvright()
{
  velocity[X] = speed;

  // Stops the player from going pass the playwin
  if (x + speed + width > MAX_X - offset - 1) // offset: adjust for shift of sprite
  {
    x = MAX_X - width - offset - 1;
    velocity[X] = 0; // reset velocity (is this necessary?)
  }

  spriteCount--;
  if (spriteCount > 5){ // alternate between 2 moving spirtes
    currentSprite = movingRDown;
  } else {
    currentSprite = movingRUp;
    if (spriteCount <= 0) spriteCount = 10;
  }

}

void Player::gravity()
{
    velocity[Y] = g;
}



// display the player in its current position
void Player::display()
{


  if (y < YLIMIT){ // Prevent clipping out of ceiling
    y = YLIMIT + 1; // set y below ceiling
    invincibleCount = 25; // 5 frames of no collision
    hurtFlashCount += 30;
    health -= 3; //lose hp
  };

  init_pair(9, COLOR_RED, COLOR_BLACK); // player flash colour if hurt
  if (hurtFlashCount > 0){
    hurtFlashCount--;
    if (10 < hurtFlashCount < 20) attron(COLOR_PAIR(9)); // flash red
  }

  mvprintw(y,x-offset,(*currentSprite).c_str());
  mvprintw(y+1,x+3-offset,(*++currentSprite).c_str()); // point sprite[1]
  attroff(COLOR_PAIR(9));
  currentSprite--;  // point sprite[0]
  velocity[X] = 0;
  velocity[Y] = 0;
}


#endif
