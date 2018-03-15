#ifndef SPRITE__H
#define SPRITE__H
#include <string>
#include "drawable.h"

class Sprite : public Drawable {
public:
  Sprite(const std::string&, const int);
  Sprite(const Sprite&);
  virtual ~Sprite() { } 
  Sprite& operator=(const Sprite&);

  virtual const Frame* getFrame() const { return frame; }
                void   setFrame( const  Frame* f ) { frame = f; }
  virtual void draw() const;
  virtual void update(Uint32 ticks);
private:
  const Frame * frame;
  int worldWidth;
  int worldHeight;
  int frameWidth;
  int frameHeight;
  int getDistance(const Sprite*) const;
  Vector2f makePosition(int x, int y, const std::string& name, const int i)const;
  Vector2f makeVelocity(int vx, int vy, const std::string& name, const int i)const;
};
#endif
