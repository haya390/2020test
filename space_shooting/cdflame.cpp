#include"cdflame.h"

int bullet_count = sizeof(HERO.BULLET) / sizeof(HERO.BULLET[0]);

int KEY_KAISU = 0;
int g_last_bullet;

void syokika(){
	HERO.SC_Hosei = 0;
	scrolly = 0;
	InitStage(HERO.StageNum);
	HERO.LIFE = 3;
	HERO.movement = 5;
	HERO.type = red;
	for (int i = 0; i < bullet_count; i++){
		HERO.BULLET[i].living = FALSE;
	}
}
void Init_ENEMY1(int i, int x, int y){

	ENEMY[i].living = TRUE;
	ENEMY[i].x = x * IMGSIZE;
	ENEMY[i].y = y * IMGSIZE;
	ENEMY[i].LIFE = 3;
	ENEMY[i].type = red;
	ENEMY[i].enemy_type = red;

}
void Init_ENEMY2(int i, int x, int y){

	ENEMY[i].living = TRUE;
	ENEMY[i].x = x * IMGSIZE;
	ENEMY[i].y = y * IMGSIZE;
	ENEMY[i].LIFE = 3;
	ENEMY[i].type = red;
	ENEMY[i].enemy_type = green;

}
void Init_ENEMY3(int i, int x, int y){

	ENEMY[i].living = TRUE;
	ENEMY[i].x = x * IMGSIZE;
	ENEMY[i].y = y * IMGSIZE;
	ENEMY[i].LIFE = 3;
	ENEMY[i].type = red;
	ENEMY[i].enemy_type = blue;

}
void Init_BOSS(int i,int x,int y){

	STAGEBOSS.living = TRUE;
	STAGEBOSS.x = x * IMGSIZE;
	STAGEBOSS.y = y * IMGSIZE - 1950;
	STAGEBOSS.LIFE = 500;
	STAGEBOSS.movement = 1;
	STAGEBOSS.type = 1;

}

void SET_PLAYER_BULLET(){

	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	int Tseigyo;

	if (key & PAD_INPUT_A){
		if (g_last_bullet == 19) {
			g_last_bullet = 0;
		}

		while(g_last_bullet < 20){
			if (HERO.BULLET[g_last_bullet].living == FALSE){
				if (g_last_bullet != 0){
					HERO.BULLET[g_last_bullet].time = GetNowCount();
						Tseigyo = HERO.BULLET[g_last_bullet].time - HERO.BULLET[g_last_bullet - 1].time;
						if (Tseigyo >= 500){
//							HERO.BULLET[i].time = Tseigyo;
							HERO.BULLET[g_last_bullet].living = TRUE;
							HERO.BULLET[g_last_bullet].SBP = HERO.y;
							HERO.BULLET[g_last_bullet].x = HERO.x;
							HERO.BULLET[g_last_bullet].y = HERO.y - 50;
							HERO.BULLET[g_last_bullet].type = HERO.type;
							HERO.BULLET[g_last_bullet].movement = 7;
							InitBulletImage(g_last_bullet);
							++g_last_bullet;
							break;
						}

				}else{
					HERO.BULLET[g_last_bullet].time = GetNowCount();
//					HERO.BULLET[i].time = GetNowCount() - timer;
					HERO.BULLET[g_last_bullet].living = TRUE;
					HERO.BULLET[g_last_bullet].SBP = HERO.y;
					HERO.BULLET[g_last_bullet].x = HERO.x;
					HERO.BULLET[g_last_bullet].y = HERO.y - 50;
					HERO.BULLET[g_last_bullet].type = HERO.type;
					HERO.BULLET[g_last_bullet].movement = 7;
					InitBulletImage(g_last_bullet);
					++g_last_bullet;
					break;
				}
			}
			break;
		}
	}
}