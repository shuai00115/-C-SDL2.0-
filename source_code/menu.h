#ifndef MENU_H
#define MENU_H

#include "common.h"
#include "button.h"

int menu_Init();
void menu_Draw();
ButtonType menu_GetButtonClicked(SDL_Event* event);
void menu_Quit();

#endif