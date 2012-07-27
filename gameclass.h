#include <allegro5/allegro.h> 
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h> 
#include <allegro5/allegro_ttf.h> 

const int cWindowWidth = 1280;
const int cWindowHeight = 720;
const int cFps = 60;

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

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *smallFont;
    ALLEGRO_FONT *normalFont;
    ALLEGRO_FONT *bigFont;
    
    bool done, paused;
};
