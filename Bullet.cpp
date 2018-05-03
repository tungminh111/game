#include "header.h"

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
