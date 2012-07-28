#include "hero.h"

Hero::Hero () : Entity () {
  keyIsPressed[0] = false;
  keyIsPressed[1] = false;
  fallingMultiplier = 1.0;
}

Hero::~Hero () {

}

void Hero::Update () {
  if (keyIsPressed[0] != keyIsPressed[1]) {
    if (keyIsPressed[key_left])
      posX -= 1;
    else
      posX += 1;
  }
  int nextY = posY + 1*fallingMultiplier;

  if (gameGrid[nextY/cTileSize + 2][posX/cTileSize] == 'x' || 
      gameGrid[nextY/cTileSize + 2][posX/cTileSize + 1] == 'x') {
    fallingMultiplier = 1.0;
  } else {
    posY += 1*fallingMultiplier;
    fallingMultiplier += 0.10;
  }
}

void Hero::Move (bool *kip) {
  keyIsPressed[0] = kip[0];
  keyIsPressed[1] = kip[1];
}

void Hero::Draw () const {
  al_draw_rectangle(posX, posY, posX + cTileSize, posY + 2*cTileSize,
      al_map_rgb(255,255,255), 1);
}
