#include "upgrade.h"

Upgrade::Upgrade (UpgradeType ut, float x, float y) {
  posX = x;
  posY = y;
  upgradeType = ut;
  boxWidth = 0.5;
  boxHeight = 0.5;
  image = 0;
  visible = true;
}

Upgrade::~Upgrade () {
  if (image)
    al_destroy_bitmap(image);
}

void Upgrade::Update () {
}

void Upgrade::Draw () const {
  if (!visible)
    return;

  float x = posX, y = posY,
        xm = x + boxWidth*cTileSize/2, ym = y + boxHeight*cTileSize/2,
        xf = x + boxWidth*cTileSize,   yf = y + boxHeight*cTileSize;
  al_draw_rectangle(x, y, xf, yf, al_map_rgb(255,255,255), 0);

  switch (upgradeType) {
    case jumpUpgrade:
      al_draw_filled_triangle(x, ym, xf, ym, xm, y, al_map_rgb(255,255,255));
      break;
    case speedUpgrade:
      al_draw_line(x, ym, xf, ym, al_map_rgb(255,255,255), 0);
      al_draw_line(x, (y+ym)/2, xf, (y+ym)/2, al_map_rgb(255,255,255), 0);
      al_draw_line(x, (yf+ym)/2, xf, (yf+ym)/2, al_map_rgb(255,255,255), 0);
      break;
    default:
      break;
  }
}

bool Upgrade::CollidesWith (const Hero & hero) const {
  if (!visible || hero.IsDead())
    return false;
  float thisTop    = posY,
        thisBottom = posY + boxHeight*cTileSize,
        thisLeft   = posX,
        thisRight  = posX + boxWidth*cTileSize,
        otherTop    = hero.GetY(),
        otherBottom = otherTop + hero.GetBoxH()*cTileSize,
        otherLeft   = hero.GetX(),
        otherRight  = otherLeft + hero.GetBoxW()*cTileSize;
    
  if (thisTop > otherBottom ||
      otherTop > thisBottom ||
      thisLeft > otherRight ||
      otherLeft > thisRight)
    return false;

  return true;
}
