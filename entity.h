#ifndef entity_h
#define entity_h

#include "allegro_includes.h"
#include "definitions.h"

class Entity {
  public:
    Entity ();
    virtual ~Entity ();

    virtual void Update () = 0;
    virtual void Draw () const = 0;
  protected:
    int posX, posY;
};

#endif
