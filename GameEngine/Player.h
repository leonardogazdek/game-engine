#pragma once

#include <SDL.h>
#include <algorithm>
#include "GameData.h"

class Player
{
private: 
	float playerX, playerY;
	float deltaX, deltaY;
	float jumpDelta;
	bool jumping;
public:
	Player();
	void HandleEvents(SDL_Event* event);
	void HandlePhysics(float dT);
	void HandleDrawing(SDL_Renderer* renderer);
};

