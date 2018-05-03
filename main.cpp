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
<<<<<<< HEAD
=======
    quit=false;
    BulletControl bulletScreen;
    Hero minh;
    minh.loadTex("art/hero");
    Enermy loc[1];
    For(i,0,0) loc[i].loadTex("art/gunenermy");
    gTexture.loadTex("art/stage1.png");
    Block block[9];
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
    block[8].loadTex("art/box.png");
    block[8].setBlock(207,402,85,86);
    loc[0].setLoop(0,370,100,200,470);

    TimeManager::setData(50); //add
    BulletManager::setData(10); //add
    HealthManager::setData(3); //add

    while (!quit) {
        while (SDL_PollEvent(&e)!=0) {
            if (e.type==SDL_QUIT) {quit=true;}
            minh.handleEvent(e);
        }
        SDL_RenderClear(gRenderer);
        gTexture.render(0,0);
        minh.operate(bulletScreen,block,9);
        For(i,0,8) {
            bulletScreen.scan(block[i]);
            block[i].render();
        }
        bulletScreen.scan(loc[0]);
        bulletScreen.operate();
        loc[0].operate();

        TimeManager::updateData(); //add
        TimeManager::displayTime(); //add

        BulletManager::displayBullet(); //add

        HealthManager::displayHealth(); //add


        bulletScreen.reload();
        SDL_RenderPresent(gRenderer);
        SDL_Delay(40);
    }








>>>>>>> e54a783c4145f7e148bb36eee50ef5184b9a24b8

    closeSDL();
    return 0;
}
