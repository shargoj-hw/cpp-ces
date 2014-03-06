#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>

using namespace std;

const Uint32 fps = 40;
const Uint32 minframetime = 1000 / fps;

int main (int argc, char *argv[])
{
  if (SDL_Init (SDL_INIT_VIDEO) != 0)
    {
      cout << "Error initializing SDL: " << SDL_GetError () << endl;
      return 1;
    }

  atexit (&SDL_Quit);
  SDL_Window *window = SDL_CreateWindow("JIM'S AWESOME GAMELOOP",
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					640, 480,
					SDL_WINDOW_OPENGL);

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

  if (window == NULL)
    {
      cout << "Error setting video mode: " << SDL_GetError () << endl;
      return 1;
    }

  bool running = true;
  SDL_Event event;
  Uint32 frametime;

  while (running)
    {
      frametime = SDL_GetTicks ();

      while (SDL_PollEvent (&event) != 0)
	{
	  switch (event.type)
	    {
	    case SDL_KEYDOWN: if (event.key.keysym.sym == SDLK_ESCAPE)
		running = false;
	      break;
	    }
	}

      if (SDL_GetTicks () - frametime < minframetime)
	SDL_Delay (minframetime - (SDL_GetTicks () - frametime));

      SDL_RenderClear(renderer);
      SDL_RenderPresent(renderer);
    }

  return 0;
}
