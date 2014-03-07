#include <SDL2/SDL.h>

#include <cstdlib>
#include <iostream>
#include "scene.hpp"
#include "sdlcontainer.hpp"

using namespace std;

const Uint32 fps = 40;
const Uint32 minframetime = 1000 / fps;

int main (int argc, char *argv[])
{
  Scene scene;
  SDLContainer &sdl = SDLContainer::get_instance();

  Uint32 frametime;

  while (!scene.is_scene_over())
    {
      frametime = SDL_GetTicks ();

      scene.update(frametime);

      if (SDL_GetTicks () - frametime < minframetime)
	SDL_Delay (minframetime - (SDL_GetTicks () - frametime));

      SDL_RenderClear(sdl.renderer);
      SDL_RenderPresent(sdl.renderer);
    }

  return 0;
}
