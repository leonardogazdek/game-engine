#include <iostream>
#include <SDL.h>
#include <chrono>
#include <thread>
#include <vector>
#include <iterator>
#include <algorithm>
#include "GameData.h"
#include "Player.h"
#include <SDL_image.h>
#include "Obstacle.h"
#include "CollisionMap.h"

using namespace std;

unsigned int maxFps = 250;

const int resX = 1280;
const int resY = 720;

int main(int argc, char** args) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		system("pause");
		// End the program
		return 1;
	}

	window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resX, resY, SDL_WINDOW_SHOWN);

	if (!window) {
		cout << "Error creating window: " << SDL_GetError() << endl;
		system("pause");
		// End the program
		return 1;
	}

	GameData gData;
	gData.GetInstance()->window = window;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	SDL_RenderSetScale(renderer, resX/1280.0f, resY/720.0f);
	bool stop = false;

	Uint32 lastUpdate = SDL_GetTicks();
	Player player = Player(renderer);

	Obstacles obs(renderer);

	obs.Add(Obstacle(renderer, SDL_Rect{ 300, 600, 100, 120 }, "house.png"));

	SDL_Surface* backgroundImg = IMG_Load("background.jpg");
	SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundImg);
	
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
		
		// PHYSICS
		Uint32 current = SDL_GetTicks();

		// Calculate dT (in seconds)

		float dT = (current - lastUpdate) / 10.0f;

		player.HandlePhysics(dT, &obs);

		lastUpdate = current;


		// DRAW

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);


		obs.Draw();
		player.HandleDrawing();
		

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