#ifndef spider_boss_h
#define spider_boss_h

#include "enemy.h"

class SpiderBoss : public Enemy {
  public:
    SpiderBoss (float, float);
    virtual ~SpiderBoss ();
    
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
