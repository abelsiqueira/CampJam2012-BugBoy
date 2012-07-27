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
    void KeyboardEventHandler (unsigned int);
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_TIMER *timer;
    bool done, paused;
};
