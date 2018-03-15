#include <iostream>
#include "sprite.h"
#include "gamedata.h"

class Bullet : public Sprite {
public:
  explicit Bullet(const string& name) :
    Sprite(name, 0),
    distance(0),
    maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")),
    tooFar(false) 
  {}
  virtual void update(Uint32 ticks);
  void TooFar() { tooFar = true;}
  bool goneTooFar() const { return tooFar; }
  void reset(){
    tooFar = false;
    distance = 0;
  }
private:
  float distance;
  float maxDistance;
  bool tooFar;
};
