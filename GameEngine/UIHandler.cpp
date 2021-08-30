#include "UIHandler.h"

UIHandler::UIHandler() {
	highlightedButton = 0;
}

void UIHandler::Draw() {
	for (auto& element : elements) {
		element->Draw();
	}
}

void UIHandler::Add(const std::shared_ptr<UIElement> &element) {
	elements.push_back(element);
	HighlightSelectedButton();
}

void UIHandler::HighlightNextButton() {
	highlightedButton++;
	if (highlightedButton >= CountBtns()) {
		highlightedButton = 0;
	}
	HighlightSelectedButton();
}

void UIHandler::HighlightPrevButton() {
	highlightedButton--;
	if (highlightedButton < 0) {
		highlightedButton = CountBtns() - 1;
	}
	HighlightSelectedButton();
}

void UIHandler::HighlightSelectedButton() {
	int btnIndex = 0;
	for (auto const &el : elements) {
		auto btnPtr = std::dynamic_pointer_cast<UIButton>(el);
		if (btnPtr != nullptr) {
			if (btnIndex == highlightedButton) {
				btnPtr->Highlight();
			}
			else {
				btnPtr->RemoveHighlight();
			}
			btnIndex++;
		}
	}
}

int UIHandler::CountBtns() {
	int count = 0;
	for (auto& el : elements) {
		if (std::dynamic_pointer_cast<UIButton>(el) != nullptr) {
			count++;
		}
	}
	return count;
}

void UIHandler::HandleEvents(SDL_Event* ev) {
	switch (ev->type) {
		case SDL_KEYDOWN: {
			switch (ev->key.keysym.sym) {
				case SDLK_DOWN: {
					HighlightNextButton();
					break;
				}
				case SDLK_UP: {
					HighlightPrevButton();
					break;
				}
				case SDLK_RETURN: {
					int btnIndex = 0;
					for (auto const& el : elements) {
						auto btnPtr = std::dynamic_pointer_cast<UIButton>(el);
						if (btnPtr != nullptr) {
							if (btnIndex == highlightedButton) {
								btnPtr->CallAction();
								break;
							}
							btnIndex++;
						}
					}
					break;
				}
			}
			break;
		}
	}
}