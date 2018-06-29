//*****************************************************************************
//*****************************************************************************
//
//			�Q�[�� ���C������
//										�t�@�C���쐬��:
//										�t�@�C���쐬��:
//
//*****************************************************************************
//*****************************************************************************
#include	"iextreme.h"			//	IEX���C�u����(�S��)
#include	"system\System.h"
#include	"system\Framework.h"
#include	"Game.h"				//	�Q�[���ėp
#include	"Player.h"				//	�v���C���[
#include	"Frame.h"				//	�s���g
#include	"Enemy.h"				//�@�G�p
#include	"Effect.h"				//�@�G�t�F�N�g
#include	"MAP.h"					//  �}�b�v�`�b�v
#include	"UI.h"
#include	"BGFG.h"
#include	"Number.h"				//�@�i���o�[
#include	"Sound.h"				//�@�T�E���h
#include	"Stage_1.h"				//�@�X�e�[�W�P
#include	"sceneTitle.h"			//�@�V�[���^�C�g��
#include	"sceneOver.h"			//�@�Q�[���I�[�o�[
#include	"sceneClear.h"			//�@�Q�[���N���A
#include	"sceneMain.h"			//	�V�[�����C��

#define COUNT_DOWN (3)
//*****************************************************************************
//
//			�O���[�o���ϐ�
//										�쐬��:
//
//*****************************************************************************
//SPR_DATA main = SPR_DATA{ 0,0,0,1960,540,0,0,1960,540 };
SPR_DATA clear = { spr_data::GAMECLEAR,192,192,768,128,0,0,600,100 };


static IMG_DATA IMG_Main[] = {
	{ spr_data::BG1,"DATA\\BG\\bg.png" },
	{ spr_data::BG2,"DATA\\BG\\bg_case.png" },
	{ spr_data::BG3,"DATA\\BG\\bg_pc.png" },
	{ spr_data::BG4,"DATA\\BG\\bg_pipe.png" },

	{ spr_data::MAPCHIP1,"DATA\\BG\\mappanel_kari.png" },
	{ spr_data::UI1,"DATA\\UI\\pint_s.png" },
	{ spr_data::UI2,"DATA\\UI\\pint_a.png" },
	{ spr_data::UI3,"DATA\\UI\\flame_out.png" },
	{ spr_data::UI4,"DATA\\UI\\pint_l.png" },
	{ spr_data::UI5,"DATA\\UI\\bar.png" },
	{ spr_data::UI6,"DATA\\Public\\strings.png" },
	{ spr_data::UI7,"DATA\\UI\\face.png" }, //�v���C���[HP
	{ spr_data::UI8,"DATA\\UI\\CharIcon.jpg" },

	{ spr_data::Player1,"DATA\\CHR\\player\\Player.png" },
	{ spr_data::Enemy1,"DATA\\CHR\\enemy_kari.png" },
	{ spr_data::Enemy2,"DATA\\CHR\\enemy.png" },

	//{ spr_data::Ext,"DATA\\Public\\flash_star.png" },
	{ spr_data::Ext,"DATA\\Public\\enemy_extinction.png" },
	{ spr_data::Circle,"DATA\\Public\\Circle.png" },
	{ spr_data::TeleExt,"DATA\\Public\\Teleport.jpg" },
	{ spr_data::Player_eff,"DATA\\Public\\Player_effect.png" },
	{ spr_data::Mulch_eff,"DATA\\Public\\mulch_ef.png" },
	{ spr_data::EdgeCircle,"DATA\\UI\\pint_s2.png" },
	{ spr_data::Number,"DATA\\Public\\number.png" },
	{ spr_data::FADE_IN1 ,"DATA\\Public\\delta.png" },
	{ spr_data::FADE_OUT1,"DATA\\Public\\delta.png" },
	{ spr_data::FADE_IN2 ,"DATA\\Public\\white.png" },
	{ spr_data::FADE_OUT2,"DATA\\Public\\black.png" },

	{ spr_data::GAMECLEAR,"DATA\\Scene\\GAME_CLEAR.png" },

	{ -1,"" },
};

static SPR_DATA numbers[10] = {
	{ spr_data::Number2,64 * 0,64 ,192,64, -64,-32 },
	{ spr_data::Number,64 * 1,0 ,64,64, -32,-32,64,64 },
	{ spr_data::Number,64 * 2,0 ,64,64, -32,-32,64,64 },
	{ spr_data::Number,64 * 3,0 ,64,64, -32,-32,64,64 },
	{ spr_data::Number,64 * 4,0 ,64,64, -32,-32,64,64 },
	{ spr_data::Number,64 * 0,64,64,64,-32,-32,64,64 },
	{ spr_data::Number,64 * 1,64,64,64,-32,-32,64,64 },
	{ spr_data::Number,64 * 2,64,64,64,-32,-32,64,64 },
	{ spr_data::Number,64 * 3,64,64,64,-32,-32,64,64 },
	{ spr_data::Number,64 * 4,64,64,64,-32,-32,64,64 },

};
//*****************************************************************************
//
//			������
//										�쐬��:
//
//*****************************************************************************
bool sceneMain::Initialize()
{
	//	���ݒ�
	iexLight::SetFog(800, 1000, 0);		//	�t�H�O(2D�ł͔����Ӗ�)

										//	�J�����ݒ�
	view = new iexView();
	state = 0;
	count_down = 0;
	scene_timer = 0;
	fade_argb = 0xDD000000;

	//pPlayer;
	//pFrame;
	//pNumber;

	return true;
}

void sceneMain::UnInit() {

}

sceneMain::~sceneMain()
{

}


enum {
	LOAD,
	INIT,
	BEGIN,
	FADE_IN,
	READY,
	MAIN,
	FADE_OUT,
	GAMEOVER,
	GAMECLEAR,
};
//*****************************************************************************
//
//				�X�V
//										�쐬��:
//
//*****************************************************************************



//	���C���X�V����
void	sceneMain::Update()
{
	switch (state)
	{
	case LOAD:
		spr_data::Load(IMG_Main);
		state = INIT;
	case INIT:
		//break;
		stage_no = stage1;
		pPlayer->Init();
		pFrame->Init();
		pScore->Init();
		state = BEGIN;
	case BEGIN:
		//�����ݒ�
		pMAP->Init(&st1_bg);
		pLandScape->Init(stage_no);
		//pLandScape->setMainBG(&main, MainBG);

		//((BG*)bg)->Init();
		//bg->data(&main)
		//		fg->Init();
		pEffect_Manager->Init();
		//pEnemy_Manager->Init();
		//stageNo = SCENE_TITLE->bgNum;
		pEnemy_Manager->Init(stage_no);
		pEnemy_Kill->Init();
		pMAP->SetCenter((OBJ2D*)pPlayer);
		pNumber->Init();
		pUI->Init();
		IEX_StopSound(BGM_TITLE);
		IEX_PlaySound(BGM_MAIN, FALSE); //BGM

		count_down = 2;
		count_down_timer = 0;
		//-------------------------------------------------------------------
		timer = 80 * 60;
		scene_timer = 0;

		//	KEY_Vibration(200,200);
		state = FADE_IN;
	case FADE_IN:
		fade_argb = fade_in(fade_argb,0x11000000);
		if ( fade_argb<0x11000000 ) {
			fade_argb = 0x00000000;
			IEX_PlaySound(SE_COUNT, FALSE);	//�J�E���g�_�E��
			count_down_timer = 0;
			state = READY;
		}
		//pEffect_Manager->searchSet(V2(0, 0), V2(0, 0), fade_In);
		//state = READY;
	case READY:

		count_down_timer++;
		if (count_down_timer > 60) {
			count_down--;
			count_down_timer = 0;
			if (count_down >= 0)IEX_PlaySound(SE_COUNT, FALSE);	//�J�E���g�_�E��
		}
		if (count_down < 0)state = MAIN;
		//pPlayer->R_Update();
		//pFrame->R_Update();
		pPlayer->R_Update();
		pFrame->R_Update();
		pEnemy_Manager->Update();
		pEnemy_Manager->UIUpdate();
		pEffect_Manager->Update();
		pScore->Update();
		pMAP->Update();
		pNumber->Update(timer);
		pLandScape->Update();

		break;
	case MAIN:
		pPlayer->Update();
		pFrame->Update();
		pEnemy_Manager->Update();
		pEnemy_Manager->UIUpdate();
		pEffect_Manager->Update();
		pScore->Update();
		pMAP->Update();
		pNumber->Update(timer);
		pUI->Update();

		pLandScape->Update();



		//pNumber->Update();

		if (pPlayer->hp <= 0) {
			if ( scene_timer++>80 ) {
				state = GAMEOVER;
			}
		}
		else if ((pScore->getKill_num() >= CLEAR_KILLNUM) || timer <= 0) {
			if ( scene_timer++>140 ) {
				state = GAMECLEAR;
			}
		}
		else timer--;

		//�f�o�b�O�p
		//if (KEY_Get(KEY_SPACE) == 3) state = GAMEOVER;
		//else if (KEY_Get(KEY_ENTER) == 3) state = GAMECLEAR;

		if ( timer<=0 )timer = 0;
		
		if (KEY_Get(KEY_SPACE) && KEY_Get(KEY_ENTER)) {
			MainFrame->ChangeScene(new sceneTitle());
		}

		break;

	case GAMEOVER:
		fade_argb = fade_out(fade_argb,0x11000000);
		if ( fade_argb>0xCC000000 ) {
			fade_argb = 0xDD000000;
			MainFrame->ChangeScene(new sceneOver());
		}
		break;
	case GAMECLEAR:
		fade_argb = fade_out(fade_argb,0x11000000);
		if ( fade_argb>0xCC000000 ) {
			fade_argb = 0xDD000000;
			MainFrame->ChangeScene(new sceneClear());
		}
		break;
	default:
		break;
	}
}

//*****************************************************************************
//
//				�`��֘A
//										�쐬��:
//
//*****************************************************************************

//	���C���`�揈��
void	sceneMain::Render()
{

	pLandScape->RenderBG();
	pMAP->Render();
	pEnemy_Manager->Render();

	if ( (pScore->getKill_num()>=CLEAR_KILLNUM)||timer<=0 ) {
		iexPolygon::Rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0,0x44000000,0); //�Ó]
	}

	pEffect_Manager->Render();
	pPlayer->Render();

	if (!pFrame->exorciseDwon_flg) { //��͂�����Ε`��
		pEnemy_Manager->UIRender();
		pScore->Render();
	}
	pLandScape->RenderFG();
	pFrame->Render();
	if (!pFrame->exorciseDwon_flg) { //��͂�����Ε`��
		pMAP->MiniMapRender();
		pPlayer->UIRender();
	}
	pNumber->Render();
	pUI->Render();

	//pD_TEXT->Render();

	if ( (pScore->getKill_num()>=CLEAR_KILLNUM)||timer<=0 ) {
		spr_data::Render(V2(200,100),&clear); //GAMECLEAR����
	}

	switch (state)
	{
	case LOAD:
	case INIT:
	case BEGIN:
		break;
	case READY:
		pNumber->RenderFree(480 - 32, 270 - 96, count_down+1, 1, 64, 0xFFFFFFFF);
		break;
	case MAIN:
	case FADE_IN:
	case FADE_OUT:
	case GAMEOVER:
	case GAMECLEAR:
		iexPolygon::Rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0,fade_argb,0); //�Ó]
		break;
	default:
		break;
	}

	//pD_TEXT->Render();


}

