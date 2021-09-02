#include "UIButton.h"
#include "UIElement.h"
#include "GameData.h"
#include <memory>

void UIButton::InitCommon(std::string &btnText) {
	this->btnText = btnText;

	this->btnFont = TTF_OpenFont("fonts/arial.ttf", 32);
	this->btnSurface = TTF_RenderText_Solid(this->btnFont, this->btnText.c_str(), SDL_Color{ 30, 30, 30 });
	SDL_Renderer* rend = GameData::GetInstance()->renderer;
	this->btnTexture = SDL_CreateTextureFromSurface(rend, btnSurface);
	this->btnRect.x = this->x;
	this->btnRect.y = this->y;
	this->btnRect.w = this->w;
	this->btnRect.h = this->h;

	this->textRect.x = this->x + (this->w / 2) - (btnSurface->w / 2);
	this->textRect.y = this->y + (this->h / 2) - (btnSurface->h / 2);
	this->textRect.w = btnSurface->w;
	this->textRect.h = btnSurface->h;

	this->highlighted = false;
}


UIButton::UIButton(int x, int y, int w, int h, std::string btnText, const std::function<void()> &action) {
	this->action = action;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	
	InitCommon(btnText);

	this->autoLayout = false;
}


UIButton::UIButton(UIHandler &hnd, std::string btnText, const std::function<void()>& action) {
	this->action = action;
	SDL_Rect* wndRect = hnd.GetWindow()->GetRect();
	this->x = wndRect->x + 10;
	SDL_Rect* bottomElem = hnd.GetBottomElementRect();
	if (bottomElem == nullptr) {
		this->y = wndRect->y + 50;
	}
	else {
		this->y = bottomElem->y + bottomElem->h + 10;
	}
	this->w = wndRect->w - 20;
	this->h = 100;
	InitCommon(btnText);
	this->autoLayout = true;
}


void UIButton::Draw() {
	if (show) {
		SDL_Renderer* rend = GameData::GetInstance()->renderer;
		SDL_SetRenderDrawColor(rend, (this->highlighted) ? 100 : 200, (this->highlighted) ? 100 : 200, (this->highlighted) ? 100 : 200, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(rend, &btnRect);
		SDL_RenderCopy(rend, btnTexture, NULL, &textRect);
	}
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

bool UIButton::IsAutoLayout() {
	return this->autoLayout;
}

SDL_Rect* UIButton::GetRect() {
	return &this->btnRect;
}