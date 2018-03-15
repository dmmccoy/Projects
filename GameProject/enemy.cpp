#include <cmath>
#include "enemy.h"
#include "gamedata.h"
#include "renderContext.h"


void Enemy::clearBullets(){
  bullets.clear();
}
Enemy::Enemy(const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  frame( RenderContext::getInstance()->getFrame(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  bullets("cannonBall")
{ }

Enemy::Enemy(const Enemy& s) :
  Drawable(s), 
  frame(s.frame),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  bullets(s.bullets)
{ }


void Enemy::draw() const { 
  frame->draw(getX(), getY());
  bullets.draw();
}

void Enemy::noticePlayer(const Player& p){
  
  if(getY() >= p.getY()-10.0 && getY() <= p.getY()+10.0) {
    if(getX() < 500){
    float x = getX()+getFrame()->getWidth()-25;
    float y = getY()+getFrame()->getHeight()/2;
    bullets.shoot( Vector2f(x, y), Vector2f(200, 0));
    }
    else{
    float x = getX();
    float y = getY()+getFrame()->getHeight()/2;
    bullets.shoot( Vector2f(x, y), Vector2f(-200, 0));
    }
  }
}

void Enemy::update(Uint32 ticks) { 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
  bullets.update(ticks);
//  if(getY() == p.getY()) setVelocityY(0);
  if ( getY() < 0) {
    setVelocityY( std::abs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-frameHeight+5) {
    setVelocityY( -std::abs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( std::abs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-frameWidth) {
    setVelocityX( -std::abs( getVelocityX() ) );
  }
  
}
