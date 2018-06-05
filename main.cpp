#include "header.h"

SDL_Window* gWindow=NULL;
SDL_Surface* gScreenSurface=NULL;
SDL_Renderer* gRenderer=NULL;
LTexture gTexture;
int SDLScreenWidth=1000;
int SDLScreenHeight=581;
LTexture giamHp;
LTexture Wasted;
int lastLevel=0;
LTexture Win;
LTexture TutorialScreen;

int main(int argc, char* args[]) {
    if (!initSDL()) {
        std::cout<<"Failed to initialize!\n";
        return 0;
    } ;
    Menu::load();

    closeSDL();
    return 0;
}
