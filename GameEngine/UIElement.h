#pragma once
#include <SDL.h>
class UIElement
{
protected:
	bool autoLayout = false;
public:
	virtual void Draw() = 0;
	virtual bool IsAutoLayout() = 0;
	virtual SDL_Rect* GetRect() = 0;
};

