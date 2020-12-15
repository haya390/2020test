#include"cdflame.h"

int bullet_count = sizeof(HERO.BULLET) / sizeof(HERO.BULLET[0]);

int KEY_KAISU = 0;

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
			for (int i = 0; i < 20; i++){
				if (HERO.BULLET[i].living == FALSE){
					if (i != 0){
						HERO.BULLET[i].time = GetNowCount();
						Tseigyo = HERO.BULLET[i].time - HERO.BULLET[i - 1].time;
//						Tseigyo = HERO.BULLET[i].time - timer - HERO.BULLET[i - 1].time;
						if (Tseigyo >= 1000){
//							HERO.BULLET[i].time = Tseigyo;
							HERO.BULLET[i].living = TRUE;
							HERO.BULLET[i].SBP = HERO.y;
							HERO.BULLET[i].x = HERO.x;
							HERO.BULLET[i].y = HERO.y - 50;
							HERO.BULLET[i].type = HERO.type;
							HERO.BULLET[i].movement = 7;
							InitBulletImage(i);
							break;
						}

				}else{
					HERO.BULLET[i].time = GetNowCount();
//					HERO.BULLET[i].time = GetNowCount() - timer;
					HERO.BULLET[i].living = TRUE;
					HERO.BULLET[i].SBP = HERO.y;
					HERO.BULLET[i].x = HERO.x;
					HERO.BULLET[i].y = HERO.y - 50;
					HERO.BULLET[i].type = HERO.type;
					HERO.BULLET[i].movement = 7;
					InitBulletImage(i);
					break;
				}

			}else{
				
			}
		}
		
	}
}