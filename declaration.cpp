#include "header.h"

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Renderer* gRenderer;
extern LTexture gTexture;
extern int SDLScreenWidth;
extern int SDLScreenHeight;
bool collised(SDL_Rect rect1,SDL_Rect rect2) {
    int x1=std::max(rect1.x,rect2.x);
    int x2=std::min(rect1.x+rect1.w-1,rect2.x+rect2.w-1);
    int y1=std::max(rect1.y,rect2.y);
    int y2=std::min(rect1.y+rect1.h-1,rect2.y+rect2.h-1);
    if (x1>x2||y1>y2) return false;
    return true;
}


///////////////////////////// HERO///////////////////////////////

///////////////////////////////ENERMY////////////////////////////////////////

///////////////////LTEXTURE///////////////////////////////////////

bool initSDL(){
    SDL_Init(SDL_INIT_VIDEO<0);
    gWindow=SDL_CreateWindow("gunminh",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                 SDLScreenWidth,SDLScreenHeight,SDL_WINDOW_SHOWN);
    gRenderer=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
    IMG_Init(IMG_INIT_PNG);
    gScreenSurface=SDL_GetWindowSurface(gWindow);
    TTF_Init();

    return true;
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
