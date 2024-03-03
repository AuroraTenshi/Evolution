#include <SDL.h>
#include <iostream>
#include "Application.h"
#define WIDTH 1000
#define HEIGHT 700


void exitProgram()
{
	std::cout << "Kilépéshez nyomj meg egy billentyût..." << std::endl;
	std::cin.get();
}

int main( int argc, char* args[] )
{
	atexit( exitProgram );

	if ( SDL_Init( SDL_INIT_VIDEO ) == -1 )
	{
		std::cout << "[SDL indítása]Hiba az SDL inicializálása közben: " << SDL_GetError() << std::endl;
		return 1;
	}
			
	SDL_Window *win = nullptr;
    win = SDL_CreateWindow( "Evolucio", 200, 60, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr)
	{
		std::cout << "[Ablak létrehozása]Hiba az SDL inicializálása közben: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *ren = nullptr;
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
	{
        std::cout << "[Renderer létrehozása]Hiba az SDL inicializálása közben: " << SDL_GetError() << std::endl;
        return 1;
    }

	Application app(ren, WIDTH, HEIGHT);

	bool quit = false;
	SDL_Event ev;

	while (!quit)
	{
		while ( SDL_PollEvent(&ev) )
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				app.KeyDown(ev.key.keysym.sym);
				break;
			case SDL_KEYUP:
				app.KeyUp(ev.key.keysym.sym);
				break;
			case SDL_MOUSEMOTION:
				break;
			}
		}

		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);

		app.Run();
		if (app.AppQuit()) quit = true;

		/*SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);

		SDL_RenderDrawLine(ren,	0, 0, mouseX, mouseY);
		*/

		SDL_RenderPresent(ren);
	}

	SDL_DestroyRenderer( ren );
	SDL_DestroyWindow( win );

	SDL_Quit();

	return 0;
}