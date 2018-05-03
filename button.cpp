#include "header.h"

LButton::LButton(){
    mPosition.x=mPosition.y=0;
    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    active=false;
}

void LButton::setPosition(const int &x,const int &y,const int &w,const int &h) {
    mPosition={x,y};
    ButtonHeight=h;
    ButtonWidth=w;
}

bool LButton::isActive() {
    return active;
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
            active=false;
        } else {
            switch(e->type) {
                case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

                case SDL_MOUSEBUTTONDOWN:
                active=true;
                break;

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
