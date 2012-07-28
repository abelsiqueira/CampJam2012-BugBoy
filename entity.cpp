#include "entity.h"
#include <iostream>

Entity::Entity (float w, float h) {
  boxWidth = w;
  boxHeight = h;
  posX = 0;
  posY = 0;
  keyIsPressed[0] = false;
  keyIsPressed[1] = false;
  fallingMultiplier = 1.0;
  dead = false;
  grounded = false;
  ySpeed = 1.0;
  xSpeed = 2.0;
  jumpSpeed = 7.0;
  lives = 1;
  invulnerable = false;
  facing = 1;
  isAffectedByGravity = true;
}

Entity::~Entity () {
  
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

        if (aux == 'x') {
          hitWall = true;
          safe = true;
          break;
        } else if (aux == 's') {
          safe = false;
        }
      }
      {
        char aux;
        aux = gameGrid[static_cast<int>((posY - 1 + boxHeight*cTileSize)/cTileSize)]
                      [static_cast<int>(nextX/cTileSize)];

        if (aux == 'x') {
          hitWall = true;
          safe = true;
        } else if (aux == 's') {
          safe = false;
        }
      }
      if (!hitWall)
        posX = nextX;
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
        if (aux == 'x') {
          hitWall = true;
          safe = true;
          break;
        } else if (aux == 's') {
          safe = false;
        }
      }
      {
        char aux;
        aux = gameGrid[static_cast<int>((posY -1 + boxHeight*cTileSize)/cTileSize)]
                      [static_cast<int>((nextX+boxWidth*cTileSize-1)/cTileSize)];
        if (aux == 'x') {
          hitWall = true;
          safe = true;
        } else if (aux == 's') {
          safe = false;
        }
      }
      if (!hitWall)
        posX = nextX;
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
    if (aux == 'x') {
      hitWall = true;
      safe = true;
      break;
    } else if (aux == 's') {
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
    if (aux == 'x') {
      hitWall = true;
      safe = true;
    } else if (aux == 's') {
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
