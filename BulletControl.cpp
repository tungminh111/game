#include "header.h"

void BulletControl::init() {
    For(i,0,(int)bulletList.size()-1) bulletList[i].Collision();
    bulletList.clear();
}

void BulletControl::addBullet(const int &x,const int &y,DIRECTION& dir) {
    Bullet bullet(x,y,dir);
    bulletList.push_back(bullet);

}

std::vector<Bullet> BulletControl::bulletList;

void BulletControl::operate() {
    For(i,0,(int)bulletList.size()-1) {
        bulletList[i].flying();
    }
}

void BulletControl::reload() {
    std::vector<Bullet> tmp;
    For(i,0,(int)bulletList.size()-1) {
        if (!bulletList[i].hit) tmp.push_back(bulletList[i]);//bulletList[i].Collision();
    }
    bulletList=tmp;
}

void BulletControl::scan(Enermy &enermy) {
    For(i,0,(int)bulletList.size()-1) enermy.checkCollision(bulletList[i]);
}

void BulletControl::scan(Block &block) {
    For(i,0,(int)bulletList.size()-1) block.checkbul(bulletList[i]);
}

