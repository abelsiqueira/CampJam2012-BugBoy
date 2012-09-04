#ifndef cricket_h
#define cricket_h

#include "enemy.h"

class Cricket : public Enemy {
  public:
    Cricket (float, float);
    virtual ~Cricket ();
    
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
