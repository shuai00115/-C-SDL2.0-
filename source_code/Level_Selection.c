#include "common.h"
#include "Level_Selection.h"
#include "save.h"

Button button_Back,button_Level1,button_Level2,button_Level3,button_Level4;

TTF_Font* font_SelectionTitle = NULL;
TTF_Font* font_SelectionOption = NULL;

int Level_Selection_Init()
{
    LoadGame(); // 加载存档数据

    font_SelectionTitle = TTF_OpenFont("../material/STXINWEI.TTF", 40);
    if(font_SelectionTitle == NULL)
    {
        SDL_Log("Failed to load font_SelectionTitle! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    font_SelectionOption = TTF_OpenFont("../material/STXINWEI.TTF", 30);
    if(font_SelectionOption == NULL)
    {
        SDL_Log("Failed to load font_SelectionOption! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    //初始化按钮
    ButtonInit(&button_Back,1050,530,100,50,"Back");
    button_Back.type = Button_Back;
    ButtonInit(&button_Level1,400,200,150,50,"Level 1");
    button_Level1.type = Button_Level1;
    ButtonInit(&button_Level2,650,200,150,50,"Level 2");
    button_Level2.type = Button_Level2;
    ButtonInit(&button_Level3,400,340,150,50,"Level 3");
    button_Level3.type = Button_Level3;
    ButtonInit(&button_Level4,650,340,150,50,"Level 4");
    button_Level4.type = Button_Level4;

    return 0;
    
   
}

void Level_Selection_Deinit(void)
{
    TTF_Quit();
}

void RenderSelectionTitle()
{
    SDL_Surface* title = TTF_RenderText_Blended(font_SelectionTitle, "Level Selection", (SDL_Color){255, 255, 255, 255});
    if(title == NULL)
    {
        SDL_Log("Failed to render title! SDL_Error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture* title_Texture = SDL_CreateTextureFromSurface(app.renderer, title);
    if(title_Texture == NULL)
    {
        SDL_Log("Failed to create texture from title image! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    SDL_Rect title_Rect = {(W-300)/2, 50, 300, 100};
     //设置渲染器颜色
    SDL_SetRenderDrawColor(app.renderer,0,0,0,255);

    SDL_RenderCopy(app.renderer, title_Texture, NULL, &title_Rect);
    SDL_DestroyTexture(title_Texture);
    SDL_FreeSurface(title);
}

void RenderSelectionBackground()
{
    SDL_Surface* background_Surface = SDL_LoadBMP("../material/background1.bmp");
    if(background_Surface == NULL)
    {
        SDL_Log("Failed to load background_Surface! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    SDL_Texture* background_Texture = SDL_CreateTextureFromSurface(app.renderer, background_Surface);
    if(background_Texture == NULL)
    {
        SDL_Log("Failed to create texture from background image! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    SDL_Rect background_Rect = {0, 0, W, H};
    SDL_RenderCopy(app.renderer, background_Texture, NULL, &background_Rect);
    SDL_DestroyTexture(background_Texture);
    SDL_FreeSurface(background_Surface);
}

void Level_Selection_Draw(void)
{
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255); // 设置为黑色或其他背景色
    SDL_RenderClear(app.renderer);
    //先渲染背景
    RenderSelectionBackground();
    //渲染标题
    RenderSelectionTitle();
    //渲染返回按钮
    RenderButton(&button_Back,font_SelectionOption);

    // 渲染关卡按钮，根据解锁状态设置不同颜色
    button_Level1.normalColor = (SDL_Color){255, 255, 255, 255}; // 第一关总是可选的
    RenderButton(&button_Level1, font_SelectionOption);

    // 第二关
    if (saveData.level1_completed)
    {
        button_Level2.normalColor = (SDL_Color){255, 255, 255, 255};
    }
    else
    {
        button_Level2.normalColor = (SDL_Color){100, 100, 100, 255}; // 灰色表示锁定
    }
    RenderButton(&button_Level2, font_SelectionOption);

    // 第三关
    if (saveData.level2_completed)
    {
        button_Level3.normalColor = (SDL_Color){255, 255, 255, 255};
    }
    else
    {
        button_Level3.normalColor = (SDL_Color){100, 100, 100, 255};
    }
    RenderButton(&button_Level3, font_SelectionOption);

    // 第四关
    if (saveData.level3_completed)
    {
        button_Level4.normalColor = (SDL_Color){255, 255, 255, 255};
    }
    else
    {
        button_Level4.normalColor = (SDL_Color){100, 100, 100, 255};
    }
    RenderButton(&button_Level4, font_SelectionOption);

    //刷新渲染器
    SDL_RenderPresent(app.renderer);
}

// 按钮点击检测
ButtonType Level_Selection_GetButtonClicked(SDL_Event *event)
{
    if (!event)
        return Button_None;

    if (isButtonClicked(&button_Back, event))
        return Button_Back;
    if (isButtonClicked(&button_Level1, event))
        return Button_Level1;

    // 检查关卡是否解锁
    if (isButtonClicked(&button_Level2, event))
    {
        if (saveData.level1_completed)
        {
            return Button_Level2;
        }
    }

    if (isButtonClicked(&button_Level3, event))
    {
        if (saveData.level2_completed)
        {
            return Button_Level3;
        }
    }

    if (isButtonClicked(&button_Level4, event))
    {
        if (saveData.level3_completed)
        {
            return Button_Level4;
        }
    }

    return Button_None;
}