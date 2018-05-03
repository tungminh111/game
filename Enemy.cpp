#include "header.h"

void Enermy::setLoop(const int &posX,const int &posY,const int &_x1,const int &_x2,const int &_y) {
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
    dem=10;
    hp=5;
}

void Enermy::operate() {
    if (died) return;
    dem++;
    dem%=60;
    if (dem==0||dem==10) {
        if (direction==RIGHT) BulletControl::addBullet(pos.x+78,pos.y+27,direction); else
            BulletControl::addBullet(pos.x+1,pos.y+27,direction);
    } else
    if (dem>10) {

        if (direction==LEFT) {
            if (pos.x<=x1)
                pos.x-=mWidth-2*canInjure[RIGHT].x-canInjure[RIGHT].w,direction=RIGHT,currentMotion=0;
            else {
                pos.x-=3;
                currentMotion++;
                currentMotion%=4;
            }
        } else {
            if (pos.x+mWidth-1>=x2)
                pos.x+=mWidth-2*canInjure[RIGHT].x-canInjure[RIGHT].w,direction=LEFT,currentMotion=0;
            else {
                pos.x+=3;
                currentMotion++;
                currentMotion%=4;
            }
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
    --hp;
    if (!hp) die();
    bullet.Collision();
}

void Enermy::die() {
    died=true;
    body[0].loadTex("art/die.png");
    body[0].render(pos.x,pos.y);
    For(i,0,3) body[i].free();
}

void Enermy::loadTex(std::string c) {
    For(i,0,3) {
        std::string s=c;
        s.push_back(char('0'+i));
        body[i].loadTex(s+".png");
    }
}
