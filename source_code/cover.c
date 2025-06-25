#include "cover.h"


TTF_Font* font_CoverOption = NULL;
TTF_Font* font_CoverTitle = NULL;

Button button_Login,button_Register;

int Cover_Init() 
{
    if(TTF_Init()<0)
    {
        SDL_Log("Failed to initialize TTF! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
     //打开字体，设置大小
    font_CoverOption = TTF_OpenFont("../material/STXINWEI.TTF", 40);
    if(font_CoverOption == NULL)
    {
        SDL_Log("Failed to load font! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    font_CoverTitle = TTF_OpenFont("../material/STXINWEI.TTF", 60);
    if(font_CoverTitle == NULL)
    {
        SDL_Log("Failed to load font! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    //初始化按钮
    ButtonInit(&button_Login,(W-200)/2,H/2-60,200,50,"Login");
    button_Login.type = Button_Login;
    ButtonInit(&button_Register,(W-200)/2,H/2+40,200,50,"Register");
    button_Register.type = Button_Register;
    return 0;
}

void renderCoverBackground()
{   //加载背景图片
    SDL_Surface* background_Surface = SDL_LoadBMP("../material/background1.bmp");
    if(background_Surface == NULL)
    {
        SDL_Log("Failed to load image! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    SDL_Texture* background_Texture = SDL_CreateTextureFromSurface(app.renderer, background_Surface);
    if(background_Texture == NULL)
    {
        SDL_Log("Failed to create background_texture! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    //设置渲染器颜色
    SDL_SetRenderDrawColor(app.renderer,0,255,0,255);
    //清空渲染器
    SDL_RenderClear(app.renderer);

    //渲染背景
    SDL_RenderCopy(app.renderer, background_Texture, NULL, NULL);  
    SDL_DestroyTexture(background_Texture);
    SDL_FreeSurface(background_Surface);
}

void renderCoverTitle()
{
    SDL_Surface* title = TTF_RenderText_Blended(font_CoverTitle, "Brawl Game", (SDL_Color){255, 255, 255, 255});
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

void cover_Draw()
{
    renderCoverBackground();
    renderCoverTitle();

    RenderButton(&button_Login, font_CoverOption);
    RenderButton(&button_Register, font_CoverOption);

    SDL_RenderPresent(app.renderer);
}

ButtonType cover_GetButtonClicked(SDL_Event* event)
{
    if(!event) return Button_None;
    if(isButtonClicked(&button_Login, event)) return Button_Login;
    if(isButtonClicked(&button_Register, event)) return Button_Register;
    return Button_None;
}

void Cover_Free()
{
    TTF_CloseFont(font_CoverOption);
    TTF_CloseFont(font_CoverTitle);
}