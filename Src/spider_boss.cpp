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
#include "spider_boss.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

SpiderBoss::SpiderBoss (float x, float y) : Enemy(x, y, 2, 2) {
  keyIsPressed[key_left] = false;
  keyIsPressed[key_right] = true;
  isAffectedByGravity = false;
  maxLives = 4;
  lives = maxLives;
  hero = 0;
  active = false;

  image = al_load_bitmap("Images/white-spider.png");
}

SpiderBoss::~SpiderBoss () {
}

void SpiderBoss::Update () {
  if (!active || dead)
    return;
  assert(hero);

  static bool waiting = true, going = false;
  static int count = 0;
  int waitingTime = 3*cFps;
  float goingSpeed = 10.0, returningSpeed = 6.0;

  if (invulnerable) {
    invCountdown--;
    if (invCountdown <= 0)
      invulnerable = false;
  }

  if (count > waitingTime) {
    going = true;
    count = 0;
    waiting = false;
    targetX = hero->GetX();
    targetY = hero->GetY();
  }

  if (waiting)
    count++;
  else if (!waiting) {
    float dx = targetX - posX,
          dy = targetY - posY;
    float nd = sqrt(dx*dx + dy*dy);
    if (nd < 5.0) {
      if (going) {
        targetX = startX;
        targetY = startY;
        going = false;
      } else {
        waiting = true;
      }
    } else {
      if (going) {
        dx = dx*goingSpeed/nd;
        dy = dy*goingSpeed/nd;
      } else {
        dx = dx*returningSpeed/nd;
        dy = dy*returningSpeed/nd;
      }
    }
    posX += dx;
    posY += dy;
  }
  
}

void SpiderBoss::Draw () const {
  Entity::Draw();
}
