#include "gameclass.h"

void GameClass::MenuUpdate () {
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
}

void GameClass::PauseMenuUpdate () {
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
}

void GameClass::EnemiesUpdate () {
  std::list<Enemy*>::iterator iter = enemies.begin(),
    iterEnd = enemies.end();

  while (iter != iterEnd) {
    Enemy *p = *iter;
    p->Update();
    if (p->CollidesWith(*hero)) {
      hero->Die();
    }
    iter++;
  }
}

void GameClass::UpgradesUpdate () {
  std::list<Upgrade*>::iterator iter = upgrades.begin(),
    iterEnd = upgrades.end();

  while (iter != iterEnd) {
    Upgrade *p = *iter;
    p->Update();
    if (p->CollidesWith(*hero)) {
      p->Take();
      hero->AddUpgrade(p->GetType());
    }
    iter++;
  }
  if (doubleJump) {
    doubleJump->Update();
    if (doubleJump->CollidesWith(*hero)) {
      doubleJump->Take();
      hero->AddUpgrade(doubleJump->GetType());
    }
  }
}

void GameClass::SeedsUpdate () {
  std::list<Seed*>::iterator iter = seeds.begin(),
    iterEnd = seeds.end();

  while (iter != iterEnd) {
    Seed *p = *iter;
    p->Update();
    for (std::list<Enemy*>::iterator i = enemies.begin();
         i != enemies.end(); i++) {
      if (p->CollidesWith(*(*i))) {
        (*i)->Die();
        p->Die();
      }
    }
    iter++;
  }
}

void GameClass::Update () {
  if (inMenu) {
    MenuUpdate();
  } else if (paused) {
    PauseMenuUpdate();
  } else if (!paused) {
    if (pSpiderBoss && 
        pSpiderBoss->IsDead() && 
        doubleJump == 0) {
      float x = pSpiderBoss->GetX(), y = pSpiderBoss->GetY();
      doubleJump = new Upgrade(doubleJumpUpgrade, x, y);
      doubleJump->SetGameGrid(gameGrid, gridWidth, gridHeight);
    }
    hero->Update();
    EnemiesUpdate();
    SeedsUpdate();
    UpgradesUpdate();
    // Update regions
    regionExit->Update();
    if (regionExit->IsTriggered()) {
      GameEnd();
    }
    regionSpiderBoss->Update();
    if (regionSpiderBoss->IsTriggered()) {
      pSpiderBoss->Activate();
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
}
