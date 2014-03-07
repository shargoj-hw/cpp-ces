#pragma once

#include <SDL2/SDL.h>
#include <list>

class SDLContainer
{
  SDLContainer();

public:
  static SDLContainer& get_instance() {
    static SDLContainer *instance;

    if (NULL != instance) 
      return *instance;
  
    return *(instance = new SDLContainer());
  }

  SDL_Renderer *renderer;
  SDL_Window *window;

  std::list<SDL_Event> get_events ();

  ~SDLContainer();
};
