#include "entity.hpp"

Entity::Entity() {}

bool Entity::has_component(std::string name) const
{
  return components.find(name) != components.end();
}

Component* Entity::get_component(std::string name)
{
  if (has_component(name))
    return components.at(name);
  else
    return NULL;
}

const Component* Entity::get_component(std::string name) const
{
  if (has_component(name))
    return components.at(name);
  else
    return NULL;
}

void Entity::set_component(std::string name, Component *component)
{
  components[name] = component;
}
