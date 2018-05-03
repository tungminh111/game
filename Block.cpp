#include "header.h"

void Block::loadTex(std::string s) {
    mTexture.loadTex(s.c_str());
}

SDL_Rect Block::getRect() {return display;}

void Block::setBlock(const int &x,const int &y,const int &w,const int &h) {
    display={x,y,w,h};
}

void Block::render() {
    mTexture.render(display.x,display.y);
}

void Block::checkbul(Bullet &bullet) {
    SDL_Rect rect1={bullet.pos.x,bullet.pos.y,bullet.width,bullet.height};
    SDL_Rect rect2=display;
    if (!collised(rect1,rect2)) return;
    bullet.Collision();
}

void Block::free() {
    mTexture.free();

}
