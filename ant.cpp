#include "ant.h"

Ant::Ant (int x, int y) : Enemy(1, 1) {
  posX = x;
  posY = y;
}

Ant::~Ant () {

}

void Ant::Update () {
  Enemy::Update();
}

void Ant::Draw () const {
  Enemy::Draw();
}
