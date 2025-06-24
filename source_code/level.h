#pragma once
#ifndef PIXEL_MAN_H
#define PIXEL_MAN_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
typedef struct {
	Uint8 r, g, b, a;
}Color;
typedef struct {
	int x, y;
	int direction;
	int blood;
	int score;
}Player;
typedef struct {
	int x, y;
	int direction;
	int active;
} Bullet;
typedef struct {
	int x, y;
	int direction;
	int active;
	int speed;
} Monsterobject;
typedef struct {
	int x, y;
	int direction;
	int active;
} Monster;
typedef struct {
	int x, y;
	int direction;
	int speed;
	int active;
	Uint32 spawnTime;
} Object;
//��ʼ����Ϸ
int initGame();
//��ѭ��
int loop1();
int loop2();
int loop3();
int loop4();
//�������
void clear();
#endif  // PIXEL_MAN_H