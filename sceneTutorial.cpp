//*****************************************************************************
//*****************************************************************************
//
//			ゲーム チュートリアル部分
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
#include	"stagetuto.h"				//　サウンド

#include	"sceneTitle.h"			//　シーンタイトル
#include	"sceneOver.h"			//　ゲームオーバー
#include	"sceneClear.h"			//　ゲームクリア
#include	"sceneMain.h"			//	シーンメイン
#include	"sceneTutorial.h"		//	シーンチュートリアル
#include	"tutorial_move.h"		//　チュートリアル行動関数

static IMG_DATA IMG_Tutorial[] = {
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
	{ spr_data::UI9 ,"DATA\\public\\hukidasi.png" },
	{ spr_data::UI10,"DATA\\public\\tuto_key.png" },
	{ spr_data::Player1,"DATA\\CHR\\player\\Player.png" },
	{ spr_data::Enemy1,"DATA\\CHR\\enemy_kari.png" },
	{ spr_data::Enemy2,"DATA\\CHR\\enemy.png" },
	{ spr_data::Enemy3,"DATA\\UI\\master.png" },

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
	{ spr_data::FADE_IN2 ,"DATA\\Public\\black.png" },
	{ spr_data::FADE_OUT2,"DATA\\Public\\black.png" },
	{ -1,"" },
};



//*****************************************************************************
//プロトタイプ宣言
//*****************************************************************************
void center_move(OBJ2D* obj);
//void tuto_operator_move(OBJ2D* obj);
//*****************************************************************************
//
//			初期化
//										作成者:
//
//*****************************************************************************
bool sceneTutorial::Initialize()
{
	//	環境設定
	iexLight::SetFog(800, 1000, 0);		//	フォグ(2Dでは半無意味)

										//	カメラ設定
	view = new iexView();
	state = 0;
	count_down = 0;
	scene_timer = 0;

	//pPlayer;
	//pFrame;
	//pNumber;

	return true;
}

void sceneTutorial::UnInit() {

}


sceneTutorial::~sceneTutorial()
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
//				更新
//										作成者:
//
//*****************************************************************************



//	メイン更新処理
void	sceneTutorial::Update()
{
	switch (state)
	{
	case LOAD:
		spr_data::Load(IMG_Tutorial);
		state = INIT;
	case INIT:
		//break;
		stage_no = tutorial;
		pPlayer->Init(V2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
		pFrame->Init();
		pScore->Init();
		center.Init();
		state = BEGIN;

	case BEGIN:
		//初期設定

		pMAP->Init(&tutorial_bg);
		pLandScape->Init(stage_no);

		pEffect_Manager->Init();
		
		pEnemy_Manager->Init(stage_no);
		pEnemy_Kill->Init();
		//pMAP->SetCenter(&center);
		pNumber->Init();
		IEX_StopSound(BGM_TITLE);
		IEX_PlaySound(BGM_MAIN, FALSE); //BGM
		tuto_operator.Init();

		count_down = COUNT_DOWN_TIME;
		count_down_timer = 0;
		//-------------------------------------------------------------------
		scene_timer = 0;

		//	KEY_Vibration(200,200);
		state = FADE_IN;
	case FADE_IN:
		//pEffect_Manager->searchSet(V2(0, 0), V2(0, 0), fade_In);
		state = READY;
	case READY:
		state = MAIN;
	case MAIN:
		
		pPlayer->Update();
		pFrame->Update();
		pEnemy_Manager->Update();
		pEnemy_Manager->UIUpdate();
		pEffect_Manager->Update();
		//pScore->Update();
		pMAP->Update();
		pNumber->Update(timer);
		pLandScape->Update();
		tuto_operator.Update();
		//pD_TEXT->set_Text(center.pos, "cpos", center.pos, 0xFFFF0000);

		timer--;
		
		//if () {
		//	
		//}
		break;
	case GAMEOVER:
		MainFrame->ChangeScene(new sceneOver());
		
		break;
	case GAMECLEAR:
		MainFrame->ChangeScene(new sceneMain());

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
void	sceneTutorial::Render()
{
	//bg->Render();
	pLandScape->RenderBG();
	pMAP->Render();
	pEnemy_Manager->Render();
	pEffect_Manager->Render();
	pPlayer->Render();


	if (!pFrame->exorciseDwon_flg) { //霊力があれば描画
		pEnemy_Manager->UIRender();
		pScore->Render();
	}

	pLandScape->RenderFG();
	pFrame->Render();
	if (!pFrame->exorciseDwon_flg) { //霊力があれば描画
		pPlayer->UIRender();
	}
	//pNumber->Render();
	pUI->Render();

	tuto_operator.Render();

	switch (state)
	{
	case READY:
		pNumber->RenderFree(480 - 32, 270 - 96, count_down, 1, 64, 0xFFFFFFFF);
		break;
	default:
		break;
	}

	//pD_TEXT->Render();

}


void center_move(OBJ2D* obj) {
	switch (obj->state)
	{
	case 0:
		obj->pos = pPlayer->pos;
		obj->sc_w = SCROLL_RIGHT;
		obj->sc_h = SCREEN_HEIGHT/ 2;
		obj->state++;
	case 1:

	default:
		break;
	}

}




//------------------------------------------------------------
//		プレイヤー操作移動説明
//------------------------------------------------------------

void TutoOperater::Init() {
	operater.clear();
	master_char.clear();
	state = 0;
	clear_flg = 0;
	ZeroMemory(iwork, sizeof(iwork));
	master_char.clear();

}

void TutoOperater::pagenext() {
	if ((operater.data + 1)->no < 0) {
		iwork[messege_end] |= TRUE;
	}
	if (!iwork[messege_end] && KEY_Get(KEY_C) == 3) {
		operater.data++;
	}
}


void move_key(OBJ2D* obj);

void TutoOperater::Update() {
	if(state > 0 && KEY_Get(KEY_SELECT) == 3){
		state = END;
	}

	switch (state)
	{
	case 0:
		//メンバ変数初期化
		operater.clear();
		suboperater.clear();
		master_char.clear();

		state = BEGIN;
	case BEGIN:
		////////////////////////////////
		//チュートリアルアイコンキャラ//
		////////////////////////////////
		//位置設定 (画面右下)
		master_char.pos = V2(SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128);
		//画像設定 
		master_char.data = &spr_tutomaster;
		//////////////////////////
		//チュートリアル吹き出し//
		//////////////////////////

		//位置設定 (画面右下)
		operater.pos = V2(SCREEN_WIDTH - 156, SCREEN_HEIGHT - 32);
		//画像設定 (未設定)
		operater.data = NULL;
		
		//ステート切り替え(ゲームルール説明)
		state = GAMERULE_BEGIN;
		//break;
	case GAMERULE_BEGIN:
		//画像設定(ゲームルール説明)
		operater.data = spr_gamerulr;
		state = GAMERULE;
		//break;
	case GAMERULE:
		if (KEY_Get(KEY_C) == 3 && iwork[messege_end]) {
			state = PLAYER_MOVE_BEGIN;
		}

		pagenext();
		break;
	case PLAYER_MOVE_BEGIN:
		ZeroMemory(iwork, sizeof(iwork));
		//プレイヤー移動説明
		suboperater.move = &move_key;
		operater.data = spr_player_move;
		state = PLAYER_MOVE;
		//break;
	case PLAYER_MOVE:
		
		//XYそれぞれ９割以上スティックが倒された
		if (iwork[messege_end]) {
			if (KEY_Get(KEY_AXISY) > 900) {
				iwork[move_y_ok] = TRUE;
			}
			if (KEY_Get(KEY_AXISX) > 900) {
				iwork[move_x_ok] = TRUE;
			}
			if (KEY_Get(KEY_AXISY) < -900) {
				iwork[move_y_ok] = TRUE;
			}
			if (KEY_Get(KEY_AXISX) < -900) {
				iwork[move_x_ok] = TRUE;
			}
		}
		
		if (iwork[move_x_ok] && iwork[move_y_ok]) {
			state = PINTO_MOVE_BEGIN;
		}
		
		pagenext();
		break;
	case PINTO_MOVE_BEGIN://プレイヤーの移動方法
		ZeroMemory(iwork, sizeof(iwork));
		operater.data = spr_pinto_move;
		state = PINTO_MOVE;
		//break;
	case PINTO_MOVE:
		
		if (iwork[messege_end]) {
			if (KEY_Get(KEY_AXISY2) > 900) {
				iwork[move_y_ok] = TRUE;
			}
			if (KEY_Get(KEY_AXISY2) < -900) {
				iwork[move_x_ok] = TRUE;
			}
		}

		if (iwork[move_x_ok] && iwork[move_y_ok] && iwork[messege_end]) {
			state = ENEMY_DWON_BEGIN;
		}

		pagenext();
		break;
	case ENEMY_DWON_BEGIN://敵の倒し方
		ZeroMemory(iwork, sizeof(iwork));
		operater.data = spr_out_enemy_move;
		state = ENEMY_DWON;
	
		break;
	case ENEMY_DWON:
		
		if (iwork[messege_end] && !iwork[enemy_pop]) {
			iwork[enemy_pop] |= TRUE;
			pEnemy_Manager->searchSet(V2(720, 320), V2(0, 0), tuto_Base, 30);
			pEnemy_Manager->searchSet(V2(720, 200), V2(0, 0), tuto_Base, -30);
		}
		if (pScore->getKill_num() >= 2 && iwork[messege_end]) {
			state = PINTO_LOCK_BEGIN; 
		}
		
		pagenext();
		break;
	case PINTO_LOCK_BEGIN:
		ZeroMemory(iwork, sizeof(iwork));
		operater.data = spr_pintrock_move;
		state = PINTO_LOCK;
		//break;
	case PINTO_LOCK:

		if (iwork[messege_end] && !iwork[enemy_pop]) {
			iwork[enemy_pop] |= TRUE;
			pEnemy_Manager->searchSet(V2(720, 320), V2(0, 0), tuto_rock, 30);
			pEnemy_Manager->searchSet(V2(720, 200), V2(0, 0), tuto_rock, -30);
		}


		if (pScore->getKill_num() >= 4 && iwork[messege_end]) {
			state = EXORCISE_BEGIN;
		}
		pagenext();

		break;
	case EXORCISE_BEGIN://霊力ゲージ説明
		ZeroMemory(iwork, sizeof(iwork));
		operater.data = spr_exorcise_move;
		state = EXORCISE;
		//break;
	case EXORCISE:
		pFrame->add_Exorcise(-(EXORCISE_MAX+1));
		
		if (iwork[messege_end] && KEY_Get(KEY_C) == 3) {
			state = MULTIFOCUS_BEGIN;
			pFrame->exorciseDwon_flg = false;
			pFrame->add_Exorcise(EXORCISE_MAX);
		}

		pagenext();
		break;
	//マルチフォーカス説明
	case MULTIFOCUS_BEGIN:
		ZeroMemory(iwork, sizeof(iwork));
		operater.data = spr_multifocus_move;
		state = MULTIFOCUS;
	case MULTIFOCUS:

		if (!iwork[enemy_pop] && iwork[messege_end]) {
			pEnemy_Manager->searchSet(V2(720, 320), V2(0, 0), tuto_multifocus, 30);
			pEnemy_Manager->searchSet(V2(720, 200), V2(0, 0), tuto_multifocus, -30);
			iwork[enemy_pop] |= TRUE;
		}
		pPlayer->mltfcs.add_point(10);
		
		if (pScore->getKill_num() >= 6 && iwork[messege_end]) {
			state = REGAMERULE_BEGIN;
		}
		pagenext();

		break;
		//再ゲーム説明
	case REGAMERULE_BEGIN:
		ZeroMemory(iwork, sizeof(iwork));
		operater.data = spr_gamerule_move;
		state = REGAMERULE;
		//break;
	case REGAMERULE:
	
		if (iwork[messege_end] && KEY_Get(KEY_SELECT)) {
			state = END;
		}
	
		pagenext();
		break;
	default:
		break;
	}
	if (state == END) {
		MainFrame->ChangeScene(new sceneMain());
	}
	//pD_TEXT->set_Text(V2(200,100),"state",state,0xFFFFFF0000);
}
void TutoOperater::Render() {
	operater.Render();
	//suboperater.Render();
	master_char.Render();
}
void TutoOperater::clear() {
	operater.clear();
	suboperater.clear();
	master_char.clear();

}

TutoOperater::TutoOperater()
{
	Init();
}

TutoOperater::~TutoOperater()
{

}

SPR_DATA tuto_move = { spr_data::UI10,128,0,256,256,-128,-128 ,0 };
void move_key(OBJ2D* obj) {
	switch (obj->state)
	{
	case 0:
		obj->data = &tuto_move;//R1 吹き出しデータ
		obj->state++;
	case 1:
		obj->pos = pPlayer->pos;
		break;
	default:
		break;
	}
}