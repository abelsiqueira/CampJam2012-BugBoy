#ifndef hero_h
#define hero_h

#include "entity.h"

class Hero : public Entity {
  public:
    Hero ();
    ~Hero ();

    void Update ();
    void Draw () const;
  protected:
};

#endif
