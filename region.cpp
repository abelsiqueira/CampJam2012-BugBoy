#include "region.h"

Region::Region (float x, float y, float w, float h) {
  posX = x;
  posY = y;
  boxWidth = w;
  boxHeight = h;
  eventFunction = 0;
  triggerEntity = 0;
  visible = false;
  active = false;
}

Region::~Region () {

}

void Region::Update () {
  if (!active || !eventFunction || !triggerEntity)
    return;
  if (triggerEntity->IsDead())
    return;

  float thisTop    = posY,
        thisBottom = posY + boxHeight*cTileSize,
        thisLeft   = posX,
        thisRight  = posX + boxWidth*cTileSize,
        otherTop    = triggerEntity->GetY(),
        otherBottom = otherTop + triggerEntity->GetBoxH()*cTileSize,
        otherLeft   = triggerEntity->GetX(),
        otherRight  = otherLeft + triggerEntity->GetBoxW()*cTileSize;
    
  if (thisTop > otherBottom ||
      otherTop > thisBottom ||
      thisLeft > otherRight ||
      otherLeft > thisRight)
    return;

  active = false;
  (*eventFunction)();
}

void Region::Draw () const {
  if (!visible) 
    return;

  al_draw_filled_rectangle(posX, posY,
      posX + boxWidth*cTileSize, posY + boxHeight*cTileSize,
      al_map_rgba(0, 0, 0, 200));
}
