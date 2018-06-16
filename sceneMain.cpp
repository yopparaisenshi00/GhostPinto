//*****************************************************************************
//*****************************************************************************
//
//			ゲーム メイン部分
//										ファイル作成者:
//										ファイル作成日:
//
//*****************************************************************************
//*****************************************************************************
#include	"iextreme.h"			//	IEXライブラリ(全般)
#include	"system\System.h"
#include	"system\Framework.h"
#include	"Game.h"				//	ゲーム汎用
#include	"Player.h"				//	プレイヤー
#include	"Frame.h"				//	ピント
#include	"Enemy.h"				//　敵用
#include	"Effect.h"				//　エフェクト
#include	"MAP.h"					//  マップチップ
#include	"UI.h"
#include	"BGFG.h"
#include	"Number.h"				//　ナンバー
#include	"Sound.h"				//　サウンド
#include	"Stage_1.h"				//　ステージ１
#include	"sceneTitle.h"			//　シーンタイトル
#include	"sceneOver.h"			//　ゲームオーバー
#include	"sceneClear.h"			//　ゲームクリア
#include	"sceneMain.h"			//	シーンメイン

#define COUNT_DOWN (3)
//*****************************************************************************
//
//			グローバル変数
//										作成者:
//
//*****************************************************************************
SPR_DATA main = SPR_DATA{ 0,0,0,1960,540,0,0,1960,540 };






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
	{ spr_data::UI7,"DATA\\UI\\face.png" }, //プレイヤーHP
	{ spr_data::UI8,"DATA\\UI\\CharIcon.jpg" },

	{ spr_data::Player1,"DATA\\CHR\\player\\Player.png" },
	{ spr_data::Enemy1,"DATA\\CHR\\enemy_kari.png" },
	{ spr_data::Enemy2,"DATA\\CHR\\enemy.png" },

	//{ spr_data::Ext,"DATA\\Public\\flash_star.png" },
	{ spr_data::Ext,"DATA\\Public\\enemy_extinction.png" },
	{ spr_data::Circle,"DATA\\Public\\Circle.png" },
	{ spr_data::TeleExt,"DATA\\Public\\Teleport.jpg" },
	{ spr_data::Player_eff,"DATA\\Public\\Player_effect.png" },
	{ spr_data::EdgeCircle,"DATA\\UI\\pint_s2.png" },
	{ spr_data::Number,"DATA\\Public\\number.png" },
	{ spr_data::FADE_IN1 ,"DATA\\Public\\delta.png" },
	{ spr_data::FADE_OUT1,"DATA\\Public\\delta.png" },
	{ spr_data::FADE_IN2 ,"DATA\\Public\\black.png" },
	{ spr_data::FADE_OUT2,"DATA\\Public\\black.png" },
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
//			初期化
//										作成者:
//
//*****************************************************************************
bool sceneMain::Initialize()
{
	//	環境設定
	iexLight::SetFog(800, 1000, 0);		//	フォグ(2Dでは半無意味)

										//	カメラ設定
	view = new iexView();
	state = 0;
	count_down = 0;
	scene_timer = 0;

	pPlayer;
	pFrame;
	pNumber;

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
	BIGEN,
	FADE_IN,
	READY,
	MAIN,
	FADE_OUT,
	GAMEOVER,
	GAMECLEAR,
};
//*****************************************************************************
//
//				更新
//										作成者:
//
//*****************************************************************************



//	メイン更新処理
void	sceneMain::Update()
{
	switch (state)
	{
	case LOAD:
		spr_data::Load(IMG_Main);
		state = INIT;
	case INIT:
		//break;
		stage_no = 0;
		pPlayer->Init();
		pFrame->Init();
		pScore->Init();
		state = BIGEN;
	case BIGEN:
		//初期設定
		pMAP->init(&st1_bg);
		pLandScape->Init(stage_no);
		pLandScape->setMainBG(&main, MainBG);

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
		IEX_StopSound(BGM_TITLE);
		IEX_PlaySound(BGM_MAIN, FALSE); //BGM

		count_down = 4;
		count_down_timer = 0;
		//-------------------------------------------------------------------
		timer = 80 * 60;
		scene_timer = 0;

		//	KEY_Vibration(200,200);
		state = FADE_IN;
	case FADE_IN:
		//pEffect_Manager->searchSet(V2(0, 0), V2(0, 0), fade_In);
		state = READY;
	case READY:

		count_down_timer++;
		if (count_down_timer > 60) {
			count_down--;
			count_down_timer = 0;
		}
		if (count_down < 0)state = MAIN;
		pPlayer->R_Update();
		pFrame->R_Update();
		pEnemy_Manager->Update();
		pEnemy_Manager->UIUpdate();
		pEffect_Manager->Update();
		pScore->Update();
		pMAP->update();
		//bg->Update();
		//fg->Update();
		pNumber->Update(timer);
		pLandScape->Update();

		break;
	case MAIN:
		pPlayer->Update();
		pFrame->Update();
		pEnemy_Manager->Update();
		pEnemy_Manager->UIUpdate();
		pEffect_Manager->Update();
		pLandScape->Update();
		pScore->Update();
		pMAP->update();
		pNumber->Update(timer);

		pLandScape->Update();



		//pNumber->Update();

		if (pPlayer->hp <= 0 /*|| KEY_Get(KEY_SPACE) == 3*/) {
			//if ( scene_timer++>60 ) {
			state = GAMEOVER;
			//}
		}
		else if (pScore->getKill_num() >= 50 || timer < 0 /*|| KEY_Get(KEY_ENTER) == 3*/) {
			//if ( scene_timer++>60 ) {
			state = GAMECLEAR;
			//}
		}

		timer--;
		break;
	case GAMEOVER:
		MainFrame->ChangeScene(new sceneOver());


		break;
	case GAMECLEAR:
		MainFrame->ChangeScene(new sceneClear());

		break;

	default:
		break;
	}
}

//*****************************************************************************
//
//				描画関連
//										作成者:
//
//*****************************************************************************

//	メイン描画処理
void	sceneMain::Render()
{
	//bg->Render();
	pLandScape->RenderBG();
	pMAP->Render();
	pEnemy_Manager->Render();
	pEffect_Manager->Render();
	pPlayer->Render();


	if (!pFrame->exorciseDwon_flg) { //霊力があれば描画
		pEnemy_Manager->UIRender();
		//pFrame->Render();   
		pScore->Render();
	}

	pLandScape->RenderFG();

	pFrame->Render();
	if (!pFrame->exorciseDwon_flg) { //霊力があれば描画

		pMAP->MiniMapRender();

		pPlayer->UIRender();
	}
	pNumber->Render();
	pUI->Render();

	switch (state)
	{
	case READY:
		pNumber->RenderFree(480 - 32, 270 - 96, count_down, 1, 64, 0xFFFFFFFF);
		break;
	default:
		break;
	}

	pD_TEXT->Render();

}

