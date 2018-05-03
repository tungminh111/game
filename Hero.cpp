#include "header.h"

Hero::Hero() {
    pos={800,270};
    direction=RIGHT;
    velX=0;
    velY=20;
    jump=jumping=false;
    canJump=120;
    currentHeight=0;
    currentMotion=0;
    width=113;
    height=130;
    fire=false;
    canInjure[RIGHT]={16,8,20,112};
    canInjure[LEFT]={77,8,20,112};
}

void Hero::loadTex(std::string c) {
    For(i,0,3) {
        std::string s=c;
        s.push_back(char('0'+i));
        body[i].loadTex(s+".png");
    }
}

void Hero::handleEvent(SDL_Event &e) {
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: jump=true; break;
            case SDLK_LEFT: velX -= 5; break;
            case SDLK_RIGHT: velX += 5; break;
            case SDLK_x:fire=true;break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: jump=false; break;
            case SDLK_LEFT: velX += 5; break;
            case SDLK_RIGHT: velX -= 5; break;
        }
    }
}

void Hero::operate(BulletControl &bulletScreen,Block block[],int blockNumber) {
    if (fire) {
        if (direction==RIGHT) bulletScreen.addBullet(pos.x+112,pos.y+41,direction); else
            bulletScreen.addBullet(pos.x-20,pos.y+41,direction);
        fire=false;
    }
    bool st=true;
    if (velX>0) {
        int velXX=velX;
        For(i,0,blockNumber-1) {
            SDL_Rect rect1=block[i].getRect();
            if (rect1.x>pos.x+width-1&&std::max(rect1.y,pos.y)<=std::min(rect1.y+rect1.h-1,pos.y+height-1)){
                velXX=std::min(velXX,rect1.x-(pos.x+width-1)-1);
            }
        }
        if (direction==RIGHT) {
            pos.x=std::min(pos.x+velXX,SDLScreenWidth);
        } else {
            direction=RIGHT;
            pos.x+=width-2*canInjure[RIGHT].x-canInjure[RIGHT].w;
            st=false;
        }
    } else
    if (velX<0) {
        int velXX=velX;
        For(i,0,blockNumber-1) {
            SDL_Rect rect1=block[i].getRect();
            if (rect1.x+rect1.w-1<pos.x&&std::max(rect1.y,pos.y)<=std::min(rect1.y+rect1.h-1,pos.y+height-1)) {
                velXX=std::max(velXX,-pos.x+(rect1.x+rect1.w-1)+1);
            }
        }
        if (direction==LEFT) {
            pos.x=std::max(pos.x+velXX,0);
        } else {
            direction=LEFT;
            pos.x-=width-2*canInjure[RIGHT].x-canInjure[RIGHT].w;
            st=false;
        }
    }
    if (velX==0) st=false;
    int stop=SDLScreenHeight-height+1;
    For(i,0,blockNumber-1) {
        SDL_Rect rect1=block[i].getRect();
        if (rect1.y>=pos.y+height-1&&std::max(rect1.x,pos.x)<=std::min(rect1.x+rect1.w-1,pos.x+width-1))
            stop=std::min(stop,rect1.y-height);
    }
    if (!currentHeight) {
        if (jump) jumping=true; else
        if (st) {
            currentMotion++;
            currentMotion%=4;
        }
        if (jumping) currentHeight+=velY,pos.y-=velY; else pos.y=std::min(pos.y+velY,stop);
    } else {
        if (jumping) currentHeight+=velY,pos.y-=velY; else {
            pos.y+=velY;
            pos.y=std::min(stop,pos.y);
            if (pos.y==stop) currentHeight=0; else currentHeight=1;
        }
        if (currentHeight==canJump) jumping=false;
    }
    if (direction==LEFT) body[currentMotion].render(pos.x,pos.y,SDL_FLIP_HORIZONTAL); else body[currentMotion].render(pos.x,pos.y);
}
