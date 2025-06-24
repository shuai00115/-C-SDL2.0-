#ifndef LEVEL_SWITCH_H
#define LEVEL_SWITCH_H

#include "common.h"
#include "button.h"

int Level1_Switch_Init();
void Level1_Switch_Draw();
void Level_Switch_DeInit();
ButtonType Level1_Switch_GetButtonClicked(SDL_Event* event);

int Level2_Switch_Init();
void Level2_Switch_Draw();
ButtonType Level2_Switch_GetButtonClicked(SDL_Event* event);

int Level3_Switch_Init();
void Level3_Switch_Draw();
ButtonType Level3_Switch_GetButtonClicked(SDL_Event* event);

int Level4_Switch_Init();
void Level4_Switch_Draw();
ButtonType Level4_Switch_GetButtonClicked(SDL_Event* event);

// 添加失败界面函数
int Level1_Fail_Init();
void Level1_Fail_Draw();
ButtonType Level1_Fail_GetButtonClicked(SDL_Event* event);

int Level2_Fail_Init();
void Level2_Fail_Draw();
ButtonType Level2_Fail_GetButtonClicked(SDL_Event* event);

int Level3_Fail_Init();
void Level3_Fail_Draw();
ButtonType Level3_Fail_GetButtonClicked(SDL_Event* event);

int Level4_Fail_Init();
void Level4_Fail_Draw();
ButtonType Level4_Fail_GetButtonClicked(SDL_Event* event);


#endif