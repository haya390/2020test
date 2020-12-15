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
void DrawBullet(int);/*1‚ÌŽžŽ©‹@/2‚ÌŽž“G‹@1/3‚ÌŽž“G‹@2/4‚ÌŽž“G‹@3*/

extern float scrolly;

#endif