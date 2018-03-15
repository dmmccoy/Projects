#include "hud.h"

void Hud::dsHud(SDL_Renderer* r,const IOmod& i, const int fps, const unsigned int time, const int state)const{
  std::stringstream strm;
  std::stringstream strm2;
  std::stringstream strm3;
  std::stringstream strm4;
  std::stringstream strm5;
  std::stringstream strm6;
  std::stringstream strm7;
  std::stringstream strm8;
  strm << "Goal: Survive 60 seconds";
  strm2 << "How to play: wasd to move";
  strm3 << "fps: " << fps << "  Total Time: " << time;
  strm4 << "Press G for god mode";
  strm5 << "Press R to reset";
  strm6 << "Press F1 to toggle hud";
  strm7 << "You Died!!! Press R to restart";
  strm8 << "YOU WON!!! Press R to replay or Q to quit";
  

  SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor( r, 255, 255, 255, 255/2);
  SDL_RenderFillRect( r, hudRect );
  SDL_SetRenderDrawColor( r, 255, 0, 0, 255 );
  SDL_RenderDrawRect(r, hudRect);

  i.writeText(strm.str(),SDL_Color({0,0,0,255/2}),
			 Gamedata::getInstance().getXmlInt("hudX")+5,
			 Gamedata::getInstance().getXmlInt("hudY")+5);
  i.writeText(strm2.str(),SDL_Color({0,0,0,255/2}),
			  Gamedata::getInstance().getXmlInt("hudX")+5,
			  Gamedata::getInstance().getXmlInt("hudY")+35);
  i.writeText(strm3.str(),SDL_Color({0,0,0,255/2}),
			  Gamedata::getInstance().getXmlInt("hudX")+5,
			  Gamedata::getInstance().getXmlInt("hudY")+65);
  i.writeText(strm4.str(),SDL_Color({0,0,0,255/2}),
			  Gamedata::getInstance().getXmlInt("hudX")+5,
			  Gamedata::getInstance().getXmlInt("hudY")+95);
  i.writeText(strm5.str(),SDL_Color({0,0,0,255/2}),
			  Gamedata::getInstance().getXmlInt("hudX")+5,
			  Gamedata::getInstance().getXmlInt("hudY")+125);
  i.writeText(strm6.str(),SDL_Color({0,0,0,255/2}),
			  Gamedata::getInstance().getXmlInt("hudX")+5,
			  Gamedata::getInstance().getXmlInt("hudY")+155);
  if(state == 1){
  i.writeText(strm7.str(),SDL_Color({0,0,0,255/2}),
			  Gamedata::getInstance().getXmlInt("hudX")+250,
			  Gamedata::getInstance().getXmlInt("hudY")+225);
  }
  else if(state == 2){
  i.writeText(strm8.str(),SDL_Color({0,0,0,255/2}),
			  Gamedata::getInstance().getXmlInt("hudX")+250,
			  Gamedata::getInstance().getXmlInt("hudY")+225);
  }
  else{}

}
