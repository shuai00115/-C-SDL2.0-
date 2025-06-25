#include "common.h"
#include "StateHandle.h"
#include "menu.h"
#include "button.h"
#include "Level_Selection.h"
#include "Level_Switch.h"
#include "cover.h"
#include "register.h"
#include "login.h"

App app;

#undef main

int Init();
void DeInit();

int main()
{
    if (Init() < 0 )
    {
        SDL_Log("Failed to initialize!\n");
        return -1;
    }

    SDL_Event MainEvent;
    while (1)
    {
        while (SDL_PollEvent(&MainEvent))
        {
            if (MainEvent.type == SDL_QUIT)
            {
                DeInit();
                return 0;
            }
            stateHandle[app.game_state](&MainEvent);
            SDL_Delay(16);
        }
    }
    DeInit();
    return 0;
}

int Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n");
        return -1;
    }

    app.window = SDL_CreateWindow("Brawl Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_RESIZABLE);
    if (app.window == NULL)
    {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
    if (app.renderer == NULL)
    {
        SDL_Log("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    if(Cover_Init() < 0)
        return -1;
    if(Register_Init() < 0)
        return -1;
    if(login_Init() < 0)
        return -1;
    if(Ranking_Init() < 0)
        return -1;


    if (menu_Init() < 0)
        return -1;

    if (Level_Selection_Init() < 0)
        return -1;

    if (Level1_Switch_Init() < 0)
        return -1;
    if (Level2_Switch_Init() < 0)
        return -1;
    if (Level3_Switch_Init() < 0)
        return -1;
    if (Level4_Switch_Init() < 0)
        return -1;

     // 添加失败界面初始化
    if (Level1_Fail_Init() < 0)
        return -1;
    if (Level2_Fail_Init() < 0)
        return -1;
    if (Level3_Fail_Init() < 0)
        return -1;
    if (Level4_Fail_Init() < 0)
        return -1;
    
    

    app.game_state = GAME_STATE_COVER;

    return 0;
}

void DeInit()
{
    Level_Selection_Deinit();
    menu_Quit();
    Cover_Free();
    register_Free();
    Ranking_Cleanup();
    login_Free();
    Level_Switch_DeInit();
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}
