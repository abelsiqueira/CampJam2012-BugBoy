#ifndef upgrades_h
#define upgrades_h

#include "hero.h"

class Upgrade {
  public:
    Upgrade (UpgradeType, float, float);
    ~Upgrade ();

    void Update ();
    void Draw () const;

    bool CollidesWith (const Hero &) const;
    void Take () { visible = false; }
    UpgradeType GetType () { return upgradeType; }
  protected:
    Upgrade ();
    float posX, posY;
    float boxWidth, boxHeight;
    UpgradeType upgradeType;

    bool visible;
    ALLEGRO_BITMAP *image;
};

#endif
