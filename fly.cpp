#include "fly.h"
#include <iostream>
#include <cmath>

Fly::Fly (int x, int y) : Enemy(0.5, 0.5) {
  posX = x;
  posY = y - 2;
  keyIsPressed[key_left] = false;
  keyIsPressed[key_right] = true;
  xSpeed = 2.0;
  ySpeed = 0.0;
}

Fly::~Fly () {

}

void Fly::Update () {
  ySpeed = 0;
  Enemy::Update();

  // If hit a wall, go back
  if (keyIsPressed[key_left] &&
      gameGrid[static_cast<int>(posY/cTileSize)]
              [static_cast<int>((posX-xSpeed)/cTileSize)] == 'x') {
    keyIsPressed[key_left]  = false;
    keyIsPressed[key_right] = true;
  } else if (keyIsPressed[key_right] &&
      (gameGrid[static_cast<int>(posY/cTileSize)]
               [static_cast<int>((posX+xSpeed)/cTileSize+boxWidth)] == 'x' ||
       gameGrid[static_cast<int>((posY+boxHeight*cTileSize)/cTileSize)]
               [static_cast<int>((posX+xSpeed)/cTileSize+boxWidth)] == 'x') ) {
    keyIsPressed[key_left]  = true;
    keyIsPressed[key_right] = false;
  }

}

void Fly::Draw () const {
  Enemy::Draw();
  return;
  if (dead)
    return;
  al_draw_circle(posX + cTileSize/2, posY + cTileSize/2,
      cTileSize/3-1, al_map_rgb(255,255,255), 3);
}
