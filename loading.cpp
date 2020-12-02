#include "loading.h"

ImageHandles g_imghandles;

BOOL LoadGameImage(){
	
	if ((g_imghandles.title = LoadGraph("media\\title.png")) == -1) return FALSE;

	if ((g_imghandles.interior[0] = LoadGraph("media\\interior0.png")) == -1) return FALSE;
	if ((g_imghandles.interior[1] = LoadGraph("media\\interior1.png")) == -1) return FALSE;
	if ((g_imghandles.interior[2] = LoadGraph("media\\interior2.jpg")) == -1) return FALSE;
	if ((g_imghandles.interior[3] = LoadGraph("media\\interior3.png")) == -1) return FALSE;
	if ((g_imghandles.interior[4] = LoadGraph("media\\interior4.png")) == -1) return FALSE;
	if ((g_imghandles.interior[5] = LoadGraph("media\\interior5.png")) == -1) return FALSE;
	if ((g_imghandles.interior[6] = LoadGraph("media\\interior6.jpg")) == -1) return FALSE;
	if ((g_imghandles.interior[7] = LoadGraph("media\\interior7.jpg")) == -1) return FALSE;
	if ((g_imghandles.interior[8] = LoadGraph("media\\interior8.jpg")) == -1) return FALSE;
	if ((g_imghandles.interior[9] = LoadGraph("media\\interior9.jpg")) == -1) return FALSE;

	if ((g_imghandles.village[0] = LoadGraph("media\\village0.png")) == -1) return FALSE;
	if ((g_imghandles.village[1] = LoadGraph("media\\village1.png")) == -1) return FALSE;
	if ((g_imghandles.village[2] = LoadGraph("media\\village2.png")) == -1) return FALSE;
	if ((g_imghandles.village[3] = LoadGraph("media\\village3.png")) == -1) return FALSE;
	if ((g_imghandles.village[4] = LoadGraph("media\\village4.png")) == -1) return FALSE;
	if ((g_imghandles.village[5] = LoadGraph("media\\village5.png")) == -1) return FALSE;
	if ((g_imghandles.village[6] = LoadGraph("media\\village6.png")) == -1) return FALSE;
	if ((g_imghandles.village[7] = LoadGraph("media\\village7.png")) == -1) return FALSE;

	if ((g_imghandles.field[0] = LoadGraph("media\\field0.png")) == -1) return FALSE;
	if ((g_imghandles.field[1] = LoadGraph("media\\field1.png")) == -1) return FALSE;
	if ((g_imghandles.field[3] = LoadGraph("media\\field3.png")) == -1) return FALSE;
	if ((g_imghandles.field[4] = LoadGraph("media\\field4.png")) == -1) return FALSE;
	if ((g_imghandles.field[5] = LoadGraph("media\\field5.png")) == -1) return FALSE;
	if ((g_imghandles.field[6] = LoadGraph("media\\field6.png")) == -1) return FALSE;
	if ((g_imghandles.field[7] = LoadGraph("media\\field7.png")) == -1) return FALSE;
	if ((g_imghandles.field[8] = LoadGraph("media\\field8.png")) == -1) return FALSE;
	if ((g_imghandles.field[9] = LoadGraph("media\\field9.png")) == -1) return FALSE;

	if ((g_imghandles.hero[ANIMFRAME] = LoadDivGraph("media\\hero2.png", 12, 3, 4, 40, 40, g_imghandles.hero)) == -1) return FALSE;
//	if ((g_imghandles.hero[ANIMFRAME] = LoadDivGraph("media\\hero.png", 12, 3, 4, 46, 48, g_imghandles.hero)) == -1) return FALSE;

	return TRUE;
}
