#ifndef gameclass_h
#define gameclass_h

#include <list>
#include "region.h"
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
    void DrawCredits () const;
    void DrawPauseMenu () const;
    void DrawGameIntro () const;
    void DrawGameMenu () const;
    void DrawGame () const;
    void DrawGameEnd () const;
    void DrawGameGrid () const;
    void DrawHud () const;
    int VisibleX, VisibleY;

    // Game
    Hero hero;
    float startX, startY;
    std::list <Enemy*> enemies;
    std::list <Seed*>  seeds;
    std::list <Upgrade*> upgrades;
    std::list <Region> regions;
    void ReadGameLevel(const char *);
    char **gameGrid;
    size_t gridWidth, gridHeight;
    bool keyIsPressed[2];
    SpiderBoss * pSpiderBoss;
    void IntroUpdate ();
    void GameEnd ();

    // Allegro
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *smallFont;
    ALLEGRO_FONT *normalFont;
    ALLEGRO_FONT *bigFont;
    ALLEGRO_FONT *hugeFont;
    ALLEGRO_BITMAP *level;
    
    bool done, paused, inMenu, inIntro, inCredits, inGameEnd, choseOption;
    int menuOption, pauseOption, introScreen;
};

#endif
