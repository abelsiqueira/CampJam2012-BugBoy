#include "gameclass.h"
#include <fstream>
#include <iostream>

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

  keyIsPressed[0] = false;
  keyIsPressed[1] = false;

  ReadGameLevel("level1.map");
  VisibleX = 0; 
  VisibleY = 0;
}

GameClass::~GameClass () {
  for (size_t i = 0; i < gridHeight; i++)
    delete []gameGrid[i];
  delete []gameGrid;

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
        hero.Update();
        std::list<Enemy*>::iterator iter = enemies.begin(),
          iterEnd = enemies.end();
        while (iter != iterEnd) {
          (*iter)->Update();
          if ((*iter)->CollidesWith(hero)) {
            hero.Die();
          }
          iter++;
        }
        VisibleX = hero.GetX() - cWindowWidth/2;
        VisibleY = hero.GetY() -  cWindowHeight/2;
        if (VisibleX < 0) 
          VisibleX = 0;
        else if (VisibleX > (int)(cTileSize*gridWidth - cWindowWidth))
          VisibleX = cTileSize*gridWidth - cWindowWidth;
        if (VisibleY < 0) 
          VisibleY = 0;
        else if (VisibleY > (int)(cTileSize*gridHeight - cWindowHeight))
          VisibleY = cTileSize*gridHeight - cWindowHeight;
      }
      if (hero.IsDead()) done = true;
      redraw = true;
    } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      done = true;
    } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
               ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

    } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

    } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN ||
               ev.type == ALLEGRO_EVENT_KEY_UP) {
      KeyboardEventHandler(ev.keyboard.keycode, ev.type);
        hero.Move(keyIsPressed);
    }

    if (redraw && al_is_event_queue_empty(eventQueue)) {
      redraw = false;
      al_clear_to_color(al_map_rgb(0,0,0));

      ALLEGRO_TRANSFORM T;
      al_identity_transform(&T);
      al_translate_transform(&T, -VisibleX, -VisibleY);
      al_use_transform(&T);

      DrawGame();
      if (paused)
        DrawPauseMenu();

      al_flip_display();
    }
  }
}

void GameClass::KeyboardEventHandler (unsigned int keycode, int ev_type) {
  switch (keycode) {
    case ALLEGRO_KEY_ESCAPE:
      done = true;
      break;
    case ALLEGRO_KEY_P:
      if (ev_type == ALLEGRO_EVENT_KEY_DOWN)
        paused = (paused ? false : true);
      break;
    case ALLEGRO_KEY_UP:
      if (ev_type == ALLEGRO_EVENT_KEY_DOWN)
        hero.Jump();
      break;
    case ALLEGRO_KEY_LEFT:
      keyIsPressed[key_left] = (ev_type == ALLEGRO_EVENT_KEY_DOWN ? true : false);
      break;
    case ALLEGRO_KEY_RIGHT:
      keyIsPressed[key_right] = (ev_type == ALLEGRO_EVENT_KEY_DOWN ? true : false);
      break;
    default:
      break;
  }
}

void GameClass::DrawPauseMenu () const {
  ALLEGRO_COLOR fontColor = al_map_rgb(255,255,255);

  al_draw_filled_rectangle(0, 0, 1280, 720, al_map_rgba(0,0,0,200));
  al_draw_text(bigFont, fontColor, cWindowWidth/2, 40, ALLEGRO_ALIGN_CENTRE, "Pause Menu");
}

void GameClass::DrawGame () const {
  DrawGameGrid();
  hero.Draw();
  std::list<Enemy*>::const_iterator iter = enemies.begin(),
    iterEnd = enemies.end();
  while (iter != iterEnd) {
    (*iter)->Draw();
    iter++;
  }
}

void GameClass::DrawGameGrid () const {
  ALLEGRO_COLOR color(al_map_rgb(255,255,255));

  for (size_t i = 0; i < gridHeight; i++) {
    for (size_t j = 0; j < gridWidth; j++) {
      switch (gameGrid[i][j]) {
        case 'x':
          //Block
          al_draw_filled_rectangle(j*cTileSize, i*cTileSize,
              (j+1)*cTileSize, (i+1)*cTileSize, color);
          break;
        case 's':
          //Spike
          al_draw_filled_triangle((j+0.5)*cTileSize, i*cTileSize+1,
              (j+1)*cTileSize-1, (i+1)*cTileSize-1, 
              j*cTileSize+1, (i+1)*cTileSize-1, al_map_rgb(255,255,255));
          break;
        case '.':
          //Nothing
        default:
          break;
      }
    }
  }
}

void GameClass::ReadGameLevel(const char * lvl) {
  std::ifstream file(lvl);
  assert (!file.fail());
  file >> gridWidth >> gridHeight;

  gameGrid = new char*[gridHeight];
  for (size_t i = 0; i < gridHeight; i++) {
    gameGrid[i] = new char[gridWidth];
    for (size_t j = 0; j < gridWidth; j++) {
      char aux;
      file >> aux;
      switch (aux) {
        case 'p':
          hero.SetPosition(j*cTileSize, i*cTileSize);
          gameGrid[i][j] = '.';
          break;
        case 'a':
          enemies.push_back(new Ant(j*cTileSize, i*cTileSize));
          enemies.back()->SetGameGrid(gameGrid, gridWidth, gridHeight);
          gameGrid[i][j] = '.';
          break;
        case 'f':
          enemies.push_back(new Fly(j*cTileSize, i*cTileSize));
          enemies.back()->SetGameGrid(gameGrid, gridWidth, gridHeight);
          gameGrid[i][j] = '.';
          break;
        default:
          gameGrid[i][j] = aux;
          break;
      }
    }
  }

  hero.SetGameGrid(gameGrid, gridWidth, gridHeight);
}
