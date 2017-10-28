#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char** args)
{
	// The window to render to
	SDL_Window* window = NULL;
	
	// The surface contained by the window
	SDL_Surface* screenSurface = NULL;
	
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		cout << "SDL Initialization Error: " << SDL_GetError() << endl;
		return 0;
	}
	
	// Create Window
	// Parameters: Caption String, x pos, y pos, width, height, creation flags
	window = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	if (window == NULL)
	{
		cout << "Window could not be created, Error: " << SDL_GetError() << endl;
		return 0;
	}
	
	screenSurface = SDL_GetWindowSurface(window);
	
	// Fill the surface white
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface -> format, 0xFF, 0xFF, 0xFF));
	
	// Update the surface
	SDL_UpdateWindowSurface(window);
	
	SDL_Delay(2000);
	
	
	// Game Loop
	while (true)
	{
		
	}
	
	
	return 0;
}
