#include "entity.h"

Entity::Entity (int w, int h) {
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
}

Entity::~Entity () {
  
}

void Entity::Update () {
  if (dead)
    return;

  if (keyIsPressed[0] != keyIsPressed[1]) {
    if (keyIsPressed[key_left]) {
      int nextX = posX - 2;
      bool hitWall = false, safe = true;
      for (int i = 0; i <= boxHeight; i++) {
        char aux = gameGrid[posY/cTileSize+i][nextX/cTileSize];
        if (aux == 'x') {
          hitWall = true;
          safe = true;
          break;
        } else if (aux == 's') {
          safe = false;
        }
      }
      if (!hitWall)
        posX = nextX;
      if (!safe)
        dead = true;
    } else {
      int nextX = posX + 2;
      bool hitWall = false, safe = true;
      for (int i = 0; i <= boxHeight; i++) {
        char aux = gameGrid[posY/cTileSize+i][nextX/cTileSize+boxWidth];
        if (aux == 'x') {
          hitWall = true;
          safe = true;
          break;
        } else if (aux == 's') {
          safe = false;
        }
      }
      if (!hitWall)
        posX = nextX;
      if (!safe)
        dead = true;
    }
  }
  int nextY = posY + ySpeed;
  
  if (nextY < 0 || nextY + boxHeight*cTileSize > cTileSize*gridHeight) {
    dead = true;
    return;
  }

  bool hitWall = false, safe = true;
  for (int i = 0; i <= boxWidth; i++) {
    char aux;
    if (ySpeed > 0)
      aux = gameGrid[nextY/cTileSize + boxHeight][posX/cTileSize+i];
    else 
      aux = gameGrid[nextY/cTileSize][posX/cTileSize+i];
    if (aux == 'x') {
      hitWall = true;
      safe = true;
      break;
    } else if (aux == 's') {
      safe = false;
    }
  }
  if (hitWall && ySpeed > 0) {
    ySpeed = 1.0;
    grounded = true;
  } else if (hitWall && ySpeed < 0) {
    ySpeed = 0.0;
  } else {
    posY = nextY;
    ySpeed += cGravity;
    grounded = false;
  }
  if (!safe)
    dead = true;
}

void Entity::Move (bool *kip) {
  keyIsPressed[0] = kip[0];
  keyIsPressed[1] = kip[1];
}

void Entity::Jump () {
  if (grounded)
    ySpeed = -5.0;
}

