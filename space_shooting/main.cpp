#include"main.h"
#include<DxLib.h>

int MAX_MONITOR_SIZE = MAPHEIGHT * IMGSIZE;
int MIN_MONITOR_SIZE = 0 - MAX_MONITOR_SIZE + gamemainsize_y;

int monitorsize_x = 960;
int monitorsize_y = 840;

int gamemainsize_x = 715;
int gamemainsize_y = 800;

int gametype = GAME_TITLE;
BOOL g_akey_prev = FALSE;

int timer;

int largefont = CreateFontToHandle("メイリオ", 42, -1, DX_FONTTYPE_NORMAL);

int g_timestart = 0;

int WINAPI WinMain(HINSTANCE h1, HINSTANCE hp, LPSTR lpc, int nC){
	SetWindowSizeChangeEnableFlag(TRUE);
	ChangeWindowMode(TRUE);
	SetWindowText("Trinity");
	SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(monitorsize_x, monitorsize_y, 32);
	if (DxLib_Init() == -1)return -1;
	if (IMGhandle() == -1)return -1;

	timer = 0;
	timer = GetNowCount();
	LONGLONG a = GetNowHiPerformanceCount();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		ClearDrawScreen();
		switch (gametype)
		{
		case GAME_TITLE:
			DrawTitle();
			break;
		case GAME_MAIN:
			DrawGameMain();
			break;
		case GAME_OVER:
 			DrawGameOver();
			break;
		case GAME_CLEAR:
			DrawGameClear();
			break;
		}
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}
void DrawTitle(){

	DrawExtendGraph(0,0,monitorsize_x,monitorsize_y,TITLE,TRUE);


	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (keychecker_b(key) == TRUE){
		syokika();
		gametype = GAME_MAIN;
		InitStage(1);
		SetGraphMode(gamemainsize_x, gamemainsize_y, 32);
		IMGhandle();
	}
}
void DrawGameMain(){
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (keychecker_b(key) == TRUE){
		clsDx();
		gametype = GAME_OVER;
		SetGraphMode(monitorsize_x, monitorsize_y, 32);
		IMGhandle();
		g_timestart = GetNowCount();
	}
	gamemain();
}
void DrawGameOver(){
	clsDx();

	int Timecount = GetNowCount();

	DrawExtendGraph(0, 0, monitorsize_x, monitorsize_y, GAMEOVER, TRUE);

	/*DrawStringToHandle(200, 200, "左を押すとコンティニュー", GetColor(255, 255, 255), largefont, 32, FALSE);
	DrawStringToHandle(200, 250, "右を押すとゲーム終了", GetColor(255, 255, 255), largefont, 32, FALSE);*/

	if (CheckHitKey(KEY_INPUT_LEFT) == TRUE){
		gametype = GAME_MAIN;
		SetGraphMode(gamemainsize_x, gamemainsize_y, 32);
		IMGhandle();
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE){
		exit(0);
	}
	if (Timecount - g_timestart > 5000){
		gametype = GAME_TITLE;
		SetGraphMode(monitorsize_x, monitorsize_y, 32);
		IMGhandle();
	}

}
void DrawGameClear(){
	
}
int keychecker_z(int key){
	if (key & PAD_INPUT_A){
		if (g_akey_prev == FALSE){
			g_akey_prev = TRUE;
			return TRUE;
		}
	}
	else{
		g_akey_prev = FALSE;
	}
	return FALSE;
}
int keychecker_b(int key){
	if (key & PAD_INPUT_10){
		if (g_akey_prev == FALSE){
			g_akey_prev = TRUE;
			return TRUE;
		}
	}
	else{
		g_akey_prev = FALSE;
	}
	return FALSE;
}