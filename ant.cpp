#include "ant.h"
#include <iostream>

Ant::Ant (int x, int y) : Enemy(1, 1) {
  posX = x;
  posY = y - 2;
  keyIsPressed[key_left] = true;
  keyIsPressed[key_right] = false;
  xSpeed = 1;
}

Ant::~Ant () {

}

void Ant::Update () {
  Enemy::Update();
  if (keyIsPressed[key_left] && 
      gameGrid[posY/cTileSize + boxHeight + 1][posX/cTileSize] == '.') {
    keyIsPressed[key_left]  = false;
    keyIsPressed[key_right] = true;
  } else if (keyIsPressed[key_right] && 
      gameGrid[posY/cTileSize + boxHeight + 1][posX/cTileSize + 1] == '.') {
    keyIsPressed[key_left]  = true;
    keyIsPressed[key_right] = false;
  }

  if (keyIsPressed[key_left] &&
      gameGrid[posY/cTileSize][(int)(posX-2*xSpeed)/cTileSize] == 'x') {
    keyIsPressed[key_left]  = false;
    keyIsPressed[key_right] = true;
  } else if (keyIsPressed[key_right] &&
      gameGrid[posY/cTileSize][(int)(posX+2*xSpeed)/cTileSize] == 'x') {
    keyIsPressed[key_left]  = true;
    keyIsPressed[key_right] = false;
  }

}

void Ant::Draw () const {
  Enemy::Draw();
}
