#pragma once
#include <iostream>
#include <SDL.h>

class GameData {
private:
	static GameData* Instance;
public:
	GameData();
	GameData* GetInstance();
	SDL_Window* window;

};
