#pragma once

#include <list>
#include "entity.hpp"
#include "system.hpp"

class Scene
{
  std::list<System*> systems;
  bool running = true;

public:
  Scene();

  std::list<Entity> entities;

  void add_system(System *system);

  void update(double dt);

  bool is_scene_over();
};
