#ifndef ant_h
#define ant_h

#include "enemy.h"

class Ant : public Enemy {
  public:
    Ant (int, int);
    ~Ant ();
    
    void Update ();
    void Draw () const;
  protected:
    
};

#endif
