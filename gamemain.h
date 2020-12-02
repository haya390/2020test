#ifndef __GAMEMAIN_H__ 
#define __GAMEMAIN_H__

#include <DxLib.h>
#include "main.h"
#include "enemy.h"

#define IMG_CHIPSIZE 40
#define MAP_INTERIOR_WIDTH 18
#define MAP_INTERIOR_HEIGHT 11
#define MAP_VILLAGE_WIDTH 19
#define MAP_VILLAGE_HEIGHT 11
#define MAP_FIELD_WIDTH 70 //�t�B�[���h�z��
#define MAP_FIELD_HEIGHT 30
#define SCR_WIDTH 800  //��ʃT�C�Y
#define SCR_HEIGHT 600 //��ʃT�C�Y
#define SCR_X_LEFT  100		//�X�N���[���ʒu
#define SCR_X_RIGHT 500		//�X�N���[���ʒu
#define SCR_Y_DOWN  400		//�X�N���[���ʒu
#define SCR_Y_UP	100		//�X�N���[���ʒu

#define ANIM_RATE 4

extern int g_mapdata_interior[MAP_INTERIOR_HEIGHT][MAP_INTERIOR_WIDTH];
extern int g_mapdata_village[MAP_VILLAGE_HEIGHT][MAP_VILLAGE_WIDTH];
extern int g_mapdata_field[MAP_FIELD_HEIGHT][MAP_FIELD_WIDTH];
//extern char g_automap[MAP_HEIGHT][MAP_WIDTH];

enum PT{
	Interior,Village,Field
};

enum MapItemInterior{
	MPITEM_FLOOR = 1, MPITEM_TABLE = 2, MPITEM_CHAIR = 3, MPITEM_BED = 4,
	MPITEM_BOOK = 5, MPITEM_CLOSET = 6, MPITEM_BOOKCLOSET = 7, MPITEM_WALL = 8,
	MPITEM_ENTRANCE = 9
};

enum MapItemVillage{
	MPITEM_GRASS = 1, MPITEM_SOIL = 2, MPITEM_HOUSE = 3, MPITEM_FOURWOOD = 4,
	MPITEM_BOARD = 5, MPITEM_POST = 6, MPITEM_WELL = 7, MPITEM_TUB = 8

};
enum MapItemField{
	MPITEM_GREEN = 1, MPITEM_SOILSIDE = 2, MPITEM_SOILVERTICAL = 3, MPITEM_BRIDGE= 4,
	MPITEM_SEA = 5, MPITEM_CAVE = 6, MPITEM_CHEST = 7, MPITEM_SING = 8,
	MPITEM_WOOD = 9
};

enum EnemyType{
	
};
enum ECF{
	ATK = 1, AGI = 2, EDU = 3, HP = 4, MP = 5

};
struct CharaData{
	float x, y;
	char player_name;
	int Lv;
	float EXP;
	int HP;
	int MP;
	int ATK; /*��������*/
	int AGI; /*�f����*/
	int EDU; /*��������*/
};

struct Stagedata{
	int animcounter;
	float scrollx;
	float scrolly;
	int hero_direction;
};
extern Stagedata g_stagedata;

enum News{
	NORTH, EAST, SOUTH, WEST
};

struct DataFrame{
	int ecf;/*���ʕ���*/
	float eff;/*����*/
	char epn[20];/*����*/
};

struct AtariInfo{
	BOOL UL, UR, DL, DR;
};


void GameMain();
void InitStage(int pt);
void DrawHero(int pt);
void DrawMap(int pt);
AtariInfo CheckFieldObstacle(float x, float y);

#endif