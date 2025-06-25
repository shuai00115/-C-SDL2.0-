#ifndef COVER_H
#define COVER_H

#include "common.h"
#include "button.h"

int Cover_Init();
void cover_Draw();
ButtonType cover_GetButtonClicked(SDL_Event* event);
void Cover_Free();

#endif