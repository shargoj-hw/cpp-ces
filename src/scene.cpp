#include "scene.hpp"
#include "DEBUG.hpp"
#include "SDLContainer.hpp"

static bool is_quitting_event(SDL_Event e);

Scene::Scene()
{
}

void Scene::update(double dt)
{
  DEBUG ("Updating the scene!");

  std::list<SDL_Event> events = SDLContainer::get_instance().get_events();

  for (SDL_Event e : events)
    {
      if (is_quitting_event(e))
	{
	  running = false;
	  return;
	}
    }

  std::list<Entity> entities = this->entities;

  for (System *s : this->systems)
    {
      entities = s->update(entities, dt);
    }


  this->entities = entities;

  DEBUG ("Done Updating the scene!")
}

void Scene::add_system(System *system)
{
  systems.push_back(system);
}

bool Scene::is_scene_over()
{
  return !running;
}

static bool is_quitting_event(SDL_Event e)
{
  DEBUG ("Have we quit?");

  return e.type == SDL_QUIT
    || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE);
}
