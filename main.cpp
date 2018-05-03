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
            if (e.type==SDL_QUIT||e.type==SDL_MOUSEBUTTONDOWN) {quit=true;}
            For(i,0,TOTAL_BUTTON-1) button[i].handleEvent(&e);
        }
        For(i,0,TOTAL_BUTTON-1) button[i].render();
        SDL_RenderPresent(gRenderer);
    }

    /////////////////////////////////////// gameplay
    quit=false;
    Hero minh;
    BulletControl bulletScreen;
    Enermy loc[1];
    minh.loadTex("art/hero");
    For(i,0,1) loc[i].loadTex("art/gunenermy");
    gTexture.loadTex("art/stage1.png");
    Block block[8];
    block[0].loadTex("art/flyinglane.png");
    block[0].setBlock(312,346,249,54);
    block[1].loadTex("art/box.png");
    block[1].setBlock(476,261,85,86);
    block[2].loadTex("art/lane1.png");
    block[2].setBlock(0,488,541,93);
    block[3].loadTex("art/lane2.png");
    block[3].setBlock(538,539,462,42);
    block[4].loadTex("art/box.png");
    block[4].setBlock(680,146,85,86);
    block[5].loadTex("art/box.png");
    block[5].setBlock(765,146,85,86);
    block[6].loadTex("art/box.png");
    block[6].setBlock(765,60,85,86);
    block[7].loadTex("art/flyinglane2.png");
    block[7].setBlock(624,231,373,101);
    loc[0].setLoop(0,370,100,200,470);

    TimeManager::setData(50); //add
    BulletManager::setData(50); //add

    while (!quit) {
        while (SDL_PollEvent(&e)!=0) {
            if (e.type==SDL_QUIT) {quit=true;}
            minh.handleEvent(e);
        }
        SDL_RenderClear(gRenderer);
        gTexture.render(0,0);
        For(i,0,7) {
            bulletScreen.scan(block[i]);
            block[i].render();
        }
        minh.operate(bulletScreen,block,8);
        bulletScreen.scan(loc[0]);
        bulletScreen.operate();
        loc[0].operate();

        TimeManager::updateData(); //add
        TimeManager::displayTime(); //add

        BulletManager::displayBullet(); //add

        SDL_RenderPresent(gRenderer);
        SDL_Delay(50);
    }









    closeSDL();
    return 0;
//aaaaaaaaaaaaab
}
