#include "Level_Switch.h"

Button button_Switch1,button_Switch1toMenu, 
    button_Switch2, button_Switch2toMenu,
    button_Switch3,button_Switch3toMenu,
    button_Switch4;

TTF_Font* font_Switch1Title = NULL;
TTF_Font* font_Switch1Option = NULL;

TTF_Font* font_Switch2Title = NULL;
TTF_Font* font_Switch2Option = NULL;

TTF_Font* font_Switch3Title = NULL;
TTF_Font* font_Switch3Option = NULL;

TTF_Font* font_Switch4Title = NULL;
TTF_Font* font_Switch4Option = NULL;

int Level1_Switch_Init(void)
{
    font_Switch1Title = TTF_OpenFont("../material/STXINWEI.TTF", 60);
    if(font_Switch1Title == NULL)
    {
        SDL_Log("Failed to load font! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    font_Switch1Option = TTF_OpenFont("../material/STXINWEI.TTF", 20);
    if(font_Switch1Option == NULL)
    {
        SDL_Log("Failed to load font! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    ButtonInit(&button_Switch1, 1050, 520, 120, 50, "Next Level");
    ButtonInit(&button_Switch1toMenu, 50, 520, 120, 50, "Menu");
    button_Switch1.type = Button_Level2;

    return 0;
}

void RenderSwitch1Title()
{
    SDL_Surface* title = TTF_RenderText_Blended(font_Switch1Title, "Congratulations!", (SDL_Color){255, 255, 255, 255});
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

void RenderSwitch1Background()
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

void Level1_Switch_Draw()
{
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255); // 设置为黑色或其他背景色
    SDL_RenderClear(app.renderer);
    //先渲染背景
    RenderSwitch1Background();
    //渲染标题
    RenderSwitch1Title();
    //渲染按钮
    RenderButton(&button_Switch1, font_Switch1Option);
    RenderButton(&button_Switch1toMenu, font_Switch1Option);
    SDL_RenderPresent(app.renderer);
}

void Level_Switch_DeInit()
{
    TTF_Quit();
}

ButtonType Level1_Switch_GetButtonClicked(SDL_Event* event)
{
    if(!event) return Button_None;
    if(isButtonClicked(&button_Switch1, event)) return Button_Level2;
    if(isButtonClicked(&button_Switch1toMenu, event)) return Button_Start;
    return Button_None;
}


// 关卡1失败界面
Button button_Fail1_Restart, button_Fail1_Menu;
TTF_Font* font_Fail1Title = NULL;
TTF_Font* font_Fail1Option = NULL;

int Level1_Fail_Init(void)
{
    font_Fail1Title = TTF_OpenFont("../material/STXINWEI.TTF", 60);
    if(font_Fail1Title == NULL)
    {
        SDL_Log("Failed to load font_Fail1Title! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    font_Fail1Option = TTF_OpenFont("../material/STXINWEI.TTF", 30);
    if(font_Fail1Option == NULL)
    {
        SDL_Log("Failed to load font_Fail1Option! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    
    ButtonInit(&button_Fail1_Restart, 400, 300, 180, 50, "Retry");
    button_Fail1_Restart.type = Button_Level1;
    ButtonInit(&button_Fail1_Menu, 600, 300, 180, 50, "Main Menu");
    button_Fail1_Menu.type = Button_Start;

    return 0;
}

void RenderFail1Title()
{
    SDL_Surface* title = TTF_RenderText_Blended(font_Fail1Title, "Game Over", (SDL_Color){255, 0, 0, 255});
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
    SDL_Rect title_Rect = {(W-300)/2, 100, 300, 100};
    SDL_RenderCopy(app.renderer, title_Texture, NULL, &title_Rect);
    SDL_DestroyTexture(title_Texture);
    SDL_FreeSurface(title);
}

void Level1_Fail_Draw()
{
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
    
    RenderSwitch1Background();
    RenderFail1Title();
    
    RenderButton(&button_Fail1_Restart, font_Fail1Option);
    RenderButton(&button_Fail1_Menu, font_Fail1Option);
    
    SDL_RenderPresent(app.renderer);
}

ButtonType Level1_Fail_GetButtonClicked(SDL_Event* event)
{
    if(!event) return Button_None;
    if(isButtonClicked(&button_Fail1_Restart, event)) return Button_Level1;
    if(isButtonClicked(&button_Fail1_Menu, event)) return Button_Start;
    return Button_None;
}



int Level2_Switch_Init(void)
{
    font_Switch2Title = TTF_OpenFont("../material/STXINWEI.TTF", 60);
    if(font_Switch2Title == NULL)
    {
        SDL_Log("Failed to load font! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    font_Switch2Option = TTF_OpenFont("../material/STXINWEI.TTF", 20);
    if(font_Switch2Option == NULL)
    {
        SDL_Log("Failed to load font! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    ButtonInit(&button_Switch2, 1050, 520, 120, 50, "Next Level");
    ButtonInit(&button_Switch2toMenu, 50, 520, 120, 50, "Menu");
    button_Switch2.type = Button_Level3;

    return 0;
}

void RenderSwitch2Title()
{
    SDL_Surface* title = TTF_RenderText_Blended(font_Switch2Title, "Congratulations!", (SDL_Color){255, 255, 255, 255});
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

void RenderSwitc2Background()
{
    SDL_Surface* background_Surface = SDL_LoadBMP("../material/background2.bmp");
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

void Level2_Switch_Draw()
{
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255); // 设置为黑色或其他背景色
    SDL_RenderClear(app.renderer);
    //先渲染背景
    RenderSwitc2Background();
    //渲染标题
    RenderSwitch2Title();
    //渲染按钮
    RenderButton(&button_Switch2, font_Switch2Option);
    RenderButton(&button_Switch2toMenu, font_Switch2Option);
    SDL_RenderPresent(app.renderer);
}

ButtonType Level2_Switch_GetButtonClicked(SDL_Event* event)
{
    if(!event) return Button_None;
    if(isButtonClicked(&button_Switch2, event)) return Button_Level3;
    if(isButtonClicked(&button_Switch2toMenu, event)) return Button_Start;
    return Button_None;
}


Button button_Fail2_Restart, button_Fail2_Menu;
TTF_Font* font_Fail2Title = NULL;
TTF_Font* font_Fail2Option = NULL;

int Level2_Fail_Init(void)
{
    font_Fail2Title = TTF_OpenFont("../material/STXINWEI.TTF", 60);
    if(font_Fail2Title == NULL)
    {
        SDL_Log("Failed to load font_Fail2Title! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    font_Fail2Option = TTF_OpenFont("../material/STXINWEI.TTF", 30);
    if(font_Fail2Option == NULL)
    {
        SDL_Log("Failed to load font_Fail2Option! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    
    ButtonInit(&button_Fail2_Restart, 400, 300, 180, 50, "Retry");
    button_Fail2_Restart.type = Button_Level2;
    ButtonInit(&button_Fail2_Menu, 600, 300, 180, 50, "Main Menu");
    button_Fail2_Menu.type = Button_Start;

    return 0;
}

void RenderFail2Title()
{
    SDL_Surface* title = TTF_RenderText_Blended(font_Fail2Title, "Game Over", (SDL_Color){255, 0, 0, 255});
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
    SDL_Rect title_Rect = {(W-300)/2, 100, 300, 100};
    SDL_RenderCopy(app.renderer, title_Texture, NULL, &title_Rect);
    SDL_DestroyTexture(title_Texture);
    SDL_FreeSurface(title);
}

void Level2_Fail_Draw()
{
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
    
    RenderSwitc2Background();
    RenderFail2Title();
    
    RenderButton(&button_Fail2_Restart, font_Fail2Option);
    RenderButton(&button_Fail2_Menu, font_Fail2Option);
    
    SDL_RenderPresent(app.renderer);
}

ButtonType Level2_Fail_GetButtonClicked(SDL_Event* event)
{
    if(!event) return Button_None;
    if(isButtonClicked(&button_Fail2_Restart, event)) return Button_Level2;
    if(isButtonClicked(&button_Fail2_Menu, event)) return Button_Start;
    return Button_None;
}



int Level3_Switch_Init(void)
{
    font_Switch3Title = TTF_OpenFont("../material/STXINWEI.TTF", 60);
    if(font_Switch3Title == NULL)
    {
        SDL_Log("Failed to load font! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    font_Switch3Option = TTF_OpenFont("../material/STXINWEI.TTF", 20);
    if(font_Switch3Option == NULL)
    {
        SDL_Log("Failed to load font! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    ButtonInit(&button_Switch3, 1050, 520, 120, 50, "Next Level");
    ButtonInit(&button_Switch3toMenu, 50, 520, 120, 50, "Menu");
    button_Switch3.type = Button_Level4;

    return 0;
}

void RenderSwitch3Title()
{
    SDL_Surface* title = TTF_RenderText_Blended(font_Switch3Title, "Congratulations!", (SDL_Color){247,186,11, 255});
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

void RenderSwitc3Background()
{
    SDL_Surface* background_Surface = SDL_LoadBMP("../material/background3.bmp");
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

void Level3_Switch_Draw()
{
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255); // 设置为黑色或其他背景色
    SDL_RenderClear(app.renderer);
    //先渲染背景
    RenderSwitc3Background();
    //渲染标题
    RenderSwitch3Title();
    //渲染按钮
    RenderButton(&button_Switch3, font_Switch3Option);
    RenderButton(&button_Switch3toMenu, font_Switch3Option);
    SDL_RenderPresent(app.renderer);
}

ButtonType Level3_Switch_GetButtonClicked(SDL_Event* event)
{
    if(!event) return Button_None;
    if(isButtonClicked(&button_Switch3, event)) return Button_Level4;
    if(isButtonClicked(&button_Switch3toMenu, event)) return Button_Start;
    return Button_None;
}


Button button_Fail3_Restart, button_Fail3_Menu;
TTF_Font* font_Fail3Title = NULL;
TTF_Font* font_Fail3Option = NULL;

int Level3_Fail_Init(void)
{
    font_Fail3Title = TTF_OpenFont("../material/STXINWEI.TTF", 60);
    if(font_Fail3Title == NULL)
    {
        SDL_Log("Failed to load font_Fail3Title! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    font_Fail3Option = TTF_OpenFont("../material/STXINWEI.TTF", 30);
    if(font_Fail3Option == NULL)
    {
        SDL_Log("Failed to load font_Fail3Option! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    
    ButtonInit(&button_Fail3_Restart, 400, 300, 180, 50, "Retry");
    button_Fail3_Restart.type = Button_Level3;
    ButtonInit(&button_Fail3_Menu, 600, 300, 180, 50, "Main Menu");
    button_Fail3_Menu.type = Button_Start;

    return 0;
}

void RenderFail3Title()
{
    SDL_Surface* title = TTF_RenderText_Blended(font_Fail3Title, "Game Over", (SDL_Color){255, 0, 0, 255});
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
    SDL_Rect title_Rect = {(W-300)/2, 100, 300, 100};
    SDL_RenderCopy(app.renderer, title_Texture, NULL, &title_Rect);
    SDL_DestroyTexture(title_Texture);
    SDL_FreeSurface(title);
}

void Level3_Fail_Draw()
{
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
    
    RenderSwitc3Background();
    RenderFail3Title();
    
    RenderButton(&button_Fail3_Restart, font_Fail3Option);
    RenderButton(&button_Fail3_Menu, font_Fail3Option);
    
    SDL_RenderPresent(app.renderer);
}

ButtonType Level3_Fail_GetButtonClicked(SDL_Event* event)
{
    if(!event) return Button_None;
    if(isButtonClicked(&button_Fail3_Restart, event)) return Button_Level3;
    if(isButtonClicked(&button_Fail3_Menu, event)) return Button_Start;
    return Button_None;
}


int Level4_Switch_Init(void)
{
    font_Switch4Title = TTF_OpenFont("../material/STXINWEI.TTF", 60);
    if(font_Switch4Title == NULL)
    {
        SDL_Log("Failed to load font! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    font_Switch4Option = TTF_OpenFont("../material/STXINWEI.TTF", 20);
    if(font_Switch4Option == NULL)
    {
        SDL_Log("Failed to load font! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    ButtonInit(&button_Switch4, 1050, 520, 120, 50, "Menu");
    button_Switch4.type = Button_Start;

    return 0;
}

void RenderSwitch4Title()
{
    SDL_Surface* title = TTF_RenderText_Blended(font_Switch4Title, "Congratulations!You'vecompleted all levels!", (SDL_Color){0, 0, 255, 255});
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
    SDL_Rect title_Rect = {(W-800)/2, 50, 800, 100};
     //设置渲染器颜色
    SDL_SetRenderDrawColor(app.renderer,0,0,0,255);

    SDL_RenderCopy(app.renderer, title_Texture, NULL, &title_Rect);
    SDL_DestroyTexture(title_Texture);
    SDL_FreeSurface(title);

}

void RenderSwitc4Background()
{
    SDL_Surface* background_Surface = SDL_LoadBMP("../material/background4.bmp");
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

void Level4_Switch_Draw()
{
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255); // 设置为黑色或其他背景色
    SDL_RenderClear(app.renderer);
    //先渲染背景
    RenderSwitc4Background();
    //渲染标题
    RenderSwitch4Title();
    //渲染按钮
    RenderButton(&button_Switch4, font_Switch4Option);
    SDL_RenderPresent(app.renderer);
}

ButtonType Level4_Switch_GetButtonClicked(SDL_Event* event)
{
    if(!event) return Button_None;
    if(isButtonClicked(&button_Switch4, event)) return Button_Start;
    return Button_None;
}


Button button_Fail4_Restart, button_Fail4_Menu;
TTF_Font* font_Fail4Title = NULL;
TTF_Font* font_Fail4Option = NULL;

int Level4_Fail_Init(void)
{
    font_Fail4Title = TTF_OpenFont("../material/STXINWEI.TTF", 60);
    if(font_Fail4Title == NULL)
    {
        SDL_Log("Failed to load font_Fail4Title! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    font_Fail4Option = TTF_OpenFont("../material/STXINWEI.TTF", 30);
    if(font_Fail4Option == NULL)
    {
        SDL_Log("Failed to load font_Fail4Option! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    
    ButtonInit(&button_Fail4_Restart, 400, 300, 180, 50, "Retry");
    button_Fail4_Restart.type = Button_Level4;
    ButtonInit(&button_Fail4_Menu, 600, 300, 180, 50, "Main Menu");
    button_Fail4_Menu.type = Button_Start;

    return 0;
}

void RenderFail4Title()
{
    SDL_Surface* title = TTF_RenderText_Blended(font_Fail4Title, "Game Over", (SDL_Color){255, 0, 0, 255});
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
    SDL_Rect title_Rect = {(W-300)/2, 100, 300, 100};
    SDL_RenderCopy(app.renderer, title_Texture, NULL, &title_Rect);
    SDL_DestroyTexture(title_Texture);
    SDL_FreeSurface(title);
}

void Level4_Fail_Draw()
{
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
    
    RenderSwitc4Background();
    RenderFail4Title();
    
    RenderButton(&button_Fail4_Restart, font_Fail4Option);
    RenderButton(&button_Fail4_Menu, font_Fail4Option);
    
    SDL_RenderPresent(app.renderer);
}

ButtonType Level4_Fail_GetButtonClicked(SDL_Event* event)
{
    if(!event) return Button_None;
    if(isButtonClicked(&button_Fail4_Restart, event)) return Button_Level4;
    if(isButtonClicked(&button_Fail4_Menu, event)) return Button_Start;
    return Button_None;
}
