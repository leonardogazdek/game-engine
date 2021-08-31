#include <iostream>
#include <SDL.h>
#include <chrono>
#include <thread>
#include <vector>
#include <iterator>
#include <algorithm>
#include <memory>
#include <SDL_image.h>
#include <fstream>
#include <cstdint>
#include <functional>
#include <filesystem>
#include <string>

#include "Player.h"
#include "Obstacle.h"
#include "GameData.h"
#include "UIHandler.h"
#include "UIElement.h"
#include "UIWindow.h"
#include "UIButton.h"
#include "MapData.h"


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

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
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

	UIHandler uiHandler;

	auto levelSelectWindow = std::make_shared<UIWindow>("Choose level", 1000, 600);
	
	uiHandler.Add(levelSelectWindow);
	

	
	MapData map;

	std::vector<std::shared_ptr<UIElement> > levelSelectMenu;
	levelSelectMenu.push_back(levelSelectWindow);

	std::shared_ptr<Player> player = nullptr;
	SDL_Surface* backgroundImg;
	SDL_Texture* backgroundTexture;

	auto loadMapData = [&player, &backgroundImg, &backgroundTexture, &map, &renderer]() {
		player = std::make_shared<Player>(renderer, map.startingPosX, map.startingPosY);


		backgroundImg = IMG_Load("textures/background.jpg");
		backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundImg);
		map.mapLoaded = true;
	};

	

	for (const std::string mapName : map.GetAllMaps()) {
		auto mapBtn = std::make_shared<UIButton>(uiHandler, mapName, [&levelSelectMenu, &uiHandler, mapName, &map, &loadMapData, &renderer]() {
			map.LoadMap(mapName); 
			loadMapData(); 
			for (const auto& elem : levelSelectMenu) {
				elem->Hide();
			}
		});
		levelSelectMenu.push_back(mapBtn);

		uiHandler.Add(mapBtn);
	}

	
	

	

	while (!stop) {
		std::uint64_t start = SDL_GetPerformanceCounter();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {
					stop = true;
					break;
				}
				case SDL_KEYDOWN: {
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE: {
							for (const auto& elem : levelSelectMenu) {
								elem->Show();
							}
							break;
						}
					}
				}
			}
			if (map.mapLoaded) {
				player->HandleEvents(&event);
			}
			uiHandler.HandleEvents(&event);
		}
		
		// PHYSICS
		Uint32 current = SDL_GetTicks();

		// Calculate dT (in seconds)

		float dT = (current - lastUpdate) / 10.0f;

		if (map.mapLoaded) {
			player->HandlePhysics(dT, &map.obs);
		}

		lastUpdate = current;


		// DRAW

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		

		if (map.mapLoaded) {
			SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
			map.obs.Draw();
			player->HandleDrawing();
		}
			
		uiHandler.Draw();
		SDL_RenderPresent(renderer);

		std::uint64_t end = SDL_GetPerformanceCounter();

		float elapsedMS = (end - start) / static_cast<float>(SDL_GetPerformanceFrequency()) * 1000.0f;


		int delay = static_cast<int>(abs(1000.0f / maxFps - elapsedMS));
		SDL_Delay(delay);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}