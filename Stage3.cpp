#include "header.h"

Hero Stage3::minh;
Enermy Stage3::loc[50];
SDL_Event Stage3::e;
int Stage3::dem;
Block Stage3::block[1];


void Stage3::load() {
    bool quit=false;
    minh.init(500,100);
    int timecount=0;
    dem=0;
    gTexture.loadTex("art/stage3.png");
    BulletControl::init();
    minh.loadTex("art/hero");
    TimeManager::setData(1000);
    BulletManager::setData(1000);
    HealthManager::setData(25);
    For(i,0,49) loc[i].loadTex("art/gunenermy");
    block[0].setBlock(0,311,1000,100);
    while (!quit) {
        while (SDL_PollEvent(&e)!=0) {
            if (e.type==SDL_QUIT) {quit=true;}
            minh.handleEvent(e);
        }
        SDL_RenderClear(gRenderer);
        ++timecount;
        gTexture.render(0,0);
        minh.operate(block,1);
        For(i,0,dem-1) BulletControl::scan(loc[i]);
        BulletControl::scan(minh);
        BulletControl::operate();
        For(i,0,dem-1) minh.checkCollision(loc[i]);
        For(i,0,dem-1) loc[i].operate();
        if (dem<50&&timecount%100==0) {
            loc[dem].setLoop(0,219,0,970,219,3);
            ++dem;
            loc[dem].setLoop(970,219,0,970,219,3);
            ++dem;
        }
        if (!HealthManager::getHealth()||!TimeManager::getTime()) {
            Wasted.render(0,0);
            SDL_RenderPresent(gRenderer);
            SDL_Delay(1000);
            Menu::load();
            return;
        }
        bool win=true;
        For(i,0,49) if (!loc[i].isDead()) win=false;
        if (win) {
            SDL_RenderClear(gRenderer);
            Win.render(0,0);
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
        SDL_Delay(15);
    }
}
