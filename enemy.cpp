#include "enemy.h"
#include <iostream>

Enemy::Enemy (float w, float h) : Entity(w, h) {

}

Enemy::~Enemy () {

}

void Enemy::Update () {
  Entity::Update();
}

void Enemy::Draw () const {
  if (dead)
    return;
  al_draw_rectangle(posX, posY, posX + boxWidth*cTileSize, posY + boxHeight*cTileSize,
      al_map_rgb(255,255,255),1);
  al_draw_ellipse(posX + boxWidth*cTileSize/2, posY + boxHeight*cTileSize/2,
      boxWidth*cTileSize/4 - 1, boxHeight*cTileSize/4 - 1, al_map_rgb(255,255,255), 1);
  al_draw_ellipse(posX + boxWidth*cTileSize/2, posY + boxHeight*cTileSize/2,
      boxWidth*cTileSize/3 - 1, boxHeight*cTileSize/3 - 1, al_map_rgb(255,255,255), 1);
  al_draw_ellipse(posX + boxWidth*cTileSize/2, posY + boxHeight*cTileSize/2,
      boxWidth*cTileSize/2 - 1, boxHeight*cTileSize/2 - 1, al_map_rgb(255,255,255), 1);
}
