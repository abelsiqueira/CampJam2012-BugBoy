#include "gameclass.h"

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
