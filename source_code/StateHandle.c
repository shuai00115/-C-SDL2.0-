#include "StateHandle.h"
#include "menu.h"
#include "button.h"
#include "Level_Selection.h"
#include "Level_Switch.h"
#include "level.h"
#include "save.h"


void MenuStateHandle(SDL_Event* event)
{
            //如果游戏状态是菜单状态
            if (app.game_state == GAME_STATE_MENU)
            {
                //检测主菜单按钮点击
                ButtonType Clicked = menu_GetButtonClicked(event);
                switch (Clicked)
                {
                case Button_None:
                    break;
                //如果点击了“Start”按钮，进入关卡选择界面
                case Button_Start:
                    app.game_state = GAME_STATE_LEVEL_SELECT;
                    break;
                //如果点击了“Quit”按钮，退出程序
                case Button_Quit:
                    Level_Selection_Deinit();
                    menu_Quit();
                    Level_Switch_DeInit();
                    SDL_DestroyRenderer(app.renderer);
                    SDL_DestroyWindow(app.window);
                    SDL_Quit();
                    exit(0);

                default:
                    break;
                }
                SDL_RenderClear(app.renderer); // 清屏
                menu_Draw();//渲染菜单界面
                SDL_RenderPresent(app.renderer); // 显示
                SDL_Delay(16);
            }
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
            saveData.level1_completed = 1; // 标记第一关已完成
            SaveGame(); // 保存进度
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
        saveData.level2_completed = 1;
        SaveGame();
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
        saveData.level3_completed = 1;
        SaveGame();
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
        saveData.level4_completed = 1;
        SaveGame();
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
    MenuStateHandle,              // 0: GAME_STATE_MENU
    LevelSelectStateHandle,       // 1: GAME_STATE_LEVEL_SELECT
    level1StateHandle,            // 2: GAME_STATE_PLAYING_LEVEL1
    level2StateHandle,            // 3: GAME_STATE_PLAYING_LEVEL2
    level3StateHandle,            // 4: GAME_STATE_PLAYING_LEVEL3
    level4StateHandle,            // 5: GAME_STATE_PLAYING_LEVEL4
    level1StateHandle,            // 6: GAME_STATE_LEVEL1SWITCH
    level2StateHandle,            // 7: GAME_STATE_LEVEL2SWITCH
    level3StateHandle,            // 8: GAME_STATE_LEVEL3SWITCH
    level4StateHandle,            // 9: GAME_STATE_LEVEL4SWITCH
    level1FailStateHandle,        // 10: GAME_STATE_LEVEL1FAIL
    level2FailStateHandle,        // 11: GAME_STATE_LEVEL2FAIL
    level3FailStateHandle,        // 12: GAME_STATE_LEVEL3FAIL
    level4FailStateHandle         // 13: GAME_STATE_LEVEL4FAIL
};
