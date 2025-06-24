#include "level.h"
#include "common.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#define PIXEL_SIZE 10
#define width 1200
#define height 600
#define Playerwidth 60
#define Playerheight 96
#define Groundheight 105
#define Bulletwidth 45
#define Bulletheight 15
#define Pointrwidth 150
#define Pointheight 45
#define Objectsize 30
#define Healthbarsize 35
#define Maxmonsters 20
#define MAX_FALLING_OBJECTS 5
#define MAX_MONSTER_OBJECTS 5 
#define FPS 60

SDL_Surface* surf = NULL;
SDL_Surface* bmpsurf1 = NULL;
SDL_Surface* bmpsurf2 = NULL;
SDL_Surface* bmpsurf3 = NULL;
SDL_Surface* bmpsurf4 = NULL;
SDL_Surface* bmpsurf5 = NULL;
SDL_Surface* bmpsurf6 = NULL;
SDL_Surface* bmpsurf7 = NULL;
SDL_Surface* bmpsurf8 = NULL;
SDL_Surface* bmpsurf9 = NULL;
SDL_Surface* bmpsurf10 = NULL;
SDL_Surface* imagebackgrandgreen = NULL;
SDL_Surface* imagegreenmonsterright = NULL;
SDL_Surface* imagegreenmonsterleft = NULL;
SDL_Surface* imagegreenobject = NULL;
SDL_Surface* imagegreenshootobjectright = NULL;
SDL_Surface* imagegreenshootobjectleft = NULL;
SDL_Surface* imagebackgrandred = NULL;
SDL_Surface* imageredmonsterright = NULL;
SDL_Surface* imageredmonsterleft = NULL;
SDL_Surface* imageredobject = NULL;
SDL_Surface* imageredshootobjectright = NULL;
SDL_Surface* imageredshootobjectleft = NULL;
SDL_Surface* imagebackgrandsummer = NULL;
SDL_Surface* imagesummermonsterright = NULL;
SDL_Surface* imagesummermonsterleft = NULL;
SDL_Surface* imagesummerobject = NULL;
SDL_Surface* textsurf = NULL;
SDL_Texture* texture1 = NULL;
SDL_Texture* texture2 = NULL;
SDL_Texture* texture3 = NULL;
SDL_Texture* texture4 = NULL;
SDL_Texture* texture5 = NULL;
SDL_Texture* texture6 = NULL;
SDL_Texture* texture7 = NULL;
SDL_Texture* texture8 = NULL;
SDL_Texture* texture9 = NULL;
SDL_Texture* texture10 = NULL;
SDL_Texture* texturebackgrandgreen = NULL;
SDL_Texture* texturegreenmonsterright = NULL;
SDL_Texture* texturegreenmonsterleft = NULL;
SDL_Texture* texturegreenobject = NULL;
SDL_Texture* texturegreenshootobjectright = NULL;
SDL_Texture* texturegreenshootobjectleft = NULL;
SDL_Texture* texturebackgrandred = NULL;
SDL_Texture* textureredmonsterright = NULL;
SDL_Texture* textureredmonsterleft = NULL;
SDL_Texture* textureredobject = NULL;
SDL_Texture* textureredshootobjectright = NULL;
SDL_Texture* textureredshootobjectleft = NULL;
SDL_Texture* texturebackgrandsummer = NULL;
SDL_Texture* texturesummermonsterright = NULL;
SDL_Texture* texturesummermonsterleft = NULL;
SDL_Texture* texturesummerobject = NULL;
SDL_Texture* textTexture = NULL;
SDL_Rect rect = { 0,0,0,0 };
SDL_Rect rect1 = { 0,0,0,0 };
TTF_Font* font = NULL;
int jumpForce = -18;//初速度
int lineForce = 10;
int speedx = 0;//速度
int speedy = 0;
int gravity = 1;
int imageJudge = 0;
int isRightWalking = 0;
int isLeftWalking = 0;
int isJumping = 0;
int direction = 0;//判定方向为右
int shootSpeed = 10;
Bullet* bullets = NULL;
int bulletCount = 0;//当前子弹数量
int bulletCapacity = 0;//数组总容量
Monster monsters[Maxmonsters];
Uint32 lastMonsterSpawnTime = 0;
int monsterSpeed = 2;
int disappearJudge = 0;
Object objects[MAX_FALLING_OBJECTS];    // 坠落物数组
int objectCount;        // 当前坠落物数量
Monsterobject monsterobjects[MAX_MONSTER_OBJECTS];    // 怪物攻击物数组
int bulletObjectCount;        // 当前怪物攻击物数量
Uint32 lastObjectSpawnTime;   // 上次生成坠落物的时间
int currentShootedCount = 0;  //当前命中怪物数量
int stage = 0;//关卡
int gaming = 0;//游戏状态
int monsterObjectSpeedMin = 0;
int monsterObjectSpeedAdd = 0;
int Monsterwidth = 0;
int Monsterheight = 0;
int Spawninteral = 3000;
int FALLING_OBJECT_SPEED = 10;
int SPAWN_INTERVAL = 1000;   // 坠落物生成间隔（毫秒）

//初始化游戏
int initGame()
{    
    srand(time(NULL));
    //加载字体
    font = TTF_OpenFont("../material/STXINWEI.TTF",40);
    if (!font) {
        printf(" TTF_OpenFont失败: %s\n", TTF_GetError());
    }
    //4.创建image
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_img 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    //5.导入图片
    bmpsurf1 = IMG_Load("../material/character_Right.png ");
    if (bmpsurf1 == NULL) {
        printf("SDL_img1 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf2 = IMG_Load("../material/character_Left.png ");
    if (bmpsurf2 == NULL) {
        printf("SDL_img2 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf3 = SDL_LoadBMP("../material/background4.bmp");
    if (bmpsurf3 == NULL) {
        printf("SDL_img3 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf4 = IMG_Load("../material/91.png");
    if (bmpsurf4 == NULL) {
        printf("SDL_img4 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf5 = IMG_Load("../material/92.png");
    if (bmpsurf5 == NULL) {
        printf("SDL_img5 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf6 = IMG_Load("../material/93.png");
    if (bmpsurf6 == NULL) {
        printf("SDL_img6 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf7 = IMG_Load("../material/94.png");
    if (bmpsurf7 == NULL) {
        printf("SDL_img7 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf8 = IMG_Load("../material/95.png");
    if (bmpsurf8 == NULL) {
        printf("SDL_img8 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf9 = IMG_Load("../material/96.png");
    if (bmpsurf9 == NULL) {
        printf("SDL_img9 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf10 = IMG_Load("../material/97.png");
    if (bmpsurf10 == NULL) {
        printf("SDL_img10 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagebackgrandgreen = SDL_LoadBMP("../material/background1.bmp");
    if (imagebackgrandgreen == NULL) {
        printf("SDL_imagebackgrandgreen 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagegreenmonsterright = IMG_Load("../material/greenright.png");
    if (imagegreenmonsterright == NULL) {
        printf("SDL_imagegreenmonsterright 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagegreenmonsterleft = IMG_Load("../material/greenleft.png");
    if (imagegreenmonsterleft == NULL) {
        printf("SDL_imagegreenmonsterleft 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagegreenobject = IMG_Load("../material/greenobject.png");
    if (imagegreenobject == NULL) {
        printf("SDL_imagegreenobject 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagegreenshootobjectright = IMG_Load("../material/greenshootright.png");
    if (imagegreenshootobjectright == NULL) {
        printf("SDL_imagegreenshootobjectright 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagegreenshootobjectleft = IMG_Load("../material/greenshootleft.png");
    if (imagegreenshootobjectleft == NULL) {
        printf("SDL_imagegreenshootobjectleft 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagebackgrandred = SDL_LoadBMP("../material/background3.bmp");
    if (imagebackgrandred == NULL) {
        printf("SDL_imagebackgrandred 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imageredmonsterright = IMG_Load("../material/redright.png");
    if (imageredmonsterright == NULL) {
        printf("SDL_imageredmonsterright 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imageredmonsterleft = IMG_Load("../material/redleft.png");
    if (imageredmonsterleft == NULL) {
        printf("SDL_imageredmonsterleft 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imageredobject = IMG_Load("../material/redobject.png");
    if (imageredobject == NULL) {
        printf("SDL_imageredobject 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imageredshootobjectright = IMG_Load("../material/redshootright.png");
    if (imageredshootobjectright == NULL) {
        printf("SDL_imageredshootobjectright 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imageredshootobjectleft = IMG_Load("../material/redshootleft.png");
    if (imagegreenshootobjectright == NULL) {
        printf("SDL_imageredshootobjectleft 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagebackgrandsummer = SDL_LoadBMP("../material/background2.bmp");
    if (imagebackgrandsummer == NULL) {
        printf("SDL_imagebackgrandsummer 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagesummermonsterright = IMG_Load("../material/summerright.png");
    if (imagesummermonsterright == NULL) {
        printf("SDL_imagesummermonsterright 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagesummermonsterleft = IMG_Load("../material/summerleft.png");
    if (imagesummermonsterleft == NULL) {
        printf("SDL_imagesummermonsterleft 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagesummerobject = IMG_Load("../material/summerobject.png");
    if (imagesummerobject == NULL) {
        printf("SDL_imagesummerobject 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    //6.创建texture
    texture1 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf1);
    if (texture1 == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture2 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf2);
    if (texture2 == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture3 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf3);
    if (texture3 == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture4 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf4);
    if (texture4 == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture5 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf5);
    if (texture5 == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture6 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf6);
    if (texture6 == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture7 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf7);
    if (texture7 == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture8 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf8);
    if (texture8 == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture9 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf9);
    if (texture9 == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture10 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf10);
    if (texture10 == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturebackgrandgreen = SDL_CreateTextureFromSurface(app.renderer, imagebackgrandgreen);
    if (texturebackgrandgreen == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturegreenmonsterright = SDL_CreateTextureFromSurface(app.renderer, imagegreenmonsterright);
    if (texturegreenmonsterright == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturegreenmonsterleft = SDL_CreateTextureFromSurface(app.renderer, imagegreenmonsterleft);
    if (texturegreenmonsterleft == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturegreenobject = SDL_CreateTextureFromSurface(app.renderer, imagegreenobject);
    if (texturegreenobject == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturegreenshootobjectright = SDL_CreateTextureFromSurface(app.renderer, imagegreenshootobjectright);
    if (texturegreenshootobjectright == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturegreenshootobjectleft = SDL_CreateTextureFromSurface(app.renderer, imagegreenshootobjectleft);
    if (texturegreenshootobjectleft == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturebackgrandred = SDL_CreateTextureFromSurface(app.renderer, imagebackgrandred);
    if (texturebackgrandred == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    textureredmonsterright = SDL_CreateTextureFromSurface(app.renderer, imageredmonsterright);
    if (textureredmonsterright == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    textureredmonsterleft = SDL_CreateTextureFromSurface(app.renderer, imageredmonsterleft);
    if (textureredmonsterleft == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    textureredobject = SDL_CreateTextureFromSurface(app.renderer, imageredobject);
    if (textureredobject == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    textureredshootobjectright = SDL_CreateTextureFromSurface(app.renderer, imageredshootobjectright);
    if (textureredshootobjectright == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    textureredshootobjectleft = SDL_CreateTextureFromSurface(app.renderer, imageredshootobjectleft);
    if (textureredshootobjectleft == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturebackgrandsummer = SDL_CreateTextureFromSurface(app.renderer, imagebackgrandsummer);
    if (texturebackgrandsummer == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturesummermonsterright = SDL_CreateTextureFromSurface(app.renderer, imagesummermonsterright);
    if (texturesummermonsterright == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturesummermonsterleft = SDL_CreateTextureFromSurface(app.renderer, imagesummermonsterleft);
    if (texturesummermonsterleft == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturesummerobject = SDL_CreateTextureFromSurface(app.renderer, imagesummerobject);
    if (texturesummerobject == NULL) {
        printf("SDL_CreateTextureFromSurface 失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bullets = NULL;
    bulletCount = 0;
    bulletCapacity = 0;
    return 0;
}
//初始化玩家
void initPlayer(Player* player) {
    int w, h = 0;
    SDL_GetWindowSize(app.window,&w,&h);
    player->x = w/2 - Playerwidth/2;
    player->y = h - Playerheight-Groundheight;
    player->direction = 0;
    player->blood = 10;
    player->score = 10;
}
//初始化子弹
void initBullet(Player* player, Bullet* bullet_test) {
    bullet_test->x = player->x + Playerwidth / 2;
    bullet_test->y = player->y + (int)Playerheight /3;
    bullet_test->active = 1;
    bullet_test->direction = player->direction;
}
// 怪物死亡时向玩家发射子弹
void spawnMonsterBullet(int monsterX, int monsterY,Player* player) {
    // 寻找空闲的子弹槽位
    for (int i = 0; i < MAX_MONSTER_OBJECTS; i++) {
        if (!monsterobjects[i].active) {
            monsterobjects[i].x = monsterX;
            monsterobjects[i].y = monsterY + Monsterheight / 2;  // 从怪物中间发射

            // 随机速度 (3-8)
            monsterobjects[i].speed = monsterObjectSpeedMin + rand() % monsterObjectSpeedAdd;

            // 随机方向 (0=右, 1=左)
            if (player->x >= monsterobjects[i].x) {
                monsterobjects[i].direction = 0;
            }
            else {
                monsterobjects[i].direction = 1;
            }
            monsterobjects[i].active = 1;
            bulletObjectCount++;
            break;
        }
    }
}
//生成怪物
void initMonster() {
    Uint32 currentTime = SDL_GetTicks();
    // 检查是否到了生成时间
    if (currentTime - lastMonsterSpawnTime < Spawninteral) {
        return;
    }
    // 查找空闲的怪物槽
    for (int i = 0; i < Maxmonsters; i++) {
        if (!monsters[i].active) {
            // 随机决定从左侧还是右侧生成
            int fromLeft = rand() % 2;

            if (fromLeft) {
                // 从左侧生成，向右移动
                monsters[i].x = -Monsterwidth;
                monsters[i].direction = 0;
            }
            else {
                // 从右侧生成，向左移动
                monsters[i].x = width;
                monsters[i].direction = 1;
            }

            monsters[i].y = height - Groundheight - Monsterheight;
            monsters[i].active = 1;
            lastMonsterSpawnTime = currentTime;
            break;
        }
    }
}
// 矩形碰撞检测函数
int checkCollision(int x1, int y1, int w1, int h1,
    int x2, int y2, int w2, int h2) 
{
    return (x1 < x2 + w2 &&
        x1 + w1 > x2 &&
        y1 < y2 + h2 &&
        y1 + h1 > y2);
}
//检测怪物子弹碰撞
void checkBulletMonsterCollision(Player* player) {
    for (int i = 0; i < bulletCount; i++) {
        if (!bullets[i].active) continue;

        for (int j = 0; j <Maxmonsters; j++) {
            if (!monsters[j].active) continue;

            // 检查碰撞
            if (checkCollision(
                bullets[i].x, bullets[i].y, Bulletwidth, Bulletheight,
                monsters[j].x, monsters[j].y, Monsterwidth, Monsterheight)) {
                //怪物发射子弹
                spawnMonsterBullet(monsters[j].x, monsters[j].y,player);
                // 碰撞发生 - 两者都消失
                bullets[i].active = 0;
                monsters[j].active = 0;
                //命中加一
                currentShootedCount++;
                break; // 一颗子弹只能击中一个怪物
            }
        }
    }
}
//检测坠落物玩家碰撞
void checkPlayerObjectCollision(Player* player) {
    for (int i = 0; i < MAX_FALLING_OBJECTS; i++) {
        if (!objects[i].active) continue;

        // 检查碰撞
        if (checkCollision(
            player->x, player->y, Playerwidth, Playerheight,
            objects[i].x, objects[i].y, Objectsize, Objectsize)) {
            // 移除坠落物
            objects[i].active = 0;
            // 生命值减少等逻辑
            player->blood--;

        }
    }
}
// 检测玩家与怪物子弹的碰撞
void checkPlayerMonsterBulletCollision(Player* player) {
    for (int i = 0; i < MAX_MONSTER_OBJECTS; i++) {
        if (!monsterobjects[i].active) continue;

        if (checkCollision(
            player->x, player->y, Playerwidth, Playerheight,
            monsterobjects[i].x, monsterobjects[i].y, Objectsize, Objectsize)) {

            // 玩家受伤逻辑
            // (这里可以添加生命值减少等效果)
            player->blood--;
            // 移除子弹
            monsterobjects[i].active = 0;
            bulletObjectCount--;
        }
    }
}
// 生成新的坠落物
void spawnObject() {
    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - lastObjectSpawnTime < SPAWN_INTERVAL) {
        return;
    }

    for (int i = 0; i < MAX_FALLING_OBJECTS; i++) {
        if (!objects[i].active) {
            // 在屏幕顶部随机位置生成
            objects[i].x = rand() % (width - Objectsize);
            objects[i].y = -Objectsize;

            // 随机速度
            objects[i].speed = FALLING_OBJECT_SPEED;

            objects[i].active = 1;
            objects[i].spawnTime = currentTime;
            lastObjectSpawnTime = currentTime;
            break;
        }
    }
}
//更新子弹位置
void updateBullet() {
    // 修复子弹更新逻辑
    int i = 0;
    while (i < bulletCount) {
        if (!bullets[i].active) {
            // 移除失效的子弹
            bullets[i] = bullets[bulletCount - 1];
            bulletCount--;
            continue;
        }
        Bullet* bullet = &bullets[i];
        if (bullet->direction == 0) {
            bullet->x += shootSpeed;
            if (bullet->x > width) {
                // 安全移除子弹
                bullets[i] = bullets[bulletCount - 1];
                bulletCount--;
                continue; // 不增加i，继续处理新移到当前位置的子弹
            }
        }
        else {
            bullet->x -= shootSpeed;
            if (bullet->x < -Bulletwidth) {
                bullets[i] = bullets[bulletCount - 1];
                bulletCount--;
                continue;
            }
        }
        i++; // 只有未移除子弹时才增加索引
    }
}
//重置子弹位置
void resetBullet() {
    for (int i = 0; i < bulletCount; i++) {
        bullets[i].active = 0;
        bullets[i].x = -Bulletwidth;
        bullets[i].y = -Bulletheight;
    }
}
// 更新怪物位置
void updateMonsters() {
    for (int j = 0; j < Maxmonsters; j++) {
        if (monsters[j].active) {
            if (monsters[j].direction == 0) {
                // 向右移动
                monsters[j].x += monsterSpeed;
                // 检查是否超出屏幕
                if (monsters[j].x > width) {
                    monsters[j].active = 0;
                }
            }
            else {
                // 向左移动
                monsters[j].x -= monsterSpeed;
                // 检查是否超出屏幕
                if (monsters[j].x < -Monsterwidth) {
                    monsters[j].active = 0;
                }
            }
        }
    }
}
//重置怪物位置
void resetMonsters() {
    for (int i = 0; i < Maxmonsters; i++) {
        monsters[i].active = 0;
        monsters[i].x = -Bulletwidth;
        monsters[i].y = -Bulletheight;
    }
}
// 更新坠落物位置
void updateObjects() {
    for (int i = 0; i < MAX_FALLING_OBJECTS; i++) {
        if (objects[i].active) {
            // 垂直下落
            objects[i].y += objects[i].speed;

            // 如果坠落物落到地面以下，标记为不活跃
            if (objects[i].y > height) {
                objects[i].active = 0;
            }
        }
    }
}
//重置坠落物位置
void resetObjects() {
    for (int i = 0; i < MAX_FALLING_OBJECTS; i++) {
        objects[i].active = 0;
        objects[i].x = -Objectsize;
        objects[i].y = -Objectsize;
    }
}
// 更新怪物攻击物位置
void updateMonsterObjects(Player* player) {
    for (int i = 0; i < MAX_MONSTER_OBJECTS; i++) {
        if (!monsterobjects[i].active) continue;

        // 根据方向移动
        if (monsterobjects[i].direction == 0) {
            monsterobjects[i].x += monsterobjects[i].speed;  // 向右移动
        }
        else {
            monsterobjects[i].x -= monsterobjects[i].speed;  // 向左移动
        }

        // 检查是否超出屏幕
        if (monsterobjects[i].x < -Objectsize ||
            monsterobjects[i].x > width) {
            monsterobjects[i].active = 0;
            bulletObjectCount--;
        }
    }
}
//重置怪物攻击物位置
void resetMonsterObjects() {
    for (int i = 0; i < MAX_MONSTER_OBJECTS; i++) {
        monsterobjects[i].active = 0;
        monsterobjects[i].x = -Objectsize;
        monsterobjects[i].y = -Objectsize;
    }
}
//绘制玩家
void drawPlayer(SDL_Renderer* Renderer,Player* player) {
             rect = (SDL_Rect){ player->x,
                      player->y,
                    Playerwidth,
                    Playerheight
    };
             if (imageJudge == 0){
                 SDL_RenderCopy(Renderer, texture1, NULL, &rect);
             }
             else {
                 SDL_RenderCopy(Renderer, texture2, NULL, &rect);
             }
}
//绘制地面
void drawGround(SDL_Renderer* Renderer, Player* player,int level){
  rect1 = (SDL_Rect){ 0,
            0,
           width,
           height
  };
  if (level == 1) {
      SDL_RenderCopy(Renderer, texturebackgrandgreen, NULL, &rect1);
  }
  if (level == 2) {
      SDL_RenderCopy(Renderer, texturebackgrandsummer, NULL, &rect1);
  }
  if (level == 3) {
      SDL_RenderCopy(Renderer, texturebackgrandred, NULL, &rect1);
  }
  if (level == 4) {
      SDL_RenderCopy(Renderer, texture3, NULL, &rect1);
  }
}
//绘制子弹
void drawBullet(SDL_Renderer* Renderer, Player* player, int level) {
    for (int i = 0; i < bulletCount; i++) {
        Bullet* bullet = &bullets[i];
        SDL_Rect rect2 = { bullet->x,
                 bullet->y,
                 Bulletwidth,
                 Bulletheight
        };
        SDL_Rect rect3 = { bullet->x - Bulletwidth,
                 bullet->y,
                 Bulletwidth,
                 Bulletheight
        };
        if (bullet->active) {
            if (level == 4 || level == 2) {
                if (bullet->direction == 0) {
                    SDL_RenderCopy(Renderer, texture4, NULL, &rect2);
                }
                else {
                    SDL_RenderCopy(Renderer, texture5, NULL, &rect3);
                }
            }
            if (level == 1) {
                if (bullet->direction == 0) {
                    SDL_RenderCopy(Renderer, texturegreenshootobjectright, NULL, &rect2);
                }
                else {
                    SDL_RenderCopy(Renderer, texturegreenshootobjectleft, NULL, &rect3);
                }
            }
            if (level == 3) {
                if (bullet->direction == 0) {
                    SDL_RenderCopy(Renderer, textureredshootobjectright, NULL, &rect2);
                }
                else {
                    SDL_RenderCopy(Renderer, textureredshootobjectleft, NULL, &rect3);
                }
            }
        }
    }
}
//绘制怪物
void drawMonster(SDL_Renderer* Renderer,int level) {
    for (int j = 0; j < Maxmonsters; j++) {
        if (monsters[j].active) {
                SDL_Rect rect4 = { monsters[j].x,
                                         monsters[j].y,
                                         Monsterwidth,
                                         Monsterheight };
                
                 if (level == 1) {
                    if (monsters[j].direction == 0) {
                        SDL_RenderCopy(Renderer, texturegreenmonsterleft, NULL, &rect4);
                    }
                    else {
                        SDL_RenderCopy(Renderer, texturegreenmonsterright, NULL, &rect4);
                    }
                }
                else if (level == 2) {
                    if (monsters[j].direction == 0) {
                        SDL_RenderCopy(Renderer, texturesummermonsterleft, NULL, &rect4);
                    }
                    else {
                        SDL_RenderCopy(Renderer, texturesummermonsterright, NULL, &rect4);
                    }
                }
                else if (level == 3) {
                    if (monsters[j].direction == 0) {
                        SDL_RenderCopy(Renderer, textureredmonsterleft, NULL, &rect4);
                    }
                    else {
                        SDL_RenderCopy(Renderer, textureredmonsterright, NULL, &rect4);
                    }
                }
                else if (level == 4) {
                     if (monsters[j].direction == 0) {
                         SDL_RenderCopy(Renderer, texture6, NULL, &rect4);
                     }
                     else {
                         SDL_RenderCopy(Renderer, texture7, NULL, &rect4);
                     }
                 }
        }
    }
}
//绘制坠落物
void drawObjects(SDL_Renderer* Renderer,int level) {
    for (int i = 0; i < MAX_FALLING_OBJECTS; i++) {
        if (!objects[i].active) continue;
        SDL_Rect rect5 = {
            objects[i].x,
            objects[i].y,
            Objectsize,
            Objectsize
        };
        if (level == 1) {
            SDL_RenderCopy(Renderer, texturegreenobject, NULL, &rect5);
        }
        if (level == 2) {
            SDL_RenderCopy(Renderer, texturesummerobject, NULL, &rect5);
        }
        if (level == 3) {
            SDL_RenderCopy(Renderer, textureredobject, NULL, &rect5);
        }
        if (level == 4) {
            SDL_RenderCopy(Renderer, texture8, NULL, &rect5);
        }
    }
}
// 绘制怪物攻击物
void drawMonsterObjects(SDL_Renderer* Renderer) {
    for (int i = 0; i < MAX_MONSTER_OBJECTS; i++) {
        if (!monsterobjects[i].active) continue;

        SDL_Rect rect6 = {
            monsterobjects[i].x,
            monsterobjects[i].y,
            Objectsize,
            Objectsize
        };
        SDL_RenderCopy(Renderer, texture9, NULL, &rect6);
    }
}
//绘制人物血条
void drawHealthBar(SDL_Renderer* Renderer, Player* player)
{
    SDL_Rect Rect[10];
    int x = 10;
    for (int i = 0; i < player->blood; i++) {
        Rect[i] = (SDL_Rect){ x,
                   10,
                  Healthbarsize,
                  Healthbarsize
        };
        x += Healthbarsize;
        SDL_RenderCopy(Renderer, texture10, NULL, &Rect[i]);
    }
}
//绘制分数
void drawPoints(SDL_Renderer* Renderer, Player* player) {
    SDL_Color color = { 0,0,0,255 };
    char textBuffer[100];
    sprintf(textBuffer,"POINT:%d/%d",currentShootedCount,player->score);
    textsurf = TTF_RenderUTF8_Blended(font,textBuffer,color);
    textTexture = SDL_CreateTextureFromSurface(Renderer, textsurf);
    SDL_Rect textRect = {
        width- Pointrwidth - 10,
        10,
    Pointrwidth,
    Pointheight
    };
    SDL_RenderCopy(Renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textsurf);
    SDL_DestroyTexture(textTexture);
}
//渲染
void screenRenderer(Player* player,int level) {
    updateBullet();
    updateMonsters();
    updateObjects();
    updateMonsterObjects(player);
    if(!gaming){
        resetBullet();
        resetMonsters();
        resetObjects();
        resetMonsterObjects();
    }
    checkBulletMonsterCollision(player);
    checkPlayerObjectCollision(player);
    checkPlayerMonsterBulletCollision(player);
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
    drawGround(app.renderer, player,level);
    drawMonster(app.renderer,level);
    drawPlayer(app.renderer, player);
        drawBullet(app.renderer, player,level);
        drawObjects(app.renderer,level);
        drawMonsterObjects(app.renderer);
        drawHealthBar(app.renderer,player);
        drawPoints(app.renderer, player);
    SDL_RenderPresent(app.renderer);
}
//关卡数据
void initNumbers(Player* player,int level) {
    switch (level) {
    case 1: {
        player->blood = 10;
        player->score = 10;
        Monsterwidth = 70;
        Monsterheight = 70;
        Spawninteral = 4000;
        FALLING_OBJECT_SPEED = 10;
        SPAWN_INTERVAL = 2000;   // 坠落物生成间隔（毫秒）
        monsterObjectSpeedMin = 2;
        monsterObjectSpeedAdd = 3;
        break;
    }
    case 2: {
        player->blood = 8;
        player->score = 10;
        Monsterwidth = 70;
        Monsterheight = 80;
        Spawninteral = 3000;
        FALLING_OBJECT_SPEED = 5;
        SPAWN_INTERVAL = 2000;   // 坠落物生成间隔（毫秒）
        monsterObjectSpeedMin = 2;
        monsterObjectSpeedAdd = 3;
        break;
    }
    case 3: {
        player->blood = 7;
        player->score = 15;
        Monsterwidth = 70;
        Monsterheight = 80;
        Spawninteral = 3000;
        FALLING_OBJECT_SPEED = 10;
        SPAWN_INTERVAL = 1000;   // 坠落物生成间隔（毫秒）
        monsterObjectSpeedMin = 4;
        monsterObjectSpeedAdd = 5;
        break;
    }
    case 4: {
        player->blood = 5;
        player->score = 20;
        Monsterwidth = 70;
        Monsterheight = 90;
        Spawninteral = 3000;
        FALLING_OBJECT_SPEED = 10;
        SPAWN_INTERVAL = 400;   // 坠落物生成间隔（毫秒）
        monsterObjectSpeedMin = 5;
        monsterObjectSpeedAdd = 6;
        break;
    }
    default:
        break;
    }
}
//游戏主循环
int loop1()
{
    if (initGame() != 0)
    {
        SDL_Log("初始化失败");
        return -1;
    }
    gaming = 1;
    stage = 1;
    Player *player = (Player *)malloc(sizeof(Player));
    initPlayer(player);
    initNumbers(player, stage);
    currentShootedCount = 0;
    SDL_Event event;
    Uint32 frameStart, frameTime;
    lastMonsterSpawnTime = SDL_GetTicks();
    lastObjectSpawnTime = SDL_GetTicks();
    // 初始化移动状态
    int movingLeft = 0;
    int movingRight = 0;
    const int moveSpeed = 6; // 移动速度
    while (1)
    {
        frameStart = SDL_GetTicks();
        Uint32 currentTime = SDL_GetTicks();
        initMonster();
        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                gaming = 0;
                screenRenderer(player, stage);
                return -1;
            case SDL_WINDOWEVENT:
                if ((event.window.event) == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    initPlayer(player);
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    movingLeft = 1;
                    imageJudge = 1;
                    player->direction = 1;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    movingRight = 1;
                    imageJudge = 0;
                    player->direction = 0;
                }
                else if (event.key.keysym.sym == SDLK_UP)
                {
                    if (isJumping == 0)
                    {
                        speedy = jumpForce;
                        isJumping = 1;
                    }
                    else if (isJumping == 1)
                    {
                        speedy = jumpForce;
                        isJumping = 2;
                    }
                }
                else if (event.key.keysym.sym == SDLK_SPACE)
                {
                    Bullet newBullet;
                    initBullet(player, &newBullet);
                    newBullet.direction = player->direction;
                    if (bulletCount >= bulletCapacity)
                    {
                        bulletCapacity += 50;
                        Bullet *temp = (Bullet *)realloc(bullets, sizeof(Bullet) * bulletCapacity);
                        if (temp)
                            bullets = temp;
                    }
                    if (bulletCount < bulletCapacity)
                    {
                        bullets[bulletCount] = newBullet;
                        bulletCount++;
                    }
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    movingLeft = 0;
                }
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    movingRight = 0;
                }
                break;
            default:
                break;
            }
        }
        if (movingLeft)
        {
            player->x -= moveSpeed;
            if (player->x < 0)
                player->x = 0;
        }
        if (movingRight)
        {
            player->x += moveSpeed;
            if (player->x > width - Playerwidth)
                player->x = width - Playerwidth;
        }

        if (isJumping != 0)
        {
            speedy += gravity;
            player->y += speedy;
            if (player->y >= height - Playerheight - Groundheight)
            {
                player->y = height - Playerheight - Groundheight;
                speedy = 0;
                isJumping = 0;
            }
        }
        // 渲染
        screenRenderer(player, stage);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < 1000 / FPS)
        {
            SDL_Delay(1000 / FPS - frameTime);
        }
        if (currentShootedCount >= player->score || player->blood <= 0)
            break;
    }
    if (currentShootedCount >= player->score)
    {
        gaming = 0;
        screenRenderer(player, stage);
        free(player);
        return 1;
    }
    if (player->blood <= 0)
    {
        gaming = 0;
        screenRenderer(player, stage);
        free(player);
        app.game_state = GAME_STATE_LEVEL1FAIL; // 改为跳转到失败界面
        return 0;
    }
}

int loop2()
{
    if(initGame() != 0)
    {
        SDL_Log("初始化失败");
        return -1;
    }
    gaming = 1;
    stage = 2;
    Player *player = (Player *)malloc(sizeof(Player));
    initPlayer(player);
    initNumbers(player, stage);
    currentShootedCount = 0;
    SDL_Event event;
    Uint32 frameStart, frameTime;
    lastMonsterSpawnTime = SDL_GetTicks();
    lastObjectSpawnTime = SDL_GetTicks();
    // 初始化移动状态
    int movingLeft = 0;
    int movingRight = 0;
    const int moveSpeed = 6; // 移动速度
    while (1)
    {
        frameStart = SDL_GetTicks();
        Uint32 currentTime = SDL_GetTicks();
        spawnObject();
        initMonster();
        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                gaming = 0;
                screenRenderer(player, stage);
                return -1;
            case SDL_WINDOWEVENT:
                if ((event.window.event) == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    initPlayer(player);
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    movingLeft = 1;
                    imageJudge = 1;
                    player->direction = 1;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    movingRight = 1;
                    imageJudge = 0;
                    player->direction = 0;
                }
                else if (event.key.keysym.sym == SDLK_UP)
                {
                    if (isJumping == 0)
                    {
                        speedy = jumpForce;
                        isJumping = 1;
                    }
                    else if (isJumping == 1)
                    {
                        speedy = jumpForce;
                        isJumping = 2;
                    }
                }
                else if (event.key.keysym.sym == SDLK_SPACE)
                {
                    Bullet newBullet;
                    initBullet(player, &newBullet);
                    newBullet.direction = player->direction;
                    if (bulletCount >= bulletCapacity)
                    {
                        bulletCapacity += 50;
                        Bullet *temp = (Bullet *)realloc(bullets, sizeof(Bullet) * bulletCapacity);
                        if (temp)
                            bullets = temp;
                    }
                    if (bulletCount < bulletCapacity)
                    {
                        bullets[bulletCount] = newBullet;
                        bulletCount++;
                    }
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    movingLeft = 0;
                }
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    movingRight = 0;
                }
                break;
            default:
                break;
            }
        }
        if (movingLeft)
        {
            player->x -= moveSpeed;
            if (player->x < 0)
                player->x = 0;
        }
        if (movingRight)
        {
            player->x += moveSpeed;
            if (player->x > width - Playerwidth)
                player->x = width - Playerwidth;
        }

        if (isJumping != 0)
        {
            speedy += gravity;
            player->y += speedy;
            if (player->y >= height - Playerheight - Groundheight)
            {
                player->y = height - Playerheight - Groundheight;
                speedy = 0;
                isJumping = 0;
            }
        }
        // 渲染
        screenRenderer(player, stage);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < 1000 / FPS)
        {
            SDL_Delay(1000 / FPS - frameTime);
        }
        if (currentShootedCount >= player->score || player->blood <= 0)
            break;
    }
        if (currentShootedCount >= player->score)
        {
            gaming= 0;
            screenRenderer(player, stage);
            free(player);
            return 1;
        }
        if (player->blood <= 0)
        {
            gaming= 0;
            screenRenderer(player, stage);
            free(player);
            app.game_state = GAME_STATE_LEVEL2FAIL;  // 改为跳转到失败界面
            return 0;
        }
    }
int loop3()
{
       if(initGame() != 0)
    {
        SDL_Log("初始化失败");
        return -1;
    }
    gaming=1;
    stage = 3;
    Player *player = (Player *)malloc(sizeof(Player));
    initPlayer(player);
    initNumbers(player, stage);
    currentShootedCount = 0;
    SDL_Event event;
    Uint32 frameStart, frameTime;
    lastMonsterSpawnTime = SDL_GetTicks();
    lastObjectSpawnTime = SDL_GetTicks();
    // 初始化移动状态
    int movingLeft = 0;
    int movingRight = 0;
    const int moveSpeed = 6; // 移动速度
    while (1)
    {
        frameStart = SDL_GetTicks();
        Uint32 currentTime = SDL_GetTicks();
        spawnObject();
        initMonster();
        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                gaming = 0;
                screenRenderer(player, stage);
                return -1;
            case SDL_WINDOWEVENT:
                if ((event.window.event) == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    initPlayer(player);
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    movingLeft = 1;
                    imageJudge = 1;
                    player->direction = 1;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    movingRight = 1;
                    imageJudge = 0;
                    player->direction = 0;
                }
                else if (event.key.keysym.sym == SDLK_UP)
                {
                    if (isJumping == 0)
                    {
                        speedy = jumpForce;
                        isJumping = 1;
                    }
                    else if (isJumping == 1)
                    {
                        speedy = jumpForce;
                        isJumping = 2;
                    }
                }
                else if (event.key.keysym.sym == SDLK_SPACE)
                {
                    Bullet newBullet;
                    initBullet(player, &newBullet);
                    newBullet.direction = player->direction;
                    if (bulletCount >= bulletCapacity)
                    {
                        bulletCapacity += 50;
                        Bullet *temp = (Bullet *)realloc(bullets, sizeof(Bullet) * bulletCapacity);
                        if (temp)
                            bullets = temp;
                    }
                    if (bulletCount < bulletCapacity)
                    {
                        bullets[bulletCount] = newBullet;
                        bulletCount++;
                    }
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    movingLeft = 0;
                }
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    movingRight = 0;
                }
                break;
            default:
                break;
            }
        }
        if (movingLeft)
        {
            player->x -= moveSpeed;
            if (player->x < 0)
                player->x = 0;
        }
        if (movingRight)
        {
            player->x += moveSpeed;
            if (player->x > width - Playerwidth)
                player->x = width - Playerwidth;
        }

        if (isJumping != 0)
        {
            speedy += gravity;
            player->y += speedy;
            if (player->y >= height - Playerheight - Groundheight)
            {
                player->y = height - Playerheight - Groundheight;
                speedy = 0;
                isJumping = 0;
            }
        }
        // 渲染
        screenRenderer(player, stage);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < 1000 / FPS)
        {
            SDL_Delay(1000 / FPS - frameTime);
        }
        if (currentShootedCount >= player->score || player->blood <= 0)
            break;
    }
        if (currentShootedCount >= player->score)
        {
            gaming= 0;
            screenRenderer(player, stage);
            free(player);
            return 1;
        }
        if (player->blood <= 0)
        {
            gaming= 0;
            screenRenderer(player, stage);
            free(player);
            app.game_state = GAME_STATE_LEVEL3FAIL;  // 改为跳转到失败界面
            return 0;
        }
    }

int loop4()
{
       if(initGame() != 0)
    {
        SDL_Log("初始化失败");
        return -1;
    }
    gaming=1;
    stage = 4;
    Player *player = (Player *)malloc(sizeof(Player));
    initPlayer(player);
    initNumbers(player, stage);
    currentShootedCount = 0;
    SDL_Event event;
    Uint32 frameStart, frameTime;
    lastMonsterSpawnTime = SDL_GetTicks();
    lastObjectSpawnTime = SDL_GetTicks();
    // 初始化移动状态
    int movingLeft = 0;
    int movingRight = 0;
    const int moveSpeed = 6; // 移动速度
    while (1)
    {
        frameStart = SDL_GetTicks();
        Uint32 currentTime = SDL_GetTicks();
        spawnObject();
        initMonster();
        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                gaming = 0;
                screenRenderer(player, stage);
                return -1;
            case SDL_WINDOWEVENT:
                if ((event.window.event) == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    initPlayer(player);
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    movingLeft = 1;
                    imageJudge = 1;
                    player->direction = 1;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    movingRight = 1;
                    imageJudge = 0;
                    player->direction = 0;
                }
                else if (event.key.keysym.sym == SDLK_UP)
                {
                    if (isJumping == 0)
                    {
                        speedy = jumpForce;
                        isJumping = 1;
                    }
                    else if (isJumping == 1)
                    {
                        speedy = jumpForce;
                        isJumping = 2;
                    }
                }
                else if (event.key.keysym.sym == SDLK_SPACE)
                {
                    Bullet newBullet;
                    initBullet(player, &newBullet);
                    newBullet.direction = player->direction;
                    if (bulletCount >= bulletCapacity)
                    {
                        bulletCapacity += 50;
                        Bullet *temp = (Bullet *)realloc(bullets, sizeof(Bullet) * bulletCapacity);
                        if (temp)
                            bullets = temp;
                    }
                    if (bulletCount < bulletCapacity)
                    {
                        bullets[bulletCount] = newBullet;
                        bulletCount++;
                    }
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    movingLeft = 0;
                }
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    movingRight = 0;
                }
                break;
            default:
                break;
            }
        }
        if (movingLeft)
        {
            player->x -= moveSpeed;
            if (player->x < 0)
                player->x = 0;
        }
        if (movingRight)
        {
            player->x += moveSpeed;
            if (player->x > width - Playerwidth)
                player->x = width - Playerwidth;
        }

        if (isJumping != 0)
        {
            speedy += gravity;
            player->y += speedy;
            if (player->y >= height - Playerheight - Groundheight)
            {
                player->y = height - Playerheight - Groundheight;
                speedy = 0;
                isJumping = 0;
            }
        }
        
    //渲染
        screenRenderer(player, stage);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < 1000 / FPS)
        {
            SDL_Delay(1000 / FPS - frameTime);
        }
        if (currentShootedCount >= player->score || player->blood <= 0)
            break;
    }
        if (currentShootedCount >= player->score)
        {
            gaming= 0;
            screenRenderer(player, stage);
            free(player);
            return 1;
        }
        if (player->blood <= 0)
        {
            gaming= 0;
            screenRenderer(player, stage);
            free(player);
            app.game_state = GAME_STATE_LEVEL4FAIL;  // 改为跳转到失败界面
            return 0;
        }
    }

// 释放资源
void clear() {
    SDL_DestroyTexture(texturebackgrandsummer);
    SDL_DestroyTexture(texturesummermonsterright);
    SDL_DestroyTexture(texturesummermonsterleft);
    SDL_DestroyTexture(texturesummerobject);
    SDL_DestroyTexture(texturebackgrandgreen);
    SDL_DestroyTexture(texturegreenmonsterright);
    SDL_DestroyTexture(texturegreenmonsterleft);
    SDL_DestroyTexture(texturegreenobject);
    SDL_DestroyTexture(texturegreenshootobjectright);
    SDL_DestroyTexture(texturegreenshootobjectleft);
    SDL_DestroyTexture(texturebackgrandred );
    SDL_DestroyTexture(textureredmonsterright);
    SDL_DestroyTexture(textureredmonsterleft);
    SDL_DestroyTexture(textureredobject);
    SDL_DestroyTexture(textureredshootobjectright);
    SDL_DestroyTexture(textureredshootobjectleft);
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(texture10);
    SDL_DestroyTexture(texture9);
    SDL_DestroyTexture(texture8);
    SDL_DestroyTexture(texture7);
    SDL_DestroyTexture(texture6);
    SDL_DestroyTexture(texture5);
    SDL_DestroyTexture(texture4);
    SDL_DestroyTexture(texture3);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture1);
    SDL_FreeSurface(imagebackgrandsummer);
    SDL_FreeSurface(imagesummermonsterright);
    SDL_FreeSurface(imagesummermonsterleft);
    SDL_FreeSurface(imagesummerobject);
    SDL_FreeSurface(imagebackgrandgreen);
    SDL_FreeSurface(imagegreenmonsterright);
    SDL_FreeSurface(imagegreenmonsterleft);
    SDL_FreeSurface(imagegreenobject);
    SDL_FreeSurface(imagegreenshootobjectright);
    SDL_FreeSurface(imagegreenshootobjectleft);
    SDL_FreeSurface(imagebackgrandred);
    SDL_FreeSurface(imageredmonsterright);
    SDL_FreeSurface(imageredmonsterleft);
    SDL_FreeSurface(imageredobject);
    SDL_FreeSurface(imageredshootobjectright);
    SDL_FreeSurface(imageredshootobjectleft);
    SDL_FreeSurface(textsurf);
    SDL_FreeSurface(bmpsurf10);
    SDL_FreeSurface(bmpsurf9);
    SDL_FreeSurface(bmpsurf8);
    SDL_FreeSurface(bmpsurf7);
    SDL_FreeSurface(bmpsurf6);
    SDL_FreeSurface(bmpsurf5);
    SDL_FreeSurface(bmpsurf4);
    SDL_FreeSurface(bmpsurf3);
    SDL_FreeSurface(bmpsurf2);
    SDL_FreeSurface(bmpsurf1);
    SDL_FreeSurface(surf);
    // 释放子弹数组
    if (bullets) {
        free(bullets);
        bullets = NULL;
    }

}