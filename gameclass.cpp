#include "gameclass.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

GameClass::GameClass () {
  srand(time(0));
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

  hugeFont = al_load_font("DejaVuSans.ttf", 80, 0);
  bigFont = al_load_font("DejaVuSans.ttf", 40, 0);
  normalFont = al_load_font("DejaVuSans.ttf", 20, 0);
  smallFont = al_load_font("DejaVuSans.ttf", 10, 0);

  keyIsPressed[0] = false;
  keyIsPressed[1] = false;

  ReadGameLevel("level1.map");
  VisibleX = 0; 
  VisibleY = 0;
  inMenu = true;
  inIntro = false;
  inCredits = false;
  menuOption = menuStartGame;
  choseOption = false;
  introScreen = 0;
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
      if (inMenu) {
        if (choseOption) {
          if (menuOption == menuStartGame) {
            inMenu = false;
            inIntro = true;
            choseOption = false;
          } else {
            done = true;
            inCredits = true;
            std::cout << "Credits" << std::endl;
          }
        }
      } else if (inIntro) {
        IntroUpdate();
      } else if (!paused) {
        if (pSpiderBoss && pSpiderBoss->IsDead()) {
          float x = pSpiderBoss->GetX(), y = pSpiderBoss->GetY();
          upgrades.push_back(new Upgrade(doubleJumpUpgrade, x, y));
          pSpiderBoss = 0;
        }
        hero.Update();
        // Update enemies
        {
          std::list<Enemy*>::iterator iter = enemies.begin(),
            iterEnd = enemies.end();
          while (iter != iterEnd) {
            (*iter)->Update();
            if ((*iter)->CollidesWith(hero)) {
              hero.Die();
            }
            iter++;
          }
        }
        // Update seeds
        {
          std::list<Seed*>::iterator iter = seeds.begin(),
            iterEnd = seeds.end();
          while (iter != iterEnd) {
            (*iter)->Update();
            for (std::list<Enemy*>::iterator i = enemies.begin();
                 i != enemies.end(); i++) {
              if ((*iter)->CollidesWith(*(*i))) {
                (*i)->Die();
                (*iter)->Die();
              }
            }
            iter++;
          }
        }
        for (std::list<Upgrade*>::iterator iter = upgrades.begin();
             iter != upgrades.end(); iter++) {
          (*iter)->Update();
          if ((*iter)->CollidesWith(hero)) {
            (*iter)->Take();
            hero.AddUpgrade((*iter)->GetType());
          }
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
      if (hero.IsDead()) {
        hero.Respawn(startX, startY);
      }
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

      if (inMenu) {
        DrawGameMenu();
      } else if (inIntro) {
        DrawGameIntro();
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

void GameClass::IntroUpdate () {

}

void GameClass::KeyboardEventHandler (unsigned int keycode, int ev_type) {
  if (inMenu && ev_type == ALLEGRO_EVENT_KEY_DOWN) {
    switch (keycode) {
      case ALLEGRO_KEY_UP:
      case ALLEGRO_KEY_DOWN:
        menuOption = 1 - menuOption;
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
    switch (keycode) {
      default:
        introScreen++;
        if (introScreen > 1)
          inIntro = false;
        break;
    }
  } else if (!inMenu) {
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
      case ALLEGRO_KEY_SPACE:
        if (ev_type == ALLEGRO_EVENT_KEY_DOWN) {
          seeds.push_back(hero.Shoot());
          if (seeds.back() == 0)
            seeds.pop_back();
        }
        break;
      default:
        break;
    }
  }
}

void GameClass::DrawHud () const {
  std::stringstream aux;
  aux << "Lives: " << hero.GetLives();
  al_draw_filled_rectangle(VisibleX + 2, VisibleY + 2, 
      VisibleX + 50, VisibleY + 15, al_map_rgb(0,0,0));
  al_draw_rectangle(VisibleX + 2, VisibleY + 2, 
      VisibleX + 50, VisibleY + 15, al_map_rgb(255,255,255), 1);
  al_draw_text(smallFont, al_map_rgb(255,255,255), VisibleX + 4, VisibleY + 2, 
      ALLEGRO_ALIGN_LEFT, aux.str().c_str());
}

void GameClass::DrawGameMenu () const {
  ALLEGRO_COLOR fontColor = al_map_rgb(255,255,255);

  al_draw_text(hugeFont, fontColor, cWindowWidth/2, 40, ALLEGRO_ALIGN_CENTRE, "Bug Boy");
  al_draw_text(bigFont, fontColor, cWindowWidth/2, 300, ALLEGRO_ALIGN_CENTRE, "Start Game");
  al_draw_text(bigFont, fontColor, cWindowWidth/2, 450, ALLEGRO_ALIGN_CENTRE, "Credits");

  float xdif = 160, ydif = 50;
  float x = cWindowWidth/2 - xdif, y = 300,
        xf = cWindowWidth/2 + xdif, yf = 300 + ydif;
  if (menuOption == menuCredits) {
    y += 150;
    yf += 150;
  }
  al_draw_rectangle(x, y, xf, yf, al_map_rgb(255,255,255), 0);
}

void GameClass::DrawGameIntro () const {
  ALLEGRO_COLOR fontColor = al_map_rgb(255,255,255);

  if (introScreen == 0) {
    std::string text[12] = {
        "  A boy is walking in a park chasing bugs.",
        "He goes into a cave, while chasing a firefly, and runs inside it for some time.",
        "He trips into a rock and falls in the ground.",
        "When he get up, he realises that he can't see the entrance.",
        "A little frightened, he walks around looking for an exit, when suddenly",
        "he feels a pressure in his pocket. A bag of sunflower seeds, which he brought",
        "along, was strangely getting bigger and bigger and bigger.",
        "He looks around and suddenly realize that, actually, he was getting smaller and",
        "smaller and smaller.",
        " - Well, I better find myself an exit, before something worse happens - he says",
        " - thankfully, this cave is naturally illuminated. Otherwise, I would be in",
        " great trouble."
    };
    for (int i = 0; i < 12; i++)
      al_draw_text(normalFont, fontColor, cWindowWidth/2, 70 + i*45, ALLEGRO_ALIGN_CENTRE, text[i].c_str());
    al_draw_text(normalFont, fontColor, cWindowWidth - 20, cWindowHeight - 30, ALLEGRO_ALIGN_RIGHT,
        "Press any key");
  } else {
    std::string text[8] = {
      "Move the boy with the arrow left and right",
      "Jump with the arrow up",
      "Throw your seeds at the bugs with the space bar",
      "Collect upgrades to improve the boy's abilities",
      "      Increase the jump height",
      "      Increase the movement speed",
      "      Increase the health",
      "      Enables double jump"
    };

    for (int i = 0; i < 8; i++)
      al_draw_text(normalFont, fontColor, 200, 200 + i*45, ALLEGRO_ALIGN_LEFT, text[i].c_str());

    Upgrade jump      (jumpUpgrade, 200, 200 + 4*45), 
            speed     (speedUpgrade, 200, 200 + 5*45), 
            life      (lifeUpgrade, 200, 200 + 6*45),
            doubleJump(doubleJumpUpgrade, 200, 200 + 7*45);

    jump.Draw();
    speed.Draw();
    life.Draw();
    doubleJump.Draw();

    al_draw_text(bigFont, fontColor, cWindowWidth/2, 40, ALLEGRO_ALIGN_CENTRE, "Instructions");

    al_draw_text(normalFont, fontColor, cWindowWidth - 20, cWindowHeight - 30, ALLEGRO_ALIGN_RIGHT,
        "Press any key");
  }
}

void GameClass::DrawPauseMenu () const {
  ALLEGRO_COLOR fontColor = al_map_rgb(255,255,255);

  al_draw_filled_rectangle(0, 0, 1280, 720, al_map_rgba(0,0,0,230));
  al_draw_text(bigFont, fontColor, cWindowWidth/2, 40, ALLEGRO_ALIGN_CENTRE, "Pause Menu");

  std::stringstream aux;
  aux << "Lives: " << hero.GetLives();
  al_draw_text(bigFont, fontColor, 50, 150, ALLEGRO_ALIGN_LEFT, aux.str().c_str());
}

void GameClass::DrawGame () const {
//  DrawGameGrid();
  al_draw_bitmap(level, 0, 0, 0);
  hero.Draw();
  {
    std::list<Enemy*>::const_iterator iter = enemies.begin(),
      iterEnd = enemies.end();
    while (iter != iterEnd) {
      (*iter)->Draw();
      iter++;
    }
  }
  {
    std::list<Seed*>::const_iterator iter = seeds.begin(),
      iterEnd = seeds.end();
    while (iter != iterEnd) {
      (*iter)->Draw();
      iter++;
    }
  }
  for (std::list<Upgrade*>::const_iterator iter = upgrades.begin();
       iter != upgrades.end(); iter++) {
    (*iter)->Draw();
  }
  DrawHud();
}

void GameClass::DrawGameGrid () const {
  ALLEGRO_COLOR color(al_map_rgb(255,255,255));

  for (size_t i = 0; i < gridHeight; i++) {
    for (size_t j = 0; j < gridWidth; j++) {
      int x = j*cTileSize, y = i*cTileSize,
          xf = (j+1)*cTileSize, yf = (i+1)*cTileSize;
      switch (gameGrid[i][j]) {
        case cBlock:
          //Block
          al_draw_filled_rectangle(x, y, xf, yf, color);
          al_draw_line(x, y, xf, yf, al_map_rgb(0,0,0),0);
          al_draw_line(x, yf, xf, y, al_map_rgb(0,0,0),0);
          al_draw_line(x, (y+yf)/2, (x+xf)/2, y, al_map_rgb(0,0,0),0);
          al_draw_line(x, (y+yf)/2, (x+xf)/2, yf, al_map_rgb(0,0,0),0);
          al_draw_line(xf, (y+yf)/2, (x+xf)/2, y, al_map_rgb(0,0,0),0);
          al_draw_line(xf, (y+yf)/2, (x+xf)/2, yf, al_map_rgb(0,0,0),0);
          break;
        case cSpike:
          //Spike
          al_draw_filled_triangle((j+0.5)*cTileSize, i*cTileSize+1,
              (j+1)*cTileSize-1, (i+1)*cTileSize-1, 
              j*cTileSize+1, (i+1)*cTileSize-1, al_map_rgb(255,255,255));
          break;
        case cNone:
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
      float x = j*cTileSize, y = i*cTileSize;
      char aux;
      file >> aux;
      switch (aux) {
        case cPlayer:
          hero.SetPosition(x, y);
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
          gameGrid[i][j] = cNone;
          break;
        case cSpeed:
          upgrades.push_back(new Upgrade(speedUpgrade, x, y));
          gameGrid[i][j] = cNone;
          break;
        case cLife:
          upgrades.push_back(new Upgrade(lifeUpgrade, x, y));
          gameGrid[i][j] = cNone;
          break;
        case cDoubleJump:
          upgrades.push_back(new Upgrade(doubleJumpUpgrade, x, y));
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

  hero.SetGameGrid(gameGrid, gridWidth, gridHeight);
}
