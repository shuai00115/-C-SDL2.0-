#ifndef BUTTON_H
#define BUTTON_H

#include "common.h"

typedef enum{
Button_None,
Button_Confirm,
Button_Cover,
Button_Login,
Button_Register,
Button_Start,
Button_Quit,
Button_Level1,
Button_Level2,
Button_Level3,
Button_Level4,
Button_Back,
Button_Ranking
}ButtonType;

typedef struct {
    SDL_Surface* Surface;
    SDL_Rect rect;
    SDL_Texture* texture;
    char* text;
    SDL_Color normalColor;
    SDL_Color ClickColor;
    int isClick;
    ButtonType type;
} Button;


void ButtonInit(Button* button,int x,int y,int w,int h,char* text);
void RenderButton(Button* button,TTF_Font* font);
int isButtonClicked(Button* button, SDL_Event* event);

#endif