#ifndef region_h
#define region_h

// Will define regions that will trigger entity events. Probably I will use
// only once, but this will be a good test.

#include "entity.h"

typedef void (*voidFunction) ();

class Region {
  public:
    Region (float, float, float, float);
    ~Region ();

    void SetEventFunction (voidFunction p) {
      eventFunction = p;
      if (triggerEntity)
        active = true;
    }
    void SetTriggerEntity (Entity *e) {
      triggerEntity = e;
      if (eventFunction)
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
  private:
    Region();
    float posX, posY;
    float boxWidth, boxHeight;
    voidFunction eventFunction;
    Entity *triggerEntity;
    bool visible, active;
};

#endif
