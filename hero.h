#ifndef hero_h
#define hero_h

#include "entity.h"
#include "seed.h"

class Hero : public Entity {
  public:
    Hero ();
    ~Hero ();

    void Update ();
    void Draw () const;

    Seed * Shoot ();
  protected:
    int shootCountdown;
};

#endif
