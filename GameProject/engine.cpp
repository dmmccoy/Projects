#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "multisprite.h"
#include "twoWaySprite.h"
#include "gamedata.h"
#include "engine.h"



void Engine::reset(){
  int i = 0;
  int temp;
  player.setPosition(Vector2f(500, 250));
  for(auto& sp: sprites2){
   if(sp->getName() == "Gordo"){
    if(i < Gamedata::getInstance().getXmlInt("Gordo/clones")*5/8) temp = 0;
    else{
      if(i%2 == 0) temp = 1;
      else temp = 2;
    }
    float a, b;
    if(temp == 1){
      a = Gamedata::getInstance().getXmlInt("world/width")-100;
      b = Gamedata::getInstance().getRandInRange(0,
		  Gamedata::getInstance().getXmlInt("world/height")-100);
    }
    else{
      a = Gamedata::getInstance().getRandInRange(0,
		  Gamedata::getInstance().getXmlInt("world/width")-100);
      b = 0;
    }
    sp->setPosition(Vector2f(a,b));
   }
   i++;
  }
  for(auto& e: enemySprites){
    e->clearBullets();
  }
  dead = false;
  clock.startClock();
  displayHud = true;
  sound.startMusic();
  draw();
  doDelay();
}

void Engine::doDelay() {
  std::stringstream stream;
  stream << "3";
  clock.pause();
  SDL_Delay(1000);
  IOmod::getInstance().
  writeText(stream.str(), SDL_Color({0,0,0,255/2}),  500, 220);
  draw();
  stream.clear();
  stream << "2";
  IOmod::getInstance().
  writeText(stream.str(), SDL_Color({0,0,0,255/2}),  500, 220);
  SDL_Delay(1000);
  draw();
  SDL_Delay(1000);
  clock.unpause();
}


class SpriteLess {
public:
  bool operator()(const Drawable* lhs, const Drawable* rhs) const {
    return lhs->getScale() < rhs->getScale();
  }
};


Engine::~Engine() { 
  std::cout << "Terminating program" << std::endl;
  for(auto& sp: sprites) delete sp;
  for(auto& sp: sprites2) delete sp;
  for(auto& e: enemySprites) delete e;
  delete strategy;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  window( rc->getWindow() ),
  frameGen(),
  back("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  ground("ground", Gamedata::getInstance().getXmlInt("ground/factor") ),
  viewport( Viewport::getInstance() ),
  hud(),
  player("Kirby"),
  sound(),
  strategy( new MidPointCollisionStrategy),
  sprites(),
  sprites2(),
  enemySprites(),
  currentSprite(-1),
  makeVideo( false ),
  displayHud( true ),
  dead(false)
{
  constexpr float u = 0.75f; //Mean size
  constexpr float d = 0.25f; //Std deviation

  std::random_device rd;
  std::mt19937 mt(rd());
  std::normal_distribution<float> dist(u,d);
  int temp;

  for (int i = 0; i < Gamedata::getInstance().getXmlInt("Bronto/clones"); ++i){
    auto* s = new TwoWaySprite("Bronto");
    float scale = dist(mt);
    while(scale < 0.1f) scale = dist(mt);
    s->setScale(scale);
    sprites.push_back(s);
  }
  std::vector<Drawable*>::iterator ptr = sprites.begin();
  ++ptr;
  sort(ptr, sprites.end(), SpriteLess());

  enemySprites.push_back(new Enemy("Shotzo"));
  enemySprites.push_back(new Enemy("ShotzoRight"));
  for (int i = 0; i < Gamedata::getInstance().getXmlInt("Gordo/clones"); ++i){
    if(i < Gamedata::getInstance().getXmlInt("Gordo/clones")*5/8) temp = 0;
    else{
      if(i%2 == 0) temp = 1;
      else temp = 2;
    }
    auto* s = new Sprite("Gordo", temp);
    sprites2.push_back(s);
  }

  Viewport::getInstance().setObjectToTrack(&player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  back.draw();
  for(auto* s : sprites){
    if(s->getScale() > 0) s->draw();
  }
  ground.draw();
  std::string name(Gamedata::getInstance().getXmlStr("Name"));
  io.writeText(name, SDL_Color({0,0,0,0}),0, 450);
  if(dead == false) clock.calcTime();
  if(displayHud == true){
    if(clock.totalTime < 60 && dead == true){
      hud.dsHud(renderer, io, clock.getFps(), clock.totalTime, 1);
    }
    else if(clock.totalTime >=60){
      hud.dsHud(renderer, io, clock.getFps(), clock.totalTime, 2);
    }
    else{
      hud.dsHud(renderer, io, clock.getFps(), clock.totalTime, 0);
    }
  }
  for(auto* s2 : sprites2) s2->draw();
  for(auto* es : enemySprites){
    if(es == enemySprites[1] && displayHud == true){
      std::stringstream stream;
      stream << "Active bullets: " << es->getPool().bulletCount();
      IOmod::getInstance().
      writeText(stream.str(), SDL_Color({0,0,0,255/2}),  650, 10);
      stream.clear();
      stream.str("");
      stream << "Bullet pool: " << es->getPool().freeCount();
      IOmod::getInstance().
      writeText(stream.str(), SDL_Color({0,0,0,255/2}), 650, 40);
    }
    es->draw();
  }
  for(auto* s : sprites){
    if(s->getScale() == 0) s->draw();
  }  
  if(dead == false) player.draw();   
//  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  back.update();
  for(auto* s : sprites) s->update(ticks);
  ground.update();
  for(auto* s2 : sprites2) s2->update(ticks);
  for(auto* es : enemySprites){
     es->noticePlayer(player);
     es->update(ticks);
  }
  player.update(ticks);
  viewport.update(); // always update viewport last
}

void Engine::checkForCollisions() {
  for( auto *it: enemySprites){
    if(it->getPool().collidedWith(player)){
      dead = true;
      displayHud = true;
      ExplodingSprite* boom2 = new ExplodingSprite(player.getName()+"Explode", player.getX(), player.getY());
      boom2->setScale(0);
      sprites.push_back(boom2); 
      sound[0];
    }
    if(strategy->execute(player, *it)){
      dead = true;
      displayHud = true;
      ExplodingSprite* boom2 = new ExplodingSprite(player.getName()+"Explode", player.getX(), player.getY());
      boom2->setScale(0);
      sprites.push_back(boom2);
      sound[0];
    }
  }
  std::vector<Drawable*>::const_iterator it2 = sprites2.begin();
  while ( it2 != sprites2.end() ) {
    if ( strategy->execute(player, **it2) ) {
      dead = true;
      displayHud = true;
      ExplodingSprite* boom2 = new ExplodingSprite(player.getName()+"Explode", player.getX(), player.getY());
      boom2->setScale(0);
      sprites.push_back(boom2);
      sound[0];
    }
    ++it2;
  }
}

void Engine::switchSprite(){
  currentSprite = ++currentSprite % sprites.size();
  Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  player.setVelocityX(0);
  player.setVelocityY(0);

  bool firstTime = true;
  bool collision = true;

  while ( !done) {
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_R] ) {
		collision = true;
		reset();
        }
        if ( keystate[SDL_SCANCODE_G] ) {
         if(clock.totalTime <60){
	  if(collision == true) collision = false;
	  else collision = true; 
         }
        }
        if ( keystate[SDL_SCANCODE_F1] ) {
	  if(displayHud == true) displayHud = false;
	  else displayHud = true;
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }
      if(dead == false && clock.totalTime <60){
        if( keystate[SDL_SCANCODE_A] &&  keystate[SDL_SCANCODE_D]) {
	  player.stop();
        }
        else if ( keystate[SDL_SCANCODE_A] ) {
          player.left();
        }
        else if(keystate[SDL_SCANCODE_D] ){
	  player.right();	
        }
        if ( keystate[SDL_SCANCODE_S] &&  keystate[SDL_SCANCODE_W]) {
	  player.stop();
        }
        else if ( keystate[SDL_SCANCODE_S] ) {
          player.down();
        }
        else if ( keystate[SDL_SCANCODE_W] ) {
          player.up();
        }
      }


    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      if(int(clock.avgTicks.size()) < Gamedata::getInstance().getXmlInt("maxFrame"))
        clock.avgTicks.push_front(ticks);
      else{
        clock.avgTicks.push_front(ticks);
        clock.avgTicks.pop_back();
    }
      draw();
      if(clock.totalTime == 10){ displayHud = false;
      clock.totalTime ++;
      }
      if ( firstTime ) {
        firstTime = false;
        doDelay();
      }
      update(ticks);
      if(clock.totalTime == 60){
        displayHud = true;
        collision = false;
      }
      if(dead == false && collision == true){
      checkForCollisions();
      }
      if(makeVideo)frameGen.makeFrame();
    }
  }
}
