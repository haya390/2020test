#include "gamemain.h"

////haya 11/18 スクロール作成中。コンパイルエラー発生。
////11/24 横スクロールが黒出てしまう。当たり判定おかしい。
////11/25 当たり判定は、C言語のキャストによる問題があり、にブロックごとにチェックする関数を使うことにする。
////表示は、y軸方向に－１すれば合うようではある。（その際、マップ表示ずれの対策要）
////12/02障害物との当たり判定を関数使用に変更


Stagedata g_stagedata;

int key;
//移動係数
float move = 1.0f;

//横方向と縦方向のカウント数。
int xcount = 0, ycount = 0;

int g_mapdata_interior[MAP_INTERIOR_HEIGHT][MAP_INTERIOR_WIDTH];
int g_mapdata_village[MAP_VILLAGE_HEIGHT][MAP_VILLAGE_WIDTH];
int g_mapdata_field[MAP_FIELD_HEIGHT][MAP_FIELD_WIDTH];
//char g_automap[MAP_HEIGHT][MAP_WIDTH];

void GameMain(){

	DrawMap(PT);
	DrawHero(PT);

	//Zキーをチェックして画面を切り替え
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (IsAKeyTrigger(key) == TRUE){
		/*g_gamestate = GAME_OVER;*/
		g_timerstart = g_lasttime;    //タイマーセット
	}
}


void InitStage(int pt){
	int map_height = 0;
	int map_width = 0;
	char buf[256];

	if (pt == Interior){
		sprintf_s(buf, 256, "media\\interior.txt");
		map_height = MAP_INTERIOR_HEIGHT;
		map_width = MAP_INTERIOR_WIDTH;

		//移動前の座標保持
		if (g_before_int_hx != 0){
			g_hx = g_before_int_hx; //190;
			g_hy = g_before_int_hy; //150;
		}
		else{
			g_hx = 250;
			g_hy = 255;
		}
	}
	else if (pt == Village){
		sprintf_s(buf, 256, "media\\village.txt");
		map_height = MAP_VILLAGE_HEIGHT;
		map_width = MAP_VILLAGE_WIDTH;

		//移動前の座標保持
		if (g_before_fie_hx != 0){
			g_hx = g_before_fie_hx; //50;
			g_hy = g_before_fie_hy; //230;
		}
		else{
			g_hx = 50;
			g_hy = 230;
		}

	}
	else if (pt == Field){
		sprintf_s(buf, 256, "media\\field.txt");
		map_height = MAP_FIELD_HEIGHT;
		map_width = MAP_FIELD_WIDTH;
		
		//移動前の座標保持
		if (g_before_vil_hx != 0){
			g_hx = g_before_vil_hx; //190;
			g_hy = g_before_vil_hy; //150;
		}
		else{
			g_hx = 190;
			g_hy = 150;
		}
	}

	int fn = FileRead_open(buf);
	for (int y = 0; y < map_height; y++){
		FileRead_gets(buf, 256, fn);
		for (int x = 0; x < map_width; x++){
			switch(PT){
			case Interior:
				if (buf[x] == 'A'){
					g_mapdata_interior[y][x] = 11;
				}
				else{
					g_mapdata_interior[y][x] = (int)(buf[x] - '0');
				}
				break;
			case Village:
				if (buf[x] == 'A'){
					g_mapdata_village[y][x] = 11;
				}
				else{
					g_mapdata_village[y][x] = (int)(buf[x] - '0');
				}
				break;
			case Field:
				if (buf[x] == 'A'){
					g_mapdata_field[y][x] = 11;
				}
				else{
					g_mapdata_field[y][x] = (int)(buf[x] - '0');
				}
				break;
			default:
				break;
			}
		}
	}
	FileRead_close(fn);

}

void DrawHero(int pt){
	char key[256];
	GetHitKeyStateAll(key);

	//添字用変数
	int ix = 0, iy = 0, result = 0;

	if (key[KEY_INPUT_LEFT] == 1 || key[KEY_INPUT_RIGHT] == 1){
		if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1){
			//移動係数を０．７１に設定
			move = 0.71f;
		}
		else{
			//斜めじゃなければ１．０に設定
			move = 1.0f;
		}
	}
	else if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) { move = 1.0f; }

	float hx = g_hx;
	float hy = g_hy;

	if (key[KEY_INPUT_LEFT] == 1)		hx -= (int)4 * move;
	if (key[KEY_INPUT_RIGHT] == 1)		hx += (int)4 * move;
	if (key[KEY_INPUT_UP] == 1)			hy -= (int)4 * move;
	if (key[KEY_INPUT_DOWN] == 1)		hy += (int)4 * move;

	AtariInfo atari = CheckFieldObstacle(hx, hy);

	//障害物チェック
	switch (pt){
	case Interior:
		if (g_mapdata_interior[(int)hy / IMG_CHIPSIZE][(int)hx / IMG_CHIPSIZE] == 0){
			if (hx >= 0 && hx < SCR_WIDTH && hy > 0 && hy < SCR_HEIGHT){
			}
		}
		else{
			if (g_mapdata_interior[(int)hy / IMG_CHIPSIZE][(int)hx / IMG_CHIPSIZE] == 11){
				PT = Village;
				InitStage(PT);
			}
			else{ hx = g_hx; }
			clsDx();
			printfDx("障害物です");
		}
		break;
	case Village:
		if (g_mapdata_village[(int)hy / IMG_CHIPSIZE][(int)hx / IMG_CHIPSIZE] == 0 || g_mapdata_village[(int)hy / IMG_CHIPSIZE][(int)hx / IMG_CHIPSIZE] == 1){
			if (hx >= 0 && hx < SCR_WIDTH && hy > 0 && hy < SCR_HEIGHT){
			}
		}
		else{
			if (g_mapdata_village[(int)hy / IMG_CHIPSIZE][(int)hx / IMG_CHIPSIZE] == 11){
				PT = Field;
				InitStage(PT);
			}
			else{ hx = g_hx; }

			clsDx();
			printfDx("障害物です");
		}
		break;
	case Field:
//		AtariInfo atari = CheckFieldObstacle(hx, hy, g_hx);

		if (g_stagedata.hero_direction == NORTH){
			if (atari.UR == TRUE || atari.UL == TRUE){
				hy = g_hy;
			}
		}
		else if (g_stagedata.hero_direction == EAST){
			if (atari.DR == TRUE || atari.UR == TRUE)	hx = g_hx;
		}
		else if (g_stagedata.hero_direction == SOUTH){
			if (atari.DL == TRUE || atari.DR == TRUE)	hy = g_hy;
		}
		else if (g_stagedata.hero_direction == WEST){
			if (atari.DL == TRUE || atari.UL == TRUE)	hx = g_hx;
		}

		//if (g_mapdata_field[(int)hy / IMG_CHIPSIZE][(int)hx / IMG_CHIPSIZE] < 5){
		//	clsDx();
		//	printfDx("通行可能\n");
		//	if (hx >= 0 && hx < SCR_WIDTH && hy > 0 && hy < SCR_HEIGHT){
		//	}
		//}
		//else{
			/*if (g_mapdata_field[(int)hy / IMG_CHIPSIZE][(int)hx / IMG_CHIPSIZE] == 11){
				PT = Interior;
				InitStage(PT);
			}*/
		//	else{ hx = g_hx; }
		//	clsDx();
		//	printfDx("障害物\n");
		//}
		break;
	default:
		break;
	}

	////スクロール補正(右)
	//if (hx - g_stagedata.scrollx > SCR_X_RIGHT && g_stagedata.scrollx < SCR_WIDTH * IMG_CHIPSIZE){
	//	g_stagedata.scrollx += (hx - g_hx);
	//}
	////スクロール補正(左)
	//if (hx - g_stagedata.scrollx < SCR_X_LEFT && g_stagedata.scrollx > 2){
	//	g_stagedata.scrollx += (hx - g_hx);
	//}
	////スクロール補正(上)
	//if (hy - g_stagedata.scrolly < SCR_Y_UP)
	//{
	//	g_stagedata.scrolly += (hy - g_hy);
	//}
	////スクロール補正(下)
	//if (((hy - g_stagedata.scrolly) > SCR_Y_DOWN) && g_stagedata.scrolly < SCR_HEIGHT * IMG_CHIPSIZE)
	//{
	//	g_stagedata.scrolly += (hy - g_hy);
	//}

	//スクロール補正
	if (hx - g_stagedata.scrollx > SCR_X_RIGHT || g_stagedata.scrollx < SCR_WIDTH){
//		if (hx - g_stagedata.scrollx > SCR_X_RIGHT && g_stagedata.scrollx < IMG_CHIPSIZE * (MAP_FIELD_WIDTH - 1)){
		if (g_stagedata.scrollx < 1960/*画面のスクロール右端*/ && g_stagedata.scrollx < 0){
			g_stagedata.scrollx += (hx - g_hx);
		}
	}
	if (hx - g_stagedata.scrollx < SCR_X_LEFT  && g_stagedata.scrollx > 0){
		g_stagedata.scrollx += (hx - g_hx);
	}

	if (hy - g_stagedata.scrolly > SCR_Y_DOWN && g_stagedata.scrolly < SCR_HEIGHT){
		g_stagedata.scrolly += (hy - g_hy);
	}
	if (hy - g_stagedata.scrolly < SCR_Y_UP  && g_stagedata.scrolly > 0){
		g_stagedata.scrolly += (hy - g_hy);
	}

	if (hx < g_stagedata.scrollx) hx = g_hx;
	if (hy < g_stagedata.scrolly) hy = g_hy;
	if (hx > IMG_CHIPSIZE *(MAP_FIELD_WIDTH - 2)) hx = g_hx;
	if (hy > IMG_CHIPSIZE *(MAP_FIELD_HEIGHT - 1)) hy = g_hy;

	g_hx = hx;
	g_hy = hy;

	clsDx();
	printfDx("hx:%f hy:%f\n", hx, hy);
	printfDx("g_hx:%f g_hy:%f\n", g_hx, g_hy);
	printfDx("g_stagedata.scrollx:%f g_stagedata.scrolly:%f\n", g_stagedata.scrollx, g_stagedata.scrolly);


	//左キーが押されてて、かつxcountが０以上なら０にしてから１引く。
	//それ以外は１引く
	if (key[KEY_INPUT_LEFT] == 1){
		if (xcount > 0)	xcount = 0;
		--xcount;
		g_stagedata.hero_direction = WEST;
	}

	//右キーが押されてて、かつxcountが０以下なら０にしてから１足す。
	//それ以外は１引く
	if (key[KEY_INPUT_RIGHT] == 1){
		if (xcount < 0)	xcount = 0;
		++xcount;
		g_stagedata.hero_direction = EAST;
	}

	//上キーが押されてて、かつycountが０以上なら０にしてから１引く。
	//それ以外は１引く
	if (key[KEY_INPUT_UP] == 1){
		if (ycount>0) ycount = 0;
		--ycount;
		g_stagedata.hero_direction = NORTH;
		
	}

	//下キーが押されてて、かつycountが０以下なら０にしてから１足す。
	//それ以外は１足す
	if (key[KEY_INPUT_DOWN] == 1){
		if (ycount < 0) ycount = 0;
		++ycount;
		g_stagedata.hero_direction = SOUTH;
	}

	//カウント数から添字を求める。
	ix = abs(xcount) % 30 / 10;
	iy = abs(ycount) % 30 / 10;

	////xカウントがプラスなら右向きなので3行目の先頭添字番号を足す。
	if (xcount>0){
		ix += 6;
		result = ix;
	}
	else if (xcount<0){
		////マイナスなら左向きなので、2行目の先頭添字番号を足す。
		ix += 3;
		result = ix;
	}

	////yカウントがプラスなら下向きなので、何もする必要なし。(分かりやすくするために書いときました)
	if (ycount>0){
		iy += 0;
		result = iy;
	}
	else if (ycount<0){
		////マイナスなら上きなので、4行目の先頭添字番号を足す。
		iy += 9;
		result = iy;
	}

	//斜め移動の場合は横顔を優先
	if (move == 0.71f)	result = ix;

	//描画
	//		DrawGraph(g_hx + IMG_CHIPSIZE /*/ 3*/, g_hy + IMG_CHIPSIZE, g_imghandles.hero[result], TRUE);
	DrawGraph(g_hx - g_stagedata.scrollx, g_hy - g_stagedata.scrolly, g_imghandles.hero[result], TRUE);

	//押されてなければカウントをゼロにする。
	if (key[KEY_INPUT_LEFT] != 1 && key[KEY_INPUT_RIGHT] != 1)	xcount = 0;
	if (key[KEY_INPUT_UP] != 1 && key[KEY_INPUT_DOWN] != 1)		ycount = 0;

}

void DrawMap(int pt){
	if (pt == Field){
		int scx = (int)g_stagedata.scrollx / IMG_CHIPSIZE;
		int scy = (int)g_stagedata.scrolly / IMG_CHIPSIZE;
		int shiftx = (int)g_stagedata.scrollx % IMG_CHIPSIZE;
		int shifty = (int)g_stagedata.scrolly % IMG_CHIPSIZE;

		for (int y = 0; y < MAP_FIELD_HEIGHT + 1; y++){
			for (int x = 0; x < MAP_FIELD_WIDTH ; x++){
				if (y + scy >= MAP_FIELD_HEIGHT) break;
				if (y + scy < 0) break;
				if (x + scx >= MAP_FIELD_WIDTH) break;
				if (x + scx < 0) break;

				switch (g_mapdata_field[(y + scy)/*-1*/][x + scx]){
				case 0:
					DrawGraph(x * IMG_CHIPSIZE - shiftx, y * IMG_CHIPSIZE - shifty, g_imghandles.field[0], TRUE);
					break;
				case 1:
					DrawGraph(x * IMG_CHIPSIZE - shiftx, y * IMG_CHIPSIZE - shifty, g_imghandles.field[1], TRUE);
					break;
				case 2:
					DrawGraph(x * IMG_CHIPSIZE - shiftx, y * IMG_CHIPSIZE - shifty, g_imghandles.field[2], TRUE);
					break;
				case 3:
					DrawGraph(x * IMG_CHIPSIZE - shiftx, y * IMG_CHIPSIZE - shifty, g_imghandles.field[3], TRUE);
					break;
				case 4:
					DrawGraph(x * IMG_CHIPSIZE - shiftx, y * IMG_CHIPSIZE - shifty, g_imghandles.field[4], TRUE);
					break;
				case 5:
					DrawGraph(x * IMG_CHIPSIZE - shiftx, y * IMG_CHIPSIZE - shifty, g_imghandles.field[5], TRUE);
					break;
				case 6:
					DrawGraph(x * IMG_CHIPSIZE - shiftx, y * IMG_CHIPSIZE - shifty, g_imghandles.field[6], TRUE);
					break;
				case 7:
					DrawGraph(x * IMG_CHIPSIZE - shiftx, y * IMG_CHIPSIZE - shifty, g_imghandles.field[7], TRUE);
					break;
				case 8:
					DrawGraph(x * IMG_CHIPSIZE - shiftx, y * IMG_CHIPSIZE - shifty, g_imghandles.field[8], TRUE);
					break;
				case 9:
					DrawGraph(x * IMG_CHIPSIZE - shiftx, y * IMG_CHIPSIZE - shifty, g_imghandles.field[9], TRUE);
					break;
				}
			}
		}
	//	//		int sc_x = (int)(g_hx / IMG_CHIPSIZE);
	//	//		int sc_y = (int)(g_hy / IMG_CHIPSIZE);
	//	for (int y = 0; y < MAP_FIELD_HEIGHT; y++){
	//		if (y /*+ sc_y*/ >= SCR_HEIGHT) break;
	//		for (int x = 0; x < MAP_FIELD_WIDTH; x++){
	//			if (x /*+ sc_x*/ >= SCR_WIDTH) break;
	//			int y2 = 0;
	//			y2 = y - 1;
	//			switch (g_mapdata_field[(MAP_FIELD_HEIGHT - y - 1/* - sc_y*/)][x/* + sc_x*/]){
	//			case 0:
	//				DrawGraph((x + 1) * IMG_CHIPSIZE, y2 * IMG_CHIPSIZE, g_imghandles.field[0], TRUE);
	//				break;
	//			case 1:
	//				DrawGraph((x + 1) * IMG_CHIPSIZE, y2 * IMG_CHIPSIZE, g_imghandles.field[1], TRUE);
	//				break;
	//			case 2:
	//				DrawGraph((x + 1) * IMG_CHIPSIZE, y2 * IMG_CHIPSIZE, g_imghandles.field[2], TRUE);
	//				break;
	//			case 3:
	//				DrawGraph((x + 1) * IMG_CHIPSIZE, y2 * IMG_CHIPSIZE, g_imghandles.field[3], TRUE);
	//				break;
	//			case 4:
	//				DrawGraph((x + 1) * IMG_CHIPSIZE, y2 * IMG_CHIPSIZE, g_imghandles.field[4], TRUE);
	//				break;
	//			case 5:
	//				DrawGraph((x + 1) * IMG_CHIPSIZE, y2 * IMG_CHIPSIZE, g_imghandles.field[5], TRUE);
	//				break;
	//			case 6:
	//				DrawGraph((x + 1) * IMG_CHIPSIZE, y2 * IMG_CHIPSIZE, g_imghandles.field[6], TRUE);
	//				break;
	//			case 7:
	//				DrawGraph((x + 1) * IMG_CHIPSIZE, y2 * IMG_CHIPSIZE, g_imghandles.field[7], TRUE);
	//				break;
	//			case 8:
	//				DrawGraph((x + 1) * IMG_CHIPSIZE, y2 * IMG_CHIPSIZE, g_imghandles.field[8], TRUE);
	//				break;
	//			case 9:
	//				DrawGraph((x + 1) * IMG_CHIPSIZE, y2 * IMG_CHIPSIZE, g_imghandles.field[9], TRUE);
	//				break;
	//			}
	//		}
	//	}
	}
	else{

		for (int y = 0; y < MAP_INTERIOR_HEIGHT; y++){
			for (int x = 0; x < MAP_INTERIOR_WIDTH; x++){
				if (pt == Interior){
					switch (g_mapdata_interior[y][x]){
					case 0:
						DrawGraph((x + 1)* IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.interior[0], TRUE);
						break;
					case 1:
						DrawGraph((x + 1)* IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.interior[1], TRUE);
						break;
					case 2:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.interior[2], TRUE);
						break;
					case 3:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.interior[3], TRUE);
						break;
					case 4:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.interior[4], TRUE);
						break;
					case 5:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.interior[5], TRUE);
						break;
					case 6:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.interior[6], TRUE);
						break;
					case 7:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.interior[7], TRUE);
						break;
					case 8:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.interior[8], TRUE);
						break;
					case 9:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.interior[9], TRUE);
						break;
					}
				}

				if (pt == Village){
					switch (g_mapdata_village[y][x]){
					case 0:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.village[0], TRUE);
						break;
					case 1:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.village[1], TRUE);
						break;
					case 2:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.village[2], TRUE);
						break;
					case 3:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.village[3], TRUE);
						break;
					case 4:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.village[4], TRUE);
						break;
					case 5:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.village[5], TRUE);
						break;
					case 6:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.village[6], TRUE);
						break;
					case 7:
						DrawGraph((x + 1) * IMG_CHIPSIZE, (y + 2) * IMG_CHIPSIZE, g_imghandles.village[7], TRUE);
						break;
					}
				}
			}
		}
	}
}

//ブロックとの当たり判定
BOOL _CheckBlockSub(float x, float y){
	int mx = (int)(x / IMG_CHIPSIZE);
	int my = (int)(y / IMG_CHIPSIZE);
	//マップの範囲外ならFALSE
	if ((mx < 0) || (mx >= SCR_WIDTH) || (my >= SCR_HEIGHT) || (my < 0)){
		return FALSE;
	}
	if (g_mapdata_field[my][mx] >= 5) return TRUE;
	return FALSE;
}
AtariInfo CheckFieldObstacle(float x, float y){
	AtariInfo result;
	result.UL = _CheckBlockSub(x , y);
	result.UR = _CheckBlockSub(x + IMG_CHIPSIZE - 3, y);
	result.DL = _CheckBlockSub(x, y + IMG_CHIPSIZE - 3);
	result.DR = _CheckBlockSub(x + IMG_CHIPSIZE - 3, y + IMG_CHIPSIZE - 3);
	return result;
}