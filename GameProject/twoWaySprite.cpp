#include "twoWaySprite.h"
#include "gamedata.h"
#include "renderContext.h"

Vector2f TwoWaySprite::makePosition(int x, int y, const std::string& name)const{
  if(name == "Kirby")return Vector2f(x, y);
  float a = Gamedata::getInstance().getRandInRange(0,
		  Gamedata::getInstance().getXmlInt("world/width"));
  float b = Gamedata::getInstance().getRandInRange(0,
		  Gamedata::getInstance().getXmlInt("world/height"));
  return Vector2f(a, b);
}

Vector2f TwoWaySprite::makeVelocity(int vx, int vy, const std::string& name)const{
  if(name == "Kirby")return Vector2f(vx, vy);
  float a = Gamedata::getInstance().getRandInRange(vx-50, vx+50);
  float b = Gamedata::getInstance().getRandInRange(vy-50, vy+50);
  a = a * (rand()%2 ?-1:1);
  b = b * (rand()%2 ?-1:1);
  return Vector2f(a, b);
}

void TwoWaySprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

TwoWaySprite::TwoWaySprite( const std::string& name) :
  Drawable(name, 
           makePosition(
		    Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y"),
		    name), 
           makeVelocity(
		    Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"),
		    name)
           ),
  frames( RenderContext::getInstance()->getFrames(name) ),
  leftFrames(RenderContext::getInstance()->getFrames(name+"Left") ),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
{ }

TwoWaySprite::TwoWaySprite(const TwoWaySprite& s) :
  Drawable(s), 
  frames(s.frames),
  leftFrames(s.leftFrames),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight )
  { }

inline namespace{
  constexpr float SCALE_EPSILON = 2e-7;
}

void TwoWaySprite::draw() const {
  if(getScale() < SCALE_EPSILON) return;
  if(getVelocityX() < 0) leftFrames[frames.size()-currentFrame-1]->draw(getX(), getY(), scale);
  else frames[currentFrame]->draw(getX(), getY(), scale);
}

void TwoWaySprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-frameHeight*scale) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-frameWidth*scale) {
    setVelocityX( -fabs( getVelocityX() ) );
  }  

}
