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
int jumpForce = -18;//���ٶ�
int lineForce = 10;
int speedx = 0;//�ٶ�
int speedy = 0;
int gravity = 1;
int imageJudge = 0;
int isRightWalking = 0;
int isLeftWalking = 0;
int isJumping = 0;
int direction = 0;//�ж�����Ϊ��
int shootSpeed = 10;
Bullet* bullets = NULL;
int bulletCount = 0;//��ǰ�ӵ�����
int bulletCapacity = 0;//����������
Monster monsters[Maxmonsters];
Uint32 lastMonsterSpawnTime = 0;
int monsterSpeed = 2;
int disappearJudge = 0;
Object objects[MAX_FALLING_OBJECTS];    // ׹��������
int objectCount;        // ��ǰ׹��������
Monsterobject monsterobjects[MAX_MONSTER_OBJECTS];    // ���﹥��������
int bulletObjectCount;        // ��ǰ���﹥��������
Uint32 lastObjectSpawnTime;   // �ϴ�����׹�����ʱ��
int currentShootedCount = 0;  //��ǰ���й�������
int stage = 0;//�ؿ�
int gaming = 0;//��Ϸ״̬
int monsterObjectSpeedMin = 0;
int monsterObjectSpeedAdd = 0;
int Monsterwidth = 0;
int Monsterheight = 0;
int Spawninteral = 3000;
int FALLING_OBJECT_SPEED = 10;
int SPAWN_INTERVAL = 1000;   // ׹�������ɼ�������룩

//��ʼ����Ϸ
int initGame()
{    
    srand(time(NULL));
    //��������
    font = TTF_OpenFont("../material/STXINWEI.TTF",40);
    if (!font) {
        printf(" TTF_OpenFontʧ��: %s\n", TTF_GetError());
    }
    //4.����image
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_img ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    //5.����ͼƬ
    bmpsurf1 = IMG_Load("../material/character_Right.png ");
    if (bmpsurf1 == NULL) {
        printf("SDL_img1 ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf2 = IMG_Load("../material/character_Left.png ");
    if (bmpsurf2 == NULL) {
        printf("SDL_img2 ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf3 = SDL_LoadBMP("../material/background4.bmp");
    if (bmpsurf3 == NULL) {
        printf("SDL_img3 ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf4 = IMG_Load("../material/91.png");
    if (bmpsurf4 == NULL) {
        printf("SDL_img4 ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf5 = IMG_Load("../material/92.png");
    if (bmpsurf5 == NULL) {
        printf("SDL_img5 ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf6 = IMG_Load("../material/93.png");
    if (bmpsurf6 == NULL) {
        printf("SDL_img6 ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf7 = IMG_Load("../material/94.png");
    if (bmpsurf7 == NULL) {
        printf("SDL_img7 ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf8 = IMG_Load("../material/95.png");
    if (bmpsurf8 == NULL) {
        printf("SDL_img8 ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf9 = IMG_Load("../material/96.png");
    if (bmpsurf9 == NULL) {
        printf("SDL_img9 ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bmpsurf10 = IMG_Load("../material/97.png");
    if (bmpsurf10 == NULL) {
        printf("SDL_img10 ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagebackgrandgreen = SDL_LoadBMP("../material/background1.bmp");
    if (imagebackgrandgreen == NULL) {
        printf("SDL_imagebackgrandgreen ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagegreenmonsterright = IMG_Load("../material/greenright.png");
    if (imagegreenmonsterright == NULL) {
        printf("SDL_imagegreenmonsterright ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagegreenmonsterleft = IMG_Load("../material/greenleft.png");
    if (imagegreenmonsterleft == NULL) {
        printf("SDL_imagegreenmonsterleft ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagegreenobject = IMG_Load("../material/greenobject.png");
    if (imagegreenobject == NULL) {
        printf("SDL_imagegreenobject ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagegreenshootobjectright = IMG_Load("../material/greenshootright.png");
    if (imagegreenshootobjectright == NULL) {
        printf("SDL_imagegreenshootobjectright ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagegreenshootobjectleft = IMG_Load("../material/greenshootleft.png");
    if (imagegreenshootobjectleft == NULL) {
        printf("SDL_imagegreenshootobjectleft ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagebackgrandred = SDL_LoadBMP("../material/background3.bmp");
    if (imagebackgrandred == NULL) {
        printf("SDL_imagebackgrandred ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imageredmonsterright = IMG_Load("../material/redright.png");
    if (imageredmonsterright == NULL) {
        printf("SDL_imageredmonsterright ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imageredmonsterleft = IMG_Load("../material/redleft.png");
    if (imageredmonsterleft == NULL) {
        printf("SDL_imageredmonsterleft ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imageredobject = IMG_Load("../material/redobject.png");
    if (imageredobject == NULL) {
        printf("SDL_imageredobject ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imageredshootobjectright = IMG_Load("../material/redshootright.png");
    if (imageredshootobjectright == NULL) {
        printf("SDL_imageredshootobjectright ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imageredshootobjectleft = IMG_Load("../material/redshootleft.png");
    if (imagegreenshootobjectright == NULL) {
        printf("SDL_imageredshootobjectleft ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagebackgrandsummer = SDL_LoadBMP("../material/background2.bmp");
    if (imagebackgrandsummer == NULL) {
        printf("SDL_imagebackgrandsummer ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagesummermonsterright = IMG_Load("../material/summerright.png");
    if (imagesummermonsterright == NULL) {
        printf("SDL_imagesummermonsterright ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagesummermonsterleft = IMG_Load("../material/summerleft.png");
    if (imagesummermonsterleft == NULL) {
        printf("SDL_imagesummermonsterleft ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    imagesummerobject = IMG_Load("../material/summerobject.png");
    if (imagesummerobject == NULL) {
        printf("SDL_imagesummerobject ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    //6.����texture
    texture1 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf1);
    if (texture1 == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture2 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf2);
    if (texture2 == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture3 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf3);
    if (texture3 == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture4 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf4);
    if (texture4 == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture5 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf5);
    if (texture5 == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture6 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf6);
    if (texture6 == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture7 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf7);
    if (texture7 == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture8 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf8);
    if (texture8 == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture9 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf9);
    if (texture9 == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texture10 = SDL_CreateTextureFromSurface(app.renderer, bmpsurf10);
    if (texture10 == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturebackgrandgreen = SDL_CreateTextureFromSurface(app.renderer, imagebackgrandgreen);
    if (texturebackgrandgreen == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturegreenmonsterright = SDL_CreateTextureFromSurface(app.renderer, imagegreenmonsterright);
    if (texturegreenmonsterright == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturegreenmonsterleft = SDL_CreateTextureFromSurface(app.renderer, imagegreenmonsterleft);
    if (texturegreenmonsterleft == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturegreenobject = SDL_CreateTextureFromSurface(app.renderer, imagegreenobject);
    if (texturegreenobject == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturegreenshootobjectright = SDL_CreateTextureFromSurface(app.renderer, imagegreenshootobjectright);
    if (texturegreenshootobjectright == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturegreenshootobjectleft = SDL_CreateTextureFromSurface(app.renderer, imagegreenshootobjectleft);
    if (texturegreenshootobjectleft == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturebackgrandred = SDL_CreateTextureFromSurface(app.renderer, imagebackgrandred);
    if (texturebackgrandred == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    textureredmonsterright = SDL_CreateTextureFromSurface(app.renderer, imageredmonsterright);
    if (textureredmonsterright == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    textureredmonsterleft = SDL_CreateTextureFromSurface(app.renderer, imageredmonsterleft);
    if (textureredmonsterleft == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    textureredobject = SDL_CreateTextureFromSurface(app.renderer, imageredobject);
    if (textureredobject == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    textureredshootobjectright = SDL_CreateTextureFromSurface(app.renderer, imageredshootobjectright);
    if (textureredshootobjectright == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    textureredshootobjectleft = SDL_CreateTextureFromSurface(app.renderer, imageredshootobjectleft);
    if (textureredshootobjectleft == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturebackgrandsummer = SDL_CreateTextureFromSurface(app.renderer, imagebackgrandsummer);
    if (texturebackgrandsummer == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturesummermonsterright = SDL_CreateTextureFromSurface(app.renderer, imagesummermonsterright);
    if (texturesummermonsterright == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturesummermonsterleft = SDL_CreateTextureFromSurface(app.renderer, imagesummermonsterleft);
    if (texturesummermonsterleft == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    texturesummerobject = SDL_CreateTextureFromSurface(app.renderer, imagesummerobject);
    if (texturesummerobject == NULL) {
        printf("SDL_CreateTextureFromSurface ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bullets = NULL;
    bulletCount = 0;
    bulletCapacity = 0;
    return 0;
}
//��ʼ�����
void initPlayer(Player* player) {
    int w, h = 0;
    SDL_GetWindowSize(app.window,&w,&h);
    player->x = w/2 - Playerwidth/2;
    player->y = h - Playerheight-Groundheight;
    player->direction = 0;
    player->blood = 10;
    player->score = 10;
}
//��ʼ���ӵ�
void initBullet(Player* player, Bullet* bullet_test) {
    bullet_test->x = player->x + Playerwidth / 2;
    bullet_test->y = player->y + (int)Playerheight /3;
    bullet_test->active = 1;
    bullet_test->direction = player->direction;
}
// ��������ʱ����ҷ����ӵ�
void spawnMonsterBullet(int monsterX, int monsterY,Player* player) {
    // Ѱ�ҿ��е��ӵ���λ
    for (int i = 0; i < MAX_MONSTER_OBJECTS; i++) {
        if (!monsterobjects[i].active) {
            monsterobjects[i].x = monsterX;
            monsterobjects[i].y = monsterY + Monsterheight / 2;  // �ӹ����м䷢��

            // ����ٶ� (3-8)
            monsterobjects[i].speed = monsterObjectSpeedMin + rand() % monsterObjectSpeedAdd;

            // ������� (0=��, 1=��)
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
//���ɹ���
void initMonster() {
    Uint32 currentTime = SDL_GetTicks();
    // ����Ƿ�������ʱ��
    if (currentTime - lastMonsterSpawnTime < Spawninteral) {
        return;
    }
    // ���ҿ��еĹ����
    for (int i = 0; i < Maxmonsters; i++) {
        if (!monsters[i].active) {
            // �����������໹���Ҳ�����
            int fromLeft = rand() % 2;

            if (fromLeft) {
                // ��������ɣ������ƶ�
                monsters[i].x = -Monsterwidth;
                monsters[i].direction = 0;
            }
            else {
                // ���Ҳ����ɣ������ƶ�
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
// ������ײ��⺯��
int checkCollision(int x1, int y1, int w1, int h1,
    int x2, int y2, int w2, int h2) 
{
    return (x1 < x2 + w2 &&
        x1 + w1 > x2 &&
        y1 < y2 + h2 &&
        y1 + h1 > y2);
}
//�������ӵ���ײ
void checkBulletMonsterCollision(Player* player) {
    for (int i = 0; i < bulletCount; i++) {
        if (!bullets[i].active) continue;

        for (int j = 0; j <Maxmonsters; j++) {
            if (!monsters[j].active) continue;

            // �����ײ
            if (checkCollision(
                bullets[i].x, bullets[i].y, Bulletwidth, Bulletheight,
                monsters[j].x, monsters[j].y, Monsterwidth, Monsterheight)) {
                //���﷢���ӵ�
                spawnMonsterBullet(monsters[j].x, monsters[j].y,player);
                // ��ײ���� - ���߶���ʧ
                bullets[i].active = 0;
                monsters[j].active = 0;
                //���м�һ
                currentShootedCount++;
                break; // һ���ӵ�ֻ�ܻ���һ������
            }
        }
    }
}
//���׹���������ײ
void checkPlayerObjectCollision(Player* player) {
    for (int i = 0; i < MAX_FALLING_OBJECTS; i++) {
        if (!objects[i].active) continue;

        // �����ײ
        if (checkCollision(
            player->x, player->y, Playerwidth, Playerheight,
            objects[i].x, objects[i].y, Objectsize, Objectsize)) {
            // �Ƴ�׹����
            objects[i].active = 0;
            // ����ֵ���ٵ��߼�
            player->blood--;

        }
    }
}
// ������������ӵ�����ײ
void checkPlayerMonsterBulletCollision(Player* player) {
    for (int i = 0; i < MAX_MONSTER_OBJECTS; i++) {
        if (!monsterobjects[i].active) continue;

        if (checkCollision(
            player->x, player->y, Playerwidth, Playerheight,
            monsterobjects[i].x, monsterobjects[i].y, Objectsize, Objectsize)) {

            // ��������߼�
            // (��������������ֵ���ٵ�Ч��)
            player->blood--;
            // �Ƴ��ӵ�
            monsterobjects[i].active = 0;
            bulletObjectCount--;
        }
    }
}
// �����µ�׹����
void spawnObject() {
    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - lastObjectSpawnTime < SPAWN_INTERVAL) {
        return;
    }

    for (int i = 0; i < MAX_FALLING_OBJECTS; i++) {
        if (!objects[i].active) {
            // ����Ļ�������λ������
            objects[i].x = rand() % (width - Objectsize);
            objects[i].y = -Objectsize;

            // ����ٶ�
            objects[i].speed = FALLING_OBJECT_SPEED;

            objects[i].active = 1;
            objects[i].spawnTime = currentTime;
            lastObjectSpawnTime = currentTime;
            break;
        }
    }
}
//�����ӵ�λ��
void updateBullet() {
    // �޸��ӵ������߼�
    int i = 0;
    while (i < bulletCount) {
        if (!bullets[i].active) {
            // �Ƴ�ʧЧ���ӵ�
            bullets[i] = bullets[bulletCount - 1];
            bulletCount--;
            continue;
        }
        Bullet* bullet = &bullets[i];
        if (bullet->direction == 0) {
            bullet->x += shootSpeed;
            if (bullet->x > width) {
                // ��ȫ�Ƴ��ӵ�
                bullets[i] = bullets[bulletCount - 1];
                bulletCount--;
                continue; // ������i�������������Ƶ���ǰλ�õ��ӵ�
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
        i++; // ֻ��δ�Ƴ��ӵ�ʱ����������
    }
}
//�����ӵ�λ��
void resetBullet() {
    for (int i = 0; i < bulletCount; i++) {
        bullets[i].active = 0;
        bullets[i].x = -Bulletwidth;
        bullets[i].y = -Bulletheight;
    }
}
// ���¹���λ��
void updateMonsters() {
    for (int j = 0; j < Maxmonsters; j++) {
        if (monsters[j].active) {
            if (monsters[j].direction == 0) {
                // �����ƶ�
                monsters[j].x += monsterSpeed;
                // ����Ƿ񳬳���Ļ
                if (monsters[j].x > width) {
                    monsters[j].active = 0;
                }
            }
            else {
                // �����ƶ�
                monsters[j].x -= monsterSpeed;
                // ����Ƿ񳬳���Ļ
                if (monsters[j].x < -Monsterwidth) {
                    monsters[j].active = 0;
                }
            }
        }
    }
}
//���ù���λ��
void resetMonsters() {
    for (int i = 0; i < Maxmonsters; i++) {
        monsters[i].active = 0;
        monsters[i].x = -Bulletwidth;
        monsters[i].y = -Bulletheight;
    }
}
// ����׹����λ��
void updateObjects() {
    for (int i = 0; i < MAX_FALLING_OBJECTS; i++) {
        if (objects[i].active) {
            // ��ֱ����
            objects[i].y += objects[i].speed;

            // ���׹�����䵽�������£����Ϊ����Ծ
            if (objects[i].y > height) {
                objects[i].active = 0;
            }
        }
    }
}
//����׹����λ��
void resetObjects() {
    for (int i = 0; i < MAX_FALLING_OBJECTS; i++) {
        objects[i].active = 0;
        objects[i].x = -Objectsize;
        objects[i].y = -Objectsize;
    }
}
// ���¹��﹥����λ��
void updateMonsterObjects(Player* player) {
    for (int i = 0; i < MAX_MONSTER_OBJECTS; i++) {
        if (!monsterobjects[i].active) continue;

        // ���ݷ����ƶ�
        if (monsterobjects[i].direction == 0) {
            monsterobjects[i].x += monsterobjects[i].speed;  // �����ƶ�
        }
        else {
            monsterobjects[i].x -= monsterobjects[i].speed;  // �����ƶ�
        }

        // ����Ƿ񳬳���Ļ
        if (monsterobjects[i].x < -Objectsize ||
            monsterobjects[i].x > width) {
            monsterobjects[i].active = 0;
            bulletObjectCount--;
        }
    }
}
//���ù��﹥����λ��
void resetMonsterObjects() {
    for (int i = 0; i < MAX_MONSTER_OBJECTS; i++) {
        monsterobjects[i].active = 0;
        monsterobjects[i].x = -Objectsize;
        monsterobjects[i].y = -Objectsize;
    }
}
//�������
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
//���Ƶ���
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
//�����ӵ�
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
//���ƹ���
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
//����׹����
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
// ���ƹ��﹥����
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
//��������Ѫ��
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
//���Ʒ���
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
//��Ⱦ
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
//�ؿ�����
void initNumbers(Player* player,int level) {
    switch (level) {
    case 1: {
        player->blood = 10;
        player->score = 10;
        Monsterwidth = 70;
        Monsterheight = 70;
        Spawninteral = 4000;
        FALLING_OBJECT_SPEED = 10;
        SPAWN_INTERVAL = 2000;   // ׹�������ɼ�������룩
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
        SPAWN_INTERVAL = 2000;   // ׹�������ɼ�������룩
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
        SPAWN_INTERVAL = 1000;   // ׹�������ɼ�������룩
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
        SPAWN_INTERVAL = 400;   // ׹�������ɼ�������룩
        monsterObjectSpeedMin = 5;
        monsterObjectSpeedAdd = 6;
        break;
    }
    default:
        break;
    }
}
//��Ϸ��ѭ��
int loop1()
{
    if (initGame() != 0)
    {
        SDL_Log("��ʼ��ʧ��");
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
    // ��ʼ���ƶ�״̬
    int movingLeft = 0;
    int movingRight = 0;
    const int moveSpeed = 6; // �ƶ��ٶ�
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
        // ��Ⱦ
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
        app.game_state = GAME_STATE_LEVEL1FAIL; // ��Ϊ��ת��ʧ�ܽ���
        return 0;
    }
}

int loop2()
{
    if(initGame() != 0)
    {
        SDL_Log("��ʼ��ʧ��");
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
    // ��ʼ���ƶ�״̬
    int movingLeft = 0;
    int movingRight = 0;
    const int moveSpeed = 6; // �ƶ��ٶ�
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
        // ��Ⱦ
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
            app.game_state = GAME_STATE_LEVEL2FAIL;  // ��Ϊ��ת��ʧ�ܽ���
            return 0;
        }
    }
int loop3()
{
       if(initGame() != 0)
    {
        SDL_Log("��ʼ��ʧ��");
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
    // ��ʼ���ƶ�״̬
    int movingLeft = 0;
    int movingRight = 0;
    const int moveSpeed = 6; // �ƶ��ٶ�
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
        // ��Ⱦ
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
            app.game_state = GAME_STATE_LEVEL3FAIL;  // ��Ϊ��ת��ʧ�ܽ���
            return 0;
        }
    }

int loop4()
{
       if(initGame() != 0)
    {
        SDL_Log("��ʼ��ʧ��");
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
    // ��ʼ���ƶ�״̬
    int movingLeft = 0;
    int movingRight = 0;
    const int moveSpeed = 6; // �ƶ��ٶ�
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
        
    //��Ⱦ
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
            app.game_state = GAME_STATE_LEVEL4FAIL;  // ��Ϊ��ת��ʧ�ܽ���
            return 0;
        }
    }

// �ͷ���Դ
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
    // �ͷ��ӵ�����
    if (bullets) {
        free(bullets);
        bullets = NULL;
    }

}