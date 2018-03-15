#include <cmath>
#include "player.h"
#include "gamedata.h"

Player::Player(const std::string& name) :
  TwoWaySprite(name),
  frameInterval(Gamedata::getInstance().getXmlFloat(name+"/frameInterval")),
  currentDirection(2),
  initialVelocity(getVelocity()){}

Player::Player(const Player& p):
  TwoWaySprite(p),
  frameInterval(p.frameInterval),
  currentDirection(p.currentDirection),
  initialVelocity(p.initialVelocity){}

void Player::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

void Player::stop() {
  setVelocityX(0);
  setVelocityY(0);
}

void Player::right() {
  if(getX() < worldWidth-frameWidth) {
    setVelocityX(initialVelocity[0]);
  }
  currentDirection = 2;
}
void Player::left() {
  if(getX() > 0) {
    setVelocityX(-initialVelocity[0]);
  }
  currentDirection = 1;
}

void Player::up() {
  if(getY() > 0){
    setVelocityY( -initialVelocity[1]);
  }
}

void Player::down() {
  if(getY() < worldHeight-frameHeight){
    setVelocityY( initialVelocity[1]);
  }
}

void Player::draw() const {
  if(getVelocityX() < 0) leftFrames[frames.size()-currentFrame-1]->draw(getX(), getY());
  else if(getVelocityX() == 0 && currentDirection == 1)
    leftFrames[frames.size()-currentFrame-1]->draw(getX(), getY());
  else frames[currentFrame]->draw(getX(), getY());
}

void Player::update(Uint32 ticks) {
  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
  if(getY() < 0){
    setVelocityY(0);
  }
  if(getY() > worldHeight-frameHeight){
    setVelocityY(0);
  }
  if(getX() < 0){
    setVelocityX(0);
  }
  if(getX() > worldWidth-frameWidth){
    setVelocityX(0);
  }
  stop();
}
  



