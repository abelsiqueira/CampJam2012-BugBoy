#include "gameclass.h"

void GameClass::KeyboardEventHandler (unsigned int keycode, int ev_type) {
  if (inMenu && ev_type == ALLEGRO_EVENT_KEY_DOWN) {
    switch (keycode) {
      case ALLEGRO_KEY_UP:
        menuOption--;
        if (menuOption < 0) menuOption = 3;
        break;
      case ALLEGRO_KEY_DOWN:
        menuOption++;
        if (menuOption > 3) menuOption = 0;
        break;
      case ALLEGRO_KEY_ESCAPE:
        done = true;
        break;
      case ALLEGRO_KEY_ENTER:
        choseOption = true;
        break;
      default:
        break;
    }
  } else if (inIntro && ev_type == ALLEGRO_EVENT_KEY_DOWN) {
    introScreen++;
    if (introScreen > 1) {
      inIntro = false;
      introScreen = 0;
    }
  } else if (inCredits && ev_type == ALLEGRO_EVENT_KEY_DOWN) {
    inCredits = false;
    inMenu = true;
  } else if (inGameEnd && ev_type == ALLEGRO_EVENT_KEY_DOWN) {
    inCredits = true;
    inGameEnd = false;
  } else if (paused && ev_type == ALLEGRO_EVENT_KEY_DOWN) {
    switch (keycode) {
      case ALLEGRO_KEY_ESCAPE:
      case ALLEGRO_KEY_P:
        paused = false;
        break;
      case ALLEGRO_KEY_UP:
        pauseOption--;
        if (pauseOption < 0) pauseOption = 2;
        break;
      case ALLEGRO_KEY_DOWN:
        pauseOption++;
        if (pauseOption > 2) pauseOption = 0;
        break;
      case ALLEGRO_KEY_ENTER:
        choseOption = true;
        break;
      default:
        break;
    }
  } else if (!inMenu) {
    switch (keycode) {
      case ALLEGRO_KEY_ESCAPE:
      case ALLEGRO_KEY_P:
        if (ev_type == ALLEGRO_EVENT_KEY_DOWN) {
          paused = true;
          pauseOption = 0;
        }
        break;
      case ALLEGRO_KEY_UP:
        if (ev_type == ALLEGRO_EVENT_KEY_DOWN)
          hero->Jump();
        break;
      case ALLEGRO_KEY_LEFT:
        keyIsPressed[key_left] = (ev_type == ALLEGRO_EVENT_KEY_DOWN ? true : false);
        break;
      case ALLEGRO_KEY_RIGHT:
        keyIsPressed[key_right] = (ev_type == ALLEGRO_EVENT_KEY_DOWN ? true : false);
        break;
      case ALLEGRO_KEY_SPACE:
        if (ev_type == ALLEGRO_EVENT_KEY_DOWN) {
          seeds.push_back(hero->Shoot());
          if (seeds.back() == 0)
            seeds.pop_back();
        }
        break;
      default:
        break;
    }
  }
}
