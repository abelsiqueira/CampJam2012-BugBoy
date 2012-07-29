/* Copyright 2012 - Abel Soares Siqueira
 * 
 * This file is part of CampJam2012-Bugboy.
 * 
 * CampJam2012-Bugboy is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * CampJam2012-Bugboy is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with CampJam2012-Bugboy.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "spider_boss.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

SpiderBoss::SpiderBoss (float x, float y) : Enemy(x, y, 2, 2) {
  keyIsPressed[key_left] = false;
  keyIsPressed[key_right] = true;
  xSpeed = 2.5;
  ySpeed = 1.0;
  isAffectedByGravity = false;
  lives = 4;
  maxLives = 4;

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
