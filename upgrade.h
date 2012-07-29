#ifndef upgrades_h
#define upgrades_h

#include "entity.h"

class Upgrade : public Entity {
  public:
    Upgrade (UpgradeType, float, float);
    ~Upgrade ();

    void Reset ();

    void Update ();
    void Draw () const;

    bool CollidesWith (const Entity &) const;
    void Take () { visible = false; }
    UpgradeType GetType () { return upgradeType; }
  protected:
    Upgrade ();
    UpgradeType upgradeType;

    bool visible;
};

#endif
