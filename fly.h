#ifndef fly_h
#define fly_h

#include "enemy.h"

class Fly : public Enemy {
  public:
    Fly (float, float);
    virtual ~Fly ();
    
    virtual void Update ();
    virtual void Draw () const;
  protected:
    
};

#endif
