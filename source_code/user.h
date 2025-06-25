#ifndef USER_H
#define USER_H

#include "common.h"

#define MAX_USERNAME_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    int score;
} ScoreEntry;

typedef struct ScoreNode {
    char username[MAX_USERNAME_LENGTH];
    int score;
    struct ScoreNode* next;
} ScoreNode;


int isUserValid(UserData *user);
int registerUser(UserData *user);
void saveUserData(UserData *user);
int loadUserData(UserData *user);

ScoreNode* createNode(const char* username, int score);
void insertSorted(ScoreNode** head, const char* username, int score);
ScoreNode* loadRankingFromFile();
void freeRankingList(ScoreNode* head);
ScoreNode* getScoreRankingList(int maxCount);

#endif