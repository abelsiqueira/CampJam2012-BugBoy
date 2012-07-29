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
#include "seed.h"
#include <iostream>
#include <cmath>

Seed::Seed (float x, float y, int direction) : Entity(0.3, 0.2) {
  posX = x;
  posY = y - 2;
  if (direction > 0) {
    keyIsPressed[key_left] = false;
    keyIsPressed[key_right] = true;
  } else {
    keyIsPressed[key_left] = true;
    keyIsPressed[key_right] = false;
  }
  xSpeed = 10.0;
  ySpeed = -4.0;
}

Seed::~Seed () {

}

void Seed::Update () {
  if (dead)
    return;
  xSpeed *= 0.99;
  if (xSpeed < 0.3)
    dead = true;
  Entity::Update();

  // If hit a wall, go back
  if (keyIsPressed[key_left] &&
      (gameGrid[static_cast<int>(posY/cTileSize)]
               [static_cast<int>((posX-xSpeed)/cTileSize)] == cBlock ||
       gameGrid[static_cast<int>((posY-1+boxHeight*cTileSize)/cTileSize)]
               [static_cast<int>((posX-xSpeed)/cTileSize)] == cBlock) ) {
    keyIsPressed[key_left]  = false;
    keyIsPressed[key_right] = true;
    xSpeed *= 0.25;
  } else if (keyIsPressed[key_right] &&
      (gameGrid[static_cast<int>(posY/cTileSize)]
               [static_cast<int>((posX+xSpeed)/cTileSize+boxWidth)] == cBlock ||
       gameGrid[static_cast<int>((posY-1+boxHeight*cTileSize)/cTileSize)]
               [static_cast<int>((posX+xSpeed)/cTileSize+boxWidth)] == cBlock) ) {
    keyIsPressed[key_left]  = true;
    keyIsPressed[key_right] = false;
    xSpeed *= 0.5;
  }

  if (gameGrid[static_cast<int>((posY+boxHeight*cTileSize-1+ySpeed)/cTileSize)]
              [static_cast<int>(posX/cTileSize)] == cBlock) {
    xSpeed *= 0.8;
  }

}

void Seed::Draw () const {
  if (dead)
    return;
  al_draw_filled_ellipse(posX + boxWidth*cTileSize/2, posY + boxHeight*cTileSize/2,
      boxWidth*cTileSize/2-1, boxHeight*cTileSize/2-1, al_map_rgb(255,255,255));
}
