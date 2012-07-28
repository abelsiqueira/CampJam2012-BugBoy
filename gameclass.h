#ifndef gameclass_h
#define gameclass_h

#include <list>
#include "hero.h"
#include "upgrade.h"
#include "list_of_enemies.h"

class GameClass {
  public:
    GameClass ();
    ~GameClass ();

    void Run ();
  private:
    // Handlers
    void KeyboardEventHandler (unsigned int, int);

    // Draw
    void DrawPauseMenu () const;
    void DrawGame () const;
    void DrawGameGrid () const;
    void DrawHud () const;
    int VisibleX, VisibleY;

    // Game
    Hero hero;
    std::list <Enemy*> enemies;
    std::list <Seed*>  seeds;
    std::list <Upgrade*> upgrades;
    void ReadGameLevel(const char *);
    char **gameGrid;
    size_t gridWidth, gridHeight;
    bool keyIsPressed[2];

    // Allegro
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *smallFont;
    ALLEGRO_FONT *normalFont;
    ALLEGRO_FONT *bigFont;
    ALLEGRO_BITMAP *level;
    
    bool done, paused;
};

#endif
