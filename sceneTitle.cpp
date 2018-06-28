#include "iextreme.h"
#include "system\System.h"
#include "system\Framework.h"

#include "Game.h"
#include "Player.h"
#include "MAP.h"
#include "Effect.h"
#include "Frame.h"
#include "BGFG.h"
#include "Sound.h"
#include "sceneMain.h"
#include "sceneTitle.h"
#include "sceneTutorial.h"


enum {
	INIT,
	READY,
	MAIN,
	FADE_OUT,
	FADE_IN,
	TUTORIAL,
};


//背景
SPR_DATA s_title = { 0,0,0,1024,604,-512,-302,90};
//主人公
SPR_DATA s_titleChar = { 0,0,608,624,536,-624 / 2,-536 / 2};
//PressStartButton
SPR_DATA s_ppsk = { 0,0,1120,474,98,-474 / 2,-98 / 2 ,0};
//0, 1013, 409, 35
//タイトルロゴ
SPR_DATA s_titleName = { 0,0,1216,440,400 ,-440 / 2,-400 / 2,0 };
//大幽霊
SPR_DATA big_ghost = { 0,608,800,318,258 ,-318 / 2,-258 / 2, 30};
//小幽霊
SPR_DATA min_ghost = { 0,608,608,158,186 ,-158 / 2,-186 / 2 ,60};

//主人公
//0 * 540
//560 * 473
//
//PressStartButton
//0 * 1013
//409 * 35
//
//タイトルロゴ
//560 * 540
//376 * 312
//
//大幽霊
//560 * 852
//254 * 193
//
//小幽霊
//814 * 852
//93 * 121

//SPR_DATA s_title =		{ spr_data::BG1,0	,0	,960,540,0,0,90 };
//SPR_DATA s_titleChar =	{ spr_data::BG2,0	,0	,560,473,-560/2	,-473/2,60};
//SPR_DATA s_titleName =	{ spr_data::BG2,560	,0	,376,312,-376/2	,-312/2,0 };
//SPR_DATA s_ppsk =		{ spr_data::BG2,0	,474,474,35	,-474 /2,-35 /2,-30 };
//
//SPR_DATA s_Enemy_b = { spr_data::BG2,561,310,256,200,256/2,200/2,20 };
//SPR_DATA s_Enemy_s = { spr_data::BG2,561 + 256,310,256,200,256 / 2,200 / 2,20 ,60};
SPR_DATA s_tutorial=	{ spr_data::BG3,0	,0	,960,540,-960/2,-540/2,0};

IMG_DATA img_title[] = {
	{ spr_data::BG1,"DATA\\Scene\\title.png" },
	//{ spr_data::BG2,"DATA\\Scene\\titleobj.png" },

	{ spr_data::BG3,"DATA\\Scene\\tuto_kari.jpg"},

//	{ 0,"DATA\\Scene\\.png" }, //pushEnter
//	{ 0,"DATA\\Scene\\.png" }, //３．２．１　GO！
	{ spr_data::FADE_IN1 ,"DATA\\Public\\delta.png" },
	{ spr_data::FADE_OUT1,"DATA\\Public\\delta.png" },
	{ spr_data::PLATE, "tuto_kari.jpg" },
	{ spr_data::Player_eff,"DATA\\Public\\Player_effect.png" },
	{ spr_data::EdgeCircle,"DATA\\UI\\pint_s2.png" },
	{ spr_data::Player1,"DATA\\CHR\\player\\Player.png" },

	{-1,""},
};

//初期化
bool sceneTitle::Initialize()
{
	
	timer = 0;
	state = 0;
	dust_timer = 150;
	key_flg = false;
	iexLight::SetFog(800, 1000, 0);
	spr_data::Load(img_title);
	bg.clear();
	ppsk.clear();
	titleChar.clear();
	titleName.clear();
	IEX_StopSound(BGM_MAIN);
	IEX_PlaySound(BGM_TITLE, TRUE); //BGM

	return TRUE;
}

//解放
sceneTitle::~sceneTitle()
{
	spr_data::Release();
}

#define PPSK_POS (V2(SCREEN_WIDTH/2,500))
#define TNAME_POS (V2(686,142))
#define EMIN_POS (V2(386,108))
#define EBIG_POS (V2(806,406))
//#define TCHR_POS (V2(292,282))
#define TCHR_POS (V2(292,252))


//更新
void sceneTitle::Update()
{
	switch (state)
	{
	case INIT://初期設定
		//メイン背景設定
		bg.data = &s_title;
		bg.pos = V2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

		//スタートロゴ設定
		ppsk.data = &s_ppsk;
		ppsk.pos = PPSK_POS;

		//キャラ画像ロゴ設定
		titleChar.data = &s_titleChar;
		titleChar.pos = TCHR_POS;

		//ゲームタイトル画像設定
		titleName.data = &s_titleName;
		titleName.pos = TNAME_POS;

		//エネミーBIG画像設定
		s_Enemy_b.data = &big_ghost;
		s_Enemy_b.pos = EBIG_POS;

		//エネミーMIN画像設定
		s_Enemy_s.data = &min_ghost;
		s_Enemy_s.pos = EMIN_POS;
		//エフェクト初期化
		pEffect_Manager->Init();
		//プレイヤー初期化
		pPlayer->Init();
		//フレーム初期化
		pFrame->Init();

		//フェードイン処理へ
		state = FADE_IN;

		//break;
	case FADE_IN:
		//		pEffect_Manager->searchSet(V2(0,0),V2(0,0),fade_In);

				// メイン処理へ
		state = MAIN;
		//break;
	case MAIN:

		//塵エフェクト
		if ( dust_timer++>=150 ) {
			for ( int i = 0; i<4; i++ ){
				pEffect_Manager->searchSet(
					V2(250*i+(rand()%50+100), SCREEN_HEIGHT-(rand()%200)),				//x=400*i-600*i,y=440-540
					V2((float)(rand()%2)/100.0f+0.02f, -(float)(rand()%2+1)), dust);	//x=0.04f-0.07f,y=-(1-3)
			}
			dust_timer = 0;
		}

		//キャラクター上下(ふわふわ)
		titleChar.pos.y += sinf(titleChar.timer++*0.05f)*0.3f;

		//PSB点滅
		if(0<timer && timer<30) Frash_Color(&ppsk,3,0xFFFFFFFF,0x00000000); //早
		else if ( 30<=timer && timer<50 ) ppsk.custom.argb = 0xFFFFFFFF;
		else Frash_Color(&ppsk,45,0x00000000,0xFFFFFFFF); //遅



		if ( KEY_Get(KEY_SPACE)==3 ) key_flg = true;
		if ( key_flg ) timer++;

		if ( timer>=50 ) {
			state = TUTORIAL;
			//			pEffect_Manager->searchSet(V2(960, 0), V2(0, 0), fade_Out);
			timer = 0;
			
			ppsk.clear();
			titleChar.clear();
			titleName.clear();
			s_Enemy_s.clear();
			s_Enemy_b.clear();
			pFrame->clear();
		}

		//{
		//	static int moveobj_data_no = 0;
		//	OBJ2D* moveObj;
		//	if (KEY_Get(KEY_C) == 3) {
		//		moveobj_data_no++;
		//		if (moveobj_data_no > 5)moveobj_data_no = 0;
		//	}
		//	moveObj = moveobj_data[moveobj_data_no];

		//	if (moveObj)
		//	{
		//		if (KEY_Get(KEY_UP))moveObj->pos.y += 2;
		//		if (KEY_Get(KEY_DOWN))moveObj->pos.y -= 2;
		//		if (KEY_Get(KEY_LEFT))moveObj->pos.x += 2;
		//		if (KEY_Get(KEY_RIGHT))moveObj->pos.x -= 2;
		//	}
		//	pD_TEXT->set_Text(moveObj->pos, "pos", moveObj->pos, 0xFFFFFFFF);
		//}

		pEffect_Manager->Update();
		pFrame->f_move();

		break;



	case TUTORIAL:
		MainFrame->ChangeScene(new sceneTutorial);

		pPlayer->Update();
		break;
	case FADE_OUT:
//		pEffect_Manager->Update();
//		if (timer++ > 120) {
			MainFrame->ChangeScene(new sceneMain);
//		}
	default:
		break;
	}

}

//描画
void sceneTitle::Render()
{
	if (bg.data) {
		float sz = pFrame->get_sz((float)bg.data->frameNum);
		shader2D->SetValue("FPower", sz > 90 ? (180 - sz) / 90 : sz / 90);
		bg.Render("depth");
	}
	//	spr_data::Render(V2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), bg, 0xFFFFFFFF, (float)0, shader2D, "depth");	
	//spr_data::Render(V2(titleChar->dw + titleChar->ofsx, SCREEN_HEIGHT + titleChar->ofsy), titleChar);

	if (titleChar.data) {
		float sz = pFrame->get_sz(titleChar.data->frameNum);
		shader2D->SetValue("FPower", sz > 90 ? (180 - sz) / 90 : sz / 90);
		titleChar.Render();
	}

	if (titleName.data) {
		float sz = pFrame->get_sz(titleName.data->frameNum);
		shader2D->SetValue("FPower", sz > 90 ? (180 - sz) / 90 : sz / 90);
		titleName.Render("depth");
	}

	//spr_data::Render(V2(SCREEN_WIDTH + titleName->ofsx, titleName->dh + titleName->ofsy), titleName, 0xFFFFFFFF, (float)0, shader2D, "depth");
	

	if (s_Enemy_b.data) {
		float sz = pFrame->get_sz((float)s_Enemy_b.data->frameNum);
		shader2D->SetValue("FPower", sz > 90 ? (180 - sz) / 90 : sz / 90);
		s_Enemy_b.Render("depth");
		//spr_data::Render(V2(s_Enemy_b->ofsx, s_Enemy_b->ofsy) + EMIN_POS, s_Enemy_b, 0xFFFFFFFF, (float)0, shader2D, "depth");
	}
	if (s_Enemy_s.data ) {
		float sz = pFrame->get_sz((float)s_Enemy_s.data->frameNum);
		shader2D->SetValue("FPower", sz > 90 ? (180 - sz) / 90 : sz / 90);
		s_Enemy_s.Render("depth");
		//spr_data::Render(V2(s_Enemy_s->ofsx, s_Enemy_s.->ofsy) + EMIN_POS, s_Enemy_s, 0xFFFFFFFF, (float)0, shader2D, "depth");
	}
	if (ppsk.data) {
		ppsk.Render();
		//spr_data::Render(V2(ppsk->ofsx, ppsk->ofsy) + PPSK_POS, ppsk, 0xFFFFFFFF, (float)0, shader2D, "depth");
	}

	if(state == TUTORIAL)pPlayer->Render();

	if ( state==MAIN ) pEffect_Manager->Render();
	iexPolygon::Rect(0,0, 960, 540,0x00000000,0);
	//pD_TEXT->Render();
}

//タイトル
void Base(OBJ2D* obj) {
	switch (obj->state)
	{
	case INIT:	//初期設定
		obj->Init();
		break;
	case 1: //死亡処理
		break;
	default:
		break;
	}
}
void Sin(OBJ2D* obj) {
	switch (obj->state)
	{
	case INIT:	//初期設定
		break;
	case 1: //死亡処理
		obj->key++;
		while (obj->key > 360) {
			obj->key -= 360;
		}
		sinf(obj->key);
		obj->key /= 0.01745;
		break;
	default:
		break;
	}
}
