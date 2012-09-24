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
#include "entity.h"
#include <iostream>

Entity::Entity (float x, float y, float w, float h) {
  boxWidth = w;
  boxHeight = h;
  SetPosition(x, y);
  keyIsPressed[0] = false;
  keyIsPressed[1] = false;
  fallingMultiplier = 1.0;
  dead = false;
  grounded = false;
  ySpeed = 1.0;
  xSpeed = 2.0;
  jumpSpeed = 7.0;
  lives = 1;
  maxLives = 1;
  invulnerable = false;
  facing = 1;
  isAffectedByGravity = true;
  image = 0;
  turnOnWallHit = false;
  softFall = false;
  visibleBox = false;
}

Entity::~Entity () {
  if (image)
    al_destroy_bitmap(image);
}

void Entity::Reset () {
  lives = maxLives;
  posX = startX;
  posY = startY;
  dead = false;
  facing = 1;
  invulnerable = false;
}

void Entity::Update () {
  if (dead)
    return;
  if (invulnerable) {
    invCountdown--;
    if (invCountdown <= 0)
      invulnerable = false;
  }

  if (keyIsPressed[0] != keyIsPressed[1]) {
    if (keyIsPressed[key_left]) {
      facing = -1;
      float nextX = posX - xSpeed;
      bool hitWall = false, safe = true;
      for (int i = 0; i < boxHeight; i++) {
        char aux;
        aux = gameGrid[static_cast<int>(posY/cTileSize+i)]
                      [static_cast<int>(nextX/cTileSize)];

        if (aux == cBlock) {
          hitWall = true;
          touchWall = true;
          safe = true;
          break;
        } else if (aux == cSpike) {
          safe = false;
        }
      }
      {
        char aux;
        aux = gameGrid[static_cast<int>((posY - 1 + boxHeight*cTileSize)/cTileSize)]
                      [static_cast<int>(nextX/cTileSize)];

        if (aux == cBlock) {
          hitWall = true;
          safe = true;
        } else if (aux == cSpike) {
            safe = false;
        }
      }
      if (!hitWall)
        posX = nextX;
      else if (turnOnWallHit) {
        keyIsPressed[key_left] = false;
        keyIsPressed[key_right] = true;
      }
      if (!safe)
        Die();
    } else {
      facing = 1;
      float nextX = posX + xSpeed;
      bool hitWall = false, safe = true;
      for (int i = 0; i < boxHeight; i++) {
        char aux;
        aux = gameGrid[static_cast<int>(posY/cTileSize+i)]
                      [static_cast<int>((nextX+boxWidth*cTileSize-1)/cTileSize)];
        if (aux == cBlock) {
          hitWall = true;
          touchWall = true;
          safe = true;
          break;
        } else if (aux == cSpike) {
          safe = false;
        }
      }
      {
        char aux;
        aux = gameGrid[static_cast<int>((posY -1 + boxHeight*cTileSize)/cTileSize)]
                      [static_cast<int>((nextX+boxWidth*cTileSize-1)/cTileSize)];
        if (aux == cBlock) {
          hitWall = true;
          safe = true;
        } else if (aux == cSpike) {
          safe = false;
        }
      }
      if (!hitWall)
        posX = nextX;
      else if (turnOnWallHit) {
        keyIsPressed[key_left] = true;
        keyIsPressed[key_right] = false;
      }
      if (!safe)
        Die();
    }
  }
  float nextY = posY + ySpeed;
  
  if (nextY < 0 || nextY + boxHeight*cTileSize > (int)(cTileSize*gridHeight)) {
    Die();
    return;
  }

  bool hitWall = false, safe = true;
  for (int i = 0; i < boxWidth; i++) {
    char aux;
    if (ySpeed > 0) {
      aux = gameGrid[static_cast<int>((nextY+boxHeight*cTileSize-1)/cTileSize)]
                    [static_cast<int>(posX/cTileSize+i)];
    } else {
      aux = gameGrid[static_cast<int>((nextY-1)/cTileSize)]
                    [static_cast<int>(posX/cTileSize+i)];
    }
    if (aux == cBlock) {
      hitWall = true;
      safe = true;
      break;
    } else if (aux == cSpike) {
      safe = false;
    }
  }
  {
    char aux;
    if (ySpeed > 0) {
      aux = gameGrid[static_cast<int>((nextY+boxHeight*cTileSize-1)/cTileSize)]
                    [static_cast<int>((posX-1+boxWidth*cTileSize)/cTileSize)];
    } else {
      aux = gameGrid[static_cast<int>((nextY-1)/cTileSize)]
                    [static_cast<int>((posX-1+boxWidth*cTileSize)/cTileSize)];
    }
    if (aux == cBlock) {
      hitWall = true;
      safe = true;
    } else if (aux == cSpike) {
      safe = false;
    }
  }
  if (hitWall && ySpeed > 0) {
    if (isAffectedByGravity)
      ySpeed = 1.0;
    else 
      ySpeed = -ySpeed;
    grounded = true;
  } else if (hitWall && ySpeed < 0) {
    if (isAffectedByGravity)
      ySpeed = 0.0;
    else
      ySpeed = -ySpeed;
  } else {
    posY = nextY;
    if (isAffectedByGravity)
      ySpeed += cGravity;
    grounded = false;
  }
  if (!safe)
    Die();
}

void Entity::Move (bool *kip) {
  keyIsPressed[0] = kip[0];
  keyIsPressed[1] = kip[1];
}

void Entity::Jump () {
  if (grounded)
    ySpeed = -jumpSpeed;
}

bool Entity::CollidesWith (const Entity & entity) const {
  if (dead || entity.IsDead())
    return false;
  float thisTop    = posY,
        thisBottom = posY + boxHeight*cTileSize,
        thisLeft   = posX,
        thisRight  = posX + boxWidth*cTileSize,
        otherTop    = entity.GetY(),
        otherBottom = otherTop + entity.GetBoxH()*cTileSize,
        otherLeft   = entity.GetX(),
        otherRight  = otherLeft + entity.GetBoxW()*cTileSize;
    
  if (thisTop > otherBottom ||
      otherTop > thisBottom ||
      thisLeft > otherRight ||
      otherLeft > thisRight)
    return false;

  return true;
}

void Entity::Draw () const {
  if (dead) return;

  if (!invulnerable || (invulnerable && invCountdown%3 == 0) ) {
    if (image) {
      int x = posX + boxWidth*cTileSize/2 - al_get_bitmap_width(image)/2,
          y = posY + boxHeight*cTileSize/2 - al_get_bitmap_height(image)/2;
      al_draw_bitmap(image, x, y, (facing > 0 ? 0 : ALLEGRO_FLIP_HORIZONTAL));
    } else {
      al_draw_rectangle(posX, posY, posX + cTileSize*boxWidth, 
          posY + cTileSize*boxHeight, cWhite, 0);
    }
    if (visibleBox) {
      al_draw_rectangle(posX, posY, posX + cTileSize*boxWidth, 
          posY + cTileSize*boxHeight, al_map_rgb(255,255,255), 0);
    }
  }
}
