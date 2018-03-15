#ifndef TWOWAYSPRITE__H
#define TWOWAYSPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class TwoWaySprite: public Drawable {
public:
  TwoWaySprite(const std::string&);
  TwoWaySprite(const TwoWaySprite&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  inline float getScale()const{ return scale; }
  void  setScale(float s){ scale = s; }

protected:
  const std::vector<Frame *> frames;
  const std::vector<Frame *> leftFrames;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  float scale;
  int worldWidth;
  int worldHeight;
  int frameWidth;
  int frameHeight;

  void advanceFrame(Uint32 ticks);
  Vector2f makeVelocity(int, int, const std::string&) const;
  Vector2f makePosition(int, int, const std::string&) const;
};
#endif
