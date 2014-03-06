#pragma once

#include "entity.hpp"
#include <list>

class System
{
public:
  System();

  void init();
  void cleanup();

  virtual std::list<Entity> update(const std::list<Entity> entities, double dt);
};
