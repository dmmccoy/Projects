#include <vector>
#include "world.h"
#include "viewport.h"
#include "frameGenerator.h"
#include "hud.h"
#include "sprite.h"
#include "player.h"
#include "enemy.h"
#include "sound.h"


class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  void switchSprite();

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;


  SDL_Renderer * const renderer;
  SDL_Window * const window;
  FrameGenerator frameGen;
  World back;
  World ground;
  Viewport& viewport;
  Hud hud;
  Player player;
  SDLSound sound;
  CollisionStrategy* strategy;



  std::vector<Drawable*> sprites;
  std::vector<Drawable*> sprites2;
  std::vector<Enemy*> enemySprites;

  int currentSprite;
  bool makeVideo;
  bool displayHud;
  bool dead;

  void draw() const;
  void update(Uint32);
  void reset();

  void checkForCollisions();

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&)=delete;
  void doDelay();
};
