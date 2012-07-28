#include "hero.h"

Hero::Hero () : Entity () {

}

Hero::~Hero () {

}

void Hero::Update () {

}

void Hero::Draw () const {
  al_draw_rectangle(posX, posY, posX + cTileSize, posY + 2*cTileSize,
      al_map_rgb(255,255,255), 1);
}
