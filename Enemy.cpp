#include "header.h"

void Enermy::setLoop(int posX,int posY,int _x1,int _x2,int _y) {
    x1=_x1;
    x2=_x2;
    y=_y;
    pos={posX,posY};
    currentMotion=0;
    direction=RIGHT;
    mWidth=mHeight=0;
    canInjure[RIGHT]={9,9,22,77};
    canInjure[LEFT]={50,9,22,77};
    died=false;
}

void Enermy::operate() {
    if (died) return;
    if (direction==LEFT) {
        if (pos.x<=x1)
            direction=RIGHT,currentMotion=0;
        else {
            pos.x-=3;
            currentMotion++;
            currentMotion%=4;
        }
    } else {
        if (pos.x+mWidth-1>=x2)
            direction=LEFT,currentMotion=0;
        else {
            pos.x+=3;
            currentMotion++;
            currentMotion%=4;
        }
    }
    if (direction==LEFT)
        body[currentMotion].render(pos.x,pos.y,SDL_FLIP_HORIZONTAL);
    else
        body[currentMotion].render(pos.x,pos.y,SDL_FLIP_NONE);
}

void Enermy::checkCollision(Bullet &bullet) {
    if (died) return;
    SDL_Rect rect1={bullet.pos.x,bullet.pos.y,bullet.width,bullet.height};
    SDL_Rect rect2={pos.x+canInjure[direction].x,pos.y+canInjure[direction].y,canInjure[direction].w,canInjure[direction].h};
    if (!collised(rect1,rect2)) return;
    die();
    bullet.Collision();
}

void Enermy::die() {
    died=true;
    body[0].loadTex("art/die.png");
    body[0].render(pos.x,pos.y);
}

void Enermy::loadTex(std::string c) {
    For(i,0,3) {
        std::string s=c;
        s.push_back(char('0'+i));
        body[i].loadTex(s+".png");
    }
}
