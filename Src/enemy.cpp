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
#include "enemy.h"
#include <iostream>

Enemy::Enemy (float x, float y, float w, float h) : Entity(x, y, w, h) {

}

Enemy::~Enemy () {

}

void Enemy::Update () {
  Entity::Update();
}

void Enemy::Draw () const {
  if (dead)
    return;
  al_draw_rectangle(posX, posY, posX + boxWidth*cTileSize, posY + boxHeight*cTileSize,
      al_map_rgb(255,255,255),1);
  al_draw_ellipse(posX + boxWidth*cTileSize/2, posY + boxHeight*cTileSize/2,
      boxWidth*cTileSize/4 - 1, boxHeight*cTileSize/4 - 1, al_map_rgb(255,255,255), 1);
  al_draw_ellipse(posX + boxWidth*cTileSize/2, posY + boxHeight*cTileSize/2,
      boxWidth*cTileSize/3 - 1, boxHeight*cTileSize/3 - 1, al_map_rgb(255,255,255), 1);
  al_draw_ellipse(posX + boxWidth*cTileSize/2, posY + boxHeight*cTileSize/2,
      boxWidth*cTileSize/2 - 1, boxHeight*cTileSize/2 - 1, al_map_rgb(255,255,255), 1);
}
