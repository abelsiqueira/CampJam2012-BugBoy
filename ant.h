#ifndef ant_h
#define ant_h

#include "enemy.h"

class Ant : public Enemy {
  public:
    Ant (int, int);
    virtual ~Ant ();
    
    virtual void Update ();
    virtual void Draw () const;
  protected:
    
};

#endif
