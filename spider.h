#ifndef spider_h
#define spider_h

#include "enemy.h"

class Spider : public Enemy {
  public:
    Spider (float, float);
    virtual ~Spider ();
    
    virtual void Update ();
    virtual void Draw () const;
  protected:
    
};

#endif
