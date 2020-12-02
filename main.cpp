#include "main.h"

//�O���[�o���ϐ�
//���Ԍv���p�ϐ�
int g_lasttime = 0;		//���O�̌v������
float g_frametime = 0;	//1���[�v�ɂ�����������
int g_timerstart;		//�^�C�}�[�p�ϐ�

GameState g_gamestate = GAME_TITLE;
int PT = Interior;

int g_gametitleimg;			//�^�C�g���C���[�W
int g_heroimg;				//�摜
float g_hx = 0, g_hy = 0;	//���W
float g_before_vil_hx = 0, g_before_vil_hy = 0;	//�ړ��O���W
float g_before_fie_hx = 0, g_before_fie_hy = 0;	//�ړ��O���W
float g_before_int_hx = 0, g_before_int_hy = 0;	//�ړ��O���W

//�{�^��
BOOL g_akey_prev;			//���O��A�{�^���̏��
//�t�H���g
int g_middlefont;			//���T�C�Y�t�H���g�n���h��
int g_largefont;			//��T�C�Y�t�H���g�n���h��
int g_smallfont;			//���T�C�Y�t�H���g�n���h��


int WINAPI WinMain(HINSTANCE h1, HINSTANCE hP, LPSTR lpC, int nC){
	//�E�B���h�E���[�h�ɂ���
	ChangeWindowMode(TRUE);
	//�E�B���h�E�T�C�Y��ύX����
	SetGraphMode(800, 600, 32);
	//DX���C�u����������
	if (DxLib_Init() == -1) return -1;

//InitStage(PT);

	//�摜��ǂݍ���
	if (LoadGameImage() == FALSE) return -1;
	g_middlefont = CreateFontToHandle("���C���I", 42, -1, DX_FONTTYPE_ANTIALIASING);
	g_largefont = CreateFontToHandle("���C���I", 90, -1, DX_FONTTYPE_ANTIALIASING);
	g_smallfont = CreateFontToHandle("���C���I", 18, -1, DX_FONTTYPE_ANTIALIASING);

	SetDrawScreen(DX_SCREEN_BACK);
	g_lasttime = GetNowCount() & INT_MAX;	//���ݎ����̋L�^
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		//1���[�v�ɂ����������Ԃ��v��
		int curtime = GetNowCount();
		g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
		g_lasttime = curtime;

		ClearDrawScreen();
		//��ʕ`��֐��ɐ؂�ւ�
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

	//�ҋ@
	WaitKey();
	//DX���C�u�����̏I������
	DxLib_End();
	return 0;
}

//�^�C�g����ʕ`��
void DrawGameTitle(){
	DrawGraph(0, 0, g_imghandles.title, FALSE);
	
	//�L�[���`�F�b�N���ĉ�ʂ�؂�ւ�
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (IsAKeyTrigger(key) == TRUE) {
		g_gamestate = GAME_MAIN;
		PT = Interior;
		InitStage(PT);
	}
}
//�Q�[���{�ҕ`��
void DrawGameMain(){
	GameMain();
}
//�Q�[���N���A��ʕ`��
void DrawGameClear(){
	DrawBox(0, 0, 800, 600, GetColor(255, 255, 255), TRUE);
	DrawStringToHandle(100, 200, "�Q�[���N���A",
		GetColor(80, 128, 255), g_largefont);
	//5�b�o������^�C�g����ʂ�
	if (g_lasttime - g_timerstart > 5000) {
		g_gamestate = GAME_TITLE;
	}
}
//�Q�[���I�[�o�[��ʕ`��
void DrawGameOver(){
	//�e�L�X�g�\��
	DrawStringToHandle(100, 200, "�Q�[���I�[�o�[",
		GetColor(255, 0, 0), g_largefont);
	//5�b�o������^�C�g����ʂ�
	if (g_lasttime - g_timerstart > 5000) g_gamestate = GAME_TITLE;
}

//�L�[�g���K�[����
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