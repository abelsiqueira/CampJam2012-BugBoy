#include "gameclass.h"

void GameClass::DrawHud () const {
  std::stringstream aux;
  if (language == langEnglish)
    aux << "Lives: " << hero->GetLives();
  else
    aux << "Vidas: " << hero->GetLives();

  al_draw_filled_rectangle(VisibleX + 2, VisibleY + 2, 
      VisibleX + 85, VisibleY + 28, cBlack);
  al_draw_rectangle(VisibleX + 2, VisibleY + 2, 
      VisibleX + 85, VisibleY + 28, cWhite, 1);
  al_draw_text(normalFont, cWhite, VisibleX + 4, VisibleY + 2, 
      ALLEGRO_ALIGN_LEFT, aux.str().c_str());
}

void GameClass::DrawGameMenu () const {
  ALLEGRO_COLOR fontColor = cWhite;

  al_draw_text(hugeFont, fontColor, cWindowWidth/2, 40, ALLEGRO_ALIGN_CENTRE, 
      "CampJam2012 - Bug Boy");
  for (int i = 0; i < 4; i++) {
    al_draw_text(bigFont, fontColor, cWindowWidth/2, 300 + i*100,
        ALLEGRO_ALIGN_CENTRE, cMenuOptionsText[language][i].c_str());
  }

  float xdif = 190, ydif = 50;
  float x = cWindowWidth/2 - xdif, y = 300 + 100*menuOption,
        xf = cWindowWidth/2 + xdif, yf = y + ydif;

  al_draw_rectangle(x, y, xf, yf, cWhite, 0);
}

void GameClass::DrawGameIntro () const {
  ALLEGRO_COLOR fontColor = cWhite;

  if (introScreen == 0) {
    for (size_t i = 0; i < cGameIntroLines; i++) {
      al_draw_text(normalFont, fontColor, cWindowWidth/2, 70 + i*45, 
          ALLEGRO_ALIGN_CENTRE, cGameIntroText[language][i].c_str());
    }
    al_draw_text(normalFont, fontColor, cWindowWidth - 20, cWindowHeight - 30, 
        ALLEGRO_ALIGN_RIGHT, cPressAnyKey[language].c_str());
  } else {
    for (size_t i = 0; i < cInstructionsLines; i++) {
      al_draw_text(normalFont, fontColor, 200, 200 + i*45, ALLEGRO_ALIGN_LEFT, 
          cInstructionsText[language][i].c_str());
    }

    Upgrade jump      (jumpUpgrade,       200, 180 + 5*45), 
            speed     (speedUpgrade,      200, 180 + 6*45), 
            life      (lifeUpgrade,       200, 180 + 7*45),
            doubleJump(doubleJumpUpgrade, 200, 180 + 8*45);

    jump.Draw();
    speed.Draw();
    life.Draw();
    doubleJump.Draw();


    al_draw_text(bigFont, fontColor, cWindowWidth/2, 40, ALLEGRO_ALIGN_CENTRE, 
        cInstructions[language].c_str());

    al_draw_text(normalFont, fontColor, cWindowWidth - 20, cWindowHeight - 30, ALLEGRO_ALIGN_RIGHT,
        cPressAnyKey[language].c_str());
  }
}

void GameClass::DrawCredits () const {
  ALLEGRO_COLOR fontColor = cWhite;

  al_draw_text(bigFont, fontColor, cWindowWidth/2, 10, ALLEGRO_ALIGN_CENTRE, 
      cCredits[language].c_str());

  for (size_t i = 0; i < cCreditsLines; i++)
    al_draw_text(normalFont, fontColor, 100, 50 + i*50, ALLEGRO_ALIGN_LEFT, 
        cCreditsText[language][i].c_str());
}

void GameClass::DrawGameEnd () const {
  ALLEGRO_COLOR fontColor = cWhite;

  for (size_t i = 0; i < cGameEndLines; i++)
    al_draw_text(normalFont, fontColor, cWindowWidth/2, 70 + i*45, 
        ALLEGRO_ALIGN_CENTRE, cGameEndText[language][i].c_str());
  al_draw_text(bigFont, fontColor, cWindowWidth/2, 500, 
      ALLEGRO_ALIGN_CENTRE, cThanks[language].c_str());
  al_draw_text(normalFont, fontColor, cWindowWidth - 20, cWindowHeight - 30, 
      ALLEGRO_ALIGN_RIGHT, cPressAnyKey[language].c_str());
}

void GameClass::DrawPauseMenu () const {
  ALLEGRO_COLOR fontColor = cBlack;

  al_draw_filled_rectangle(0, 0, cWindowWidth, cWindowHeight, cWhite);
  al_draw_text(hugeFont, fontColor, cWindowWidth/2, 40, ALLEGRO_ALIGN_CENTRE, 
      cPause[language].c_str());

  std::stringstream aux[8];
  for (int i = 0; i < 4; i++)
    aux[i] << cPauseInformation[language][i];
  aux[4] << hero->GetLives();
  aux[5] << hero->GetJumpUpgrades();
  aux[6] << hero->GetSpeedUpgrades();
  aux[7] << hero->GetLifeUpgrades();


  float xdif = 500, ydif = 50;
  float x = cWindowWidth/2 + 10, y = 250 + 100*pauseOption,
        xf = cWindowWidth/2 + xdif, yf = y + ydif;

  al_draw_rectangle(25, 225, 600, 475, cBlack, 0);

  for (int i = 0; i < 4; i++)
    al_draw_text(bigFont, fontColor, 50, 250 + 50*i, 
        ALLEGRO_ALIGN_LEFT, aux[i].str().c_str());
  for (int i = 0; i < 4; i++)
    al_draw_text(bigFont, fontColor, 550, 250 + 50*i, 
        ALLEGRO_ALIGN_LEFT, aux[i+4].str().c_str());

  for (int i = 0; i < 3; i++)
    al_draw_text(bigFont, fontColor, cWindowWidth/2 + 50, 250 + 100*i, 
        ALLEGRO_ALIGN_LEFT, cPauseMenuOptionsText[language][i].c_str());

  al_draw_rectangle(x, y, xf, yf, cBlack,0);
}

void GameClass::DrawGame () const {
  al_draw_bitmap_region(level, VisibleX, VisibleY,
      cWindowWidth, cWindowHeight, VisibleX, VisibleY, 0);
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

  regionExit->Draw();
  regionSpiderBoss->Draw();
  regionCricketBoss->Draw();

  DrawHud();
}


void GameClass::DrawGameGrid () const {
  ALLEGRO_COLOR color(cWhite);

  for (size_t i = 0; i < gridHeight; i++) {
    for (size_t j = 0; j < gridWidth; j++) {
      int x = j*cTileSize, y = i*cTileSize,
          xf = (j+1)*cTileSize, yf = (i+1)*cTileSize;
      switch (gameGrid[i][j]) {
        case cBlock:
          if (i > 0 && gameGrid[i-1][j] == cNone)
            DrawFloor(x, y, xf, yf);
          else
            DrawBlock(x, y, xf, yf);
          break;
        case cSpike:
          DrawSpike(x, y, xf, yf);
          break;
        case cNone:
          if (i < gridHeight-1 && gameGrid[i+1][j] == cBlock)
            DrawGrass(x, y, xf, yf);
          //Nothing
        default:
          break;
      }
    }
  }

  float x = regionExit->GetX() + 
      cTileSize*regionExit->GetWidth()/2;
  float y = regionExit->GetY();
  al_draw_text(hugeFont, cWhite, x, y,
      ALLEGRO_ALIGN_CENTRE, cExit[language].c_str());
}

void GameClass::DrawGrass (float, float, float, float) const {
}

void GameClass::DrawFloor (float x, float y, float xf, float yf) const {
  al_draw_filled_rectangle(x, y, xf, yf, cWhite);
  for (int i = 0; i < 5; i++) {
    float z = y + 2*i;
    al_draw_line(x, z, xf, z, cBlack, 0);
  }
  for (size_t i = 0; i < 20; i++) {
    float difX = 10 + (cTileSize-10)*(rand()%1001)/1000.0;
    float difY = 10 + (cTileSize-10)*(rand()%1001)/1000.0;
    al_draw_pixel(x + difX, y + difY, cBlack);
  }
}

void GameClass::DrawBlock (float x, float y, float xf, float yf) const {
  al_draw_filled_rectangle(x, y, xf, yf, cWhite);
  for (size_t i = 0; i < 20; i++) {
    float difX = cTileSize*(rand()%1001)/1000.0;
    float difY = cTileSize*(rand()%1001)/1000.0;
    al_draw_pixel(x + difX, y + difY, cBlack);
  }
}

void GameClass::DrawSpike (float x, float y, float xf, float yf) const {
  if ((xf - x < cTileSize/6) || 
      (rand()%1001 < 0)) {
    float z = y + 0.2*cTileSize*(rand()%1001)/1000.0;
    al_draw_filled_triangle((x+xf)/2, z+1, xf, yf, x, yf, cWhite);
    return;
  }
  float xm = x + (xf - x)*(1 + 2*(rand()%1001)/1000.0)/4;
  DrawSpike( x, y, xm, yf);
  DrawSpike(xm, y, xf, yf);
}
