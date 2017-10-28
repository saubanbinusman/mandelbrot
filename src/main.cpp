#include <iostream>
#include <cmath>

#include <SDL2/SDL.h>

using namespace std;

// Screen dimensions
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;

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
	
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // White
	SDL_RenderClear(renderer); // Fil it with white
	
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // Black
	
	/*
	for (int i = 0; i < SCREEN_WIDTH; i += 1)
	{
		SDL_RenderDrawPoint(renderer, i, i);
	}
	
	for (int i = SCREEN_WIDTH, j = 0; i >= 0; i -= 1, j += 1)
	{
		SDL_RenderDrawPoint(renderer, i, j);
	}
	
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		SDL_RenderDrawPoint(renderer, i, SCREEN_HEIGHT >> 1);
	}
	
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		SDL_RenderDrawPoint(renderer, SCREEN_WIDTH >> 1, i);
	}*/
	
	//const double PI = 3.14159265358979323846;
	
	for (double x = -1.0; x <= 1.0; x += 0.001)
	{
		double y = sqrt(1.0 - (x * x));
		
		int xx = (int)(x * 100) + (SCREEN_WIDTH >> 1);
		int yy = (int)(y * 100);
		
		//cout << "(" << xx << ", " << yy << ")" << endl;
		
		//double x_Rad = (double)(x) * (PI / 180.0);
		
		//int y = (int)(sin(x_Rad) * 45) + (SCREEN_WIDTH >> 1);
		
		//int y = (int)((sin((double)x)) + (SCREEN_HEIGHT >> 1));
		
		//int xx = (x < 180) ? x : -x + (SCREEN_WIDTH);
		
		SDL_RenderDrawPoint(renderer, xx, (SCREEN_WIDTH >> 1) + yy);
		SDL_RenderDrawPoint(renderer, xx, (SCREEN_WIDTH >> 1) - yy);
		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}
	
	SDL_RenderPresent(renderer);
	
	SDL_DestroyRenderer(renderer);
	
	// Delay to allow the user to see the window
	// otherwise, it just flashes and closes
	SDL_Delay(3000);
	
	// Free up memory
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
