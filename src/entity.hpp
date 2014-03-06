#pragma once

#include "component.hpp"

class Entity
{
public:
  Entity();

  bool has_component(component_t component_type);
  Component get_component(component_t component_type);
  void set_component(Component component);
};
