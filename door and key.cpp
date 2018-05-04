#include "header.h"

LTexture Door::mTexture;
SDL_Rect Door::display;
int Key::keyGathered;
int Key::keyNeeded;

void Door::load(const int &stage){
    if (Key::keyGathered<Key::keyNeeded) return ;
    if (stage==1) Stage1::load();
    if (stage==2) Stage2::load();
    if (stage==3) Stage3::load();
};

void Door::render(const int &x,const int &y){
    mTexture.render(x,y);
    display.x=x;
    display.y=y;
};

void Door::loadTex(std::string c){
    mTexture.loadTex(c.c_str());
    display.w=mTexture.getWidth();
    display.h=mTexture.getHeight();
};

void Door::free() {
    mTexture.free();
}

SDL_Rect Door::getRect(){ return display;};

void Key::Gather() {
    if (gathered) return;
    gathered=true;
    ++keyGathered;
    mTexture.free();
}

SDL_Rect Key::getRect(){ return display;}

void Key::render(const int &x,const int &y){
    mTexture.render(x,y);
    display.x=x;
    display.y=-100;
    display.h=y+mTexture.getHeight()+120;
};

void Key::loadTex(std::string c){
    gathered=false;
    mTexture.loadTex(c.c_str());
    display.w=mTexture.getWidth();
};

void Key::free() {
    mTexture.free();
}
void Key::init() {keyGathered=0;};
void Key::setKey(const int &keyNum) {keyNeeded=keyNum;};
bool Key::enough(){ return keyGathered==keyNeeded;};

void Key::displayKey() {
    gScreenSurface = IMG_Load("art/key.png");
    SDL_Texture* key = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);

    SDL_Rect dstRect;
    if (keyGathered == 1) dstRect.x = 80;
    else dstRect.x = 40;
    dstRect.y = 60;
    dstRect.w = gScreenSurface->w;
    dstRect.h = gScreenSurface->h;

    SDL_FreeSurface(gScreenSurface);

    for (int i = 0; i < keyGathered; i++) {
        SDL_RenderCopy(gRenderer, key, NULL, &dstRect);
        dstRect.x += 80;
    }
}
