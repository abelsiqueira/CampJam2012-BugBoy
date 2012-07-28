#ifndef enemy_h
#define enemy_h

#include "entity.h"

class Enemy : public Entity {
  public:
    Enemy (int, int);
    virtual ~Enemy ();
    
    virtual void Update ();
    virtual void Draw () const;
  protected:
    
};

#endif
