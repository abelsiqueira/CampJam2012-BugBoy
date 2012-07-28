#include "hero.h"

Hero::Hero () : Entity () {
}

Hero::~Hero () {

}

void Hero::Update () {
  Entity::Update();
}

void Hero::Draw () const {
  if (dead)
    return;
  al_draw_rectangle(posX, posY, posX + cTileSize, posY + 2*cTileSize,
      al_map_rgb(255,255,255), 1);
}
