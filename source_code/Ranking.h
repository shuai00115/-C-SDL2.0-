#ifndef RANKING_H
#define RANKING_H

#include "common.h"
#include "user.h"
#include "button.h"

extern ScoreNode* rankingList;

int Ranking_Init();
void Ranking_Draw();
void Ranking_Cleanup();
void updateRankingList(ScoreNode** rankingList);
ButtonType ranking_GetbuttonClicked(SDL_Event* event);

#endif