#include "header.h"

int HealthManager::health;
int HealthManager::maxHealth;

void HealthManager::setData(int _maxHealth) {
    maxHealth = _maxHealth;
    health = maxHealth;
}

void HealthManager::updateHealth(int change) {
    health += change;
    if (health > maxHealth) health = maxHealth;
    if (health < 0) health = 0;
}

void HealthManager::displayHealth() {
    SDL_Rect dstRect;
    dstRect.x = 20;
    dstRect.y = 15;
    dstRect.w = 172;
    dstRect.h = 38;

    //health bar
    gScreenSurface = IMG_Load("art/HealthBar.png");
    SDL_Texture* healthBar = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);
    SDL_FreeSurface(gScreenSurface);
    SDL_RenderCopy(gRenderer, healthBar, NULL, &dstRect);

    SDL_DestroyTexture(healthBar);

    //health
    for (int i = 0; i < health; i++) {
        SDL_Rect dstRect1;
        dstRect1 = dstRect;
        dstRect1.w = 160 / health;
        dstRect1.h = 30;
        dstRect1.y += 4;
        dstRect1.x += 8 + i * 160 / health;

        gScreenSurface = IMG_Load("art/Health.png");
        SDL_Texture* health = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);
        SDL_FreeSurface(gScreenSurface);
        SDL_RenderCopy(gRenderer, health, NULL, &dstRect1);

        SDL_DestroyTexture(health);
    }
}
