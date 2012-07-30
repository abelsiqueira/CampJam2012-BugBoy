#ifndef seed_h
#define seed_h

#include "entity.h"

class Seed : public Entity {
  public:
    Seed (float, float, int);
    virtual ~Seed ();
    
    virtual void Update ();
    virtual void Draw () const;
  protected:
    
};

#endif
