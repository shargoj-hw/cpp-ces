#pragma once

#include <SDL2/SDL.h>
#include "entity.hpp"
#include <list>

class System
{
public:
  virtual void init() {}
  virtual void cleanup() {}

  virtual void update(const std::list<SDL_Event> events, 
				   std::list<Entity> *entities,
				   double dt) = 0;
};
