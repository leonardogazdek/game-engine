#pragma once

#include <functional>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "GameData.h"


#include "UIElement.h"
class UIButton :
    public UIElement
{
private:
    std::function<void()> action;
    int x, y, w, h;
    std::string btnText;
    SDL_Rect btnRect, textRect;
    TTF_Font *btnFont;
    SDL_Surface* btnSurface;
    SDL_Texture* btnTexture;
    bool highlighted;

public:
    UIButton(int x, int y, int w, int h, std::string btnText, const std::function<void()>& action);
    void Draw();
    void Highlight();
    void RemoveHighlight();
    void CallAction();
};

