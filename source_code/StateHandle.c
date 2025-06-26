#include "StateHandle.h"


extern ScoreNode* rankingList;

UserData currentUser; // 当前用户信息

void CoverStateHandle(SDL_Event* event)
{
    ButtonType clicked = cover_GetButtonClicked(event);
    switch (clicked)
    {
    case Button_None:
        break;
    case Button_Login:
        app.game_state = GAME_STATE_LOGIN;
        break;
    case Button_Register:
        app.game_state = GAME_STATE_REGISTER;
        break;
    default:
        break;
    }
    SDL_RenderClear(app.renderer);   // 清屏
    cover_Draw();                    // 渲染菜单界面
    SDL_RenderPresent(app.renderer); // 显示
    SDL_Delay(16);
}

void LoginStateHandle(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        
        // 检查用户名输入框是否被点击
        if (x >= usernameInputBox.rect.x && x <= usernameInputBox.rect.x + usernameInputBox.rect.w &&
            y >= usernameInputBox.rect.y && y <= usernameInputBox.rect.y + usernameInputBox.rect.h) {
            currentFocus = 1;
        }
        // 检查密码输入框是否被点击
        else if (x >= passwordInputBox.rect.x && x <= passwordInputBox.rect.x + passwordInputBox.rect.w &&
                 y >= passwordInputBox.rect.y && y <= passwordInputBox.rect.y + passwordInputBox.rect.h) {
            currentFocus = 2;
        }
        else {
            currentFocus = 0; // 点击其他区域，取消焦点
        }
        
        // 更新输入框焦点状态
        usernameInputBox.isFocused = (currentFocus == 1);
        passwordInputBox.isFocused = (currentFocus == 2);
    }

    // 只处理当前有焦点的输入框
    if (event->type == SDL_KEYDOWN) {
        if (currentFocus == 1) {
            handleInputBox(event, &usernameInputBox);
        } else if (currentFocus == 2) {
            handleInputBox(event, &passwordInputBox);
        }
    }

    ButtonType clicked = login_GetButtonClicked(event);
    switch (clicked)
    {
    case Button_None:
        break;
    case Button_Confirm:
        // 处理登录逻辑
        UserData user;
        strcpy(user.username, usernameInputBox.text);
        strcpy(user.password, passwordInputBox.text);
        if (isUserValid(&user)) {
        // 登录成功
        loadUserData(&user); // 将用户历史数据加载到内存
        currentUser = user; // 保存当前用户信息
        app.game_state = GAME_STATE_MENU;
    } else {
            // 登录失败
            loginFail_Draw();
            SDL_Delay(2000);
            app.game_state = GAME_STATE_LOGIN;
        }
        break;
    case Button_Back:
        app.game_state = GAME_STATE_COVER;
        break;
    default:
        break;
    }

    
    SDL_RenderClear(app.renderer);   // 清屏
    login_Draw();                    // 渲染登录界面
    SDL_RenderPresent(app.renderer); // 显示
    SDL_Delay(16);
}

void RegisterStateHandle(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        // 检查用户名输入框是否被点击
        if (x >= usernameInputBoxRegister.rect.x && x <= usernameInputBoxRegister.rect.x + usernameInputBoxRegister.rect.w &&
            y >= usernameInputBoxRegister.rect.y && y <= usernameInputBoxRegister.rect.y + usernameInputBoxRegister.rect.h) {
            currentFocusRegister = 1;
        }
        // 检查密码输入框是否被点击
        else if (x >= passwordInputBoxRegister.rect.x && x <= passwordInputBoxRegister.rect.x + passwordInputBoxRegister.rect.w &&
                 y >= passwordInputBoxRegister.rect.y && y <= passwordInputBoxRegister.rect.y + passwordInputBoxRegister.rect.h) {
            currentFocusRegister = 2;
        }
        else {
            currentFocusRegister = 0; // 点击其他区域，取消焦点
        }

        // 更新输入框焦点状态
        usernameInputBoxRegister.isFocused = (currentFocusRegister == 1);
        passwordInputBoxRegister.isFocused = (currentFocusRegister == 2);
    }

    // 只处理当前有焦点的输入框
    if (event->type == SDL_KEYDOWN) {
        if (currentFocusRegister == 1) {
            handleRegisterInputBox(event, &usernameInputBoxRegister);
        } else if (currentFocusRegister == 2) {
            handleRegisterInputBox(event, &passwordInputBoxRegister);
        }
    }

    ButtonType clicked = register_GetButtonClicked(event);
    switch (clicked)
    {
    case Button_None:
        break;
    case Button_Confirm:
        // 处理注册逻辑
        UserData user;
        strcpy(user.username, usernameInputBoxRegister.text);
        strcpy(user.password, passwordInputBoxRegister.text);
        // 初始化通关状态
        user.saveData.level1_completed = 0;
        user.saveData.level2_completed = 0;
        user.saveData.level3_completed = 0;
        user.saveData.level4_completed = 0;
        user.saveData.score = 0;

        if (registerUser(&user) == 0) {
            // 注册成功
        currentUser = user; // 保存当前用户信息
        app.game_state = GAME_STATE_MENU;
        } else {
            // 注册失败
            registerFail_Draw();
            SDL_Delay(2000);
            app.game_state = GAME_STATE_REGISTER;
        }
        break;
    case Button_Back:
        app.game_state = GAME_STATE_COVER;
        break;
    default:
        break;
    }
    SDL_RenderClear(app.renderer);   // 清屏
    register_Draw();                    // 渲染注册界面
    SDL_RenderPresent(app.renderer); // 显示
    SDL_Delay(16);
}

void MenuStateHandle(SDL_Event *event)
{
    // 检测主菜单按钮点击
    ButtonType Clicked = menu_GetButtonClicked(event);
    switch (Clicked)
    {
    case Button_None:
        break;
    // 如果点击了“Start”按钮，进入关卡选择界面
    case Button_Start:
        app.game_state = GAME_STATE_LEVEL_SELECT;
        break;
    // 如果点击了“Quit”按钮，退出程序
    case Button_Quit:
        Level_Selection_Deinit();
        menu_Quit();
        Level_Switch_DeInit();
        SDL_DestroyRenderer(app.renderer);
        SDL_DestroyWindow(app.window);
        SDL_Quit();
        exit(0);
        break;
    case Button_Ranking:
        updateRankingList(&rankingList); // 更新排行榜数据
        app.game_state = GAME_STATE_RANKING;
        break;
    default:
        break;
    }
    SDL_RenderClear(app.renderer);   // 清屏
    menu_Draw();                     // 渲染菜单界面
    SDL_RenderPresent(app.renderer); // 显示
    SDL_Delay(16);
}

void RankingStateHandle(SDL_Event* event)
{
    ButtonType clicked = ranking_GetbuttonClicked(event);
    switch(clicked)
    {
        case Button_None:
            break;
        case Button_Back:
            app.game_state = GAME_STATE_MENU;
            break;
        default:
            break;
    }
    SDL_RenderClear(app.renderer);   // 清屏
    Ranking_Draw();                    // 渲染排行榜界面
    SDL_RenderPresent(app.renderer); // 显示
    SDL_Delay(16);

}

void LevelSelectStateHandle(SDL_Event* event)
{
    // 检测关卡选择界面按钮点击
    ButtonType Clicked = Level_Selection_GetButtonClicked(event);
    switch (Clicked)
    {
    case Button_None:
        break;
    // 如果点击了“Back”按钮，返回主菜单界面
    case Button_Back:
        app.game_state = GAME_STATE_MENU;
        break;
    // 如果点击了关卡按钮，进入相应关卡
    case Button_Level1:
        app.game_state = GAME_STATE_PLAYING_LEVEL1; 
        break;
    case Button_Level2:
        app.game_state = GAME_STATE_PLAYING_LEVEL2;
        break;
    case Button_Level3:
        app.game_state = GAME_STATE_PLAYING_LEVEL3;
        break;
    case Button_Level4:
        app.game_state = GAME_STATE_PLAYING_LEVEL4;
        break;
    default:
        break;
    }
    SDL_RenderClear(app.renderer); // 清屏
    Level_Selection_Draw();        // 渲染关卡选择界面
    SDL_Delay(16);
}

void level1StateHandle(SDL_Event* event)
{
    if(app.game_state == GAME_STATE_PLAYING_LEVEL1)
    {
        int result = loop1(); // 关卡1逻辑

        if (result == 1)
        {                                             // 通关
            currentUser.saveData.level1_completed = 1; // 更新当前用户的通关状态
            currentUser.saveData.score += 50; // 通关关卡加50分
            saveUserData(&currentUser); // 保存用户数据
            app.game_state = GAME_STATE_LEVEL1SWITCH; // 跳转到通关界面
        }
        else if (result == -1)
        {                                             // 失败
            app.game_state = GAME_STATE_LEVEL_SELECT; // 跳转到关卡选择
        }
    }
   
    // 处理关卡切换界面的逻辑
    if (app.game_state == GAME_STATE_LEVEL1SWITCH)
    {
        ButtonType clicked = Level1_Switch_GetButtonClicked(event);
        
        if (clicked == Button_Level2) {
            app.game_state = GAME_STATE_PLAYING_LEVEL2;
            return;
        }
        if(clicked == Button_Start)
        {
            app.game_state = GAME_STATE_LEVEL_SELECT;
            return;
        }
        
        // 渲染
        SDL_RenderClear(app.renderer);
        Level1_Switch_Draw();
        SDL_RenderPresent(app.renderer);
        SDL_Delay(16);
    }
}

void level2StateHandle(SDL_Event* event)
{
    if(app.game_state == GAME_STATE_PLAYING_LEVEL2)
    {
        int result = loop2();//关卡2逻辑
    if (result == 1)
    {                                             // 通关
        currentUser.saveData.level2_completed = 1; // 更新当前用户的通关状态
        currentUser.saveData.score += 100; // 通关关卡加100分
        saveUserData(&currentUser); // 保存用户数据
        app.game_state = GAME_STATE_LEVEL2SWITCH; // 跳转到通关界面
    }
    else if (result == -1)
    {                                             // 失败
        app.game_state = GAME_STATE_LEVEL_SELECT; // 跳转到关卡选择
    }
    }
    
    if(app.game_state == GAME_STATE_LEVEL2SWITCH)
    {
        ButtonType clicked =Level2_Switch_GetButtonClicked(event);
        // 状态转换
        if (clicked == Button_Level3) {
            app.game_state = GAME_STATE_PLAYING_LEVEL3;
            return;
        }
        if(clicked == Button_Start)
        {
            app.game_state = GAME_STATE_LEVEL_SELECT;
            return;
        }
        
        // 渲染
        SDL_RenderClear(app.renderer);
        Level2_Switch_Draw();
        SDL_RenderPresent(app.renderer);
        SDL_Delay(16);
       
    }
    
}

void level3StateHandle(SDL_Event* event)
{
    if(app.game_state == GAME_STATE_PLAYING_LEVEL3)
    {
        int result = loop3();//关卡3逻辑
    if (result == 1)
    {                                             // 通关
        currentUser.saveData.level3_completed = 1; // 更新当前用户的通关状态
        currentUser.saveData.score += 200; // 通关关卡加200分
        saveUserData(&currentUser); // 保存用户数据
        app.game_state = GAME_STATE_LEVEL3SWITCH; // 跳转到通关界面
    }
    else if (result == -1)
    {                                             // 失败
        app.game_state = GAME_STATE_LEVEL_SELECT; // 跳转到关卡选择
    }
    }
    
    if(app.game_state == GAME_STATE_LEVEL3SWITCH)
    {
        ButtonType clicked = Level3_Switch_GetButtonClicked(event);
        // 状态转换
        if (clicked == Button_Level4) {
            app.game_state = GAME_STATE_PLAYING_LEVEL4;
            return;
        }
        if(clicked == Button_Start)
        {
            app.game_state = GAME_STATE_LEVEL_SELECT;
            return;
        }
        
        // 渲染
        SDL_RenderClear(app.renderer);
        Level3_Switch_Draw();
        SDL_RenderPresent(app.renderer);
        SDL_Delay(16);
    }
    
}

void level4StateHandle(SDL_Event* event)
{
    if(app.game_state == GAME_STATE_PLAYING_LEVEL4)
    {
        int result = loop4();//关卡4逻辑
    if (result == 1)
    {                                             // 通关
        currentUser.saveData.level4_completed = 1; // 更新当前用户的通关状态
        currentUser.saveData.score += 400; // 通关关卡加400分
        saveUserData(&currentUser); // 保存用户数据
        app.game_state = GAME_STATE_LEVEL4SWITCH; // 跳转到通关界面
    }
    else if (result == -1)
    {                                             // 失败
        app.game_state = GAME_STATE_LEVEL_SELECT; // 跳转到关卡选择
    }
    }
    
    if(app.game_state == GAME_STATE_LEVEL4SWITCH)
    {
        ButtonType clicked = Level4_Switch_GetButtonClicked(event);
        // 状态转换
        if (clicked == Button_Start) {
            app.game_state = GAME_STATE_LEVEL_SELECT;
            return;
        }
        
        // 渲染
        SDL_RenderClear(app.renderer);
        Level4_Switch_Draw();
        SDL_RenderPresent(app.renderer);
        SDL_Delay(16);
    }
}

// 关卡1失败状态处理
void level1FailStateHandle(SDL_Event* event) {
    ButtonType clicked = Level1_Fail_GetButtonClicked(event);
    
    if (clicked == Button_Level1) {
        app.game_state = GAME_STATE_PLAYING_LEVEL1;
    } else if (clicked == Button_Start) {
        app.game_state = GAME_STATE_MENU;
    }
    
    SDL_RenderClear(app.renderer);
    Level1_Fail_Draw();
    SDL_RenderPresent(app.renderer);
    SDL_Delay(16);
}

// 关卡2失败状态处理
void level2FailStateHandle(SDL_Event* event) {
    ButtonType clicked = Level2_Fail_GetButtonClicked(event);
    
    if (clicked == Button_Level2) {
        app.game_state = GAME_STATE_PLAYING_LEVEL2;
    } else if (clicked == Button_Start) {
        app.game_state = GAME_STATE_MENU;
    }
    
    SDL_RenderClear(app.renderer);
    Level2_Fail_Draw();
    SDL_RenderPresent(app.renderer);
    SDL_Delay(16);
}

// 关卡3失败状态处理
void level3FailStateHandle(SDL_Event* event) {
    ButtonType clicked = Level3_Fail_GetButtonClicked(event);
    
    if (clicked == Button_Level3) {
        app.game_state = GAME_STATE_PLAYING_LEVEL3;
    } else if (clicked == Button_Start) {
        app.game_state = GAME_STATE_MENU;
    }
    
    SDL_RenderClear(app.renderer);
    Level3_Fail_Draw();
    SDL_RenderPresent(app.renderer);
    SDL_Delay(16);
}

// 关卡4失败状态处理
void level4FailStateHandle(SDL_Event* event) {
    ButtonType clicked = Level4_Fail_GetButtonClicked(event);
    
    if (clicked == Button_Level4) {
        app.game_state = GAME_STATE_PLAYING_LEVEL4;
    } else if (clicked == Button_Start) {
        app.game_state = GAME_STATE_MENU;
    }
    
    SDL_RenderClear(app.renderer);
    Level4_Fail_Draw();
    SDL_RenderPresent(app.renderer);
    SDL_Delay(16);
}


StateHandle stateHandle[] = {
    CoverStateHandle,             // 0: GAME_STATE_COVER
    LoginStateHandle,             // 1: GAME_STATE_LOGIN
    RegisterStateHandle,          // 2: GAME_STATE_REGISTER
    MenuStateHandle,              // 3: GAME_STATE_MENU
    RankingStateHandle,           // 4: GAME_STATE_RANKING
    LevelSelectStateHandle,       // 5: GAME_STATE_LEVEL_SELECT
    level1StateHandle,            // 6: GAME_STATE_PLAYING_LEVEL1
    level2StateHandle,            // 7: GAME_STATE_PLAYING_LEVEL2
    level3StateHandle,            // 8: GAME_STATE_PLAYING_LEVEL3
    level4StateHandle,            // 9: GAME_STATE_PLAYING_LEVEL4
    level1StateHandle,            // 10: GAME_STATE_LEVEL1SWITCH
    level2StateHandle,            // 11: GAME_STATE_LEVEL2SWITCH
    level3StateHandle,            // 12: GAME_STATE_LEVEL3SWITCH
    level4StateHandle,            // 13: GAME_STATE_LEVEL4SWITCH
    level1FailStateHandle,        // 14: GAME_STATE_LEVEL1FAIL
    level2FailStateHandle,        // 15: GAME_STATE_LEVEL2FAIL
    level3FailStateHandle,        // 16: GAME_STATE_LEVEL3FAIL
    level4FailStateHandle         // 17: GAME_STATE_LEVEL4FAIL
};
