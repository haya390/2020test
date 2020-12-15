#include"loading.h"
#include"cdflame.h"
#include<string.h>

int G_IMGhandle[10][13];
int TITLE;
int GAMEOVER;
int field;
int BULLET[4];

Charadata HERO;
CharaData ENEMY[10];
CharaData STAGEBOSS;

BOOL IMGhandle(){

	

	/*タイトル画像の読み込み*/
	TITLE = LoadGraph("media\\GameEndImg\\タイトル.png");
	if (TITLE == -1)return FALSE;

	/*ゲーム本編の背景画像*/
	field = LoadGraph("media\\stagedata\\背景(ステージ1).png");

	/*ゲームオーバー画像の読み込み*/
	GAMEOVER = LoadGraph("media\\GameEndImg\\ゲームオーバー画面.png");

	/*弾の読み込み*/
	BULLET[0] = LoadGraph("media\\弾\\属性弾(赤) 候補1.png");
	if (BULLET[0] == -1)return FALSE;
	BULLET[1] = LoadGraph("media\\弾\\属性弾(青) 候補3.png");
	if (BULLET[1] == -1)return FALSE;
	BULLET[2] = LoadGraph("media\\弾\\属性弾(緑) 候補1.png");
	if (BULLET[2] == -1)return FALSE;
	BULLET[3] = LoadGraph("media\\弾\\レーザー 自機専用.png");
	if (BULLET[3] == -1)return FALSE;

	/*敵機の画像読み込み（雑魚）*/
	for (int i = 0 , soeji = 1; i < 13; i++,soeji++){
		
		char red[50], blue[50], green[50];
		sprintf_s(red, "media\\赤\\%d.プレ―ン(赤).png", soeji);
		sprintf_s(blue, "media\\青\\%d.プレ―ン(青).png", soeji);
		sprintf_s(green, "media\\緑\\%d.プレ―ン(緑).png", soeji);

		G_IMGhandle[enemy1][i] = LoadGraph(red,soeji);
		if (G_IMGhandle[enemy1][i] == -1)return FALSE;
		G_IMGhandle[enemy2][i] = LoadGraph(blue,soeji);
		if (G_IMGhandle[enemy2][i] == -1)return FALSE;
		G_IMGhandle[enemy3][i] = LoadGraph(green,soeji);
		if (G_IMGhandle[enemy3][i] == -1)return FALSE;
	}

	/*ボスの画像読み込み*/
	STAGEBOSS.IMG1[0] = LoadGraph("media\\enemy_img\\STBF.png");
	STAGEBOSS.IMG1[1] = LoadGraph("media\\enemy_img\\STBFS.png");
	STAGEBOSS.IMG2[0] = LoadGraph("media\\enemy_img\\ST1B0.png");
	STAGEBOSS.IMG2[1] = LoadGraph("media\\enemy_img\\ST1B1.png");
	STAGEBOSS.IMG2[2] = LoadGraph("media\\enemy_img\\ST1B2.png");
	STAGEBOSS.IMG2[3] = LoadGraph("media\\enemy_img\\ST1B3.png");

	/*自機の画像読み込み*/
	LoadDivGraph("media\\img_sub\\R.png", 12, 6, 2, 55, 55, HERO.IMGH[0]);
	LoadDivGraph("media\\img_sub\\B.png", 12, 6, 2, 55, 55, HERO.IMGH[1]);
	LoadDivGraph("media\\img_sub\\G.png", 12, 6, 2, 55, 55, HERO.IMGH[2]);
	LoadDivGraph("media\\img_sub\\L.png", 12, 12, 1, 55, 55, HERO.IMGH[3]);

	return TRUE;
}
BOOL InitBulletImage(int i){
	switch (HERO.type)
	{
	case red:
		HERO.BULLET[i].BULLET_IMAGE = BULLET[0];
		break;
	case blue:
		HERO.BULLET[i].BULLET_IMAGE = BULLET[1];
		break;
	case green:
		HERO.BULLET[i].BULLET_IMAGE = BULLET[2];
		break;
	case beam:
		HERO.BULLET[i].BULLET_IMAGE = BULLET[3];
		break;
	}

	return TRUE;
}