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


class Block;
class Key;
class LTexture;
class LButton;
class Enermy;
class Hero;
class Door;
class HealthManager;
class TimeManager;
class BulletManager;
class BulletControl;
class Bullet;
class menu;
class stage1;


bool collised(SDL_Rect rect1,SDL_Rect rect2);
bool inside(SDL_Rect rect1,SDL_Rect rect2);
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
    void render(const int &x,const int &y,SDL_RendererFlip flip=SDL_FLIP_NONE,SDL_Rect*clip=NULL,double angle=0,SDL_Point* center=NULL);
    int getWidth();
    int getHeight();
private:
    int mWidth,mHeight;
    SDL_Texture* mTexture;
};

class Bullet{
public:
    Bullet();
    Bullet(const int &x,const int &y,DIRECTION &dir);
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
    static void addBullet(const int &x,const int &y,DIRECTION &dir);
    static void operate();
    static void scan(Enermy &enermy);
    static void scan(Block &block);
    static void reload();
    static void init();
    static void scan(Hero &hero);
private:
    static std::vector<Bullet> bulletList;

};

class Hero {
public:
    void init();
    void loadTex(std::string c);
    void handleEvent(SDL_Event &e);
    void die();
    void operate(Block block[],const int &blockNumber);
    bool scanK(Key& key);
    void checkCollision(Bullet &bullet);
    void checkCollision(Enermy &enermy);
    bool scanD();
private:
    int velX,velY;
    LTexture body[4];
    int hp;
    bool died;
    int bullet;
    DIRECTION direction;
    SDL_Point pos;
    int mWidth,mHeight;
    int currentMotion;
    int canJump,ableHeight;
    bool jumping,jump,fire,laning;
    SDL_Rect canInjure[TOTAL_DIR];
};

class Enermy{
public:
    void setLoop(const int &posX,const int &posY,const int &_x1,const int &_x2,const int &_y,const int &_hp);
    void die();
    void operate();
    void checkCollision(Bullet &bullet);
    void loadTex(std::string c);
    SDL_Rect getRect();
    bool isDead();
private:
    int x1,x2,y,mWidth,mHeight;
    int currentMotion;
    SDL_Point pos;
    DIRECTION direction;
    bool died;
    int dem;
    int hp;
    ENERMYTYPE type;
    LTexture body[4];
    SDL_Rect canInjure[TOTAL_DIR];
};

class LButton {
public:
    LButton();
    void setPosition(const int &x,const int &y,const int &w,const int &h);
    void handleEvent(SDL_Event* e);
    void render();
    void link(std::string path);
    bool isActive();
private:
    std::string type;
    bool active;
    SDL_Point mPosition;
    LButtonSprite mCurrentSprite;
    int ButtonWidth,ButtonHeight;
};

class Block {
public:
    void loadTex(std::string s);
    void render();
    void setBlock(const int &x,const int &y,const int &w,const int &h);
    SDL_Rect getRect();
    void checkbul(Bullet&bullet);
    void free();
private:
    SDL_Rect display;
    LTexture mTexture;
};
class TimeManager {
public:
    static void setData(const int &_time);
    static void updateData();
    static void displayTime();
    static int getTime();
private:
    static int baseTime;
    static int time;
    static TTF_Font* gFont;
};

class BulletManager {
public:
    static void setData(const int &_time);
    static void updateData();
    static void displayBullet();
    static int get();
private:
    static int bullet;
    static TTF_Font* gFont;
};

class Door{
public:
    static void load(const int &stage);
    static void render(const int &x,const int &y);
    static void loadTex(std::string c);
    static SDL_Rect getRect();
    static void free();
private:
    static LTexture mTexture;
    static SDL_Rect display;
};

class Key{
public:
    friend class Door;
    SDL_Rect getRect();
    void render(const int &x,const int &y);
    void loadTex(std::string c);
    void Gather();
    static void setKey(const int& keyNum);
    void free();
    static bool enough();
private:
    SDL_Rect display;
    bool gathered;
    LTexture mTexture;
    static int keyGathered;
    static int keyNeeded;
};

class Menu{
public:
    static void load();
};

class Stage1{
public:
    static void load();
private:
    static Hero minh;
    static Enermy loc[3];
    static Block block[9];
    static Key key;
    static SDL_Event e;
};

class Stage2{
public:
    static void load();
private:
    static Hero minh;
    static Enermy loc[5];
    static Block block[9];
    static Key key[2];
    static SDL_Event e;
};

class HealthManager {
public:
    static void setData(int _maxHealth);
    static void updateHealth(int change);
    static void displayHealth();
    static int getHealth();
private:
    static int health;
    static int maxHealth;
};

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Renderer* gRenderer;
extern LTexture gTexture;
extern int SDLScreenWidth;
extern int SDLScreenHeight;
extern int buttonNumber;
extern LTexture giamHp;
extern LTexture Wasted;
extern int lastLevel;
#endif
