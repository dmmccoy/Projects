#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include "twoWaySprite.h"
#include "explodingSprite.h"

class Player : public TwoWaySprite {
public:
  Player(const std::string&);
  Player(const Player&);

  virtual void update(Uint32 ticks);
  void stop();
  void right();
  void left();
  void up();
  void down();
  void draw()const;

protected:
  float frameInterval;
  int currentDirection;

  Vector2f initialVelocity;

  Player& operator=(const Player&);
  void advanceFrame(Uint32);
};
#endif
