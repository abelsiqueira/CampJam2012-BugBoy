#include "gameclass.h"

GameClass::GameClass () {
  al_init();
  display = al_create_display(cWindowWidth, cWindowHeight);
  al_set_window_title(display, "Campjam");
  eventQueue = al_create_event_queue();
  timer = al_create_timer(1.0/cFps);

  al_init_font_addon();
  al_init_ttf_addon();
  al_init_primitives_addon();
  al_install_keyboard();
  al_install_mouse();
  al_init_image_addon();
  al_install_audio();
  al_init_acodec_addon();
  al_reserve_samples(1);

  al_register_event_source(eventQueue, al_get_display_event_source(display));
  al_register_event_source(eventQueue, al_get_timer_event_source(timer));
  al_register_event_source(eventQueue, al_get_keyboard_event_source());
  al_register_event_source(eventQueue, al_get_mouse_event_source());

  bigFont = al_load_font("DejaVuSans.ttf", 40, 0);
  normalFont = al_load_font("DejaVuSans.ttf", 20, 0);
  smallFont = al_load_font("DejaVuSans.ttf", 10, 0);
}

GameClass::~GameClass () {
  al_destroy_font(bigFont);
  al_destroy_font(normalFont);
  al_destroy_font(smallFont);
  al_destroy_timer(timer);
  al_destroy_event_queue(eventQueue);
  al_destroy_display(display);
}

void GameClass::Run () {
  bool redraw = false;
  done = false;
  paused = false;
  
  al_start_timer(timer);

  while (!done) {
    ALLEGRO_EVENT ev;
    al_wait_for_event(eventQueue, &ev);

    if (ev.type == ALLEGRO_EVENT_TIMER) {
      // Update
      if (!paused) {
      }
      redraw = true;
    } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      done = true;
    } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
               ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

    } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

    } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      KeyboardEventHandler(ev.keyboard.keycode);
    }

    if (redraw && al_is_event_queue_empty(eventQueue)) {
      redraw = false;
      al_clear_to_color(al_map_rgb(0,0,0));

      if (paused)
        DrawPauseMenu ();

      al_flip_display();
    }
  }
}

void GameClass::KeyboardEventHandler (unsigned int keycode) {
  switch (keycode) {
    case ALLEGRO_KEY_ESCAPE:
      done = true;
      break;
    case ALLEGRO_KEY_P:
      paused = (paused ? false : true);
      break;
    default:
      break;
  }
}

void GameClass::DrawPauseMenu () const {
  ALLEGRO_COLOR fontColor = al_map_rgb(255, 255, 255),
                menuColor = al_map_rgba( 20, 100, 120, 100);

  al_draw_filled_rectangle(10, 10, cWindowWidth - 10, cWindowHeight - 10, menuColor);
  al_draw_text(bigFont, fontColor, cWindowWidth/2, 40, ALLEGRO_ALIGN_CENTRE, "Pause Menu");
}
