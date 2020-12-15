#include<DxLib.h>
#include"gamemain.h"
#include"loading.h"
#include"cdprocess.h"




int MAPDATA[MAPHEIGHT][MAPWIDTH];

int hx, hy;
int i = 0;
int IMG_FLAME_RATE = 0;
int IMG_TYPE_FLAG = 0;
int SHP;

void InitStage(int i){
	char buf[256];
	sprintf_s(buf, 256, "media\\stagedata\\stage%d.txt",i);
	int fh = FileRead_open(buf);
	int y = 0;
	for (y = 0; y < MAPHEIGHT; y++){
		FileRead_gets(buf, 256, fh);
		for (int x = 0; x < MAPWIDTH; x++){
			MAPDATA[y][x] = (int)(buf[x] - '0');
			if (MAPDATA[y][x] == MAP_HERO){
				HERO.x = x * IMGSIZE;
				HERO.y = y * IMGSIZE;
				SHP = y;
			}
			if (MAPDATA[y][x] == enemy1){
				Init_ENEMY1(i, x, y);
			}
			if (MAPDATA[y][x] == enemy2){
				Init_ENEMY2(i, x, y);
			}
			if (MAPDATA[y][x] == enemy3){
				Init_ENEMY3(i, x, y);
			}
			if (MAPDATA[y][x] == boss){
				Init_BOSS(i,x, y);
			}
		}
	}
	SHP = y - SHP;
	FileRead_close(fh);
}

void gamemain(){
	DrawMap();
	move();

	/*

	*/

	SET_PLAYER_BULLET();
	DrawBullet(P);

	
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (key & PAD_INPUT_2){
		if (HERO.type == beam){
			HERO.type = red;
			IMG_TYPE_FLAG = 0;
		}
		else{
			HERO.type++;
			IMG_TYPE_FLAG++;
		}

	}

	
	

	clsDx();
	printfDx("Y軸:%f\nX軸:%f\nスクロール量:%f\n時間:%d\nスクロール補正値:%d", HERO.y, HERO.x,scrolly, GetNowCount() / 1000 - timer / 1000,HERO.SC_Hosei);
}

void DrawMap(){

	DrawGraph(0, 0 - 1950 + scrolly, field, TRUE);

	if (GetNowCount() - timer > 1000)IMG_FLAME_RATE++;

	for (int y = 0; y < MAPHEIGHT; y++){
		for (int x = 0; x < MAPWIDTH; x++){
			
			switch (MAPDATA[y][x])
			{
			case enemy1:
				DrawGraph(x * IMGSIZE, y * IMGSIZE - 1950, G_IMGhandle[enemy1][IMG_FLAME_RATE], TRUE);
				break;
			case enemy2:
				DrawGraph(x * IMGSIZE, y * IMGSIZE - 1950, G_IMGhandle[enemy2][IMG_FLAME_RATE], TRUE);
				break;
			case enemy3:
				DrawGraph(x * IMGSIZE, y * IMGSIZE - 1950, G_IMGhandle[enemy3][IMG_FLAME_RATE], TRUE);
				break;
			case player:
				DrawGraph(HERO.x, HERO.y - 1950 + scrolly, HERO.IMGH[IMG_TYPE_FLAG][IMG_FLAME_RATE], TRUE);
				break;
			case boss:
				DrawExtendGraph(STAGEBOSS.x , STAGEBOSS.y + scrolly, STAGEBOSS.x + IMGSIZE, STAGEBOSS.y + scrolly + IMGSIZE, STAGEBOSS.IMG1[0], TRUE);
				DrawExtendGraph(STAGEBOSS.x, STAGEBOSS.y + scrolly - IMGSIZE, STAGEBOSS.x + IMGSIZE, STAGEBOSS.y + scrolly + IMGSIZE - IMGSIZE, STAGEBOSS.IMG2[0], TRUE);
				break;
			}
		}
	}
	if (IMG_FLAME_RATE == 11) IMG_FLAME_RATE = 0;
}