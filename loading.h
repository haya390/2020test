#ifndef __LOADING_H__
#define __LOADING_H__

#include <DxLib.h>

#define ANIMFRAME 12

struct ImageHandles{
	int interior[10];
	int village[8];
	int field[10];
	int hero[ANIMFRAME];
	int npc[4];
	int monster[5];
	int title;
	int mapitems[30];
};
extern ImageHandles g_imghandles;

BOOL LoadGameImage();

#endif