#ifndef __CDFLAME_H__
#define __CDFLAME_H__

#include<DxLib.h>
#include<stdio.h>
#include"cdprocess.h"

enum ATKtype{
	red = 1, blue = 2, green = 3, beam = 4
};

struct Data{
	float SBP;/*弾が最初に出た場所*/
	float x; /*横軸*/
	float y; /*縦軸*/
	BOOL living; /*存在証明*/
	int type; /*属性の切り替え*/
	float movement; /*移動量*/
	int BULLET_IMAGE;/*弾の画像*/
	int time;/*クールタイム*/
};

struct Charadata{
	float x;/*横軸*/
	float y;/*縦軸*/
	int SC_Hosei;/*スクロール前に発生したY軸の変更によって発生する相違を補正する*/
	int LIFE;/*最大被弾回数*/
	float movement;/*移動量*/
	BOOL ScrollUpper;/*上方向へのスクロール可否*/
	BOOL ScrollBelow;/*下方向へのスクロール可否*/
	int type;/*属性の切り替え*/
	BOOL living;/*存在証明*/
	Data BULLET[20];/*自機/敵機の弾*/
	int StageNum;/*コンティニューする際のステージナンバーの記録*/
	int IMGH[4][12];/*自機の画像*/
};

struct CharaData{
	int enemy_type;/*1 2 3パターン*/
	float x;/*横軸*/
	float y;/*縦軸*/
	int LIFE;/*最大被弾回数*/
	float movement;/*移動量*/
	int type;/*属性の切り替え*/
	BOOL living;/*存在証明*/
	Data BULLET[20];/*自機/敵機の弾*/
	int IMG1[2];/*雑魚的の画像もしくはボスの前部分専用*/
	int IMG2[4];/*ボスの後ろ部分専用*/
};

extern Charadata HERO;
extern CharaData ENEMY[10];
extern CharaData STAGEBOSS;

extern int hx,ex;
extern int hy,ey;
extern int KEY_KAISU;

extern int g_last_bullet;

void syokika();
void Init_ENEMY1(int, int, int);
void Init_ENEMY2(int, int, int);
void Init_ENEMY3(int, int, int);
void Init_BOSS(int, int, int);
void SET_PLAYER_BULLET();

#endif