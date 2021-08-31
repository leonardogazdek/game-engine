#include "UIWindow.h"
#include <iostream>

UIWindow::UIWindow(std::string windowTitle, int w, int h) {
	int screenWidth, screenHeight;
	SDL_GetWindowSize(GameData::GetInstance()->window, &screenWidth, &screenHeight);
	this->x = static_cast<int>((screenWidth / 2.0f) - (w / 2.0f));
	this->y = static_cast<int>((screenHeight / 2.0f) - (h / 2.0f));
	this->w = w;
	this->h = h;
	windowRect.x = this->x;
	windowRect.y = this->y;
	windowRect.w = this->w;
	windowRect.h = this->h;
	this->windowTitle = windowTitle;
	titleFont = TTF_OpenFont("fonts/arial.ttf", 32);
	titleSurface = TTF_RenderText_Solid(titleFont, this->windowTitle.c_str(), titleColor);
	titleTexture = SDL_CreateTextureFromSurface(GameData::GetInstance()->renderer, titleSurface);
	titleRect.x = this->x + 5;
	titleRect.y = this->y + 5;
	titleRect.w = titleSurface->w;
	titleRect.h = titleSurface->h;
	titleBarRect.x = this->x + 5;
	titleBarRect.y = this->y + 5;
	titleBarRect.w = this->w - 10;
	titleBarRect.h = titleSurface->h;
	this->autoLayout = false;
}

void UIWindow::Draw() {
	SDL_Renderer* rend = GameData::GetInstance()->renderer;
	SDL_SetRenderDrawColor(rend, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(rend, &windowRect);
	SDL_SetRenderDrawColor(rend, 200, 200, 200, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(rend, &titleBarRect);
	SDL_RenderCopy(rend, titleTexture, NULL, &titleRect);
}

SDL_Rect* UIWindow::GetRect() {
	return &this->windowRect;
}

bool UIWindow::IsAutoLayout() {
	return this->autoLayout;
}