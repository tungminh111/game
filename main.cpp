#include "header.h"

SDL_Window* gWindow=NULL;
SDL_Surface* gScreenSurface=NULL;
SDL_Renderer* gRenderer=NULL;
LTexture gTexture;
int SDLScreenWidth=1000;
int SDLScreenHeight=486;

int main(int argc, char* args[]) {
    bool quit=false;
    SDL_Event e;
    if (!initSDL()) {
        std::cout<<"Failed to initialize!\n";
        return 0;
    } ;
    /////////////////////////////////// start background////////////////////////////

    if (!loadMediaSDL("art/startbackground.png")) {
        std::cout<<"Failed to load media!\n";
        return 0;
    }
    gTexture.render(0,0);
    LButton button[TOTAL_BUTTON];
    button[START].link("start.png");
    button[START].setPosition(414,164,161,89);
    button[CONTINUE].link("continue.png");
    button[CONTINUE].setPosition(550,255,164,89);
    button[TUTORIAL].link("tutorial.png");
    button[TUTORIAL].setPosition(702,346,167,89);
    while (!quit) {
        while (SDL_PollEvent(&e)!=0) {
            if (e.type==SDL_QUIT) {quit=true;}
            For(i,0,TOTAL_BUTTON-1) button[i].handleEvent(&e);
        }
        For(i,0,TOTAL_BUTTON-1) button[i].render();
        SDL_RenderPresent(gRenderer);
        break;
    }

    ////////////////////////////////////////////////////
    SDL_RenderClear(gRenderer);
    Hero minh;
    BulletControl bulletScreen;
    minh.loadTex("art/hero");
    SDL_Point heroPos={0,0};
    int cur=0;
    Enermy loc;
    loc.setLoop(200,50,200,300,50);
    while (!quit) {
        while (SDL_PollEvent(&e)!=0) {
            if (e.type==SDL_QUIT) {quit=true;}
            minh.handleEvent(e);
        }
        SDL_RenderClear(gRenderer);
        minh.operate(bulletScreen);
        bulletScreen.operate();
        bulletScreen.scan(loc);
        loc.operate();
        SDL_RenderPresent(gRenderer);
        SDL_Delay(50);

    }









    closeSDL();
    return 0;
}
