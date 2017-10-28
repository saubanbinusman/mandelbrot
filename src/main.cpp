#include <iostream>
#include <cmath>

#include <SDL2/SDL.h>

using namespace std;

// Screen dimensions
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;

double mapDouble(double valToMap, double valMin, double valMax, double mappedMin, double mappedMax)
{
	return ((valToMap - valMin) / (valMax - valMin)) * (mappedMax - mappedMin) + mappedMin;
}

int main(int argc, char** args)
{
	// The window to render to
	SDL_Window* window = NULL;
	
	// The surface contained by the window
	//SDL_Surface* screenSurface = NULL;
	
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
	
	//screenSurface = SDL_GetWindowSurface(window);
	
	// Fill the surface white
	//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface -> format, 0xFF, 0xFF, 0xFF));
	
	// Update the surface
	//SDL_UpdateWindowSurface(window);
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	if (renderer == NULL)
	{
		cout << "Could not create Renderer, Error: " << SDL_GetError() << endl;
		return 0;
	}
	
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // Black
	SDL_RenderClear(renderer); // Fil it with Black
	
	// Mandelbrot Plotting
	int iterations = 100;
	
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			double a = mapDouble(x, 0, SCREEN_WIDTH, -2, 2);
			double b = mapDouble(y, 0, SCREEN_HEIGHT, -2, 2);
			
			double aCopy = a;
			double bCopy = b;
			
			int n = 0;
			
			while (n < iterations)
			{
				double aa = (a * a) - (b * b);
				double bb = 2 * a * b;
				
				a = aa + aCopy;
				b = bb + bCopy;
				
				// Checking for divergance (infinity can be any user-defined value)
				
				double infinity = 32;
				if (fabs(a + b) > infinity)
				{
					break;
				}
				
				n++;
			}
			
			int grayVal = mapDouble(n, 0, 100, 0, 255);
			
			if (n == 100)
			{
				grayVal = 0xFF;
			}
			
			SDL_SetRenderDrawColor(renderer, grayVal, grayVal, grayVal, 0xFF);
			SDL_RenderDrawPoint(renderer, x, y);
		}
		
		// Uncomment this line for an animated effect
		// SDL_RenderPresent(renderer);
	}
	
	SDL_RenderPresent(renderer);
	
	SDL_DestroyRenderer(renderer);
	
	// Waits for the user to close the window
	SDL_bool done = SDL_FALSE;
	while (!done)
	{
		SDL_Event event;
		
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				done = SDL_TRUE;
			}
		}
	}
	
	// Free up memory
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
