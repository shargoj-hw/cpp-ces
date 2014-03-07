#pragma once

#include "entity.hpp"
#include <list>

class System
{
public:
  virtual void init() = 0;
  virtual void cleanup() = 0;

  virtual std::list<Entity> update(const std::list<Entity> entities, double dt) = 0;
};
