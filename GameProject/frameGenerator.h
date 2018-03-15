#include <string>
#include <SDL.h>
#include "renderContext.h"

const std::string USERNAME = "mccoy";
const int unsigned MAX_FRAMES = 300;


class FrameGenerator {
public:
  FrameGenerator() : 
    rend(RenderContext::getInstance()->getRenderer()), 
    window(RenderContext::getInstance()->getWindow()),
    frameCount(0)
  {}
  void makeFrame();
  unsigned int getFrameCount() const { return frameCount; }
private:
  SDL_Renderer* const rend;
  SDL_Window* const window;
  unsigned int frameCount;
  FrameGenerator(const FrameGenerator&);
  FrameGenerator& operator=(const FrameGenerator&);
};
