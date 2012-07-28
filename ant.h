#ifndef ant_h
#define ant_h

#include "enemy.h"

class Ant : public Enemy {
  public:
    Ant (float, float);
    virtual ~Ant ();
    
    virtual void Update ();
    virtual void Draw () const;
  protected:
    
};

#endif
