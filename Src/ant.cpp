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
#include "ant.h"
#include <iostream>

Ant::Ant (float x, float y) : Enemy(x, y, 1.0, 0.5) {
  keyIsPressed[key_left] = true;
  keyIsPressed[key_right] = false;
  xSpeed = 0.5;

  image = al_load_bitmap("Images/ant.png");
}

Ant::~Ant () {

}

void Ant::Update () {
  Enemy::Update();
  // Dont Fall
  if (keyIsPressed[key_left] && 
      gameGrid[static_cast<int>((posY-1)/cTileSize + boxHeight + 1)]
              [static_cast<int>(posX/cTileSize)] == cNone) {
    keyIsPressed[key_left]  = false;
    keyIsPressed[key_right] = true;
  } else if (keyIsPressed[key_right] && 
      gameGrid[static_cast<int>((posY-1)/cTileSize + boxHeight + 1)]
              [static_cast<int>(posX/cTileSize + boxWidth)] == cNone) {
    keyIsPressed[key_left]  = true;
    keyIsPressed[key_right] = false;
  }

  // If hit a wall, go back
  if (keyIsPressed[key_left] &&
      gameGrid[static_cast<int>(posY/cTileSize)]
              [static_cast<int>((posX-xSpeed)/cTileSize)] == cBlock) {
    keyIsPressed[key_left]  = false;
    keyIsPressed[key_right] = true;
  } else if (keyIsPressed[key_right] &&
      gameGrid[static_cast<int>(posY/cTileSize)]
              [static_cast<int>((posX+xSpeed)/cTileSize+boxWidth)] == cBlock) {
    keyIsPressed[key_left]  = true;
    keyIsPressed[key_right] = false;
  }

}

void Ant::Draw () const {
  if (dead) return;

  if (!invulnerable || (invulnerable && invCountdown%3 == 0) ) {
    if (image) {
      int x = posX + boxWidth*cTileSize/2 - al_get_bitmap_width(image)/2,
          y = posY + boxHeight*cTileSize/2 - al_get_bitmap_height(image)/2;
      al_draw_bitmap(image, x, y, (facing > 0 ? 0 : ALLEGRO_FLIP_HORIZONTAL));
    } else {
      al_draw_rectangle(posX, posY, posX + cTileSize*boxWidth, 
          posY + cTileSize*boxHeight, al_map_rgb(255,255,255), 0);
    }
  }
}
