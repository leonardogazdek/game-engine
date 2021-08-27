#pragma once

#include <SDL.h>
#include <algorithm>
#include "GameData.h"
#include <SDL_image.h>
#include "Obstacle.h"
#include <cmath>

class Player
{
private: 
	float playerX, playerY;
	float deltaX, deltaY;
	float jumpDelta;
	unsigned int movementKeysPressed;
	SDL_Rect playerRect;
	SDL_Surface* imageTexture;
	SDL_Texture* playerTexture;
	SDL_Renderer* renderer;
	bool canJump;
public:
	Player(SDL_Renderer* renderer);
	~Player();
	void HandleEvents(SDL_Event* event);
	void HandlePhysics(float dT, Obstacles* obstacles);
	void HandleDrawing();
};

