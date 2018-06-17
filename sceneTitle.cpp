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

#define PPSK_POS (V2(SCREEN_WIDTH,500))
enum {
	INIT,
	READY,
	MAIN,
	FADE_OUT,
	FADE_IN,
	TUTORIAL,
};

//ŽålŒö
//0 * 540
//560 * 473
//
//PressStartButton
//0 * 1013
//409 * 35
//
//ƒ^ƒCƒgƒ‹ƒƒS
//560 * 540
//376 * 312
//
//‘å—H—ì
//560 * 852
//254 * 193
//
//¬—H—ì
//814 * 852
//93 * 121

SPR_DATA s_title =		{ spr_data::BG1,0	,0	,960,540,0,0,90 };
SPR_DATA s_titleChar =	{ spr_data::BG2,0	,0	,560,473,-560/2	,-473/2,60};
SPR_DATA s_titleName =	{ spr_data::BG2,560	,0	,376,312,-376/2	,-312/2,0 };
SPR_DATA s_ppsk =		{ spr_data::BG2,0	,474,474,35	,-474 /2,-35 /2,-30 };

SPR_DATA s_tutorial=	{ spr_data::BG3,0	,0	,960,540,0,0,0 };

IMG_DATA img_title[] = {
	{ spr_data::BG1,"DATA\\Scene\\title.png" },
	{ spr_data::BG2,"DATA\\Scene\\titleobj.png" },

	{ spr_data::BG3,"DATA\\Scene\\tuto_kari.jpg"},

//	{ 0,"DATA\\Scene\\.png" }, //pushEnter
//	{ 0,"DATA\\Scene\\.png" }, //‚RD‚QD‚P@GOI
	{ spr_data::FADE_IN1 ,"DATA\\Public\\delta.png" },
	{ spr_data::FADE_OUT1,"DATA\\Public\\delta.png" },
	{ spr_data::PLATE, "tuto_kari.jpg" },
	{ spr_data::Player_eff,"DATA\\Public\\Player_effect.png" },
	{ spr_data::EdgeCircle,"DATA\\UI\\pint_s2.png" },
	{ spr_data::Player1,"DATA\\CHR\\player\\Player.png" },


	{-1,""},
};

//‰Šú‰»
bool sceneTitle::Initialize()
{
	
	timer = 0;
	state = 0;
	iexLight::SetFog(800, 1000, 0);
	spr_data::Load(img_title);
	bg = nullptr;
	ppsk = nullptr;
	titleChar = nullptr;
	titleName = nullptr;
	IEX_StopSound(BGM_MAIN);
	IEX_PlaySound(BGM_TITLE, TRUE); //BGM

	return TRUE;
}

//‰ð•ú
sceneTitle::~sceneTitle()
{
	spr_data::Release();
}

//XV
void sceneTitle::Update()
{
	switch (state)
	{
	case INIT:
		bg		 =	&s_title;
		ppsk =		&s_ppsk;
		titleChar = &s_titleChar;
		titleName = &s_titleName;
		pEffect_Manager->Init();
		pPlayer->Init();
		pFrame->Init();
		state = FADE_IN;

		//break;
	case FADE_IN:
//		pEffect_Manager->searchSet(V2(0,0),V2(0,0),fade_In);
		state = MAIN;
		//break;
	case MAIN:
		
		if (KEY_Get(KEY_SPACE) == 3) {
			state = TUTORIAL;
//			pEffect_Manager->searchSet(V2(960, 0), V2(0, 0), fade_Out);
			timer = 0;
			bg = &s_tutorial;
			ppsk = titleChar = titleName = nullptr;
		}
		pEffect_Manager->Update();
		pFrame->f_move();

		break;
	case TUTORIAL:
		if (KEY_Get(KEY_SPACE) == 3)
		MainFrame->ChangeScene(new sceneMain);

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

//•`‰æ
void sceneTitle::Render()
{
	if (bg)			spr_data::Render(V2(0, 0),bg);
	/*if (titleChar) {
		float sz = pFrame->get_sz((float)titleChar->frameNum);
		shader2D->SetValue("FPower", sz > 90 ? (180 - sz) / 90 : sz / 90);
		spr_data::Render(V2(titleChar->dw + titleChar->ofsx, SCREEN_HEIGHT + titleChar->ofsy), titleChar, 0xFFFFFFFF,(float)0, shader2D, "depth");
	}
	*/
	if (titleChar)spr_data::Render(V2(titleChar->dw + titleChar->ofsx, SCREEN_HEIGHT + titleChar->ofsy), titleChar);

	if (titleName) {
		float sz = pFrame->get_sz((float)titleName->frameNum);
		shader2D->SetValue("FPower", sz > 90 ? (180 - sz) / 90 : sz / 90);
		spr_data::Render(V2(SCREEN_WIDTH + titleName->ofsx, titleName->dh + titleName->ofsy), titleName, 0xFFFFFFFF, (float)0, shader2D, "depth");
	}
	if (ppsk) {
		float sz = pFrame->get_sz((float)ppsk->frameNum);
		shader2D->SetValue("FPower", sz > 90 ? (180 - sz) / 90 : sz / 90);
		
		spr_data::Render(V2(ppsk->ofsx,ppsk->ofsy) + PPSK_POS, ppsk, 0xFFFFFFFF,(float)0, shader2D, "depth");
	}

	if(state == TUTORIAL)pPlayer->Render();

	pEffect_Manager->Render();
	iexPolygon::Rect(0,0, 960, 540,0x00000000,0);
}