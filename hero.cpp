#include "hero.h"

Hero::Hero () : Entity(1, 3) {
}

Hero::~Hero () {

}

void Hero::Update () {
  Entity::Update();
}

void Hero::Draw () const {
  if (dead)
    return;
  al_draw_rectangle(posX, posY, 
      posX + boxWidth*cTileSize, posY + boxHeight*cTileSize,
      al_map_rgb(255,255,255), 1);
}
