#ifndef STATEHANDLE_H
#define STATEHANDLE_H

#include "common.h"

void MenuStateHandle(SDL_Event* event);
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