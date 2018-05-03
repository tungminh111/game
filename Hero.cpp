#include "header.h"

Hero::Hero() {
    pos={0,370};
    direction=RIGHT;
    velX=velY=0;
    velY=16;
    jump=jumping=false;
    canJump=80;
    currentHeight=0;
    currentMotion=0;
    fire=false;
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
            case SDLK_x:
                fire=true; //add
                break;
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

void Hero::operate(BulletControl &bulletScreen) {
    if (fire) {
        if (direction==RIGHT) bulletScreen.addBullet(pos.x+112,pos.y+41,direction); else
            bulletScreen.addBullet(pos.x-20,pos.y+41,direction);
        fire=false;
        BulletManager::updateData();
    }
    SDL_Point past=pos;
    bool st=true;
    if (velX>0) {
        if (direction==RIGHT) {
            pos.x=std::min(pos.x+velX,SDLScreenWidth);
        } else {
            direction=RIGHT;
            st=false;
        }
    } else
    if (velX<0) {
        if (direction==LEFT) {
            pos.x=std::max(pos.x+velX,0);
        } else {
            direction=LEFT;
            st=false;
        }
    }
    if (velX==0) st=false;
    if (!currentHeight) {
        if (jump) jumping=true; else
        if (st) {
            currentMotion++;
            currentMotion%=4;
        }
        if (jumping) currentHeight+=velY,pos.y-=velY;
    } else {
        if (jumping) currentHeight+=velY,pos.y-=velY; else {
            pos.y+=currentHeight-std::max(0,currentHeight-velY);
            currentHeight=std::max(0,currentHeight-velY);
        }
        if (currentHeight==canJump) jumping=false;
    }

    if (direction==LEFT) body[currentMotion].render(pos.x,pos.y,SDL_FLIP_HORIZONTAL); else body[currentMotion].render(pos.x,pos.y);
}
