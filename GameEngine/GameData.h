#pragma once
#include <iostream>
#include <SDL.h>

class GameData {
private:
	static GameData* Instance;
public:
	GameData();
	static GameData* GetInstance();
	SDL_Window* window;
	SDL_Renderer* renderer;

};
