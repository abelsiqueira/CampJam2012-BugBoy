#include "enemy.h"

Enemy::Enemy (int w, int h) : Entity(w, h) {

}

Enemy::~Enemy () {

}

void Enemy::Update () {
  Entity::Update();
}

void Enemy::Draw () const {
  if (dead)
    return;
  al_draw_filled_ellipse(posX + boxWidth*cTileSize/2, posY + boxHeight*cTileSize/2,
      boxWidth*cTileSize/2 - 1, boxHeight*cTileSize/2 - 1, al_map_rgb(255,255,255));
}
