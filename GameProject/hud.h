#include <iostream>
#include <sstream>
#include <string>
#include <SDL.h>
#include "ioMod.h"
#include "clock.h"
#include "gamedata.h"


class Hud {
public:
  Hud(): hudRect(new SDL_Rect{Gamedata::getInstance().getXmlInt("hudX"),
			      Gamedata::getInstance().getXmlInt("hudY"),
			      Gamedata::getInstance().getXmlInt("hudW"),
			      Gamedata::getInstance().getXmlInt("hudH")}){}
  ~Hud(){delete hudRect;}
  void dsHud(SDL_Renderer*, const IOmod&, const int, const unsigned int, const int)const;
private:
  SDL_Rect *hudRect;
};
