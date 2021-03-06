#include "header.h"

void Menu::load(){
    bool quit=false;
    SDL_Event e;
    if (!loadMediaSDL("art/startbackground.png")) {
        std::cout<<"Failed to load media!\n";
        return;
    }
    gTexture.render(0,0);
    LButton button[TOTAL_BUTTON];
    button[START].link("start.png");
    button[START].setPosition(414,211,161,89);
    button[CONTINUE].link("continue.png");
    button[CONTINUE].setPosition(550,300,164,89);
    button[TUTORIAL].link("tutorial.png");
    button[TUTORIAL].setPosition(702,394,167,89);
    while (!quit) {
        while (SDL_PollEvent(&e)!=0) {
            if (e.type==SDL_QUIT) {quit=true;}
            For(i,0,TOTAL_BUTTON-1) button[i].handleEvent(&e);
            if (button[START].isActive()) {
                Stage1::load();
                return;
            }
            if (button[CONTINUE].isActive()) {
                switch (lastLevel) {
                    case (1): Stage1::load();return;
                    case (2): Stage2::load();return;
                    case (3): Stage3::load();return;
                    default: break;
                }
            }
            if (button[TUTORIAL].isActive()) {
                SDL_Event x;
                SDL_PollEvent(&x);
                bool st=false;
                while (!st) {
                    while (SDL_PollEvent(&x)!=0) {
                        if (x.type==SDL_MOUSEBUTTONDOWN) {st=true;break;}
                    }
                    SDL_RenderClear(gRenderer);
                    TutorialScreen.render(0,0);
                    SDL_RenderPresent(gRenderer);

                }
            }
        }
        SDL_RenderClear(gRenderer);
        gTexture.render(0,0);
        For(i,0,TOTAL_BUTTON-1) button[i].render();
        SDL_RenderPresent(gRenderer);
    }

};
