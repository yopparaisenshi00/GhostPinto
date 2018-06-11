#include "iextreme.h"
#include "system\System.h"
#include "system\Framework.h"

#include "Game.h"
#include "Player.h"
#include "MAP.h"
#include "Effect.h"
#include "BGFG.h"
#include "Sound.h"
#include "sceneMain.h"
#include "sceneTitle.h"


enum {
	INIT,
	READY,
	MAIN,
	FADE_OUT,
	FADE_IN,
	TUTORIAL,
};


SPR_DATA s_title =		{ 0,0,0,960,540,0,0 };
SPR_DATA s_ppsk =		{ 0,0,576,419,31,-419 / 2,-31/2 ,459,40};
SPR_DATA s_titleName =	{ 0,0,640,640,94 ,-640 / 2,-94 / 2 };
SPR_DATA s_titleChar =	{ 0,640,576,331,380,-331/2,-380/2};
SPR_DATA s_tutorial= { spr_data::BG2,0,0,960,540,0,0 };

IMG_DATA img_title[] = {
	{ spr_data::BG1,"DATA\\Scene\\title.png" },
	{ spr_data::BG2,"DATA\\Scene\\tuto_kari.jpg"},

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
			pPlayer->Init();
			bg = &s_tutorial;
			ppsk = titleChar =titleName = nullptr;

		}
		pEffect_Manager->Update();

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
	if (ppsk)		spr_data::Render(V2(640 , 460),ppsk);
	if (titleChar)	spr_data::Render(V2(210, 330),titleChar);
	if (titleName)	spr_data::Render(V2(500, 100),titleName);
	if(state == TUTORIAL)pPlayer->Render();

	pEffect_Manager->Render();
	iexPolygon::Rect(0,0, 960, 540,0x00000000,0);
}