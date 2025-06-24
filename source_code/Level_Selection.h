#ifndef LEVEL_SELECTION_H
#define LEVEL_SELECTION_H

#include "common.h"
#include "button.h"

int Level_Selection_Init();
void Level_Selection_Draw(void);
void Level_Selection_Deinit(void);

ButtonType Level_Selection_GetButtonClicked(SDL_Event* event);

#endif