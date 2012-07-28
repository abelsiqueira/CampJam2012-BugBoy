#ifndef ant_h
#define ant_h

#include "enemy.h"

class Ant : public Enemy {
  public:
    Ant ();
    ~Ant ();
    
    void Update ();
    void Draw () const;
  protected:
    
};

#endif
