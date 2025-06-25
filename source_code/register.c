#include "register.h"


TTF_Font* font_RegisterTitle = NULL;
TTF_Font* font_RegisterOption = NULL;

Button button_RegisterConfirm,register_Back;
InputBox usernameInputBoxRegister;
InputBox passwordInputBoxRegister;

int currentFocusRegister = 0; // 初始化无焦点


int Register_Init()
{
    if(TTF_Init()<0)
    {
        SDL_Log("Failed to initialize TTF! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
     //打开字体，设置大小
    font_RegisterOption = TTF_OpenFont("../material/STXINWEI.TTF", 28);
    if(font_RegisterOption == NULL)
    {
        SDL_Log("Failed to load font! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    font_RegisterTitle = TTF_OpenFont("../material/STXINWEI.TTF", 60);
    if(font_RegisterTitle == NULL)
    {
        SDL_Log("Failed to load font! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    //初始化按钮
    ButtonInit(&button_RegisterConfirm,1050, 520, 120, 50,"Register");
    button_RegisterConfirm.type = Button_Confirm;
    ButtonInit(&register_Back,50, 520, 120, 50,"Back");
    register_Back.type = Button_Cover;

    // 初始化输入框
    usernameInputBoxRegister.rect = (SDL_Rect){300, 200, 200, 50};
    strcpy(usernameInputBoxRegister.text, "");
    usernameInputBoxRegister.length = 0;
    usernameInputBoxRegister.isFocused = 0;

    passwordInputBoxRegister.rect = (SDL_Rect){300, 250, 200, 50};
    strcpy(passwordInputBoxRegister.text, "");
    passwordInputBoxRegister.length = 0;
    passwordInputBoxRegister.isFocused = 0;

    return 0;
}

void renderRegisterBackground()
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

void renderRegisterTitle()
{
    SDL_Surface* title = TTF_RenderText_Blended(font_RegisterTitle, "Register", (SDL_Color){255, 255, 255, 255});
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

void renderRegisterFailTitle()
{
    SDL_Surface* title = TTF_RenderText_Blended(font_RegisterTitle, "The username has been used!", (SDL_Color){255, 255, 255, 255});
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
    SDL_Rect title_Rect = {(W-400)/2, 50, 400, 100};
     //设置渲染器颜色
    SDL_SetRenderDrawColor(app.renderer,0,0,0,255);

    SDL_RenderCopy(app.renderer, title_Texture, NULL, &title_Rect);
    SDL_DestroyTexture(title_Texture);
    SDL_FreeSurface(title);
}

void renderRegisterOption(char* option, int x, int y)
{
    SDL_Surface* option_Surface = TTF_RenderText_Blended(font_RegisterOption, option, (SDL_Color){255, 255, 255, 255});
    if(option_Surface == NULL)
    {
        SDL_Log("Failed to render option! SDL_Error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture* option_Texture = SDL_CreateTextureFromSurface(app.renderer, option_Surface);
    if(option_Texture == NULL)
    {
        SDL_Log("Failed to create texture from option image! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    SDL_Rect option_Rect = {x, y, 200, 50};
     //设置渲染器颜色
    SDL_SetRenderDrawColor(app.renderer,0,0,0,255);

    SDL_RenderCopy(app.renderer, option_Texture, NULL, &option_Rect);
    SDL_DestroyTexture(option_Texture);
    SDL_FreeSurface(option_Surface);
}


void handleRegisterInputBox(SDL_Event* event, InputBox* inputBox)
{
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_BACKSPACE && inputBox->length > 0) {
            inputBox->text[--inputBox->length] = '\0';
        } else if (event->key.keysym.sym == SDLK_RETURN) {
            // 处理回车事件
        } else if (inputBox->length < MAX_USERNAME_LENGTH - 1) {
            char c = (char)event->key.keysym.sym;
            if (isalnum(c)) {
                inputBox->text[inputBox->length++] = c;
                inputBox->text[inputBox->length] = '\0';
            }
        }
    }
}

void renderInputBoxRegister(InputBox* inputBox, TTF_Font* font)
{
    // 绘制输入框背景
    if (inputBox->isFocused) {
        SDL_SetRenderDrawColor(app.renderer, 240, 240, 255, 255); // 浅蓝色背景表示焦点
    } else {
        SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
    }
    SDL_RenderFillRect(app.renderer, &inputBox->rect);

    // 绘制输入框边框
    if (inputBox->isFocused) {
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 255, 255); // 蓝色边框表示焦点
    } else {
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    }
    SDL_RenderDrawRect(app.renderer, &inputBox->rect);

    // 检查输入框文本是否为空
    if (inputBox->length > 0) {
        // 绘制输入的文本
        SDL_Surface* text_Surface = TTF_RenderText_Blended(font, inputBox->text, (SDL_Color){0, 0, 0, 255});
        if (text_Surface == NULL) {
            SDL_Log("Failed to create text_Surface! SDL_Error: %s\n", SDL_GetError());
            return;
        }
        SDL_Texture* text_Texture = SDL_CreateTextureFromSurface(app.renderer, text_Surface);
        if (text_Texture == NULL) {
            SDL_Log("Failed to create text_Texture! SDL_Error: %s\n", SDL_GetError());
            SDL_FreeSurface(text_Surface);
            return;
        }
        SDL_Rect text_rect = {
            inputBox->rect.x + 5,
            inputBox->rect.y + (inputBox->rect.h - text_Surface->h) / 2,
            text_Surface->w,
            text_Surface->h
        };
        SDL_RenderCopy(app.renderer, text_Texture, NULL, &text_rect);
        SDL_DestroyTexture(text_Texture);
        SDL_FreeSurface(text_Surface);
    }
}


void register_Draw()
{
    renderRegisterBackground();
    renderRegisterTitle();
    RenderButton(&button_RegisterConfirm, font_RegisterOption);
    RenderButton(&register_Back, font_RegisterOption);
    renderRegisterOption("Username:", 100, 200);
    renderRegisterOption("Password:", 100, 250);
    // 绘制输入框
    renderInputBoxRegister(&usernameInputBoxRegister, font_RegisterOption);
    renderInputBoxRegister(&passwordInputBoxRegister, font_RegisterOption);


    SDL_RenderPresent(app.renderer);
}

void registerFail_Draw()
{
    renderRegisterBackground();
    renderRegisterFailTitle();
    SDL_RenderPresent(app.renderer);
}

void register_Free()
{
    TTF_CloseFont(font_RegisterOption);
    TTF_CloseFont(font_RegisterTitle);
}

ButtonType register_GetButtonClicked(SDL_Event* event)
{
    if(!event) return Button_None;
    if(isButtonClicked(&button_RegisterConfirm, event)) return Button_Confirm;
    if(isButtonClicked(&register_Back, event)) return Button_Back;
    return Button_None;
}

