#include "Obstacle.h"

Obstacle::Obstacle(SDL_Renderer* renderer, SDL_Rect rect, const char* textureImgFile) {
	this->renderer = renderer;
	this->rect = rect;
	this->textureImg = IMG_Load(textureImgFile);
	this->texture = SDL_CreateTextureFromSurface(renderer, this->textureImg);
}

void Obstacle::Draw() {
	SDL_RenderCopy(this->renderer, this->texture, NULL, &rect);
}

SDL_Rect* Obstacle::GetRect() {
	return &(this->rect);
}

Obstacles::Obstacles(SDL_Renderer* renderer) {
	this->renderer = renderer;
}

void Obstacles::Add(Obstacle obstacle) {
	obstacles.push_back(obstacle);
}

void Obstacles::Draw() {
	for (Obstacle& o : obstacles) {
		o.Draw();
	}
}

std::vector<Obstacle>* Obstacles::GetObstacles() {
	return &(this->obstacles);
}