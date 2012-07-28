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
    void Respawn (float, float);

    Seed * Shoot ();
    void AddUpgrade (UpgradeType);
    void Jump ();
  protected:
    int shootCountdown;
    int upgradesJump, upgradesSpeed, upgradesLife;
    bool hasDoubleJump;
    int consecJumps;
};

#endif
