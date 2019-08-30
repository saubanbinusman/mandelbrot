#include <iostream>
#include <cmath>

#include <SDL2/SDL.h>

using namespace std;

// Screen dimensions
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

SDL_Renderer* renderer;

double mapDouble(double valToMap, double valMin, double valMax, double mappedMin, double mappedMax)
{
	return ((valToMap - valMin) / (valMax - valMin)) * (mappedMax - mappedMin) + mappedMin;
}

void generateMandelBrot(int maxIterations, int bailOut, double xStart, double xEnd, double yStart, double yEnd)
{
	unsigned int start = SDL_GetTicks();
	
	for (int Px = 0; Px < SCREEN_WIDTH; Px++)
	{
		for (int Py = 0; Py < SCREEN_HEIGHT; Py++)
		{
			double x0 = mapDouble(Px, 0, SCREEN_WIDTH, xStart, xEnd);
			double y0 = mapDouble(Py, 0, SCREEN_HEIGHT, yStart, yEnd);
			
			double x = x0;
			double y = y0;
			
			int iteration = 0;
			
			while (iteration < maxIterations && fabs(x + y) < bailOut)
			{
				double xTemp = (x * x) - (y * y) + x0;
				
				y = (2 * x * y) + y0;
				x = xTemp;
				
				iteration++;
			}
			
			int r, g, b;
			
			if (iteration == maxIterations) r = 0, g = 0, b = 0;
			else if (iteration < 100) r = (iteration * 6) % 256, g = (iteration * 30) % 256, b = (iteration * 7) % 256;
			else r = 255, g = 255, b = 255;
			
			SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
			SDL_RenderDrawPoint(renderer, Px, Py);
		}
		
		// Shows progress of current calculation on console
		//cout << ((double)(Px + 1) / SCREEN_WIDTH) * 100 << "%" << endl;
		
		// Uncomment this line for an animated effect
		// SDL_RenderPresent(renderer);
	}
	
	SDL_RenderPresent(renderer);
	
	unsigned int end = SDL_GetTicks();
	
	cout << "Took " << (end - start) << " ms to render." << endl;
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
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	if (renderer == NULL)
	{
		cout << "Could not create Renderer, Error: " << SDL_GetError() << endl;
		return 0;
	}
	
	int bailout = 16;
	int iterations = 100;
	
	double startX = -2.0;
	double endX = 2.0;
	
	double startY = -2.0;
	double endY = 2.0;
	
	generateMandelBrot(iterations, bailout, startX, endX, startY, endY);
	
	// Waits for the user to close the window
	SDL_bool done = SDL_FALSE;
	while (!done)
	{
		SDL_Event event;
		
		while (SDL_PollEvent(&event))
		{
			bool call = false;
			
			switch(event.type)
			{
				case SDL_QUIT:
					done = SDL_TRUE;
					break;
				
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_LEFT:
							startX -= 0.05;
							endX -= 0.05;
							call = true;
							break;
						
						case SDLK_RIGHT:
							startX += 0.05;
							endX += 0.05;
							call = true;
							break;
						
						case SDLK_UP:
							startY -= 0.05;
							endY -= 0.05;
							call = true;
							break;
						
						case SDLK_DOWN:
							startY += 0.05;
							endY += 0.05;
							call = true;
							break;
						
						case SDLK_j:
							startX += 0.05;
							endX -= 0.05;
							startY += 0.05;
							endY -= 0.05;
							call = true;
							break;
						
						case SDLK_k:
							startX -= 0.05;
							endX += 0.05;
							startY -= 0.05;
							endY += 0.05;
							call = true;
							break;
						
						default:
							break;
					}
					
					if (call) generateMandelBrot(iterations, bailout, startX, endX, startY, endY);
					call = false;
					break; 
				
				default:
					break;
			}
		}
	}
	
	// Free up memory
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
