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
#include "upgrade.h"

Upgrade::Upgrade (UpgradeType ut, float x, float y) : Entity (0.5, 0.5) {
  posX = x;
  posY = y;
  upgradeType = ut;
  visible = true;
  xSpeed = 0;
}

Upgrade::~Upgrade () {
  if (image)
    al_destroy_bitmap(image);
}

void Upgrade::Update () {
  Entity::Update();
}

void Upgrade::Draw () const {
  if (!visible)
    return;

  float x = posX, y = posY,
        xm = x + boxWidth*cTileSize/2, ym = y + boxHeight*cTileSize/2,
        xf = x + boxWidth*cTileSize,   yf = y + boxHeight*cTileSize;
  al_draw_rectangle(x, y, xf, yf, al_map_rgb(255,255,255), 0);

  switch (upgradeType) {
    case jumpUpgrade:
      al_draw_filled_triangle(x, ym, xf, ym, xm, y, al_map_rgb(255,255,255));
      break;
    case speedUpgrade:
      al_draw_line(x, ym, xf, ym, al_map_rgb(255,255,255), 0);
      al_draw_line(x, (y+ym)/2, xf, (y+ym)/2, al_map_rgb(255,255,255), 0);
      al_draw_line(x, (yf+ym)/2, xf, (yf+ym)/2, al_map_rgb(255,255,255), 0);
      break;
    case lifeUpgrade:
      al_draw_filled_rectangle(x, y, xm, ym, al_map_rgb(255,255,255));
      al_draw_filled_rectangle(xm, ym, xf, yf, al_map_rgb(255,255,255));
      break;
    case doubleJumpUpgrade:
      al_draw_line(x, y, xf, yf, al_map_rgb(255,255,255),0);
      al_draw_line(x, yf, xf, y, al_map_rgb(255,255,255),0);
      al_draw_line(xm, y, xm, yf, al_map_rgb(255,255,255),0);
      al_draw_line(x, ym, xf, ym, al_map_rgb(255,255,255),0);
    default:
      break;
  }
}

bool Upgrade::CollidesWith (const Entity & hero) const {
  if (!visible || hero.IsDead())
    return false;
  float thisTop    = posY,
        thisBottom = posY + boxHeight*cTileSize,
        thisLeft   = posX,
        thisRight  = posX + boxWidth*cTileSize,
        otherTop    = hero.GetY(),
        otherBottom = otherTop + hero.GetBoxH()*cTileSize,
        otherLeft   = hero.GetX(),
        otherRight  = otherLeft + hero.GetBoxW()*cTileSize;
    
  if (thisTop > otherBottom ||
      otherTop > thisBottom ||
      thisLeft > otherRight ||
      otherLeft > thisRight)
    return false;

  return true;
}
