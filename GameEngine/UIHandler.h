#pragma once

#include <memory>
#include <SDL.h>
#include <vector>
#include "UIElement.h"
#include "UIWindow.h"

class UIHandler
{
private:
	std::vector<std::shared_ptr<UIElement>> elements;
	int highlightedButton;
	void HighlightPrevButton();
	void HighlightNextButton();
	void HighlightSelectedButton();
public:
	UIHandler();
	void Draw();
	void Add(const std::shared_ptr<UIElement> &element);
	int CountBtns();
	void HandleEvents(SDL_Event* ev);
	const std::shared_ptr<UIWindow> GetWindow();
	SDL_Rect* GetBottomElementRect();
};

