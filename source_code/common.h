#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define MAX_USERNAME_LENGTH 50  // 用户名最大长度
#define MAX_PASSWORD_LENGTH 50  // 密码最大长度
#define W 1200
#define H 600

typedef enum{
    GAME_STATE_COVER,
    GAME_STATE_LOGIN,
    GAME_STATE_REGISTER,
    GAME_STATE_MENU,
    GAME_STATE_RANKING,
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


typedef struct {
    int level1_completed;
    int level2_completed;
    int level3_completed;
    int level4_completed;
    int score; // 添加分数字段
} SaveData;

extern SaveData saveData;



typedef struct{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    SaveData saveData;
}UserData;

extern UserData currentUser;

typedef struct {
    SDL_Rect rect;
    char text[MAX_USERNAME_LENGTH];
    int length;
    int isFocused;
} InputBox;

typedef struct app{
    SDL_Window* window;
    SDL_Renderer* renderer;
    Game_State game_state;
} App;

extern App app;

#endif