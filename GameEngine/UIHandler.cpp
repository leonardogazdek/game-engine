#include "UIHandler.h"

void UIHandler::Draw() {
	for (auto& element : elements) {
		element->Draw();
	}
}

void UIHandler::Add(std::shared_ptr<UIElement> &element) {
	elements.push_back(element);
}