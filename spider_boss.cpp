#include "spider_boss.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

SpiderBoss::SpiderBoss (float x, float y) : Enemy(2, 2) {
  posX = x;
  posY = y - 2;
  keyIsPressed[key_left] = false;
  keyIsPressed[key_right] = true;
  xSpeed = 2.5;
  ySpeed = 1.0;
  isAffectedByGravity = false;
  lives = 10;

  image = al_load_bitmap("Images/white-spider.png");
}

SpiderBoss::~SpiderBoss () {
}

void SpiderBoss::Update () {
  static float count = 0;
  count++;
  if (rand()%2000 < count) {
    count = 0;
    if (xSpeed != 0) {
      xSpeed = 0;
      ySpeed = 0;
    } else {
      xSpeed = rand()%301/100.0;
      ySpeed = 2*(rand()%101/100.0) - 1;
    }
  }

  Enemy::Update();

  // If hit a wall, go back
  if (keyIsPressed[key_left] &&
      (gameGrid[static_cast<int>(posY/cTileSize)]
               [static_cast<int>((posX-xSpeed)/cTileSize)] == cBlock  ||
       gameGrid[static_cast<int>((posY-1+boxHeight*cTileSize)/cTileSize)]
               [static_cast<int>((posX-xSpeed)/cTileSize)] == cBlock) ) {
    keyIsPressed[key_left]  = false;
    keyIsPressed[key_right] = true;
  } else if (keyIsPressed[key_right] &&
      (gameGrid[static_cast<int>(posY/cTileSize)]
               [static_cast<int>((posX+xSpeed)/cTileSize+boxWidth)] == cBlock ||
       gameGrid[static_cast<int>((posY-1+boxHeight*cTileSize)/cTileSize)]
               [static_cast<int>((posX+xSpeed)/cTileSize+boxWidth)] == cBlock) ) {
    keyIsPressed[key_left]  = true;
    keyIsPressed[key_right] = false;
  }

}

void SpiderBoss::Draw () const {
  if (dead)
    return;
  if (!invulnerable || (invulnerable && invCountdown%3 == 0) ) {
    int x = posX + boxWidth*cTileSize/2 - al_get_bitmap_width(image)/2,
        y = posY + boxHeight*cTileSize/2 - al_get_bitmap_height(image)/2;
    al_draw_bitmap(image, x, y, 0);
  }
}
