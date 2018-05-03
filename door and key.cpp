#include "header.h"

LTexture Door::mTexture;
SDL_Rect Door::display;
int Key::keyGathered;
int Key::keyNeeded;

void Door::load(const int &stage){
    if (Key::keyGathered<Key::keyNeeded) return ;
    if (stage==1) Stage1::load();
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
    ++keyGathered;
    mTexture.free();
}

SDL_Rect Key::getRect(){ return display;}

void Key::render(const int &x,const int &y){
    mTexture.render(x,y);
    display.x=0;
    display.y=y;
};

void Key::loadTex(std::string c){
    mTexture.loadTex(c.c_str());
    display.w=mTexture.getWidth();
    display.h=SDLScreenHeight;
};
