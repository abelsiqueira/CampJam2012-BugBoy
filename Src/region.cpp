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
#include "region.h"

Region::Region (float x, float y) {
  posX = x;
  posY = y;
  boxWidth = 0;
  boxHeight = 0;
  triggerEntity = 0;
  visible = false;
  active = false;
}

Region::Region (float x, float y, float w, float h) {
  posX = x;
  posY = y;
  boxWidth = w;
  boxHeight = h;
  triggerEntity = 0;
  visible = false;
  active = false;
}

Region::~Region () {

}

void Region::SetPoint (float x, float y) {
  if (posX > x) {
    float aux = x;
    x = posX;
    posX = aux;
  }
  if (posY > y) {
     float aux = y;
     y = posY;
     posY = aux;
  }
  boxWidth = (x - posX)/cTileSize + 1;
  boxHeight = (y - posY)/cTileSize + 1;
}

void Region::Update () {
  if (!active || 
      !triggerEntity ||
      triggerEntity->IsDead()) {
    triggered = false;
    return;
  }

  float thisTop    = posY,
        thisBottom = posY + boxHeight*cTileSize,
        thisLeft   = posX,
        thisRight  = posX + boxWidth*cTileSize,
        otherTop    = triggerEntity->GetY(),
        otherBottom = otherTop + triggerEntity->GetBoxH()*cTileSize,
        otherLeft   = triggerEntity->GetX(),
        otherRight  = otherLeft + triggerEntity->GetBoxW()*cTileSize;
    
  if (thisTop > otherBottom ||
      otherTop > thisBottom ||
      thisLeft > otherRight ||
      otherLeft > thisRight) {
    triggered = false;
    return;
  }

  active = false;
  triggered = true;
}

void Region::Draw () const {
  if (!visible) 
    return;

  al_draw_filled_rectangle(posX, posY,
      posX + boxWidth*cTileSize, posY + boxHeight*cTileSize,
      al_map_rgba(150, 150, 150, 150));
}
