#ifndef gameclass_h
#define gameclass_h

#include <list>
#include <string>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include "region.h"
#include "hero.h"
#include "upgrade.h"
#include "list_of_enemies.h"

class GameClass {
  public:
    GameClass ();
    ~GameClass ();

    void Run ();
    bool HasFailed () const { return hasFailed; }
  private:
    int AllegroInitialization ();

    // Updates
    void Update ();
    void MenuUpdate ();
    void PauseMenuUpdate ();
    void EnemiesUpdate ();
    void SeedsUpdate ();
    void UpgradesUpdate ();

    // Handlers
    void KeyboardEventHandler (unsigned int, int);

    // Draw
    void DrawBlock (float, float, float, float) const;
    void DrawFloor (float, float, float, float) const;
    void DrawGrass (float, float, float, float) const;
    void DrawSpike (float, float, float, float) const;
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
    Hero *hero;
    float startX, startY;
    std::list <Enemy*> enemies;
    std::list <Seed*>  seeds;
    std::list <Upgrade*> upgrades;
    Upgrade *doubleJump, *wallJump;
    Region *regionExit;
    Region *regionSpiderBoss;
    Region *regionCricketBoss;
    int ReadGameLevel(const char *);
    char **gameGrid;
    size_t gridWidth, gridHeight;
    bool keyIsPressed[2];
    SpiderBoss * pSpiderBoss;
    CricketBoss *pCricketBoss;
    void GameEnd ();
    void Reset ();

    // Allegro
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *smallFont;
    ALLEGRO_FONT *normalFont;
    ALLEGRO_FONT *bigFont;
    ALLEGRO_FONT *hugeFont;
    ALLEGRO_BITMAP *level;
    ALLEGRO_AUDIO_STREAM *music;
    
    bool done, paused, inMenu, inIntro, inCredits, inGameEnd, choseOption;
    int menuOption, pauseOption, introScreen;
    int language;

    bool hasFailed;
    int errorValue;
};

#endif
