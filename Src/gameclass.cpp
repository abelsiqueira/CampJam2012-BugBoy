/* Copyright 2012 - Abel Soares Siqueira
 * 
 * This file is part of CampJam2012-Bugboy.
 * 
 * CampJam2012-Bugboy is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * CampJam2012-Bugboy is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with CampJam2012-Bugboy.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "gameclass.h"

GameClass::GameClass () {
  srand(time(0));

  AllegroInitialization();

  keyIsPressed[0] = false;
  keyIsPressed[1] = false;

  VisibleX = 0; 
  VisibleY = 0;
  inMenu = true;
  inGameEnd = false;
  inIntro = false;
  inCredits = false;
  menuOption = menuStartGame;
  choseOption = false;
  introScreen = 0;
  doubleJump = 0;

  regions.push_back(Region(1*cTileSize, 31*cTileSize, 12, 4));
  regions.back().SetTriggerEntity(hero);

  language = langEnglish;

#ifdef PRINT_LEVEL
  ALLEGRO_BITMAP *outImage;
  outImage = al_create_bitmap(cTileSize*gridWidth, cTileSize*gridHeight);
  al_set_target_bitmap(outImage);
  al_clear_to_color(al_map_rgb(0,0,0));
  DrawGame();
  al_save_bitmap("Images/level.png", outImage);
  al_set_target_bitmap(al_get_backbuffer(display));
#endif
}

void GameClass::AllegroInitialization () {
  al_init();
  display = al_create_display(cWindowWidth, cWindowHeight);
  al_set_window_title(display, "CampJam 2012 - Bug Boy");
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

  hugeFont = al_load_font("DejaVuSans.ttf", 80, 0);
  bigFont = al_load_font("DejaVuSans.ttf", 40, 0);
  normalFont = al_load_font("DejaVuSans.ttf", 20, 0);
  smallFont = al_load_font("DejaVuSans.ttf", 10, 0);
  ReadGameLevel("level1.map");
  
  music = al_load_audio_stream("Music/background.ogg", 4, 1024);
  assert(music);
  al_attach_audio_stream_to_mixer(music, al_get_default_mixer());
  al_set_audio_stream_gain(music, 0.5);
  al_set_audio_stream_playing(music, true);
  assert(al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP));

}

GameClass::~GameClass () {
  while (!enemies.empty()) {
    Enemy *p = enemies.front();
    delete p;
    enemies.pop_front();
  }
  while (!seeds.empty()) {
    Seed *p = seeds.front();
    delete p;
    seeds.pop_front();
  }
  while (!upgrades.empty()) {
    Upgrade *p = upgrades.front();
    delete p;
    upgrades.pop_front();
  }
  delete hero;
  if (doubleJump)
    delete doubleJump;
  for (size_t i = 0; i < gridHeight; i++)
    delete []gameGrid[i];
  delete []gameGrid;

  al_destroy_bitmap(level);
  al_destroy_font(bigFont);
  al_destroy_font(normalFont);
  al_destroy_font(smallFont);
  al_destroy_timer(timer);
  al_destroy_event_queue(eventQueue);
  al_destroy_display(display);
}

void GameClass::Reset () {
  while (!seeds.empty()) {
    Seed *p = seeds.front();
    delete p;
    seeds.pop_front();
  }
  for (std::list<Enemy*>::iterator iter = enemies.begin();
       iter != enemies.end(); iter++) {
    (*iter)->Reset();
  }
  for (std::list<Upgrade*>::iterator iter = upgrades.begin();
       iter != upgrades.end(); iter++) {
    (*iter)->Reset();
  }
  if (doubleJump)
    delete doubleJump;
  hero->Reset();
}

void GameClass::GameEnd () {
  inGameEnd = true;
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
      Update();
      redraw = true;
    } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      done = true;
    } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
               ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

    } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

    } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN ||
               ev.type == ALLEGRO_EVENT_KEY_UP) {
      KeyboardEventHandler(ev.keyboard.keycode, ev.type);
      hero->Move(keyIsPressed);
    }

    if (redraw && al_is_event_queue_empty(eventQueue)) {
      redraw = false;
      al_clear_to_color(al_map_rgb(0,0,0));

      if (inMenu) {
        DrawGameMenu();
      } else if (inIntro) {
        DrawGameIntro();
      } else if (inCredits) {
        DrawCredits();
      } else if (inGameEnd) {
        DrawGameEnd();
      } else {
        ALLEGRO_TRANSFORM T;
        al_identity_transform(&T);
        al_translate_transform(&T, -VisibleX, -VisibleY);
        al_use_transform(&T);

        DrawGame();
        al_identity_transform(&T);
        al_use_transform(&T);
        if (paused)
          DrawPauseMenu();
      }

      al_flip_display();
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
      float x = j*cTileSize, y = i*cTileSize;
      char aux;
      file >> aux;
      switch (aux) {
        case cPlayer:
          hero = new Hero(x, y);
          startX = x;
          startY = y;
          gameGrid[i][j] = cNone;
          break;
        case cAnt:
          enemies.push_back(new Ant(x, y));
          enemies.back()->SetGameGrid(gameGrid, gridWidth, gridHeight);
          gameGrid[i][j] = cNone;
          break;
        case cFly:
          enemies.push_back(new Fly(x, y));
          enemies.back()->SetGameGrid(gameGrid, gridWidth, gridHeight);
          gameGrid[i][j] = cNone;
          break;
        case cSpider:
          enemies.push_back(new Spider(x, y));
          enemies.back()->SetGameGrid(gameGrid, gridWidth, gridHeight);
          gameGrid[i][j] = cNone;
          break;
        case cSpiderBoss:
          pSpiderBoss = new SpiderBoss(x, y);
          pSpiderBoss->SetGameGrid(gameGrid, gridWidth, gridHeight);
          enemies.push_back(pSpiderBoss);
          gameGrid[i][j] = cNone;
          break;
        case cJump:
          upgrades.push_back(new Upgrade(jumpUpgrade, x, y));
          upgrades.back()->SetGameGrid(gameGrid, gridWidth, gridHeight);
          gameGrid[i][j] = cNone;
          break;
        case cSpeed:
          upgrades.push_back(new Upgrade(speedUpgrade, x, y));
          upgrades.back()->SetGameGrid(gameGrid, gridWidth, gridHeight);
          gameGrid[i][j] = cNone;
          break;
        case cLife:
          upgrades.push_back(new Upgrade(lifeUpgrade, x, y));
          upgrades.back()->SetGameGrid(gameGrid, gridWidth, gridHeight);
          gameGrid[i][j] = cNone;
          break;
        case cDoubleJump:
          upgrades.push_back(new Upgrade(doubleJumpUpgrade, x, y));
          upgrades.back()->SetGameGrid(gameGrid, gridWidth, gridHeight);
          gameGrid[i][j] = cNone;
          break;
        default:
          gameGrid[i][j] = aux;
          break;
      }
    }
  }

  level = al_create_bitmap(cTileSize*gridWidth, cTileSize*gridHeight);
  al_set_target_bitmap(level);
  DrawGameGrid();
  al_set_target_bitmap(al_get_backbuffer(display));

  hero->SetGameGrid(gameGrid, gridWidth, gridHeight);
}
