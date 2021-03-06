#include "main.h"

//グローバル変数
//時間計測用変数
int g_lasttime = 0;		//直前の計測時間
float g_frametime = 0;	//1ループにかかった時間
int g_timerstart;		//タイマー用変数

GameState g_gamestate = GAME_TITLE;
int PT = Interior;

int g_gametitleimg;			//タイトルイメージ
int g_heroimg;				//画像
float g_hx = 0, g_hy = 0;	//座標
float g_before_vil_hx = 0, g_before_vil_hy = 0;	//移動前座標
float g_before_fie_hx = 0, g_before_fie_hy = 0;	//移動前座標
float g_before_int_hx = 0, g_before_int_hy = 0;	//移動前座標

//ボタン
BOOL g_akey_prev;			//直前のAボタンの状態
//フォント
int g_middlefont;			//中サイズフォントハンドル
int g_largefont;			//大サイズフォントハンドル
int g_smallfont;			//小サイズフォントハンドル


int WINAPI WinMain(HINSTANCE h1, HINSTANCE hP, LPSTR lpC, int nC){
	//ウィンドウモードにする
	ChangeWindowMode(TRUE);
	//ウィンドウサイズを変更する
	SetGraphMode(800, 600, 32);
	//DXライブラリ初期化
	if (DxLib_Init() == -1) return -1;

//InitStage(PT);

	//画像を読み込み
	if (LoadGameImage() == FALSE) return -1;
	g_middlefont = CreateFontToHandle("メイリオ", 42, -1, DX_FONTTYPE_ANTIALIASING);
	g_largefont = CreateFontToHandle("メイリオ", 90, -1, DX_FONTTYPE_ANTIALIASING);
	g_smallfont = CreateFontToHandle("メイリオ", 18, -1, DX_FONTTYPE_ANTIALIASING);

	SetDrawScreen(DX_SCREEN_BACK);
	g_lasttime = GetNowCount() & INT_MAX;	//現在時刻の記録
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		//1ループにかかった時間を計測
		int curtime = GetNowCount();
		g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
		g_lasttime = curtime;

		ClearDrawScreen();
		//画面描画関数に切り替え
		switch (g_gamestate)
		{
		case GAME_TITLE:
			DrawGameTitle();
			break;
		case GAME_MAIN:
			DrawGameMain();
			break;
		case GAME_CLEAR:
			DrawGameClear();
			break;
		case GAME_OVER:
			DrawGameOver();
			break;
		case GAME_IVENT:
			break;
		}
		ScreenFlip();
	}

	//待機
	WaitKey();
	//DXライブラリの終了処理
	DxLib_End();
	return 0;
}

//タイトル画面描画
void DrawGameTitle(){
	DrawGraph(0, 0, g_imghandles.title, FALSE);
	
	//キーをチェックして画面を切り替え
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (IsAKeyTrigger(key) == TRUE) {
		g_gamestate = GAME_MAIN;
		PT = Interior;
		InitStage(PT);
	}
}
//ゲーム本編描画
void DrawGameMain(){
	GameMain();
}
//ゲームクリア画面描画
void DrawGameClear(){
	DrawBox(0, 0, 800, 600, GetColor(255, 255, 255), TRUE);
	DrawStringToHandle(100, 200, "ゲームクリア",
		GetColor(80, 128, 255), g_largefont);
	//5秒経ったらタイトル画面へ
	if (g_lasttime - g_timerstart > 5000) {
		g_gamestate = GAME_TITLE;
	}
}
//ゲームオーバー画面描画
void DrawGameOver(){
	//テキスト表示
	DrawStringToHandle(100, 200, "ゲームオーバー",
		GetColor(255, 0, 0), g_largefont);
	//5秒経ったらタイトル画面へ
	if (g_lasttime - g_timerstart > 5000) g_gamestate = GAME_TITLE;
}

//キートリガー処理
BOOL IsAKeyTrigger(int key){
	if (key & PAD_INPUT_A){
		if (g_akey_prev == FALSE){
			g_akey_prev = TRUE;
			if (PT == Interior){
				PT = Village;
			}
			else if(PT == Village){
				PT = Field;
			}
			else if(PT == Field){
				PT = Interior;
			}
			InitStage(PT);
			return TRUE;
		}
	}
	else{
		g_akey_prev = FALSE;
	}
	return FALSE;
}