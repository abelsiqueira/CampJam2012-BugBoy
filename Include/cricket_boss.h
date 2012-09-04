#ifndef cricket_boss_h
#define cricket_boss_h

#include "enemy.h"

class CricketBoss : public Enemy {
  public:
    CricketBoss (float, float);
    virtual ~CricketBoss ();
    
    virtual void Update ();
    virtual void Draw () const;

    void SetHero (Entity *h) {
      hero = h;
    }
    void Activate () {
      active = true;
    }
    void Deactivate () {
      active = false;
    }
  protected:
    Entity *hero;
    bool active;
    float targetX, targetY;
};

#endif
