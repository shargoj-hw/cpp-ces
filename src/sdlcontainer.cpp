#include "sdlcontainer.hpp"

SDLContainer::SDLContainer()
{
  if (SDL_Init (SDL_INIT_VIDEO) != 0)
    {
      throw "Couldn't initialize SDL";
    }

  atexit (&SDL_Quit);

  window = SDL_CreateWindow("New Window",
			    SDL_WINDOWPOS_UNDEFINED,
			    SDL_WINDOWPOS_UNDEFINED,
			    640, 480,
			    SDL_WINDOW_OPENGL);

  if (window == NULL)
    {
      throw "Error setting video mode.";
    }

  renderer = SDL_CreateRenderer(window, -1, 0);
}

std::list<SDL_Event> SDLContainer::get_events()
{
  std::list<SDL_Event> events;

  SDL_Event event;

  while (SDL_PollEvent (&event) != 0)
    {
      events.push_back(event);
    }

  return events;
}
