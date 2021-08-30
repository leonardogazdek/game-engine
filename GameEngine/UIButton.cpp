#include "UIButton.h"

UIButton::UIButton(int x, int y, int w, int h, std::string btnText, const std::function<void()> &action) {
	this->action = action;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->btnText = btnText;

	this->btnFont = TTF_OpenFont("fonts/arial.ttf", 32);
	this->btnSurface = TTF_RenderText_Solid(this->btnFont, this->btnText.c_str(), SDL_Color{ 30, 30, 30 });
	SDL_Renderer* rend = GameData::GetInstance()->renderer;
	this->btnTexture = SDL_CreateTextureFromSurface(rend, btnSurface);
	this->btnRect.x = x;
	this->btnRect.y = y;
	this->btnRect.w = w;
	this->btnRect.h = h;

	this->textRect.x = x + (w/2) - (btnSurface->w / 2);
	this->textRect.y = y + (h / 2) - (btnSurface->h / 2);
	this->textRect.w = btnSurface->w;
	this->textRect.h = btnSurface->h;

	this->highlighted = false;

}

void UIButton::Draw() {
	SDL_Renderer* rend = GameData::GetInstance()->renderer;
	SDL_SetRenderDrawColor(rend, (this->highlighted) ? 100 : 200, (this->highlighted) ? 100 : 200, (this->highlighted) ? 100 : 200, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(rend, &btnRect);
	SDL_RenderCopy(rend, btnTexture, NULL, &textRect);
}

void UIButton::Highlight() {
	this->highlighted = true;
}

void UIButton::RemoveHighlight() {
	this->highlighted = false;
}

void UIButton::CallAction() {
	this->action();
}