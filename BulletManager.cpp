#include "header.h"

int BulletManager::bullet;
TTF_Font* BulletManager::gFont;

void BulletManager::setData(const int &_bullet) {
    bullet = _bullet;
    gFont = TTF_OpenFont( "font/brush.ttf", 30 );
}

void BulletManager::updateData() {
    bullet--;
}

int BulletManager::get(){ return bullet;}

void BulletManager::displayBullet() {
    //draw icon
    SDL_Rect dstRect;
    dstRect.x = 120;
    dstRect.y = 20;
    dstRect.w = 30;
    dstRect.h = 30;

    gScreenSurface = IMG_Load("art/bullet_icon.png");
    SDL_Texture* icon = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);
    SDL_FreeSurface(gScreenSurface);

    SDL_RenderCopy(gRenderer, icon, NULL, &dstRect);

    SDL_DestroyTexture(icon);

    //draw number
    gScreenSurface = TTF_RenderText_Solid(gFont, std::to_string(bullet).c_str(), {0,0,0,255});
    SDL_Texture* number = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);
    dstRect.x = dstRect.x + 40;
    dstRect.y = dstRect.y + 5;
    dstRect.w = gScreenSurface->w;
    dstRect.h = gScreenSurface->h;
    SDL_FreeSurface(gScreenSurface);

    SDL_RenderCopy(gRenderer, number, NULL, &dstRect);

    SDL_DestroyTexture(number);
}

