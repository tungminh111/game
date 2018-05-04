#include "header.h"

Hero Stage1::minh;
Enermy Stage1::loc[3];
Block Stage1::block[9];
Key Stage1::key;
SDL_Event Stage1::e;
void Stage1::load() {
    lastLevel=std::max(lastLevel,1);
    BulletControl::init();
    gTexture.loadTex("art/stage1.png");
    bool quit=false;
    Key::init();
    /////////////hero///////////////
    minh.init(0,270);
    minh.loadTex("art/hero");

    ////////////setblock////////////
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
    block[7].loadTex("art/flyinglane2.png");
    block[7].setBlock(624,231,373,101);
    block[8].loadTex("art/box.png");
    block[8].setBlock(207,402,85,86);


    /////////setenermy/////////////////
    For(i,0,2) loc[i].loadTex("art/gunenermy");
    loc[0].setLoop(840,143,820,955,140,3);
    loc[1].setLoop(360,255,300,460,255,3);
    loc[2].setLoop(600,450,600,800,450,5);
    Door::loadTex("art/door.png");

    ////////display statistic////////////
    TimeManager::setData(50);
    BulletManager::setData(15);
    HealthManager::setData(3);
    Key::setKey(1);
    key.loadTex("art/key.png");

    while (!quit) {
        while (SDL_PollEvent(&e)!=0) {
            if (e.type==SDL_QUIT) {quit=true;}
            minh.handleEvent(e);
        }
        SDL_RenderClear(gRenderer);
        gTexture.render(0,0);
        Door::render(815,440);
        key.render(890,217);
        minh.operate(block,9);
        if (minh.scanK(key)) key.Gather();
        if (minh.scanD()) {
            bool st=Key::enough();
            Door::load(2);
            if (st) {
            return;
            }
        }
        For(i,0,8) {
            BulletControl::scan(block[i]);
            block[i].render();
        }
        For(i,0,2) BulletControl::scan(loc[i]);
        BulletControl::scan(minh);
        BulletControl::operate();
        For(i,0,2) minh.checkCollision(loc[i]);
        For(i,0,2) loc[i].operate();
        if (!HealthManager::getHealth()||!TimeManager::getTime()) {
            Wasted.render(0,0);
            SDL_RenderPresent(gRenderer);
            SDL_Delay(1000);
            Menu::load();
            return;
        }
        TimeManager::updateData();
        TimeManager::displayTime();

        BulletManager::displayBullet();
        HealthManager::displayHealth();
        BulletControl::reload();
        SDL_RenderPresent(gRenderer);
        SDL_Delay(25);
    }

}
