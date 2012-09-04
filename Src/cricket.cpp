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
#include "cricket.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

Cricket::Cricket (float x, float y) : Enemy(x, y, 1.75, 0.8) {
  keyIsPressed[key_left] = false;
  keyIsPressed[key_right] = true;
  isAffectedByGravity = true;
  maxLives = 1;
  lives = maxLives;
  hero = 0;
  active = true;
  turnOnWallHit = true;
  softFall = true;

  image = al_load_bitmap("Images/cricket-small.png");
}

Cricket::~Cricket () {
}

void Cricket::Update () {
  if (!active || dead)
    return;

  static int count = 0;
  static int waitingTime = cFps/4 + rand()%(2*cFps);

  if (invulnerable) {
    invCountdown--;
    if (invCountdown <= 0)
      invulnerable = false;
  }


  if (grounded && (count > waitingTime)) {
    if (rand()%2 == 0) {
      bool aux = keyIsPressed[key_left];
      keyIsPressed[key_left] = keyIsPressed[key_right];
      keyIsPressed[key_right] = aux;
    }
    count = 0;
    ySpeed = -(3 + rand()%7);
    waitingTime = cFps/4 + rand()%(2*cFps);
  }
  count++;

  if (!grounded)
    xSpeed = 5;
  else
    xSpeed = 0;

  Enemy::Update();

  
}

void Cricket::Draw () const {
  Enemy::Draw();
}
