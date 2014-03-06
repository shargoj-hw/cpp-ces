#pragma once

#include <list>
#include "entity.hpp"
#include "system.hpp"

class Scene
{
public:
  Scene();

  std::list<Entity> entities;
  std::list<System> systems;

  void update(double dt);
};
