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
#include <string>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>

GameClass::GameClass () {
  srand(time(0));
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

  keyIsPressed[0] = false;
  keyIsPressed[1] = false;

  ReadGameLevel("level1.map");
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

  music = 0;
  music = al_load_audio_stream("Music/background.ogg", 4, 1024);
  assert(music);
  al_attach_audio_stream_to_mixer(music, al_get_default_mixer());
  al_set_audio_stream_gain(music, 0.5);
  al_set_audio_stream_playing(music, true);
  assert(al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP));

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
      if (inMenu) {
        if (choseOption) {
            inMenu = false;
          choseOption = false;
          if (menuOption == menuStartGame) {
            inIntro = true;
            Reset();
          } else if (menuOption == menuCredits) {
            inCredits = true;
          } else if (menuOption == menuLanguage) {
            language = 1 - language;
            inMenu = true;
          } else {
            inMenu = true;
            done = true;
          }
        }
      } else if (inIntro) {
        IntroUpdate();
      } else if (paused) {
        if (choseOption) {
          choseOption = false;
          if (pauseOption == pauseContinue) {
             paused = false;
          } else if (pauseOption == pauseGoToMenu) {
            inMenu = true;
            paused = false;
          } else if (pauseOption == pauseExit) {
            done = true;
          }
        }
      } else if (!paused) {
        if (pSpiderBoss && pSpiderBoss->IsDead() && (doubleJump == 0) ) {
          float x = pSpiderBoss->GetX(), y = pSpiderBoss->GetY();
          doubleJump = new Upgrade(doubleJumpUpgrade, x, y);
          doubleJump->SetGameGrid(gameGrid, gridWidth, gridHeight);
        }
        hero->Update();
        // Update enemies
        {
          std::list<Enemy*>::iterator iter = enemies.begin(),
            iterEnd = enemies.end();
          while (iter != iterEnd) {
            (*iter)->Update();
            if ((*iter)->CollidesWith(*hero)) {
              hero->Die();
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
        // Update upgrades
        for (std::list<Upgrade*>::iterator iter = upgrades.begin();
             iter != upgrades.end(); iter++) {
          (*iter)->Update();
          if ((*iter)->CollidesWith(*hero)) {
            (*iter)->Take();
            hero->AddUpgrade((*iter)->GetType());
          }
        }
        if (doubleJump) {
          doubleJump->Update();
          if (doubleJump->CollidesWith(*hero)) {
            doubleJump->Take();
            hero->AddUpgrade(doubleJump->GetType());
          }
        }
        // Update regions
        for (std::list<Region>::iterator iter = regions.begin();
             iter != regions.end(); iter++) {
          iter->Update();
          if (iter->IsTriggered()) {
            GameEnd();
          }
        }
        VisibleX = hero->GetX() - cWindowWidth/2;
        VisibleY = hero->GetY() -  cWindowHeight/2;
        if (VisibleX < 0) 
          VisibleX = 0;
        else if (VisibleX > (int)(cTileSize*gridWidth - cWindowWidth))
          VisibleX = cTileSize*gridWidth - cWindowWidth;
        if (VisibleY < 0) 
          VisibleY = 0;
        else if (VisibleY > (int)(cTileSize*gridHeight - cWindowHeight))
          VisibleY = cTileSize*gridHeight - cWindowHeight;
      }
      if (hero->IsDead()) {
        hero->Respawn(startX, startY);
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

void GameClass::IntroUpdate () {

}

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
    switch (keycode) {
      default:
        introScreen++;
        if (introScreen > 1)
          inIntro = false;
        break;
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

void GameClass::DrawHud () const {
  std::stringstream aux;
  if (language == langEnglish)
    aux << "Lives: " << hero->GetLives();
  else
    aux << "Vidas: " << hero->GetLives();

  al_draw_filled_rectangle(VisibleX + 2, VisibleY + 2, 
      VisibleX + 85, VisibleY + 28, al_map_rgb(0,0,0));
  al_draw_rectangle(VisibleX + 2, VisibleY + 2, 
      VisibleX + 85, VisibleY + 28, al_map_rgb(255,255,255), 1);
  al_draw_text(normalFont, al_map_rgb(255,255,255), VisibleX + 4, VisibleY + 2, 
      ALLEGRO_ALIGN_LEFT, aux.str().c_str());
}

void GameClass::DrawGameMenu () const {
  ALLEGRO_COLOR fontColor = al_map_rgb(255,255,255);
  std::string start[2] = { "Start Game", "Iniciar o Jogo" };
  std::string cred[2] = { "Credits", "Créditos" };
  std::string lang[2] = {"Change Language", "Mudar Idioma" };
  std::string ex[2] = { "Exit", "Sair" };

  al_draw_text(hugeFont, fontColor, cWindowWidth/2, 40, ALLEGRO_ALIGN_CENTRE, 
      "CampJam2012 - Bug Boy");
  al_draw_text(bigFont, fontColor, cWindowWidth/2, 300, ALLEGRO_ALIGN_CENTRE, 
      start[language].c_str());
  al_draw_text(bigFont, fontColor, cWindowWidth/2, 400, ALLEGRO_ALIGN_CENTRE, 
      cred[language].c_str());
  al_draw_text(bigFont, fontColor, cWindowWidth/2, 500, ALLEGRO_ALIGN_CENTRE, 
      lang[language].c_str());
  al_draw_text(bigFont, fontColor, cWindowWidth/2, 600, ALLEGRO_ALIGN_CENTRE, 
      ex[language].c_str());

  float xdif = 190, ydif = 50;
  float x = cWindowWidth/2 - xdif, y = 300 + 100*menuOption,
        xf = cWindowWidth/2 + xdif, yf = y + ydif;

  al_draw_rectangle(x, y, xf, yf, al_map_rgb(255,255,255), 0);
}

void GameClass::DrawGameIntro () const {
  ALLEGRO_COLOR fontColor = al_map_rgb(255,255,255);

  if (introScreen == 0) {
    if (language == langEnglish) {
      std::string text[12] = {
          "  A boy is walking in a park chasing bugs.",
          "He goes into a cave, while chasing a firefly, and plays inside it for some time.",
          "He trips into a rock and falls in the ground.",
          "When he gets up, he realises that he can't see the entrance.",
          "A little frightened, he walks around looking for an exit, when suddenly",
          "he feels a pressure in his pocket. A bag of sunflower seeds, which he brought",
          "along, was strangely getting bigger and bigger and bigger.",
          "He looks around and suddenly realizes that, actually, he was getting smaller and",
          "smaller and smaller.",
          " - Well, I better find myself an exit, before something worse happens - he says",
          " - thankfully, this cave is naturally illuminated. Otherwise, I would be in",
          " great trouble."
      };
      for (int i = 0; i < 12; i++)
        al_draw_text(normalFont, fontColor, cWindowWidth/2, 70 + i*45, ALLEGRO_ALIGN_CENTRE, text[i].c_str());
    } else {
      std::string text[12] = {
          "  Um garoto está andando pelo parque caçando insetos.",
          "Ele entra numa caversa, enquanto caçava um vagalume, e brinca lá dentro por",
          "um tempo. Ele tropeça numa pedra e cai no chão.",
          "Quando ele levanta, ele percebe que não consegue ver a entrada.",
          "Um pouco assustado, ele anda um pouco procurando por uma saída quando, de",
          "repente, sente uma pressão no seu bolso. Um saco de sementes de girassol, que",
          "ele havia trazido, estava estranhamente crescendo e crescendo e crescendo.",
          "Ele olha ao redor e percebe que, na verdade, ele estava ficando menor e menor",
          "e menor.",
          " - Bem, é melhor eu encontrar uma saída, antes que alguma coisa pior aconteça",
          " - ele diz - ainda bem que esta caverna é iluminada naturalmente. Caso contrário",
          " eu estaria em sérios problemas."
      };
      for (int i = 0; i < 12; i++)
        al_draw_text(normalFont, fontColor, cWindowWidth/2, 70 + i*45, ALLEGRO_ALIGN_CENTRE, text[i].c_str());
    }
    al_draw_text(normalFont, fontColor, cWindowWidth - 20, cWindowHeight - 30, ALLEGRO_ALIGN_RIGHT,
        "Press any key");
  } else {
    if (language == langEnglish) {
      std::string text[9] = {
        "Move the boy with the arrows left and right",
        "Jump with the arrow up",
        "Throw your seeds at the bugs with the space bar",
        "Pause with ESC or P",
        "Collect upgrades to improve the boy's abilities",
        "      Increase the jump height",
        "      Increase the movement speed",
        "      Increase the life",
        "      Enables double jump"
      };

      for (int i = 0; i < 9; i++)
        al_draw_text(normalFont, fontColor, 200, 200 + i*45, ALLEGRO_ALIGN_LEFT, text[i].c_str());
    } else {
      std::string text[9] = {
        "Mova o garoto com os direcionais para esquerda e direita",
        "Pule com o direcional para cima",
        "Atire suas sementes nos insetos com a barra de espaço",
        "Pause com ESC ou P",
        "Colete upgrades para melhorar as habilidades do garoto",
        "      Aumenta a altura do pulo",
        "      Aumenta a velocidade de movimento",
        "      Aumenta a vida",
        "      Permite o salto duplo"
      };

      for (int i = 0; i < 9; i++)
        al_draw_text(normalFont, fontColor, 200, 200 + i*45, ALLEGRO_ALIGN_LEFT, text[i].c_str());
    }

    Upgrade jump      (jumpUpgrade,       200, 180 + 5*45), 
            speed     (speedUpgrade,      200, 180 + 6*45), 
            life      (lifeUpgrade,       200, 180 + 7*45),
            doubleJump(doubleJumpUpgrade, 200, 180 + 8*45);

    jump.Draw();
    speed.Draw();
    life.Draw();
    doubleJump.Draw();

    std::string inst[2] = { "Instruction", "Instruções" };
    std::string any[2]  = { "Press any key", "Aperte qualquer tecla" };

    al_draw_text(bigFont, fontColor, cWindowWidth/2, 40, ALLEGRO_ALIGN_CENTRE, 
        inst[language].c_str());

    al_draw_text(normalFont, fontColor, cWindowWidth - 20, cWindowHeight - 30, ALLEGRO_ALIGN_RIGHT,
        any[language].c_str());
  }
}

void GameClass::DrawCredits () const {
  ALLEGRO_COLOR fontColor = al_map_rgb(255,255,255);
  std::string cred[2] = { "Credits", "Créditos" };

  al_draw_text(bigFont, fontColor, cWindowWidth/2, 10, ALLEGRO_ALIGN_CENTRE, cred[language].c_str());

  if (language == langEnglish) {
    std::string text[13] = {
      "Game Design: Abel Soares Siqueira",
      "Game Programming: Abel Soares Siqueira",
      "Game Art:",
      "  Spider: http://openclipart.org/detail/73135/spider-by-redccshirt",
      "  Fly: http://openclipart.org/detail/119407/fly-01-by-anonymous",
      "  Ant: http://openclipart.org/detail/18532/formiga-by-guseinstein",
      "  Music: Cave by Miguel Herrero: http://www.jamendo.com/en/track/224865/cave",
      "",
      "Game developed for the CampJam'12",
      "This game is distributed under the terms of the GNU GPL. Read the README.md and COPYING",
      "You can download this game source at",
      "        https://github.com/abelsiqueira/CampJam2012-BugBoy.git",
      "Special thanks to Kally Chung for all the support and for playing the game"
    };
    for (int i = 0; i < 13; i++)
      al_draw_text(normalFont, fontColor, 100, 50 + i*50, ALLEGRO_ALIGN_LEFT, text[i].c_str());
  } else {
    std::string text[13] = {
      "Design do Jogo: Abel Soares Siqueira",
      "Programação: Abel Soares Siqueira",
      "Arte:",
      "  Aranha: http://openclipart.org/detail/73135/spider-by-redccshirt",
      "  Mosca: http://openclipart.org/detail/119407/fly-01-by-anonymous",
      "  Formiga: http://openclipart.org/detail/18532/formiga-by-guseinstein",
      "  Música: Cave by Miguel Herrero: http://www.jamendo.com/en/track/224865/cave",
      "",
      "Jogo desenvolvido para o CampJam'12",
      "Este jogo é distribuído sob os termos da GNU GPL. Leia README.md e COPYING",
      "Você pode baixar o código deste jogo em",
      "        https://github.com/abelsiqueira/CampJam2012-BugBoy.git",
      "Agradecimentos especiais à Kally Chung pelo suporte e por jogar"
    };
    for (int i = 0; i < 13; i++)
      al_draw_text(normalFont, fontColor, 100, 50 + i*50, ALLEGRO_ALIGN_LEFT, text[i].c_str());
  }
}

void GameClass::DrawGameEnd () const {
  ALLEGRO_COLOR fontColor = al_map_rgb(255,255,255);

  if (language == langEnglish) {
    std::string text[8] = {
      "  With his new found powers, the boy finds the way he came from.",
      "As he approaches the cave entrance, the fatigue kicks in. In his",
      "tiny body, this was enough to make him feint...",
      "",
      "  When he wakes up, he is a regular boy again, devoid of any special",
      "powers, but back to his usual size.",
      " - Could I've been dreaming? Is this the real life? Is this just fantasy?",
      " Was my mind playing tr... Oh a dragonfly!"
    };
    for (int i = 0; i < 8; i++)
      al_draw_text(normalFont, fontColor, cWindowWidth/2, 70 + i*45, 
          ALLEGRO_ALIGN_CENTRE, text[i].c_str());
    al_draw_text(bigFont, fontColor, cWindowWidth/2, 500, 
        ALLEGRO_ALIGN_CENTRE, "Thanks for playing");
    al_draw_text(normalFont, fontColor, cWindowWidth - 20, cWindowHeight - 30, ALLEGRO_ALIGN_RIGHT,
        "Press any key");
  } else {
    std::string text[8] = {
      "  Com seus poderes recém descobertos, o garoto encontra o lugar de onde veio.",
      "Conforme se aproxima da entrada da caverna, a fatiga é demais. Em seu corpo",
      "minúsculo, isso é suficiente para fazê-lo desmaiar...",
      "",
      "  Quando ele acorda, ele é apenas um garoto normal novamente, sem nenhuma poder",
      "especial, mas com seu tamanho usual",
      " - Será que estive apenas sonhando? Esta é a vida real? É apenas fantasia?",
      " Será que minha mente est... Olha, uma libélula!"
    };
    for (int i = 0; i < 8; i++)
      al_draw_text(normalFont, fontColor, cWindowWidth/2, 70 + i*45, 
          ALLEGRO_ALIGN_CENTRE, text[i].c_str());
    al_draw_text(bigFont, fontColor, cWindowWidth/2, 500, 
        ALLEGRO_ALIGN_CENTRE, "Obrigado por jogar");
    al_draw_text(normalFont, fontColor, cWindowWidth - 20, cWindowHeight - 30, ALLEGRO_ALIGN_RIGHT,
        "Aperte qualquer tecla");
  }
}

void GameClass::DrawPauseMenu () const {
  ALLEGRO_COLOR fontColor = al_map_rgb(0,0,0);

  std::string pause[2] = { "Pause Menu", "Menu de Pausa" };
  std::string lives[2] = { "Lives: ", "Vidas: " };
  std::string jump[2] = { "Jump Upgrades: ", "Upgrades de Pulo: "};
  std::string speed[2] = { "Speed Upgrades: ", "Upgrades de Velocidade: "};
  std::string life[2] = { "Life Upgrades: ", "Upgrades de Vida: "};

  al_draw_filled_rectangle(0, 0, cWindowWidth, cWindowHeight, al_map_rgb(255,255,255));
  al_draw_text(hugeFont, fontColor, cWindowWidth/2, 40, ALLEGRO_ALIGN_CENTRE, pause[language].c_str());

  std::stringstream aux[8];
  aux[0] << lives[language];
  aux[4] << hero->GetLives();
  aux[1] << jump[language];
  aux[5] << hero->GetJumpUpgrades();
  aux[2] << speed[language];
  aux[6] << hero->GetSpeedUpgrades();
  aux[3] << life[language];
  aux[7] << hero->GetLifeUpgrades();


  float xdif = 500, ydif = 50;
  float x = cWindowWidth/2 + 10, y = 250 + 100*pauseOption,
        xf = cWindowWidth/2 + xdif, yf = y + ydif;

  al_draw_rectangle(25, 225, 600, 475, al_map_rgb(0,0,0), 0);

  for (int i = 0; i < 4; i++)
    al_draw_text(bigFont, fontColor, 50, 250 + 50*i, 
        ALLEGRO_ALIGN_LEFT, aux[i].str().c_str());
  for (int i = 0; i < 4; i++)
    al_draw_text(bigFont, fontColor, 550, 250 + 50*i, 
        ALLEGRO_ALIGN_LEFT, aux[i+4].str().c_str());

  if (language == langEnglish) {
    std::string options[3] = { "Continue", "Return to Main Menu", "Exit" };
    for (int i = 0; i < 3; i++)
      al_draw_text(bigFont, fontColor, cWindowWidth/2 + 50, 250 + 100*i, 
          ALLEGRO_ALIGN_LEFT, options[i].c_str());
  } else {
    std::string options[3] = { "Continuar", "Retorna ao Menu", "Sair" };
    for (int i = 0; i < 3; i++)
      al_draw_text(bigFont, fontColor, cWindowWidth/2 + 50, 250 + 100*i, 
          ALLEGRO_ALIGN_LEFT, options[i].c_str());
  }

  al_draw_rectangle(x, y, xf, yf, al_map_rgb(0,0,0),0);
}

void GameClass::DrawGame () const {
  al_draw_bitmap(level, 0, 0, 0);
  hero->Draw();
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
  if (doubleJump)
    doubleJump->Draw();
  for (std::list<Region>::const_iterator iter = regions.begin();
       iter != regions.end(); iter++) {
    iter->Draw();
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

  if (language == langEnglish) {
    al_draw_text(hugeFont, al_map_rgb(255,255,255), 
        6*cTileSize, 31*cTileSize, ALLEGRO_ALIGN_CENTRE, "EXIT");
  } else {
    al_draw_text(hugeFont, al_map_rgb(255,255,255), 
        6*cTileSize, 31*cTileSize, ALLEGRO_ALIGN_CENTRE, "SAÍDA");
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
