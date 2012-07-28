#ifndef enemy_h
#define enemy_h

#include "entity.h"

class Enemy : public Entity {
  public:
    Enemy (int, int);
    ~Enemy ();
    
    void Update ();
    void Draw () const;
  protected:
    
};

#endif
