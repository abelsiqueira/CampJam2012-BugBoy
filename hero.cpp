#include "hero.h"

Hero::Hero () : Entity () {
  keyIsPressed[0] = false;
  keyIsPressed[1] = false;
  fallingMultiplier = 1.0;
  dead = false;
  grounded = false;
  ySpeed = 1.0;
}

Hero::~Hero () {

}

void Hero::Update () {
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
  
  if (nextY + 2*cTileSize > cWindowHeight) {
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

void Hero::Move (bool *kip) {
  keyIsPressed[0] = kip[0];
  keyIsPressed[1] = kip[1];
}

void Hero::Jump () {
  if (grounded)
    ySpeed = -5.0;
}

void Hero::Draw () const {
  if (dead)
    return;
  al_draw_rectangle(posX, posY, posX + cTileSize, posY + 2*cTileSize,
      al_map_rgb(255,255,255), 1);
}
