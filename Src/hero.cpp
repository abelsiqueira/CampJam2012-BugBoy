/* Copyright 2012 - Abel Soares Siqueira
 * 
 * This file is part of CampJam2012-Bugboy.
 * 
 * CampJam2012-Bugboy is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * CampJam2012-Bugboy is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with CampJam2012-Bugboy.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "hero.h"
#include <iostream>

Hero::Hero (float x, float y) : Entity(x, y, 1, 2) {
  lives = 2;
  maxLives = lives;
  xSpeed = 2.7;
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
  lives = maxLives + upgradesLife;
  posX = x;
  posY = y - (boxHeight-1)*cTileSize - 2;
  shootCountdown = 0;
}

void Hero::Reset () {
  Entity::Reset();
  lives = maxLives;
  upgradesLife = 0;
  upgradesSpeed = 0;
  upgradesJump = 0;
  hasDoubleJump = false;
  consecJumps = 0;
  xSpeed = 2.7;
  jumpSpeed = 6.0;
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
