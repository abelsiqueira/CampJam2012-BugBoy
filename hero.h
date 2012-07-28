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
    void AddUpgrade (UpgradeType);
  protected:
    int shootCountdown;
    int upgradesJump, upgradesSpeed, upgradesLife;
};

#endif
