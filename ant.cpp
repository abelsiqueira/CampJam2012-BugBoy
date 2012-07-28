#include "ant.h"

Ant::Ant () : Enemy(1, 1) {
}

Ant::~Ant () {

}

void Ant::Update () {
  Enemy::Update();
}

void Ant::Draw () const {
  Enemy::Draw();
}
