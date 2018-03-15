#include <cmath>
#include "sprite.h"
#include "gamedata.h"
#include "renderContext.h"


Vector2f Sprite::makePosition(int x, int y, const std::string& name, const int i)const{
  if(name == "Gordo"){
    float a, b;
    if(i == 1){
      a = Gamedata::getInstance().getXmlInt("world/width")-100;
      b = Gamedata::getInstance().getRandInRange(0,
		  Gamedata::getInstance().getXmlInt("world/height")-100);
    }
    else{
      a = Gamedata::getInstance().getRandInRange(0,
		  Gamedata::getInstance().getXmlInt("world/width")-100);
      b = 0;
    }
//  std::cout << a << " " << b << std::endl;
  return Vector2f(a, b);
  }
  return Vector2f(x, y);
}

Vector2f Sprite::makeVelocity(int vx, int vy, const std::string& name, const int i)const{
  if(name == "Gordo"){
    float a = Gamedata::getInstance().getRandInRange(vx-50, vx+50);
    float b = Gamedata::getInstance().getRandInRange(vy-50, vy+50);
    if(i == 0) return Vector2f(0, b);
    else if(i == 1) return Vector2f(a, 0);
    else return Vector2f(a, b);
  }
  return Vector2f(vx, vy);
}

Sprite::Sprite(const std::string& name, const int i) :
  Drawable(name,
           makePosition(
		    Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y"),
		    name, i), 
           makeVelocity(
		    Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"),
		    name, i)
           ),
  frame( RenderContext::getInstance()->getFrame(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight())
{ }

Sprite::Sprite(const Sprite& s) :
  Drawable(s), 
  frame(s.frame),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight())
{ }

Sprite& Sprite::operator=(const Sprite& rhs) {
  Drawable::operator=( rhs );
  frame = rhs.frame;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  return *this;
}

void Sprite::draw() const { 
  frame->draw(getX(), getY()); 
}

void Sprite::update(Uint32 ticks) { 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( std::abs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-frameHeight) {
    setVelocityY( -std::abs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( std::abs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-frameWidth) {
    setVelocityX( -std::abs( getVelocityX() ) );
  }  
}
