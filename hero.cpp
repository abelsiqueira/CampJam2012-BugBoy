#include "hero.h"
#include <iostream>

Hero::Hero () : Entity(1, 2) {
  lives = 1;
  xSpeed = 2.5;
  jumpSpeed = 6.0;
  shootCountdown = 0;
  upgradesJump = 0;
  upgradesSpeed = 0;
  upgradesLife = 0;
  hasDoubleJump = false;
  consecJumps = 0;
}

void Hero::Respawn (float x, float y) {
  dead = false;
  lives = 1 + upgradesLife;
  posX = x;
  posY = y - (boxHeight-1)*cTileSize - 2;
  shootCountdown = 0;
}

Hero::~Hero () {

}

void Hero::Jump () {
  if (grounded || (hasDoubleJump && (consecJumps < 1)) ) {
    consecJumps++;
    ySpeed = -jumpSpeed;
  }
}

void Hero::Update () {
  if (grounded)
    consecJumps = 0;
  if (shootCountdown > 0)
    shootCountdown--;
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
  if (shootCountdown > 0)
    return 0;
  shootCountdown = cShootCooldown;
  float x = posX, y = posY;
  if (facing > 0)
    x += boxWidth*cTileSize;
  y += boxHeight*cTileSize/4;
  Seed * seed = new Seed(x, y, facing);
  seed->SetGameGrid(gameGrid, gridWidth, gridHeight);
  return seed;
}

void Hero::AddUpgrade (UpgradeType ut) {
  switch (ut) {
    case jumpUpgrade:
      upgradesJump++;
      jumpSpeed += 1.0;
      break;
    case speedUpgrade:
      upgradesSpeed++;
      xSpeed += 1.0;
      break;
    case lifeUpgrade:
      upgradesLife++;
      lives++;
      break;
    case doubleJumpUpgrade:
      hasDoubleJump = true;
      break;
    default:
      break;
  }
}
