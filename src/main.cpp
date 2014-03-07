#include <SDL2/SDL.h>

#include <cstdlib>
#include <iostream>
#include "scene.hpp"
#include "sdlcontainer.hpp"
#include "DEBUG.hpp"
#include <random>

using namespace std;

const Uint32 fps = 40;
const Uint32 minframetime = 1000 / fps;

//   ____                                                  _       
//  / ___|___  _ __ ___  _ __   ___  _ __   ___ _ __   ___| |_ ___ 
// | |   / _ \| '_ ` _ \| '_ \ / _ \| '_ \ / _ \ '_ \ / _ \ __/ __|
// | |__| (_) | | | | | | |_) | (_) | | | |  __/ | | |  __/ |_\__ \
//  \____\___/|_| |_| |_| .__/ \___/|_| |_|\___|_| |_|\___|\__|___/
//                      |_|                                        

class KeyComponent : public Component
{
public:
  SDL_Keysym key; bool unpressed;
  KeyComponent(SDL_Keysym key) : key(key), unpressed(false) {}
};

class VectorComponent : public Component
{
public:
  double x, y;
  VectorComponent(double x, double y) : x(x), y(y) {};
};

class TTLComponent : public Component
{
public:
  double ttl, elapsed;
  TTLComponent(double ttl) : ttl(ttl), elapsed(0) {}

  bool is_dead () const { 
    return elapsed > ttl; 
  }
};

//  ____            _                     
// / ___| _   _ ___| |_ ___ _ __ ___  ___ 
// \___ \| | | / __| __/ _ \ '_ ` _ \/ __|
//  ___) | |_| \__ \ ||  __/ | | | | \__ \
// |____/ \__, |___/\__\___|_| |_| |_|___/
//        |___/                           

class KeyAdderSystem : public System
{
  std::uniform_real_distribution<double> vels {-50, 50};
  std::default_random_engine re;

public:
  virtual void update(const std::list<SDL_Event> events, 
		      std::list<Entity> *entities,
		      double dt) 
  {
    DEBUG ("TRYING TO ADD KEYS!");

    for (SDL_Event ev : events)
      {
	if (ev.type == SDL_KEYDOWN)
	  {
	    Entity e;
	    e.set_component("key", new KeyComponent(ev.key.keysym));
	    e.set_component("pos", new VectorComponent(WIDTH/2, HEIGHT/2));
	    e.set_component("vel", new VectorComponent(vels(re), vels(re)));

	    entities->push_back(e);
	  }

	if (ev.type == SDL_KEYUP)
	  {
	    for (Entity& e : *entities)
	      {
		if (e.has_component("key"))
		  {
		    KeyComponent *key = dynamic_cast<KeyComponent*>(e.get_component("key"));

		    if (!key->unpressed)
		      {
			key->unpressed = true;
			e.set_component("TTL", new TTLComponent(7));
		      }
		  }
	      }
	  }
      }
  }  
};

class VelocitySystem : public System
{
public:
  VelocitySystem() {}

  virtual void update(const std::list<SDL_Event> events, 
		      std::list<Entity> *entities,
		      double dt) 
  {
    DEBUG ("TRYING TO ADD KEYS!");

    for (Entity& e : *entities)
      {
	if (e.has_component("pos") && e.has_component("vel"))
	  {
	    VectorComponent *pos = dynamic_cast<VectorComponent*>(e.get_component("pos"));
	    VectorComponent *vel = dynamic_cast<VectorComponent*>(e.get_component("vel"));

	    pos->x += vel->x * dt;
	    pos->y += vel->y * dt;
	  }
      }
  }
};

class TTLSystem : public System
{
public:
  TTLSystem() {}

  virtual void update(const std::list<SDL_Event> events, 
		      std::list<Entity> *entities,
		      double dt) 
  {
    DEBUG ("TRYING TO ADD KEYS!");

    for (Entity& e : *entities)
      {
	if (e.has_component("TTL"))
	  {
	    Component* c = e.get_component("TTL");
	    TTLComponent *tc = dynamic_cast<TTLComponent*>(c);

	    tc->elapsed += dt;
	  }
      }

    entities->remove_if([] (const Entity& e) {
	return e.has_component("TTL")
	  && dynamic_cast<const TTLComponent*>(e.get_component("TTL"))->is_dead();
      });
  }  
};

#include <SDL2/SDL2_gfxPrimitives.h>
class SDLRenderSystem : public System
{
  void debug_write_keys (std::list<Entity> *entities)
  {
    std::cout << "Keys: ";
    for (Entity e : *entities)
      {
	if (e.has_component("key"))
	  {
	    KeyComponent *kc = dynamic_cast<KeyComponent*>(e.get_component("key"));

	    std::cout << (char)(kc->key.sym) << ", ";
	  }
      }
    std::cout << std::endl;
  }

  void draw_keys (std::list<Entity> *entities)
  {
    SDLContainer &sdl = SDLContainer::get_instance();

    for (Entity e : *entities)
      {
	if (e.has_component("key") && e.has_component("pos"))
	  {
	    KeyComponent *kc = dynamic_cast<KeyComponent*>(e.get_component("key"));
	    VectorComponent *vc = dynamic_cast<VectorComponent*>(e.get_component("pos"));


	    if (!kc->unpressed)
	      {
		filledCircleRGBA(sdl.renderer, vc->x, vc->y, 50, 0, 255, 0, 255);
		characterRGBA(sdl.renderer, vc->x, vc->y, kc->key.sym, 255, 0, 255, 255);
	      }
	    else
	      {
		TTLComponent *ttl = dynamic_cast<TTLComponent*>(e.get_component("TTL"));		

		double percent = 1 - (ttl->elapsed / ttl->ttl);

		filledCircleRGBA(sdl.renderer, vc->x, vc->y, 50, 255, 0, 0, percent * 255);
		characterRGBA(sdl.renderer, vc->x, vc->y, kc->key.sym, 0, 0, 255, percent * 255);
	      }
	  }
      }
  }

public:
  SDLRenderSystem() {}

  virtual void update(const std::list<SDL_Event> events, 
		      std::list<Entity> *entities,
		      double dt) 
  {
    SDLContainer &sdl = SDLContainer::get_instance();

    // if (SDL_GetTicks () - dt < minframetime)
    //   SDL_Delay (minframetime - (SDL_GetTicks () -dt));

    SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl.renderer);

    DEBUG ("Rendering!");
    
    draw_keys(entities);

    SDL_RenderPresent(sdl.renderer);
  }
};

int main (int argc, char *argv[])
{
  Scene scene;
  SDLContainer &sdl = SDLContainer::get_instance();

  scene.add_system(new KeyAdderSystem);
  scene.add_system(new VelocitySystem);
  scene.add_system(new TTLSystem);
  scene.add_system(new SDLRenderSystem);

  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
			   "Welcome!",
			   "Type stuff and you should see the letters "
			   "you type float around on the screen! They'll "
			   "start to disappear when you let them go :)",
			   sdl.window);

  Uint32 frametime, last_frametime;

  while (!scene.is_scene_over())
    {
      last_frametime = frametime;
      frametime = SDL_GetTicks ();

      scene.update(((double)frametime - last_frametime) / 1000.0);
    }

  return 0;
}
