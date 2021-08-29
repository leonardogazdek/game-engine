#pragma once
#include <vector>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include "CollisionMap.h"

class Obstacle {
private:
	SDL_Surface* textureImg;
	SDL_Texture* texture;
	SDL_Rect rect;
	SDL_Renderer* renderer;
public:
	Obstacle(SDL_Renderer* renderer, SDL_Rect rect, const char* textureImg);
	void Draw();
	SDL_Rect* GetRect();
};

class Obstacles {
private:
	SDL_Renderer* renderer;
	std::vector<Obstacle> obstacles;
public:
	Obstacles(SDL_Renderer* renderer);
	void Add(Obstacle obstacle);
	void Draw();
	std::vector<Obstacle>* GetObstacles();
};