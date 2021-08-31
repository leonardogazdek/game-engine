#pragma once
#include "UIElement.h"
#include "GameData.h"
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_image.h>

class UIWindow :
    public UIElement
{
private:
    std::string windowTitle;
    int x, y, w, h;
    SDL_Rect windowRect;
    SDL_Rect titleBarRect;
    TTF_Font* titleFont;
    SDL_Color titleColor{ 0,0,0 };
    SDL_Surface* titleSurface;
    SDL_Texture* titleTexture;
    SDL_Rect titleRect;
public:
    UIWindow(std::string windowTitle, int w, int h);
    void Draw();
    SDL_Rect* GetRect();
    bool IsAutoLayout();
};

