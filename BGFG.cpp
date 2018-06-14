#include "iextreme.h"
#include "system\System.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Frame.h"
#include "MAP.h"
#include "BGFG.h"
#include "stage_data.h"

enum 
{
	BG_CASE = spr_data::BG2,
	BG_PC = spr_data::BG3,
	BG_PIPE = spr_data::BG4,
	Capsule_l = spr_data::BG2,
	Capsule_d = spr_data::BG2,

	Mini_capsule_l = spr_data::BG2,
	Mini_capsule_d = spr_data::BG2,

	Break_capsule_u = spr_data::BG2,
	Break_capsule_o = spr_data::BG2,

	Fly_capsule_l = spr_data::BG2,
	Fly_capsule_d = spr_data::BG2,

	Fly_capsule_m = spr_data::BG2,

	Fly_mini_capsule_l = spr_data::BG2,
	Fly_mini_capsule_d = spr_data::BG2,

	Fly_mini_capsule_m = spr_data::BG2,

	Display_a = spr_data::BG2,
	Display_b = spr_data::BG2,
	Display_c = spr_data::BG2,
	Display_d = spr_data::BG2,

};

SPR_DATA spr_pc[] = {
	SPR_DATA{ BG_PC,0,0,248,157,-124,-157,0 } ,
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,1 },
};
SPR_DATA spr_container[] = {
	SPR_DATA{ BG_PC,0,256,248,157 ,-128,-157 ,0},
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,1 }
};

//地上大カプセル
SPR_DATA spr_Capsule_l = { Capsule_l,0, 0,177, 512, -89, -512};
SPR_DATA spr_Capsule_d = { Capsule_d,0,256,0,177,512,-89,-512};

//地上小カプセル
SPR_DATA spr_Mini_capsule_l ={ Mini_capsule_l,512,0,128,498,-128 / 2,-498 / 2 };
SPR_DATA spr_Mini_capsule_d ={ Mini_capsule_d,640,0,128,498,-128 / 2,-498 / 2 };

//地上割カプセル脚
SPR_DATA spr_Break_capsule_u = {  Break_capsule_u,512,256,158,256,-158 / 2,-256 / 2 };
//割カプセル頭
SPR_DATA spr_Break_capsule_o = {  Break_capsule_o,1664,0,153,141,-76,-70 };

//空中大カプセル
SPR_DATA spr_Fly_capsule_d ={  Fly_capsule_d,896,0,128,512,-128 / 2,-512 / 2 };
SPR_DATA spr_Fly_capsule_l ={  Fly_capsule_l,768,0,128,512,-128 / 2,-512 / 2 };

//空中大メタルカプセル
SPR_DATA spr_Fly_capsule_m = {  Fly_capsule_m,1024,0,153,448,-77,-448 / 2 };

//空中小カプセル
SPR_DATA spr_Fly_mini_capsule_l = {  Fly_mini_capsule_l,1280,0,113,384,-57,-384 / 2 };
SPR_DATA spr_Fly_mini_capsule_d = {  Fly_mini_capsule_d,1408,0,113,384,-57,-384 / 2 };

//空中小メタルカプセル
SPR_DATA spr_Fly_mini_capsule_m = {  Fly_mini_capsule_m,1536,0,113,337,-57,-169 };

//ディスプレイ類
SPR_DATA spr_Display_a = {  Display_a,1280,384,128,93,-128 / 2,-47 };
SPR_DATA spr_Display_b = {  Display_b,1408,384,128,75,-128 / 2,-38 };
SPR_DATA spr_Display_c = {  Display_c,1536,384,128,97,-128 / 2,-49 };
SPR_DATA spr_Display_d ={  Display_d,  1664,384,128,97,-128 / 2,-49 };

enum {
	INIT = 0,	//初期設定
	BEGIN,	//
	BEGIN2,	//
	
	MOVE,	//移動処理
	MOVE2,	//
	MOVE3,	//
	MOVE4,	//
	MOVE5,	//

	CLEAR,	//初期化
};

float BG_REDUCED_DATA[] = {
	1,1.1,1.3,2,4,6
};
float FG_REDUCED_DATA[] = {
	0.5,0.7,
};

void LandScape::Init(int stage_no) {
	
	bg.clear();
	for (int i = 0; i < LANDSCAPE_MAX;i++) {
		if (!LandScapeObjs[i])continue;
		LandScapeObjs[i]->clear();
	}
	timer = 0;
	data = &stage1_bg_effct[stage_no];

	for (int i = 0; i < BG_REDUCED_LV_MAX;i++) {
		BG_RenderBox[i].Init(BG_REDUCED_DATA[i]);
	}
	for (int i = 0; i < FG_REDUCED_LV_MAX; i++) {
		FG_RenderBox[i].Init(FG_REDUCED_DATA[i]);
	}

}


void LandScape::Update() {
	stage_update();

	//bg.Update();
	for (int i = 0; i < LANDSCAPE_MAX; i++) {
		if (!LandScapeObjs[i] || !LandScapeObjs[i]->init_fg)continue;
		LandScapeObjs[i]->Update();
	}
	for (int i = 0; i < BG_REDUCED_LV_MAX; i++) {
		BG_RenderBox[i].Update();
	}
	for (int i = 0; i < FG_REDUCED_LV_MAX; i++) {
		FG_RenderBox[i].Update();
	}

}
static int d_txt_x = 0;
static int d_txt_y = 0;

void LandScape::RenderBG() {
	bg.Render();
	d_txt_y = 0;
	d_txt_x = 0;
	for (int i = BG_REDUCED_LV_MAX -1; i >= 0; i--) {
		BG_RenderBox[i].Render();
	}
}
void LandScape::RenderFG() {

	for (int i = FG_REDUCED_LV_MAX - 1; i >= 0; i--) {
		FG_RenderBox[i].Render();
	}

}



void LandScape::stage_update() {
	timer++;
	//timerで管理
	while (data->appearTime <= timer)
	{
		if (data->appearTime < 0) {
			data++;
			break;
		}
		if (data->moveType == nullptr) break;
		searchSet(data->type,data->pos, data->speed,data->moveType,nullptr,data->z);
		data++;
	}
}


void LandScape::ReducedObj::Init(float _Reduced_level) {
	clear();
	Reduced_level = _Reduced_level;
	pos = V2((SCREEN_WIDTH - (SCREEN_WIDTH / Reduced_level))/2, (SCREEN_HEIGHT - (SCREEN_HEIGHT / Reduced_level))/2);
	bot = (pos.y * 2);
	
}

void LandScape::ReducedObj::Update() {
	for (int i = 0; i < count; i++) {
		data[i]->custom.scaleX = 1 / Reduced_level;
		data[i]->custom.scaleY = 1 / Reduced_level;

		switch (data[i]->type)
		{
		case LSD::CENTER:
			data[i]->pos = pos + (data[i]->pos / Reduced_level);
			
			break;
		case LSD::TOP:
			data[i]->pos =V2(pos.x,0) + (data[i]->pos / Reduced_level);
			break;
		case LSD::BOT:
			data[i]->pos = V2(pos.x,bot) + V2((data[i]->pos.x / Reduced_level),(data[i]->pos.y / Reduced_level));
			
			break;
		default:
			data[i]->pos = pos + (data[i]->pos / Reduced_level);
			break;
		}
	}
}
void LandScape::ReducedObj::Render() {

	for (int i = 0; i < count; i++) {
		data[i]->Render();
		count = 0;

		//横
		iexPolygon::Rect((int)(pos.x), (int)(0), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFFFFFF00);
		iexPolygon::Rect((int)(pos.x), (int)(0 + SCREEN_HEIGHT / Reduced_level), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFFFFFF00);
		//縦
		iexPolygon::Rect((int)(pos.x), (int)(0), 1, (int)SCREEN_HEIGHT / Reduced_level, 0, 0xFFFFFF00);
		iexPolygon::Rect((int)(pos.x + (int)(SCREEN_WIDTH / Reduced_level)), (int)(0), 1, SCREEN_HEIGHT / Reduced_level, 0, 0xFFFFFF00);


		//横
		iexPolygon::Rect((int)(pos.x), (int)(pos.y), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFF00FF00);
		iexPolygon::Rect((int)(pos.x), (int)(pos.y + SCREEN_HEIGHT / Reduced_level), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFF00FF00);
		//縦
		iexPolygon::Rect((int)(pos.x), (int)(pos.y), 1, (int)SCREEN_HEIGHT / Reduced_level, 0, 0xFF00FF00);
		iexPolygon::Rect((int)(pos.x + (int)(SCREEN_WIDTH / Reduced_level)), (int)(pos.y), 1, SCREEN_HEIGHT / Reduced_level, 0, 0xFF00FF00);


		iexPolygon::Rect((int)(pos.x), (int)(bot), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFFFF0000);
		iexPolygon::Rect((int)(pos.x), (int)(bot + SCREEN_HEIGHT / Reduced_level), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFFFF0000);
		//SCREEN_WIDTH / Reduced_level
		////縦
		iexPolygon::Rect((int)(pos.x), (int)(bot), 1, (int)SCREEN_HEIGHT / Reduced_level, 0, 0xFFFF0000);
		iexPolygon::Rect((int)(pos.x + (int)(SCREEN_WIDTH / Reduced_level)), (int)(bot), 1, SCREEN_HEIGHT / Reduced_level, 0, 0xFFFF0000);
	}
}


//---------------------------------------------------------------
//
// 背景 :: 廃止
//
//---------------------------------------------------------------

//BG::BG()
//{
//
//}
//
//BG::~BG()
//{
//			
//}
//
//void BG::Init() {
//	
//	for (int i = 0; i < BG_MAX; i++) {
//		if (obj[i])obj[i]->Init();
//	}
//}
//
//
//
//void BG::Update() {
//	for (int i = 0; i < BG_MAX; i++) {
//		if (obj[i] && obj[i]->move)
//			obj[i]->Update();
//	}
//}
//void BG::Render() {
//	for (int i = 0; i < BG_MAX;i++ ) {
//		if(obj[i])obj[i]->Render();
//	}
//}

//---------------------------------------------------------------
//
//	前景::廃止
//
//---------------------------------------------------------------

//FG::FG()
//{
//	}
//
//FG::~FG()
//{
//
//}
//
//void FG::Init() {
//	for (int i = 0; i < BG_MAX; i++) {
//		if (obj[i])obj[i]->Init();
//	}
//
//}
//
//void FG::Update() {
//
//	for (int i = 0; i < BG_MAX; i++) {
//		if (obj[i] && obj[i]->move)
//			obj[i]->Update();
//	}
//}
//void FG::Render() {
//	for (int i = 0; i < BG_MAX; i++) {
//		if (obj[i])obj[i]->Render();
//	}
//}


//---------------------------------------------------------------
//
// 背景Obj
//
//---------------------------------------------------------------
//--プロトタイプ宣言--//
void Reduced(LAND_SCAPE_OBJ* obj);
//---------------------------------------------------------------
// 共通関数
//---------------------------------------------------------------

void LAND_SCAPE_OBJ::Init() {
	clear();
	custom.scaleMode = SCALE_MODE::BOTTOMCENTER;
}

void LAND_SCAPE_OBJ::Update() {
	if (move)move(this);
	custom.scaleMode = SCALE_MODE::BOTTOMCENTER;

	animation();
	Reduced(this);
}


void LAND_SCAPE_OBJ::Render() {
	if (!data)return;
	shader2D->SetValue("FPower", sz);
	spr_data::Render(pos, data, &custom, 0xFFFFFFFF, shader2D, "depth");

}



void Reduced(LAND_SCAPE_OBJ* obj) {
	int scale = obj->z / 10;
	//int ScrollX = pMAP->getScrollX();
	//int ScrollY = pMAP->getScrollY();
	V2 Scroll(pMAP->getScrollX(), pMAP->getScrollY());
	obj->pos = obj->wpos - Scroll;

	if (scale > -1) {
		obj->pos = obj->wpos - Scroll;
		switch (scale)
		{
		case 0:
		case 1:
			scale = 0;
			break;
		case 2:
		case 3:
			scale = 1;
			break;
		case 4:
		case 5:
			scale = 2;
			break;
		case 6:
		case 7:
			scale = 3;
			break;
		case 8:
		case 9:
			scale = 4;
			break;
		default:
			break;
		}
	}
	//前景
	else {
		switch (scale)
		{
		case -1://break;
		case -2://break;
		case -3://break;
		case -4://break;
		case -5:
			scale = -1;
			break;
		case -6://break;
		case -7://break;
		case -8://break;
		case -9:
			scale = -2;
			break;
		default:
			break;
		}
	}

	pLandScape->add_RenderObj(obj,scale);
}


//---------------------------------------------------------------
// 個別動作関数
//---------------------------------------------------------------

void MainBG(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:

	case BEGIN:
		
	default:
		break;
	}
}

void BG_pc(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		//obj->animeData = spr_pc;
		obj->data = &spr_pc[0];
		obj->state = BEGIN;
		break;
	case BEGIN:
		obj->state = MOVE;
		break;
	case MOVE:
		break;
	case CLEAR:
		break;
	default:
		break;
	}

}
void BG_container(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->animeData = spr_container;
		obj->data = &spr_container[0];
		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}

void BG_Capsule_l(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->data = &spr_Capsule_l;
		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}
