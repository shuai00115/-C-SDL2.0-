#ifndef LOGIN_H
#define LOGIN_H

#include "common.h"
#include "button.h"
#include <ctype.h>

extern InputBox usernameInputBox;
extern InputBox passwordInputBox;

extern int currentFocus; // 0: 无焦点, 1: 用户名, 2: 密码

void handleInputBox(SDL_Event* event, InputBox* inputBox);

int login_Init();
void login_Draw();
void loginFail_Draw();
void login_Free();

ButtonType login_GetButtonClicked(SDL_Event* event);

#endif