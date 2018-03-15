#ifndef ENEMY__H
#define ENEMY__H
#include <string>
#include "drawable.h"
#include "player.h"
#include "bulletPool.h"

class Enemy : public Drawable {
public:
  Enemy(const std::string&);
  Enemy(const Enemy&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  void noticePlayer(const Player&);
  void clearBullets();
  BulletPool getPool() { return bullets;}
private:
  const Frame * frame;
  int worldWidth;
  int worldHeight;
  int frameWidth;
  int frameHeight;
  BulletPool bullets;
  int getDistance(const Enemy*) const;

  Vector2f makePosition(int x, int y, const std::string& name, const int i)const;
  Vector2f makeVelocity(int vx, int vy, const std::string& name, const int i)const;
};
#endif
