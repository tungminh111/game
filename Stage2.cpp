#include "header.h"

Hero Stage2::minh;
Enermy Stage2::loc[5];
Block Stage2::block[9];
Key Stage2::key[2];
SDL_Event Stage2::e;

void Stage2::load() {
    lastLevel=std::max(lastLevel,2);
    gTexture.loadTex("art/stage1.png");
    Key::init();
    BulletControl::init();
    bool quit=false;
    /////////////hero///////////////
    minh.init(0,270);
    minh.loadTex("art/hero");

    ////////////setblock////////////
    block[0].loadTex("art/flyinglane.png");
    block[0].setBlock(330,346,249,54);
    block[1].loadTex("art/box.png");
    block[1].setBlock(490,261,85,86);
    block[2].loadTex("art/lane1.png");
    block[2].setBlock(0,488,541,93);
    block[3].loadTex("art/lane2.png");
    block[3].setBlock(538,539,462,42);
    block[4].loadTex("art/box.png");
    block[4].setBlock(680,146,85,86);
    block[5].loadTex("art/box.png");
    block[5].setBlock(765,146,85,86);
    block[6].loadTex("art/flyinglane3.png");
    block[6].setBlock(150,60,462,40);
    block[7].loadTex("art/flyinglane2.png");
    block[7].setBlock(624,231,373,101);
    block[8].loadTex("art/box.png");
    block[8].setBlock(207,402,85,86);


    /////////setenermy/////////////////
    For(i,0,4) loc[i].loadTex("art/gunenermy");
    loc[0].setLoop(840,143,820,955,140,3);
    loc[1].setLoop(360,255,300,460,255,5);
    loc[2].setLoop(600,450,600,800,450,5);
    loc[3].setLoop(264,-28,264,400,-28,5);
    loc[4].setLoop(310,404,310,410,404,20);
    Door::loadTex("art/door.png");

    ////////display statistic////////////
    TimeManager::setData(60);
    BulletManager::setData(20);
    HealthManager::setData(3);
    Key::setKey(2);
    key[0].loadTex("art/key.png");
    key[1].loadTex("art/key.png");
    while (!quit) {
        while (SDL_PollEvent(&e)!=0) {
            if (e.type==SDL_QUIT) {quit=true;}
            minh.handleEvent(e);
        }
        SDL_RenderClear(gRenderer);
        gTexture.render(0,0);
        Door::render(815,440);
        key[0].render(890,217);
        key[1].render(150,40);
        minh.operate(block,9);
        For(i,0,1) if (minh.scanK(key[i])) key[i].Gather();
        if (minh.scanD()) {
            bool st=Key::enough();
            Door::load(3);
            if (st) {
            return;
            }
        }
        For(i,0,8) {
            BulletControl::scan(block[i]);
            block[i].render();
        }
        For(i,0,4) BulletControl::scan(loc[i]);
        BulletControl::scan(minh);
        BulletControl::operate();
        For(i,0,4) minh.checkCollision(loc[i]);
        For(i,0,4) loc[i].operate();
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
        Key::displayKey();
        SDL_RenderPresent(gRenderer);
        SDL_Delay(20);
    }

}
