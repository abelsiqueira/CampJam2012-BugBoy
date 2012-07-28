#ifndef hero_h
#define hero_h

#include "entity.h"

class Hero : public Entity {
  public:
    Hero ();
    ~Hero ();

    void SetGameGrid (char **gg, size_t w, size_t h) {
      gameGrid = gg;
      gridWidth = w;
      gridHeight = h;
    }
    void SetPosition (int x, int y) {
      posX = x; posY = y;
    }

    void Update ();
    void Move (bool *);
    void Draw () const;
    void Jump ();

    bool IsDead () const { return dead; }
    int GetX () const { return posX; }
    int GetY () const { return posY; }
  protected:
    bool keyIsPressed[2];
    float fallingMultiplier;
    char **gameGrid;
    size_t gridWidth, gridHeight; 
    float ySpeed;

    bool dead, grounded;
};

#endif
