#ifndef STATEHANDLE_H
#define STATEHANDLE_H

#include "common.h"
#include "menu.h"
#include "button.h"
#include "Level_Selection.h"
#include "Level_Switch.h"
#include "level.h"
#include "cover.h"
#include "login.h"
#include "register.h"
#include "user.h"
#include "Ranking.h"

void CoverStateHandle(SDL_Event* event);
void LoginStateHandle(SDL_Event* event);
void RegisterStateHandle(SDL_Event* event);
void MenuStateHandle(SDL_Event* event);
void RankingStateHandle(SDL_Event* event);
void LevelSelectStateHandle(SDL_Event* event);
void level1StateHandle(SDL_Event* event);
void level2StateHandle(SDL_Event* event);
void level3StateHandle(SDL_Event* event);
void level4StateHandle(SDL_Event* event);

void level1FailStateHandle(SDL_Event* event);
void level2FailStateHandle(SDL_Event* event);
void level3FailStateHandle(SDL_Event* event);
void level4FailStateHandle(SDL_Event* event);

extern StateHandle stateHandle[];

#endif