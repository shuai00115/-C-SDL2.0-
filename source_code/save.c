#include "save.h"
#include <stdio.h>

SaveData saveData;

void InitSaveData()
{
    saveData.level1_completed = 0;
    saveData.level2_completed = 0;
    saveData.level3_completed = 0;
    saveData.level4_completed = 0;
}

void SaveGame() {
    FILE *file = fopen("save.txt", "w");  // 文本模式写入
    if (file) {
        fprintf(file, "level1_completed=%d\n", saveData.level1_completed);
        fprintf(file, "level2_completed=%d\n", saveData.level2_completed);
        fprintf(file, "level3_completed=%d\n", saveData.level3_completed);
        fprintf(file, "level4_completed=%d\n", saveData.level4_completed);
        fclose(file);
    }
}

void LoadGame() {
    FILE *file = fopen("save.txt", "r");  // 文本模式读取
    if (file) {
        // 正确顺序读取每一行
        fscanf(file, "level1_completed=%d\n", &saveData.level1_completed);
        fscanf(file, "level2_completed=%d\n", &saveData.level2_completed);
        fscanf(file, "level3_completed=%d\n", &saveData.level3_completed);
        fscanf(file, "level4_completed=%d\n", &saveData.level4_completed);
        fclose(file);
    } else {
        InitSaveData();  // 如果没有存档，初始化默认数据
    }
}