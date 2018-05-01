#include "header.h"

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Renderer* gRenderer;
extern LTexture gTexture;
extern int SDLScreenWidth;
extern int SDLScreenHeight;


LButton::LButton(){
    mPosition.x=mPosition.y=0;
    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(int x,int y,int w,int h) {
    mPosition={x,y};
    ButtonHeight=h;
    ButtonWidth=w;
}

void LButton::handleEvent(SDL_Event* e) {
    if (e->type==SDL_MOUSEMOTION||e->type==SDL_MOUSEBUTTONDOWN||e->type==SDL_MOUSEBUTTONUP) {
        int x,y;
        SDL_GetMouseState(&x,&y);
        ////////////////////check inside///////////////////////
        bool inside = true;
        if( x < mPosition.x )
        {
            inside = false;
        }
        else if( x > mPosition.x + ButtonWidth )
        {
            inside = false;
        }
        else if( y < mPosition.y )
        {
            inside = false;
        }
        else if( y > mPosition.y + ButtonHeight )
        {
            inside = false;
        }
        ////////////////////////////////////////////////
        if  (!inside) {
            mCurrentSprite=BUTTON_SPRITE_MOUSE_OUT;
        } else {
            switch(e->type) {
                case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

               // case SDL_MOUSEBUTTONDOWN:
               // mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
               // break;

            }
        }
    }

}

void LButton::link(std::string path) {
    type=path;
}

void LButton::render() {
    std::string path=type;
    if (mCurrentSprite==BUTTON_SPRITE_MOUSE_OVER_MOTION) path="touched"+path;
    path="art/"+path;
    LTexture tmp;
    tmp.loadTex(path.c_str());
    tmp.render(mPosition.x,mPosition.y);
}

Hero::Hero() {
    pos={50,50};
    direction=RIGHT;
    velX=velY=0;
    velY=16;
    jump=jumping=false;
    canJump=80;
    currentHeight=0;
    currentMotion=0;
    fire=false;
}
///////////////////////////// HERO///////////////////////////////
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

void Hero::operate(BulletControl &bulletScreen) {
    if (fire) {
        if (direction==RIGHT) bulletScreen.addBullet(pos.x+112,pos.y+41,direction); else
            bulletScreen.addBullet(pos.x-20,pos.y+41,direction);
        fire=false;
    }

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

///////////////////////////////ENERMY////////////////////////////////////////

void Enermy::setLoop(int posX,int posY,int _x1,int _x2,int _y) {
    x1=_x1;
    x2=_x2;
    y=_y;
    pos={posX,posY};
    currentMotion=0;
    direction=RIGHT;
    mWidth=mHeight=0;
    canInjure[RIGHT]={16,8,20,112};
    canInjure[LEFT]={77,8,20,112};
}

void Enermy::operate() {
    if (died) return;
    if (direction==LEFT) {
        if (pos.x<=x1)
            direction=RIGHT,currentMotion=0;
        else {
            pos.x-=5;
            currentMotion++;
            currentMotion%=4;
        }
    } else {
        if (pos.x+mWidth-1>=x2)
            direction=LEFT,currentMotion=0;
        else {
            pos.x+=5;
            currentMotion++;
            currentMotion%=4;
        }
    }
    std::string s;
    s.push_back(char('0'+currentMotion));
    body.loadTex(("art/gunenermy"+s+".png").c_str());
    if (direction==LEFT)
        body.render(pos.x,pos.y,SDL_FLIP_HORIZONTAL);
    else
        body.render(pos.x,pos.y,SDL_FLIP_NONE);
}

void Enermy::checkCollision(Bullet &bullet) {
    if (died) return;
    int x0=std::max(bullet.pos.x,pos.x+canInjure[direction].x);
    int x1=std::min(pos.x+canInjure[direction].x+canInjure[direction].w-1,bullet.pos.x+bullet.width-1);
    int y0=std::max(bullet.pos.y,pos.y+canInjure[direction].y);
    int y1=std::min(pos.y+canInjure[direction].y+canInjure[direction].h-1,bullet.pos.y+bullet.height-1);
    if (x0>x1||y0>y1) return;
    die();
    bullet.Collision();
}

void Enermy::die() {
    died=true;
    body.loadTex("art/die.png");
    body.render(pos.x,pos.y);
}

///////////////////LTEXTURE///////////////////////////////////////

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadTex(std::string c) {
    SDL_Texture* loadedTexture=NULL;
    SDL_Surface* loadedSurface=IMG_Load(c.c_str());
    bool success=true;
    if (loadedSurface==NULL) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", c.c_str(), IMG_GetError() );
        success=false;
    } else {
        loadedTexture=SDL_CreateTextureFromSurface(gRenderer,loadedSurface);
        if (loadedTexture==NULL) {
            std::cout<<"Unable to create texture from "<<c<<"! SDL error: "<<SDL_GetError()<<"\n";
            success=false;
        } else {
            mTexture=loadedTexture;
            mWidth=loadedSurface->w;
            mHeight=loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return success;
}

int LTexture::getHeight() {return mHeight;}
int LTexture::getWidth() {return mWidth;}

void LTexture::free() {
    SDL_DestroyTexture(mTexture);
    if (mTexture!=NULL) {
        mTexture=NULL;
        mWidth=mHeight=0;
    }
}

void LTexture::render(int x,int y,SDL_RendererFlip flip,SDL_Rect*clip,double angle,SDL_Point* center) {
    SDL_Rect renderQuad={x,y,mWidth,mHeight};
    if (clip!=NULL) {renderQuad.w=clip->w;renderQuad.h=clip->h;}
    SDL_RenderCopyEx(gRenderer,mTexture,clip,&renderQuad,angle,center,flip);
}
/////////////////////////// BULLET////////////////////////////////
Bullet::Bullet(int x,int y,DIRECTION dir){
    pos={x,y};
    direction=dir;
    hit=false;
}

void Bullet::flying() {
    if (hit) return;
    mBullet.loadTex("art/bullet.png");
    mBullet.render(pos.x,pos.y);
    if (direction==LEFT) pos.x-=10; else pos.x+=10;
}

void Bullet::Collision() {
    hit=true;
}

////////////////////////////BULLET CONTROL//////////////////

BulletControl::BulletControl(){
    bulletList.clear();
}

void BulletControl::addBullet(int x,int y,DIRECTION dir) {
    Bullet bullet(x,y,dir);
    bulletList.push_back(bullet);

}

void BulletControl::operate() {
    For(i,0,(int)bulletList.size()-1) bulletList[i].flying();
}

void BulletControl::scan(Enermy &enermy) {
    For(i,0,(int)bulletList.size()-1) enermy.checkCollision(bulletList[i]);
}

bool initSDL(){
    bool success=true;
    if (SDL_Init(SDL_INIT_VIDEO<0)) {
        std::cout<<"SDL could not initialize! SDL_Error: "<< SDL_GetError()<<"\n";
        success=false;
    } else {
        gWindow=SDL_CreateWindow("gunminh",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                 SDLScreenWidth,SDLScreenHeight,SDL_WINDOW_SHOWN);
        if (gWindow==NULL) {
            std::cout<<"SDL could not initialize! SDL_Error: "<< SDL_GetError()<<"\n";
            success=false;
        } else {
            gRenderer=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
            if (gRenderer==NULL) {
                std::cout<<"Renderer could not be created! SDL error: "<<SDL_GetError()<<"\n";
            } else {
                SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
                if (!(IMG_Init(IMG_INIT_PNG))&IMG_INIT_PNG) {
                    std::cout<<"SDL_image could not initialized! SDL_image error: "<<IMG_GetError()<<"\n";
                    success=false;
                } else
                    gScreenSurface=SDL_GetWindowSurface(gWindow);
            }
        }
    }
    return success;
}

bool loadMediaSDL(std::string c) {
    bool success=true;
    gTexture.free();
    if (!gTexture.loadTex(c)) {
        std::cout<<"Unable to load Texture Image: "<<c<<"\n";
        success=false;
    }
    return success;
}

void closeSDL() {
    gTexture.free();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow=NULL;
    gRenderer=NULL;
    IMG_Quit();
    SDL_Quit();
}
