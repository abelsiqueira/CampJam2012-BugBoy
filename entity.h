#ifndef entity_h
#define entity_h

#include "allegro_includes.h"
#include "definitions.h"

class Entity {
  public:
    Entity (float, float, float, float);
    virtual ~Entity ();

    virtual void Update ();
    virtual void Draw () const;

    virtual void Reset ();

    void SetGameGrid (char **gg, size_t w, size_t h) {
      gameGrid = gg;
      gridWidth = w;
      gridHeight = h;
    }
    void SetPosition (float x, float y) {
      posX = x; 
      posY = y - (boxHeight-1)*cTileSize - 2;
      startX = posX;
      startY = posY;
    }
    virtual void Die () {
      if (dead || invulnerable)
        return;
      lives--;
      if (lives <= 0)
        dead = true;
      invulnerable = true;
      invCountdown = cInvulnerableCountdown;
    }

    void Move (bool *);
    void Jump ();

    bool IsDead () const { return dead; }
    float GetX () const { return posX; }
    float GetY () const { return posY; }
    float GetBoxW () const { return boxWidth; }
    float GetBoxH () const { return boxHeight; }
    int GetLives () const { return lives; }

    bool CollidesWith (const Entity &) const;
  protected:
    Entity ();
    float posX, posY;
    float startX, startY;
    bool keyIsPressed[2];
    float fallingMultiplier;
    char **gameGrid;
    int gridWidth, gridHeight;
    float ySpeed, xSpeed, jumpSpeed;
    float boxWidth, boxHeight;

    bool dead, grounded, invulnerable, isAffectedByGravity;
    int lives, maxLives;
    int invCountdown;
    int facing;

    ALLEGRO_BITMAP *image;
};

#endif
