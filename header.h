#ifndef bnxinhdep2
#define bnxinhdep2

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <windows.h>
#include <vector>
#include <sstream>
#define For(i,a,b) for(auto i=a;i<=b;i++)
#define Ford(i,a,b) for(auto i=a;i>=b;i--)
bool initSDL();
bool loadMediaSDL(std::string c);
void closeSDL();
class Enermy;
class Hero;
class Block;
bool collised(SDL_Rect rect1,SDL_Rect rect2);
enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_TOTAL = 2
};

enum DIRECTION {
    LEFT,
    RIGHT,
    TOTAL_DIR
};

enum BUTTONTYPE {
    START,
    CONTINUE,
    TUTORIAL,
    TOTAL_BUTTON
};

enum ENERMYTYPE{
    GUN_ENERMY,
    KNIFE_ENERMY,
    TOTAL_ENERMY_TYPE
};


class LTexture {
public:
    LTexture();
    ~LTexture();
    void free();
    bool loadTex(std::string c);
    void render(int x,int y,SDL_RendererFlip flip=SDL_FLIP_NONE,SDL_Rect*clip=NULL,double angle=0,SDL_Point* center=NULL);
    int getWidth();
    int getHeight();
private:
    int mWidth,mHeight;
    SDL_Texture* mTexture;
};

class Bullet{
public:
    Bullet();
    Bullet(int x,int y,DIRECTION dir);
    void flying();
    void Collision();
    SDL_Point pos;
    int width=20;
    int height=6;
    bool hit;
    LTexture mBullet;
    DIRECTION direction;
};

class BulletControl{
public:
    BulletControl();
    void addBullet(int x,int y,DIRECTION dir);
    void operate();
    void scan(Enermy &enermy);
    void scan(Block &block);
    void reload();
private:
    std::vector<Bullet> bulletList;

};

class Hero {
public:
    Hero();
    void loadTex(std::string c);
    void handleEvent(SDL_Event &e);
    void die();
    void operate(BulletControl &bulletScreen,Block block[],int blockNumber);
private:
    int velX,velY;
    LTexture body[4];
    int hp;
    int bullet;
    DIRECTION direction;
    SDL_Point pos;
    int width,height;
    int currentMotion;
    int canJump,currentHeight;
    bool jumping,jump,fire;
    SDL_Rect canInjure[TOTAL_DIR];
};

class Enermy{
public:
    void setLoop(int posX,int posY,int _x1,int _x2,int _y);
    void die();
    void operate();
    void checkCollision(Bullet &bullet);
    void loadTex(std::string c);
private:
    int x1,x2,y,mWidth,mHeight;
    int currentMotion;
    SDL_Point pos;
    DIRECTION direction;
    bool died;
    int hp;
    ENERMYTYPE type;
    LTexture body[4];
    SDL_Rect canInjure[TOTAL_DIR];
};

class LButton {
public:
    LButton();
    void setPosition(int x,int y,int w,int h);
    void handleEvent(SDL_Event* e);
    void render();
    void link(std::string path);
private:
    std::string type;
    SDL_Point mPosition;
    LButtonSprite mCurrentSprite;
    int ButtonWidth,ButtonHeight;
};

class Block {
public:
    void loadTex(std::string s);
    void render();
    void setBlock(int x,int y,int w,int h);
    SDL_Rect getRect();
    void checkbul(Bullet&bullet);
private:
    SDL_Rect display;
    LTexture mTexture;
};
class TimeManager {
public:
    static void setData(int _time);
    static void updateData();
    static void displayTime();
private:
    static int baseTime;
    static int time;
    static TTF_Font* gFont;
};

class BulletManager {
public:
    static void setData(int _time);
    static void updateData();
    static void displayBullet();
private:
    static int bullet;
    static TTF_Font* gFont;
};

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Renderer* gRenderer;
extern LTexture gTexture;
extern int SDLScreenWidth;
extern int SDLScreenHeight;
extern int buttonNumber;
#endif
