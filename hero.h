#ifndef hero_h
#define hero_h

#include "entity.h"

class Hero : public Entity {
  public:
    Hero ();
    ~Hero ();

    void SetGameGrid (char **gg) {
      gameGrid = gg;
    }
    void Update ();
    void Move (bool *);
    void Draw () const;
  protected:
    bool keyIsPressed[2];
    float fallingMultiplier;
    char **gameGrid;

    bool dead;
};

#endif
