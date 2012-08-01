#ifndef region_h
#define region_h

// Will define regions that will trigger entity events. Probably I will use
// only once, but this will be a good test.

#include "entity.h"

class Region {
  public:
    Region (float, float);
    Region (float, float, float, float);
    ~Region ();

    void SetPoint (float, float);
    void SetTriggerEntity (Entity *e) {
      triggerEntity = e;
      active = true;
    }
    void Activate () {
      active = true;
    }
    void Deactivate () {
      active = false;
    }
    void Show () {
      visible = true;
    }
    void Hide () {
      visible = false;
    }
    void Update ();
    void Draw () const;
    bool IsTriggered () const { return triggered; }
    float GetX () const { return posX; }
    float GetY () const { return posY; }
    float GetWidth () const { return boxWidth; }
    float GetHeight () const { return boxHeight; }
  private:
    Region();
    float posX, posY;
    float boxWidth, boxHeight;
    Entity *triggerEntity;
    bool visible, active, triggered;
};

#endif
