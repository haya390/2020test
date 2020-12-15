#ifndef __CDFLAME_H__
#define __CDFLAME_H__

#include<DxLib.h>
#include<stdio.h>
#include"cdprocess.h"

enum ATKtype{
	red = 1, blue = 2, green = 3, beam = 4
};

struct Data{
	float SBP;/*�e���ŏ��ɏo���ꏊ*/
	float x; /*����*/
	float y; /*�c��*/
	BOOL living; /*���ݏؖ�*/
	int type; /*�����̐؂�ւ�*/
	float movement; /*�ړ���*/
	int BULLET_IMAGE;/*�e�̉摜*/
	int time;/*�N�[���^�C��*/
};

struct Charadata{
	float x;/*����*/
	float y;/*�c��*/
	int SC_Hosei;/*�X�N���[���O�ɔ�������Y���̕ύX�ɂ���Ĕ������鑊���␳����*/
	int LIFE;/*�ő��e��*/
	float movement;/*�ړ���*/
	BOOL ScrollUpper;/*������ւ̃X�N���[����*/
	BOOL ScrollBelow;/*�������ւ̃X�N���[����*/
	int type;/*�����̐؂�ւ�*/
	BOOL living;/*���ݏؖ�*/
	Data BULLET[20];/*���@/�G�@�̒e*/
	int StageNum;/*�R���e�B�j���[����ۂ̃X�e�[�W�i���o�[�̋L�^*/
	int IMGH[4][12];/*���@�̉摜*/
};

struct CharaData{
	int enemy_type;/*1 2 3�p�^�[��*/
	float x;/*����*/
	float y;/*�c��*/
	int LIFE;/*�ő��e��*/
	float movement;/*�ړ���*/
	int type;/*�����̐؂�ւ�*/
	BOOL living;/*���ݏؖ�*/
	Data BULLET[20];/*���@/�G�@�̒e*/
	int IMG1[2];/*�G���I�̉摜�������̓{�X�̑O������p*/
	int IMG2[4];/*�{�X�̌�땔����p*/
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