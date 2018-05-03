#include "header.h"

SDL_Window* gWindow=NULL;
SDL_Surface* gScreenSurface=NULL;
SDL_Renderer* gRenderer=NULL;
LTexture gTexture;
int SDLScreenWidth=1000;
int SDLScreenHeight=581;

int main(int argc, char* args[]) {
    bool quit=false;
    SDL_Event e;
    if (!initSDL()) {
        std::cout<<"Failed to initialize!\n";
        return 0;
    } ;
    /////////////////////////////////// start background////////////////////////////

    Menu::load();
    /////////////////////////////////////// gameplay

    closeSDL();
    return 0;
}
