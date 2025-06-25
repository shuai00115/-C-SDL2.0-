#include "user.h"
#include "button.h"

extern UserData currentUser;

// 检查用户是否存在且密码正确
int isUserValid(UserData *user)
{
    FILE *file = fopen("user_data.txt", "r"); // 打开用户数据文件
    if (!file)
    {                                               // 如果文件打开失败
        printf("Unable to open user data file!\n"); // 输出错误信息
        return 0;                                   // 返回失败标志
    }

    char line[200]; // 存储文件中的一行数据
    while (fgets(line, sizeof(line), file))
    {                                                                                                          // 逐行读取文件数据
        char storedUsername[MAX_USERNAME_LENGTH], storedPassword[MAX_PASSWORD_LENGTH];                         // 存储文件中的用户名和密码
        int level1_completed,level2_completed,level3_completed,level4_completed,score;                               // 存储玩家的通关状态
        sscanf(line, "%s %s %d %d %d %d %d", storedUsername, storedPassword, &level1_completed, &level2_completed, &level3_completed, &level4_completed, &score);                                                // 解析数据

        if (strcmp(user->username, storedUsername) == 0 && strcmp(user->password, storedPassword) == 0)
        {                
            // 加载玩家的通关状态
            user->saveData.level1_completed = level1_completed;
            user->saveData.level2_completed = level2_completed;
            user->saveData.level3_completed = level3_completed;
            user->saveData.level4_completed = level4_completed;
            user->saveData.score = score; // 加载分数
            fclose(file); // 关闭文件
            return 1;     // 返回成功标志
        }
    }

    fclose(file); // 关闭文件
    return 0;     // 如果没有找到匹配的用户，返回失败标志
}

// 检查用户名是否已存在
int isUsernameExist(char *username)
{
    FILE *file = fopen("user_data.txt", "r"); // 打开用户数据文件
    if (!file)
    {                                               // 如果文件打开失败
        printf("Unable to open user data file!\n"); // 输出错误信息
        return 0;                                   // 返回失败标志
    }

    char line[200]; // 存储文件中的一行数据
    while (fgets(line, sizeof(line), file))
    {                                             // 逐行读取文件数据
        char storedUsername[MAX_USERNAME_LENGTH]; // 存储文件中的用户名
        sscanf(line, "%s", storedUsername);       // 解析数据
        if (strcmp(username, storedUsername) == 0)
        {                 // 如果用户名已经存在
            fclose(file); // 关闭文件
            return 1;     // 返回存在标志
        }
    }

    fclose(file); // 关闭文件
    return 0;     // 如果没有找到匹配的用户名，返回不存在标志
}

// 注册新用户
int registerUser(UserData *user)
{
    // 检查用户名是否已存在
    if (isUsernameExist(user->username))
    {
        return -1; // 如果用户名已存在，返回失败标志
    }

    // 将新用户数据添加到文件中
    FILE *file = fopen("user_data.txt", "a"); // 打开用户数据文件（以追加模式）
    if (!file)
    {                                                 // 如果文件打开失败
        printf("Unable to open file for writing!\n"); // 输出错误信息
        return -1;                                    // 返回失败标志
    }

    // 将用户数据写入文件（包括用户名、密码和通关状态）
    fprintf(file, "%s %s %d %d %d %d %d\n", user->username, user->password, 
        user->saveData.level1_completed, user->saveData.level2_completed, 
        user->saveData.level3_completed, user->saveData.level4_completed, user->saveData.score);
    fclose(file); // 关闭文件
    return 0;     // 返回成功标志
}

// 保存用户数据（包括关卡通关状态）
void saveUserData(UserData *user)
{
    FILE *file = fopen("user_data.txt", "r+"); // 打开用户数据文件（以读写模式）
    if (!file)
    {                                               // 如果文件打开失败
        printf("Unable to open user data file!\n"); // 输出错误信息
        return;                                     // 返回
    }

    char line[200]; // 存储文件中的一行数据
    long pos;       // 存储文件中的位置
    while ((pos = ftell(file)) != -1 && fgets(line, sizeof(line), file))
    {                                             // 逐行读取文件数据
        char storedUsername[MAX_USERNAME_LENGTH]; // 存储文件中的用户名
        sscanf(line, "%s", storedUsername);       // 解析数据
        if (strcmp(user->username, storedUsername) == 0)
        {                               // 如果找到了匹配的用户名
            fseek(file, pos, SEEK_SET); // 移动到该用户数据的开头
            // 更新用户数据（包括用户名、密码和通关状态）
            fprintf(file, "%s %s %d %d %d %d %d\n", user->username, user->password,
                    user->saveData.level1_completed, user->saveData.level2_completed,
                    user->saveData.level3_completed, user->saveData.level4_completed, user->saveData.score);
            fclose(file); // 关闭文件
            return;       // 返回
        }
    }

    fclose(file); // 关闭文件
}

int loadUserData(UserData *user)
{
    FILE *file = fopen("user_data.txt", "r"); // 打开用户数据文件
    if (!file)
    {                                               // 如果文件打开失败
        printf("Unable to open user data file!\n"); // 输出错误信息
        return -1;                                  // 返回失败标志
    }

    char line[200]; // 存储文件中的一行数据
    while (fgets(line, sizeof(line), file))
    {                                                                                                          // 逐行读取文件数据
        char storedUsername[MAX_USERNAME_LENGTH];                                                              // 存储文件中的用户名
        int level1_completed,level2_completed,level3_completed,level4_completed,score;                               // 存储玩家的通关状态
        if (sscanf(line, "%s %s %d %d %d %d %d", storedUsername, user->password, &level1_completed, &level2_completed, &level3_completed, &level4_completed, &score) != 7) {
            // 如果解析失败，跳过该行
            continue;
        }
        if (strcmp(user->username, storedUsername) == 0)
        { // 如果找到了匹配的用户名
            // 加载保存的关卡通关状态
            user->saveData.level1_completed = level1_completed;
            user->saveData.level2_completed = level2_completed;
            user->saveData.level3_completed = level3_completed;
            user->saveData.level4_completed = level4_completed;
            user->saveData.score = score;
            fclose(file); // 关闭文件
            return 0;     // 返回成功标志
        }
    }

    fclose(file); // 关闭文件
    return -1;    // 如果没有找到匹配的用户，返回失败标志
}


// 创建新节点
ScoreNode* createNode(const char* username, int score) {
    ScoreNode* newNode = (ScoreNode*)malloc(sizeof(ScoreNode));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->username, username);
    newNode->score = score;
    newNode->next = NULL;
    return newNode;
}

// 插入节点并保持链表按分数降序排列
void insertSorted(ScoreNode** head, const char* username, int score) {
    ScoreNode* newNode = createNode(username, score);
    
    if (*head == NULL || (*head)->score < score) {
        newNode->next = *head;
        *head = newNode;
    } else {
        ScoreNode* current = *head;
        while (current->next != NULL && current->next->score > score) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// 从文件加载排名数据到链表
ScoreNode* loadRankingFromFile() {
    FILE* file = fopen("user_data.txt", "r");
    if (!file) {
        printf("Unable to open user data file!\n");
        return NULL;
    }
    
    ScoreNode* head = NULL;
    char line[200];
    
    while (fgets(line, sizeof(line), file)) {
        char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
        int level1_completed, level2_completed, level3_completed, level4_completed, score;
        if (sscanf(line, "%s %s %d %d %d %d %d", username, password, 
                 &level1_completed, &level2_completed, 
                 &level3_completed, &level4_completed, &score) == 7) {
            insertSorted(&head, username, score);
        }
    }
    
    fclose(file);
    return head;
}

// 释放链表内存
void freeRankingList(ScoreNode* head) {
    ScoreNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// 获取排名链表（返回前maxCount名）
ScoreNode* getScoreRankingList(int maxCount) {
    ScoreNode* fullList = loadRankingFromFile();
    if (!fullList) return NULL;
    
    ScoreNode* topList = NULL;
    ScoreNode* current = fullList;
    int count = 0;
    
    while (current != NULL && count < maxCount) {
        insertSorted(&topList, current->username, current->score);
        current = current->next;
        count++;
    }
    
    freeRankingList(fullList);
    return topList;
}

