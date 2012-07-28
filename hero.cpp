#include "hero.h"

Hero::Hero () : Entity(1, 2) {
  lives = 3;
  xSpeed = 3.0;
  jumpSpeed = 7.0;
}

Hero::~Hero () {

}

void Hero::Update () {
  Entity::Update();
}

void Hero::Draw () const {
  if (dead)
    return;
  if (!invulnerable || (invulnerable && invCountdown%3 == 0)) {
    al_draw_rectangle(posX, posY, 
        posX + boxWidth*cTileSize-1, posY + boxHeight*cTileSize-1,
        al_map_rgb(255,255,255), 1);
    float x = posX + boxWidth*cTileSize/2, y = posY + boxHeight*cTileSize/5;
    if (facing > 0)
      x += boxWidth*cTileSize/4;
    else
      x -= boxWidth*cTileSize/4;
    al_draw_filled_circle(x, y, boxWidth*cTileSize/5, al_map_rgb(255,255,255));
  }
}

Seed * Hero::Shoot () {
  float x = posX, y = posY;
  if (facing > 0)
    x += boxWidth*cTileSize;
  y += boxHeight*cTileSize/4;
  Seed * seed = new Seed(x, y, facing);
  seed->SetGameGrid(gameGrid, gridWidth, gridHeight);
  return seed;
}
