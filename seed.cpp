#include "seed.h"
#include <iostream>
#include <cmath>

Seed::Seed (float x, float y, int direction) : Entity(0.3, 0.2) {
  posX = x;
  posY = y - 2;
  if (direction > 0) {
    keyIsPressed[key_left] = false;
    keyIsPressed[key_right] = true;
  } else {
    keyIsPressed[key_left] = true;
    keyIsPressed[key_right] = false;
  }
  xSpeed = 10.0;
  ySpeed = -4.0;
}

Seed::~Seed () {

}

void Seed::Update () {
  if (dead)
    return;
  xSpeed *= 0.99;
  if (xSpeed < 0.3)
    dead = true;
  Entity::Update();

  // If hit a wall, go back
  if (keyIsPressed[key_left] &&
      (gameGrid[static_cast<int>(posY/cTileSize)]
               [static_cast<int>((posX-xSpeed)/cTileSize)] == 'x' ||
       gameGrid[static_cast<int>((posY-1+boxHeight*cTileSize)/cTileSize)]
               [static_cast<int>((posX-xSpeed)/cTileSize)] == 'x') ) {
    keyIsPressed[key_left]  = false;
    keyIsPressed[key_right] = true;
    xSpeed *= 0.25;
  } else if (keyIsPressed[key_right] &&
      (gameGrid[static_cast<int>(posY/cTileSize)]
               [static_cast<int>((posX+xSpeed)/cTileSize+boxWidth)] == 'x' ||
       gameGrid[static_cast<int>((posY-1+boxHeight*cTileSize)/cTileSize)]
               [static_cast<int>((posX+xSpeed)/cTileSize+boxWidth)] == 'x') ) {
    keyIsPressed[key_left]  = true;
    keyIsPressed[key_right] = false;
    xSpeed *= 0.5;
  }

}

void Seed::Draw () const {
  if (dead)
    return;
  al_draw_filled_ellipse(posX + boxWidth*cTileSize/2, posY + boxHeight*cTileSize/2,
      boxWidth*cTileSize/2-1, boxHeight*cTileSize/2-1, al_map_rgb(255,255,255));
}
