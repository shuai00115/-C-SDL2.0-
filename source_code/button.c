#include "button.h"

void ButtonInit(Button* button,int x,int y,int w,int h,char* text)
{
    button->rect.x = x;
    button->rect.y = y;
    button->rect.w = w;
    button->rect.h = h;
    button->text = text;
    button->normalColor = (SDL_Color){255,255,255,0};
    button->ClickColor = (SDL_Color){255,0,0,255};
    button->isClick = 0;
    button->texture = NULL;
}

void RenderButton(Button* button,TTF_Font* font)
{
    // 1. 绘制按钮背景（矩形）
    SDL_SetRenderDrawColor(app.renderer, 0, 128, 255, 255); // 蓝色背景
    SDL_RenderFillRect(app.renderer, &button->rect);
    
    // 2. 绘制按钮边框
    SDL_SetRenderDrawColor(app.renderer, 0, 102, 204, 255); // 深蓝色边框
    SDL_RenderDrawRect(app.renderer, &button->rect);

    //设置按钮颜色
    SDL_Color Button_Color = button->isClick? button->ClickColor : button->normalColor;
    //创建文本surface
    SDL_Surface* text_Surface = TTF_RenderText_Blended(font, button->text, Button_Color);
    if(text_Surface == NULL)
    {
        SDL_Log("Failed to create text_Surface! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    //创建文本texture
    button->texture = SDL_CreateTextureFromSurface(app.renderer, text_Surface);
    if(button->texture == NULL)
    {
        SDL_Log("Failed to create button->texture! SDL_Error: %s\n", SDL_GetError());
        SDL_FreeSurface(text_Surface);
        return;
    }
     SDL_Rect text_rect = {
        button->rect.x + (button->rect.w - text_Surface->w)/2, // 水平居中
        button->rect.y + (button->rect.h - text_Surface->h)/2, // 垂直居中
        text_Surface->w,
        text_Surface->h
    };

    //渲染按钮
    SDL_RenderCopy(app.renderer, button->texture, NULL, &text_rect);
    //释放资源
    SDL_FreeSurface(text_Surface);
    SDL_DestroyTexture(button->texture);
}

int isButtonClicked(Button* button, SDL_Event* event)
{
    if(event->type == SDL_MOUSEBUTTONDOWN)
    {
        int MouseX = event->motion.x;
        int MouseY = event->motion.y;
        //判断鼠标是否在按钮区域
        if(MouseX >= button->rect.x && 
        MouseX <= button->rect.x + button->rect.w && 
        MouseY >= button->rect.y && 
        MouseY <= button->rect.y + button->rect.h)
        {
            button->isClick = 1;
            return 1;
        }
        else
        {
            button->isClick = 0;
        }
    }
    else if(event->type == SDL_MOUSEBUTTONUP)
    {
        button->isClick = 0;
    }
    return 0;
    
}