#ifndef __CDPROCESS_H__
#define __CDPROCESS_H__

#include"main.h"
#include"gamemain.h"
#include"cdflame.h"

enum hanbetu{
	P, E
};

void move();
BOOL CheckEnd(int);
void CheckScroll(int);
void DrawBullet(int);/*1�̎����@/2�̎��G�@1/3�̎��G�@2/4�̎��G�@3*/

extern float scrolly;

#endif