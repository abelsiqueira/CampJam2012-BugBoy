#include "entity.h"

Entity::Entity () {
  posX = 0;
  posY = 0;
  keyIsPressed[0] = false;
  keyIsPressed[1] = false;
  fallingMultiplier = 1.0;
  dead = false;
  grounded = false;
  ySpeed = 1.0;
}

Entity::~Entity () {
  
}

void Entity::Update () {
  if (dead)
    return;

  if (keyIsPressed[0] != keyIsPressed[1]) {
    if (keyIsPressed[key_left]) {
      int nextX = posX - 2;
      if (gameGrid[posY/cTileSize]  [nextX/cTileSize] != 'x' &&
          gameGrid[posY/cTileSize+1][nextX/cTileSize] != 'x' &&
          gameGrid[posY/cTileSize+2][nextX/cTileSize] != 'x') {
        posX = nextX;
      }
    } else {
      int nextX = posX + 2;
      if (gameGrid[posY/cTileSize]  [nextX/cTileSize+1] != 'x' &&
          gameGrid[posY/cTileSize+1][nextX/cTileSize+1] != 'x' &&
          gameGrid[posY/cTileSize+2][nextX/cTileSize+1] != 'x') {
        posX = nextX;
      }
    }
  }
  int nextY = posY + ySpeed;
  
  if (nextY + 2*cTileSize > cTileSize*gridHeight) {
    dead = true;
    return;
  }

  if (gameGrid[nextY/cTileSize + 2][(posX)/cTileSize] == 'x' || 
      gameGrid[nextY/cTileSize + 2][(posX)/cTileSize+1] == 'x') {
    ySpeed = 1.0;
    grounded = true;
  } else {
    posY = nextY;
    ySpeed += cGravity;
    grounded = false;
  }
}

void Entity::Move (bool *kip) {
  keyIsPressed[0] = kip[0];
  keyIsPressed[1] = kip[1];
}

void Entity::Jump () {
  if (grounded)
    ySpeed = -5.0;
}

