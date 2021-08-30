#pragma once
#include <vector>
#include <memory>
#include "UIElement.h"
class UIHandler
{
private:
	std::vector<std::shared_ptr<UIElement>> elements;
public:
	void Draw();
	void Add(std::shared_ptr<UIElement> &element);
};

