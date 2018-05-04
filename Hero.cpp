#include "header.h"

void Hero::init(const int &x,const int &y) {
    pos={x,y};
    direction=RIGHT;
    velX=0;
    velY=15;
    jump=jumping=false;
    ableHeight=120;
    currentMotion=0;
    mWidth=80;
    mHeight=92;
    fire=false;
    laning=false;
    canInjure[RIGHT]={9,9,22,77};
    canInjure[LEFT]={50,9,22,77};
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
            case SDLK_LEFT: velX -= 6; break;
            case SDLK_RIGHT: velX += 6; break;
            case SDLK_x:fire=true;break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: jump=false; break;
            case SDLK_LEFT: if (velX<0) velX += 6; break;
            case SDLK_RIGHT: if (velX) velX -= 6; break;
        }
    }
}

void Hero::operate(Block block[],const int &blockNumber) {
    if (fire&&BulletManager::get()) {
        if (direction==RIGHT) BulletControl::addBullet(pos.x+78,pos.y+27,direction); else
            BulletControl::addBullet(pos.x+1,pos.y+27,direction);
        fire=false;
        BulletManager::updateData();
    }
    bool st=true;
    if (velX>0) {
        int velXX=velX;
        For(i,0,blockNumber-1) {
            SDL_Rect rect1=block[i].getRect();
            if (rect1.x>pos.x+canInjure[direction].x+canInjure[direction].w-1
            &&          std::max(rect1.y,pos.y+canInjure[direction].y)
                        <=std::min(rect1.y+rect1.h-1,pos.y+canInjure[direction].y+canInjure[direction].h-1)){
                velXX=std::min(velXX,rect1.x-(pos.x+canInjure[direction].x+canInjure[direction].w-1)-1);
            }
        }
        if (direction==RIGHT) {
            pos.x=std::min(pos.x+velXX,SDLScreenWidth-mWidth+1);
        } else {
            direction=RIGHT;
            pos.x+=mWidth-2*canInjure[RIGHT].x-canInjure[RIGHT].w;
            st=false;
        }
    } else
    if (velX<0) {
        int velXX=velX;
        For(i,0,blockNumber-1) {
            SDL_Rect rect1=block[i].getRect();
            if (rect1.x+rect1.w-1<pos.x+canInjure[direction].x
            &&          std::max(rect1.y,pos.y+canInjure[direction].y)
                        <=std::min(rect1.y+rect1.h-1,pos.y+canInjure[direction].y+canInjure[direction].h-1)) {
                velXX=std::max(velXX,-(pos.x+canInjure[direction].x)+(rect1.x+rect1.w-1)+1);
            }
        }
        if (direction==LEFT) {
            pos.x=std::max(pos.x+velXX,0);
        } else {
            direction=LEFT;
            pos.x-=mWidth-2*canInjure[RIGHT].x-canInjure[RIGHT].w;
            st=false;
        }
    }
    if (velX==0) st=false;
    int stopFall=SDLScreenHeight-mHeight+1;
    int stopJump=canJump;
    For(i,0,blockNumber-1) {
        SDL_Rect rect1=block[i].getRect();
        if (std::max(rect1.x,pos.x+canInjure[direction].x)
            <=std::min(rect1.x+rect1.w-1,pos.x+canInjure[direction].x+canInjure[direction].w-1)) {
                if (rect1.y>pos.y+canInjure[direction].y+canInjure[direction].h-1)
                    stopFall=std::min(stopFall,rect1.y-(canInjure[direction].y+canInjure[direction].h));
                if (rect1.y+rect1.h-1<pos.y)
                    stopJump=std::max(stopJump,rect1.y+rect1.h);
            }
    }
    if (laning) {
        if (jump) jumping=true,laning=false,canJump=stopFall-ableHeight+1; else
        if (st) {
            currentMotion++;
            currentMotion%=4;
        }
        if (pos.y<stopFall) laning=false;
    } else {
        if (jumping) {
            pos.y-=velY;
            pos.y=std::max(pos.y,stopJump);
            if (pos.y==stopJump) jumping=false;
        } else {
            pos.y+=velY;
            pos.y=std::min(stopFall,pos.y);
            if (pos.y==stopFall) laning=true; else laning=false;
        }
    }
    if (direction==LEFT) body[currentMotion].render(pos.x,pos.y,SDL_FLIP_HORIZONTAL);
    else body[currentMotion].render(pos.x,pos.y);
}

bool Hero::scanD() {
    SDL_Rect rect1={pos.x+canInjure[direction].x,pos.y+canInjure[direction].y,canInjure[direction].w,canInjure[direction].h};
    if (!inside(rect1,Door::getRect())) return false; else return true;
}

bool Hero::scanK(Key& key) {
    SDL_Rect rect1={pos.x+canInjure[direction].x,pos.y+canInjure[direction].y,canInjure[direction].w,canInjure[direction].h};
    if (!inside(rect1,key.getRect())) return false; else return true;
}

void Hero::checkCollision(Bullet &bullet){
    if (died) return;
    SDL_Rect rect1={bullet.pos.x,bullet.pos.y,bullet.width,bullet.height};
    SDL_Rect rect2={pos.x+canInjure[direction].x,pos.y+canInjure[direction].y,canInjure[direction].w,canInjure[direction].h};
    if (!collised(rect1,rect2)) return;
    --hp;
    giamHp.render(pos.x+canInjure[direction].x,pos.y-23);
    HealthManager::updateHealth(-1);
    if (!hp) die();
    bullet.Collision();
};

void Hero::checkCollision(Enermy &enermy){
    if (enermy.isDead()) return;
    if (died) return;
    SDL_Rect rect1=enermy.getRect();
    SDL_Rect rect2={pos.x+canInjure[direction].x,pos.y+canInjure[direction].y,canInjure[direction].w,canInjure[direction].h};
    if (!collised(rect1,rect2)) return;
    --hp;
    giamHp.render(pos.x+canInjure[direction].x,pos.y-23);
    HealthManager::updateHealth(-1);
    if (!hp) die();
};

void Hero::die() {
    died=true;
    body[0].loadTex("art/die.png");
    body[0].render(pos.x,pos.y);
    For(i,0,3) body[i].free();
}
