#ifndef gameclass_h
#define gameclass_h

#include "hero.h"

class GameClass {
  public:
    GameClass ();
    ~GameClass ();

    void Run ();
  private:
    // Handlers
    void KeyboardEventHandler (unsigned int);

    // Draw
    void DrawPauseMenu () const;
    void DrawGame () const;
    void DrawGameGrid () const;

    // Game
    void ReadGameLevel(const char *);
    char **gameGrid;
    size_t gridWidth, gridHeight;
    Hero hero;


    // Allegro
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *smallFont;
    ALLEGRO_FONT *normalFont;
    ALLEGRO_FONT *bigFont;
    
    bool done, paused;
};

#endif
