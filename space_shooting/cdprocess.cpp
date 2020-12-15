#include"cdprocess.h"

#define SCROLL_STAPOS 500

float scrolly = 0;

void move(){
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (key & PAD_INPUT_UP && CheckEnd(1) == TRUE){
		HERO.y -= HERO.movement;
		CheckScroll(1);
		
	}
	if (key & PAD_INPUT_DOWN && CheckEnd(2) == TRUE){
		HERO.y += HERO.movement;
		CheckScroll(2);

	}
	if (key & PAD_INPUT_LEFT && CheckEnd(3) == TRUE){
		HERO.x -= HERO.movement;
	}
	if (key & PAD_INPUT_RIGHT && CheckEnd(4) == TRUE){
		HERO.x += HERO.movement;
	}

}

BOOL CheckEnd(int i){

	switch (i)
	{
	case 1:
		if (HERO.y - HERO.movement <= 0) return FALSE;
		break;
	case 2:
		if (SHP * IMGSIZE + ((50 - SHP) * IMGSIZE) <= HERO.y + IMGSIZE + HERO.movement)return FALSE;
		break;
	case 3:
		if (HERO.x - HERO.movement < 0)return FALSE;
		break;
	case 4:
		if (HERO.x + HERO.movement + IMGSIZE > gamemainsize_x)return FALSE;
		break;
	}

	return TRUE;
	
}
void CheckScroll(int flag){

	int field_bottom = 2750 - gamemainsize_y;
	int field_central = 2750 - field_bottom;
	int field_head = 0;
	
	if (HERO.y >= 0 && HERO.y <= 800){
		if (flag == 2){
			scrolly -= HERO.movement;
			HERO.SC_Hosei += HERO.movement;
		}

	}
	if (HERO.y > 800 && HERO.y <= 1950){
		if (flag == 1){
			scrolly += HERO.movement;
		}
		else if (flag == 2){
			scrolly -= HERO.movement;
		}
	}
	if (HERO.y > 1950 && HERO.y <= 2750){
		if (flag == 1){
			scrolly += HERO.movement;
		}
		if (flag == 2 && scrolly == 0){
			HERO.SC_Hosei += HERO.movement;
		}
	}

	/*画面外へ出ないように補正*/
	if ((HERO.y + IMGSIZE) > MAX_MONITOR_SIZE - scrolly){
		HERO.y -= HERO.movement;
	}
	if ((SHP * IMGSIZE - HERO.SC_Hosei ) > (HERO.y - HERO.movement)){
		HERO.y += HERO.movement;
	}
	
}

void _Init_PLAYER_BULLET(int i){

//	HERO.BULLET[i].time = 0;
	HERO.BULLET[i].living = FALSE;
	HERO.BULLET[i].SBP = 0;
	HERO.BULLET[i].x = 0;
	HERO.BULLET[i].y = 0;
	HERO.BULLET[i].type = 0;
	HERO.BULLET[i].movement = 0;
}

void DrawBullet(int flag){
	int largefont = CreateFontToHandle("メイリオ", 42, -1, DX_FONTTYPE_NORMAL);

	if (flag == E){

	}else if (flag == P){
		for (int i = 0; HERO.BULLET[i].living < 20 ; i++){
			//for (int i = 0; HERO.BULLET[i].living == TRUE; i++){
			if (HERO.BULLET[i].living == TRUE){
				switch (HERO.BULLET[i].type)
				{
				case red:
					DrawGraph(HERO.BULLET[i].x, HERO.BULLET[i].y - 1950, HERO.BULLET[i].BULLET_IMAGE, TRUE);
					break;
				case blue:
					DrawGraph(HERO.BULLET[i].x, HERO.BULLET[i].y - 1950, HERO.BULLET[i].BULLET_IMAGE, TRUE);
					break;
				case green:
					DrawGraph(HERO.BULLET[i].x, HERO.BULLET[i].y - 1950, HERO.BULLET[i].BULLET_IMAGE, TRUE);
					break;
				case beam:
					DrawExtendGraph(HERO.BULLET[i].x, HERO.BULLET[i].y - 1950, HERO.BULLET[i].x + IMGSIZE, HERO.BULLET[i].y - 1950 + IMGSIZE, HERO.BULLET[i].BULLET_IMAGE, TRUE);
					break;
				}
				if (HERO.BULLET[i].SBP - 800 > HERO.BULLET[i].y){
					_Init_PLAYER_BULLET(i);
				}
				HERO.BULLET[i].y -= HERO.BULLET[i].movement;
			}
		}
	}
	
}