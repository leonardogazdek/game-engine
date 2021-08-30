#pragma once
#include <vector>
#include <memory>
#include "UIElement.h"
#include "UIButton.h"

class UIHandler
{
private:
	std::vector<std::shared_ptr<UIElement>> elements;
	int highlightedButton;
	void HighlightPrevButton();
	void HighlightNextButton();
public:
	UIHandler();
	void Draw();
	void Add(const std::shared_ptr<UIElement> &element);
	int CountBtns();
	void HighlightSelectedButton();
};

