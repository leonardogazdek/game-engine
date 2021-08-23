#include <iostream>
#include <SDL.h>
#include <chrono>
#include <thread>
#include <vector>
#include <iterator>
#include <algorithm>
#include "GameData.h"
#include "Player.h"

using namespace std;

unsigned int maxFps = 250;

// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args) {
	// Pointers to our window and surface
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	// Initialize SDL. SDL_Init will return -1 if it fails.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		system("pause");
		// End the program
		return 1;
	}

	// Create our window
	window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

	// Make sure creating the window succeeded
	if (!window) {
		cout << "Error creating window: " << SDL_GetError() << endl;
		system("pause");
		// End the program
		return 1;
	}

	GameData().GetInstance()->window = window;

	renderer = SDL_CreateRenderer(window, -1, 0);

	bool stop = false;

	Uint32 lastUpdate = SDL_GetTicks();
	Player player = Player();
	while (!stop) {
		Uint64 start = SDL_GetPerformanceCounter();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {
					stop = true;
					break;
				}
			}
			player.HandleEvents(&event);
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		// PHYSICS
		Uint32 current = SDL_GetTicks();

		// Calculate dT (in seconds)

		float dT = (current - lastUpdate) / 10.0f;

		player.HandlePhysics(dT);

		lastUpdate = current;


		// DRAW

		player.HandleDrawing(renderer);

		SDL_RenderPresent(renderer);

		Uint64 end = SDL_GetPerformanceCounter();

		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

		// Cap to 60 FPS
		int delay = abs(1000.0f / maxFps - elapsedMS);
		SDL_Delay(delay);
	}

	

	

	// Destroy the window. This will also destroy the surface
	SDL_DestroyWindow(window);

	// Quit SDL
	SDL_Quit();

	// End the program
	return 0;
}