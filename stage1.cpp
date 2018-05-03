#include "header.h"

void Stage1::load() {
    bool quit=false;
    SDL_Event e;
    Hero minh;
    minh.loadTex("art/hero");
    Enermy loc[3];
    For(i,0,2) loc[i].loadTex("art/gunenermy");
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
    loc[0].setLoop(840,143,820,955,140);
    loc[1].setLoop(360,255,300,460,255);
    loc[2].setLoop(600,450,600,800,450);
    Door::loadTex("art/door.png");
    TimeManager::setData(50);
    BulletManager::setData(10);
    HealthManager::setData(3);
    while (!quit) {
        while (SDL_PollEvent(&e)!=0) {
            if (e.type==SDL_QUIT) {quit=true;}
            minh.handleEvent(e);
        }
        SDL_RenderClear(gRenderer);
        gTexture.render(0,0);
        Door::render(815,440);
        minh.operate(block,9);
        For(i,0,8) {
            BulletControl::scan(block[i]);
            block[i].render();
        }
        For(i,0,2) BulletControl::scan(loc[i]);
        BulletControl::operate();
        For(i,0,2) loc[i].operate();
        TimeManager::updateData();
        TimeManager::displayTime();

        BulletManager::displayBullet();
        HealthManager::displayHealth();
        BulletControl::reload();
        SDL_RenderPresent(gRenderer);
        SDL_Delay(40);
    }

}
