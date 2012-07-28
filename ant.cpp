#include "ant.h"
#include <iostream>

Ant::Ant (float x, float y) : Enemy(0.5, 0.5) {
  posX = x;
  posY = y - 2;
  keyIsPressed[key_left] = true;
  keyIsPressed[key_right] = false;
  xSpeed = 0.5;
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
  if (dead)
    return;
  al_draw_circle(posX + boxWidth*cTileSize/2, posY + boxHeight*cTileSize/2,
      boxWidth*cTileSize/2-1, al_map_rgb(255,255,255), 3);
}
