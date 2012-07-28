#ifndef entity_h
#define entity_h

#include "allegro_includes.h"
#include "definitions.h"

class Entity {
  public:
    Entity ();
    virtual ~Entity ();

    virtual void Update ();
    virtual void Draw () const = 0;

    void SetGameGrid (char **gg, size_t w, size_t h) {
      gameGrid = gg;
      gridWidth = w;
      gridHeight = h;
    }
    void SetPosition (int x, int y) {
      posX = x; posY = y;
    }

    void Move (bool *);
    void Jump ();

    bool IsDead () const { return dead; }
    int GetX () const { return posX; }
    int GetY () const { return posY; }
  protected:
    int posX, posY;
    bool keyIsPressed[2];
    float fallingMultiplier;
    char **gameGrid;
    size_t gridWidth, gridHeight;
    float ySpeed;

    bool dead, grounded;
};

#endif
