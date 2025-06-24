#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef enum{
    GAME_STATE_MENU,
    GAME_STATE_LEVEL_SELECT,
    GAME_STATE_PLAYING_LEVEL1,
    GAME_STATE_PLAYING_LEVEL2,
    GAME_STATE_PLAYING_LEVEL3,
    GAME_STATE_PLAYING_LEVEL4,
    GAME_STATE_LEVEL1SWITCH,
    GAME_STATE_LEVEL2SWITCH,
    GAME_STATE_LEVEL3SWITCH,
    GAME_STATE_LEVEL4SWITCH,
    GAME_STATE_LEVEL1FAIL,
    GAME_STATE_LEVEL2FAIL,    
    GAME_STATE_LEVEL3FAIL,    
    GAME_STATE_LEVEL4FAIL
}Game_State;

typedef void (*StateHandle)(SDL_Event*);



typedef struct app{
    SDL_Window* window;
    SDL_Renderer* renderer;
    Game_State game_state;
} App;

extern App app;


typedef struct {
    int level1_completed;
    int level2_completed;
    int level3_completed;
    int level4_completed;
} SaveData;

extern SaveData saveData;

#define W 1200
#define H 600

#endif