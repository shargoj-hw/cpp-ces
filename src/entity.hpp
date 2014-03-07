#pragma once

#include "component.hpp"
#include <map>
#include <string>

class Entity
{
  std::map<std::string, Component*> components;
public:
  Entity();

  bool has_component(std::string name) const;
  Component* get_component(std::string name);
  const Component* get_component(std::string name) const;
  void set_component(std::string name, Component *component);
};
