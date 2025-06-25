#include "Ranking.h"

ScoreNode* rankingList = NULL;
TTF_Font* font_Ranking = NULL;

Button button_BacktoMenu;


// 初始化排名页面
int Ranking_Init() {
    font_Ranking = TTF_OpenFont("../material/STXINWEI.TTF", 24);
    if (!font_Ranking) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    ButtonInit(&button_BacktoMenu, 1050, 520, 120, 50, "Back");
    button_BacktoMenu.type = Button_Back;
    
    // 获取排名链表（前10名）
    rankingList = getScoreRankingList(10);
    return 0;
}

void renderRankingBackground()
{
    //加载背景图片
    SDL_Surface* background_Surface = SDL_LoadBMP("../material/background1.bmp");
    if(background_Surface == NULL)
    {
        SDL_Log("Failed to load image! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    SDL_Texture* background_Texture = SDL_CreateTextureFromSurface(app.renderer, background_Surface);
    if(background_Texture == NULL)
    {
        SDL_Log("Failed to create background_texture! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    //设置渲染器颜色
    SDL_SetRenderDrawColor(app.renderer,0,255,0,255);
    //清空渲染器
    SDL_RenderClear(app.renderer);

    //渲染背景
    SDL_RenderCopy(app.renderer, background_Texture, NULL, NULL);  
    SDL_DestroyTexture(background_Texture);
    SDL_FreeSurface(background_Surface);
}

// 渲染排名页面
void Ranking_Draw() {
    // 清空屏幕
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
    
    renderRankingBackground();

    // 绘制标题
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* titleSurface = TTF_RenderText_Solid(font_Ranking, "Score Ranking", textColor);
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(app.renderer, titleSurface);
    SDL_Rect titleRect = {400, 50, titleSurface->w, titleSurface->h};
    SDL_RenderCopy(app.renderer, titleTexture, NULL, &titleRect);
    
    // 释放标题资源
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);
    
    // 绘制排名列表（链表版本）
    int position = 0;
    ScoreNode* current = rankingList;
    while (current != NULL && position < 10) {
        char rankText[100];
        sprintf(rankText, "%d. %-15s: %d", position + 1, current->username, current->score);
        
        SDL_Surface* rankSurface = TTF_RenderText_Solid(font_Ranking, rankText, textColor);
        SDL_Texture* rankTexture = SDL_CreateTextureFromSurface(app.renderer, rankSurface);
        SDL_Rect rankRect = {350, 150 + position * 40, rankSurface->w, rankSurface->h};
        SDL_RenderCopy(app.renderer, rankTexture, NULL, &rankRect);
        
        // 释放资源
        SDL_FreeSurface(rankSurface);
        SDL_DestroyTexture(rankTexture);
        
        current = current->next;
        position++;
    }
    
    RenderButton(&button_BacktoMenu,font_Ranking);
    // 更新屏幕
    SDL_RenderPresent(app.renderer);
}

// 更新排行榜链表
void updateRankingList(ScoreNode** rankingList) {
    // 释放原有的链表内存
    freeRankingList(*rankingList);
    // 重新加载排名数据
    *rankingList = loadRankingFromFile();
}


// 清理排名页面资源
void Ranking_Cleanup() {
    if (font_Ranking) {
        TTF_CloseFont(font_Ranking);
        font_Ranking = NULL;
    }
    
    // 释放链表内存
    freeRankingList(rankingList);
    rankingList = NULL;
}


ButtonType ranking_GetbuttonClicked(SDL_Event* event)
{
    if(!event) return Button_None;
    if(isButtonClicked(&button_BacktoMenu, event)) return Button_Back;
    return Button_None;
}