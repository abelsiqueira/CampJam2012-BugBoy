#ifndef spider_boss_h
#define spider_boss_h

#include "enemy.h"

class SpiderBoss : public Enemy {
  public:
    SpiderBoss (float, float);
    virtual ~SpiderBoss ();
    
    virtual void Update ();
    virtual void Draw () const;
  protected:
    
};

#endif
