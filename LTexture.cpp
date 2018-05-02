#include "header.h"

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
