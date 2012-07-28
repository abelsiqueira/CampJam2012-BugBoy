#ifndef entity_h
#define entity_h

#include "allegro_includes.h"
#include "definitions.h"

class Entity {
  public:
    Entity (float, float);
    virtual ~Entity ();

    virtual void Update ();
    virtual void Draw () const = 0;

    void SetGameGrid (char **gg, size_t w, size_t h) {
      gameGrid = gg;
      gridWidth = w;
      gridHeight = h;
    }
    void SetPosition (int x, int y) {
      posX = x; 
      posY = y - (boxHeight-1)*cTileSize - 2;
    }

    void Move (bool *);
    void Jump ();

    bool IsDead () const { return dead; }
    int GetX () const { return posX; }
    int GetY () const { return posY; }
  protected:
    Entity ();
    float posX, posY;
    bool keyIsPressed[2];
    float fallingMultiplier;
    char **gameGrid;
    int gridWidth, gridHeight;
    float ySpeed, xSpeed, jumpSpeed;
    float boxWidth, boxHeight;

    bool dead, grounded;
};

#endif
