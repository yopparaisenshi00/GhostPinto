#include "iextreme.h"
#include "system\System.h"
#include "system\Framework.h"
#include "Game.h"
#include "sceneMain.h"
#include "sceneTitle.h"
#include "sceneOver.h"
#include "Enemy.h"
#include "Ranking.h"


SPR_DATA over = { 0,192,192,640,128,0,0,600,90 }; //GAMEOVER����
SPR_DATA over_back = { 8,0,0,960,540,0,0 }; //�Q�[���I�[�o�[���
SPR_DATA over_psb = { 7,0,1120,474,98,-474/2,-98/2}; //PushStartButton

IMG_DATA img_over[] = {
	{ 0,"DATA\\Scene\\GAME_OVER.png" }, //GAMEOVER����
	{ 7,"DATA\\Scene\\title.png" },
	{ 8,"DATA\\Scene\\over.png" }, //�Q�[���I�[�o�[���
	{ -1,"" },
};



//������
bool sceneOver::Initialize()
{
	iexLight::SetFog(800, 1000, 0);
	spr_data::Load(img_over);
	state = 0;
	timer = 0;
	fade_argb = 0xDD000000;		//�t�F�[�h�p
	return TRUE;
}

//���
sceneOver::~sceneOver()
{
	spr_data::Release();
	state = 0;
	timer = 0;
}

//�X�V
void sceneOver::Update()
{
	//timer++;
	//if ( timer>80&&KEY_Get(KEY_SPACE)==3 ) {
	//	state = 3;
	//}

}

//�`��
void sceneOver::Render()
{
	switch (state) {
		case 0: //�t�F�[�h�C��
			spr_data::Render(V2(0,0), &over_back); //�Q�[���N���A���
			iexPolygon::Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,0,fade_argb,0); //�t�F�[�h�C��
			fade_argb = fade_in(fade_argb,0x11000000);
			if ( fade_argb<=0x11000000 ) {
				fade_argb = 0x00000000;
				state++;
			}
			break;
		case 1:
			//spr_data::Render(V2(200, 200), &over); //�Q�[���I�[�o�[����
			spr_data::Render(V2(0, 0), &over_back); //�Q�[���I�[�o�[���
			//PushStartButton----------------------------------------------------
			if ( timer>=20 ) {
				if ( (timer%70*2)>=70 ) over_psb_argb = 0xFFFFFFFF;
				else over_psb_argb = 0x00000000;
				spr_data::Render(V2(480,500),&over_psb,over_psb_argb,0);
			}
			//-------------------------------------------------------------------
			if ( KEY_Get(KEY_SPACE)==3||timer>60*20 ) {
				//MainFrame->ChangeScene(new sceneTitle()); //�^�C�g����
				state++;
				timer = 0;
				fade_argb = 0x22000000;
			}
			timer++;
			break;
		case 2: //�t�F�[�h�A�E�g
			iexPolygon::Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,0,fade_argb,0);
			if ( timer>=25 ) {
				MainFrame->ChangeScene(new sceneTitle()); //�^�C�g����
				timer = 0;
			}
			timer++;
			//iexPolygon::Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,0,fade_argb,0);
			//fade_argb = fade_out(fade_argb,0x11000000);
			//if ( fade_argb>=0xEE000000 ) {
			//	fade_argb = 0xFF000000;
			//	MainFrame->ChangeScene(new sceneTitle()); //�^�C�g����
			//}
			break;
		default:
			break;
	}

	//char str[128];
	//sprintf_s(str, 128, "score:%d", pEnemy_Kill->getKill_num_Each(pink));
	//IEX_DrawText(str, 300, 300, 128, 16, 0xFFFF0000);
	//sprintf_s(str, 128, "kill:%d", pScore->kill_num);
	//IEX_DrawText(str, 300, 300, 128, 16, 0xFFFF0000);
}