#include "header.h"
#include "time.h"

int TimeManager::time;
int TimeManager::baseTime;
TTF_Font* TimeManager::gFont;

void TimeManager::setData(int _time) {
    time = _time;
    baseTime = SDL_GetTicks() / 1000 + time;
    gFont = TTF_OpenFont( "font/brush.ttf", 30 );
}

void TimeManager::updateData() {
    time = baseTime - SDL_GetTicks() / 1000;
}

void TimeManager::displayTime() {
    //draw icon
    SDL_Rect dstRect;
    dstRect.x = 210;
    dstRect.y = 20;
    dstRect.w = 30;
    dstRect.h = 30;

    gScreenSurface = IMG_Load("art/clock_icon.png");
    SDL_Texture* icon = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);
    SDL_FreeSurface(gScreenSurface);

    SDL_RenderCopy(gRenderer, icon, NULL, &dstRect);

    SDL_DestroyTexture(icon);

    //draw number
    gScreenSurface = TTF_RenderText_Solid(gFont, std::to_string(time).c_str(), {0,0,0,255});
    SDL_Texture* number = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);
    dstRect.x = dstRect.x + 40;
    dstRect.y = dstRect.y + 5;
    dstRect.w = gScreenSurface->w;
    dstRect.h = gScreenSurface->h;
    SDL_FreeSurface(gScreenSurface);

    SDL_RenderCopy(gRenderer, number, NULL, &dstRect);

    SDL_DestroyTexture(number);
}
