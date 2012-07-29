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
#include "fly.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

Fly::Fly (float x, float y) : Enemy(x, y, 0.5, 0.4) {
  keyIsPressed[key_left] = false;
  keyIsPressed[key_right] = true;
  xSpeed = 2.5;
  ySpeed = 0.0;
  isAffectedByGravity = false;

  image = al_load_bitmap("Images/fly.png");
}

Fly::~Fly () {

}

void Fly::Update () {
  static float count = 0;
  ySpeed = ((rand()%101)/100.0)*5*sin(count);
  count += 0.01*M_PI;
  xSpeed += (2*(rand()%101/100.0) - 1)*0.4;
  float maxSpeed = 4.0;
  if (xSpeed > maxSpeed) xSpeed = maxSpeed;
  else if (xSpeed < 0) xSpeed = 0;

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

void Fly::Draw () const {
  Entity::Draw();
}
