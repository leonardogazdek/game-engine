#include <iostream>
#include <SDL.h>
#include <chrono>
#include <thread>
#include <vector>
#include <iterator>
#include <algorithm>
#include <memory>
#include "GameData.h"
#include "Player.h"
#include <SDL_image.h>
#include "Obstacle.h"
#include <fstream>
#include <cstdint>
#include <functional>
#include "UIHandler.h"
#include "UIElement.h"
#include "UIWindow.h"
#include "UIButton.h"


unsigned int maxFps = 250;

const int resX = 1280;
const int resY = 720;

int main(int argc, char** args) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		system("pause");
		// End the program
		return 1;
	}

	window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resX, resY, SDL_WINDOW_SHOWN);

	if (!window) {
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		system("pause");
		return 1;
	}

	GameData::GetInstance()->window = window;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	SDL_RenderSetScale(renderer, resX/1280.0f, resY/720.0f);
	bool stop = false;

	GameData::GetInstance()->renderer = renderer;

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return 1;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 1;
	}


	Uint32 lastUpdate = SDL_GetTicks();

	std::ifstream mapFile("maps/first.gmap", std::ios::binary);

	std::uint16_t startingPosX, startingPosY, obstacles;
	mapFile.read(reinterpret_cast<char*>(&startingPosX), sizeof(startingPosX));
	mapFile.read(reinterpret_cast<char*>(&startingPosY), sizeof(startingPosY));
	mapFile.read(reinterpret_cast<char*>(&obstacles), sizeof(obstacles));


	Obstacles obs(renderer);
	for (int i = 0; i < obstacles; i++) {
		std::uint16_t x, y, w, h;
		char textureFile[50];

		mapFile.read(reinterpret_cast<char*>(&x), sizeof(x));
		mapFile.read(reinterpret_cast<char*>(&y), sizeof(y));
		mapFile.read(reinterpret_cast<char*>(&w), sizeof(w));
		mapFile.read(reinterpret_cast<char*>(&h), sizeof(h));
		mapFile.read(textureFile, sizeof(textureFile));

		obs.Add(Obstacle(renderer, SDL_Rect{ x, y, w, h }, std::string("textures/" + std::string(textureFile)).c_str()));
	}
	
	mapFile.close();



	Player player = Player(renderer, startingPosX, startingPosY);


	SDL_Surface* backgroundImg = IMG_Load("textures/background.jpg");
	SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundImg);

	UIHandler uiHandler;

	auto testWindow = std::make_shared<UIWindow>("My window", 1000, 600);
	auto testButton = std::make_shared<UIButton>(300, 300, 300, 50, "wyd", []() { std::cout << "test" << std::endl;});
	uiHandler.Add(std::dynamic_pointer_cast<UIElement>(testWindow));
	uiHandler.Add(std::dynamic_pointer_cast<UIElement>(testButton));

	uiHandler.HighlightSelectedButton();

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
		uiHandler.Draw();
		SDL_RenderPresent(renderer);

		Uint64 end = SDL_GetPerformanceCounter();

		float elapsedMS = (end - start) / static_cast<float>(SDL_GetPerformanceFrequency()) * 1000.0f;


		int delay = abs(1000.0f / maxFps - elapsedMS);
		SDL_Delay(delay);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}