#ifndef REGISTER_H
#define REGISTER_H

#include "common.h"
#include "button.h"
#include "user.h"
#include <ctype.h>

int Register_Init();
void register_Draw();
void registerFail_Draw();
void register_Free();

extern InputBox usernameInputBoxRegister;
extern InputBox passwordInputBoxRegister;

extern int currentFocusRegister;

void handleRegisterInputBox(SDL_Event* event, InputBox* inputBox);

ButtonType register_GetButtonClicked(SDL_Event* event);

#endif