#pragma once

#include <typeinfo>

typedef std::type_info component_t;

class Component
{
public:
  virtual ~Component() {}
};
