#include "menu.h"

static Button button_Start, button_Quit;


TTF_Font* font_MenuTitle = NULL;
TTF_Font* font_MenuOption = NULL;

int menu_Init()
{
    if(TTF_Init()<0)
    {
        SDL_Log("Failed to initialize TTF! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
     //打开字体，设置大小
    font_MenuOption = TTF_OpenFont("../material/STXINWEI.TTF", 40);
    if(font_MenuOption == NULL)
    {
        SDL_Log("Failed to load font! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    font_MenuTitle = TTF_OpenFont("../material/STXINWEI.TTF", 60);
    if(font_MenuTitle == NULL)
    {
        SDL_Log("Failed to load font! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    //初始化按钮
    ButtonInit(&button_Start,(W-200)/2,H/2-60,200,50,"Start");
    button_Start.type = Button_Start;
    ButtonInit(&button_Quit,(W-200)/2,H/2+40,200,50,"Quit");
    button_Quit.type = Button_Quit;
    return 0;
}

void RenderMenuBackground()
{

    //加载背景图片
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

void RenderMenuTitle()
{
    SDL_Surface* title = TTF_RenderText_Blended(font_MenuTitle, "Brawl Game", (SDL_Color){255, 255, 255, 255});
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

void menu_Draw()
{ 
    //渲染背景
   RenderMenuBackground();
    //渲染标题
    RenderMenuTitle();
   //渲染按钮
   RenderButton(&button_Start,font_MenuOption);
   RenderButton(&button_Quit,font_MenuOption);
    //显示渲染器内容
    SDL_RenderPresent(app.renderer);
 
}

ButtonType menu_GetButtonClicked(SDL_Event* event)
{
    if(!event) return Button_None;
    if(isButtonClicked(&button_Start, event)) return button_Start.type;
    if(isButtonClicked(&button_Quit, event)) return button_Quit.type;
    return Button_None;
}

void menu_Quit()
{
    //销毁
  
    TTF_Quit();
}
