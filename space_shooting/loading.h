#ifndef __LOADING_H__
#define __LOADING_H__

#include<DxLib.h>

enum youso
{
	enemy1 = 1,enemy2,enemy3,player,boss
};

extern int G_IMGhandle[10][13];
extern int field;
extern int gif[4][12];
extern int BOSS;
extern int TITLE;
extern int GAMEOVER;
extern int BULLET[4];

BOOL IMGhandle();
BOOL InitBulletImage(int);

#endif