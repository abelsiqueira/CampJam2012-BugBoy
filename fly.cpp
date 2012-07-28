#include "fly.h"
#include <iostream>
#include <cmath>

Fly::Fly (float x, float y) : Enemy(0.5, 0.4) {
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
      (gameGrid[static_cast<int>(posY/cTileSize)]
               [static_cast<int>((posX-xSpeed)/cTileSize)] == 'x'  ||
       gameGrid[static_cast<int>((posY-1+boxHeight*cTileSize)/cTileSize)]
               [static_cast<int>((posX-xSpeed)/cTileSize)] == 'x') ) {
    keyIsPressed[key_left]  = false;
    keyIsPressed[key_right] = true;
  } else if (keyIsPressed[key_right] &&
      (gameGrid[static_cast<int>(posY/cTileSize)]
               [static_cast<int>((posX+xSpeed)/cTileSize+boxWidth)] == 'x' ||
       gameGrid[static_cast<int>((posY-1+boxHeight*cTileSize)/cTileSize)]
               [static_cast<int>((posX+xSpeed)/cTileSize+boxWidth)] == 'x') ) {
    keyIsPressed[key_left]  = true;
    keyIsPressed[key_right] = false;
  }

}

void Fly::Draw () const {
  if (dead)
    return;
  al_draw_line(posX, posY + boxHeight*cTileSize/2,
               posX + boxWidth*cTileSize/2, posY, 
               al_map_rgb(255,255,255),1);

  al_draw_line(posX, posY + boxHeight*cTileSize/2,
               posX + boxWidth*cTileSize/2, posY + boxHeight*cTileSize, 
               al_map_rgb(255,255,255),1);

  al_draw_line(posX + boxWidth*cTileSize, posY + boxHeight*cTileSize/2,
               posX + boxWidth*cTileSize/2, posY, 
               al_map_rgb(255,255,255),1);

  al_draw_line(posX + boxWidth*cTileSize, posY + boxHeight*cTileSize/2,
               posX + boxWidth*cTileSize/2, posY + boxHeight*cTileSize,
               al_map_rgb(255,255,255),1);

}
