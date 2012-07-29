#ifndef region_h
#define region_h

// Will define regions that will trigger entity events. Probably I will use
// only once, but this will be a good test.

#include "entity.h"

class Region {
  public:
    Region (float, float, float, float);
    ~Region ();

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
  private:
    Region();
    float posX, posY;
    float boxWidth, boxHeight;
    Entity *triggerEntity;
    bool visible, active, triggered;
};

#endif
