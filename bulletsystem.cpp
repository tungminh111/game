#include "header.h"

/////////////////////////// BULLET////////////////////////////////
Bullet::Bullet(int x,int y,DIRECTION dir){
    pos={x,y};
    direction=dir;
    hit=false;
}

void Bullet::flying() {
    if (hit) return;
    mBullet.loadTex("art/bullet.png");
    mBullet.render(pos.x,pos.y);
    if (direction==LEFT) pos.x-=10; else pos.x+=10;
}

void Bullet::Collision() {
    hit=true;
}

////////////////////////////BULLET CONTROL//////////////////

BulletControl::BulletControl(){
    bulletList.clear();
}

void BulletControl::addBullet(int x,int y,DIRECTION dir) {
    Bullet bullet(x,y,dir);
    bulletList.push_back(bullet);

}

void BulletControl::operate() {
    For(i,0,(int)bulletList.size()-1) bulletList[i].flying();
}

void BulletControl::scan(Enermy &enermy) {
    For(i,0,(int)bulletList.size()-1) enermy.checkCollision(bulletList[i]);
}

void BulletControl::scan(Block &block) {
    For(i,0,(int)bulletList.size()-1) block.checkbul(bulletList[i]);
}

