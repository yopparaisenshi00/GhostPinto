#include "iextreme.h"
#include "system\System.h"
#include "Game.h"
#include "Player/Player.h"
#include "Player/Frame.h"
#include "Enemy.h"
#include "Effect.h"
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
//メイン背景 
SPR_DATA main = SPR_DATA{ 0,0,0,1960,540,0,0,1960,540 };

//地上大カプセル
SPR_DATA spr_Capsule_l = { Capsule_l,0,  0,	177,512,-89,-512 };
SPR_DATA spr_Capsule_d = { Capsule_d,256,0,	177,512,-89,-512 };

//地上小カプセル
SPR_DATA spr_Mini_capsule_l = { Mini_capsule_l,512,0,128,226,-128 / 2,-226 };
SPR_DATA spr_Mini_capsule_d = { Mini_capsule_d,640,0,128,226,-128 / 2,-226 };

//地上割カプセル脚
SPR_DATA spr_Break_capsule_u = { Break_capsule_u,512,256,158,256,-158 / 2,-256 };
//割カプセル頭
SPR_DATA spr_Break_capsule_o = { Break_capsule_o,1664,0,153,141,-76,-70 };

//空中大カプセル
SPR_DATA spr_Fly_capsule_d = { Fly_capsule_d,896,0,128,512,-128 / 2,-512 / 2 };
SPR_DATA spr_Fly_capsule_l = { Fly_capsule_l,768,0,128,512,-128 / 2,-512 / 2 };

//空中大メタルカプセル
SPR_DATA spr_Fly_capsule_m = { Fly_capsule_m,1024,0,153,448,-77,-448 / 2 };

//空中小カプセル
SPR_DATA spr_Fly_mini_capsule_l = { Fly_mini_capsule_l,1280,0,113,384,-57,-384 / 2 };
SPR_DATA spr_Fly_mini_capsule_d = { Fly_mini_capsule_d,1408,0,113,384,-57,-384 / 2 };

//空中小メタルカプセル
SPR_DATA spr_Fly_mini_capsule_m = { Fly_mini_capsule_m,1536,0,113,337,-57,-169 };

//ディスプレイ類
SPR_DATA spr_Display_a = { Display_a,1280,384,128,93,-128 / 2,-93 / 2 };
SPR_DATA spr_Display_b = { Display_b,1408,384,128,75,-128 / 2,-75 / 2 };
SPR_DATA spr_Display_c = { Display_c,1536,384,128,97,-128 / 2,-97 / 2,2 };
SPR_DATA spr_Display_d = { Display_d,  1664,384,128,97,-128 / 2,-97 / 2 ,2};

LAND_SCAPE_DATA* bg_effect[] = {
	{ tutorial_bg_effect },
	{ stage1_bg_effect },
};

enum {
	INIT = 0,	//初期設定
	BEGIN,	//
	BEGIN2,	//

	MOVE,	//移動処理
	MOVE2,	//
	MOVE3,	//
	MOVE4,	//
	MOVE5,	//
	BREAK,
	CLEAR,	//初期化
};

float BG_REDUCED_DATA[] = {
	1,1.2,1.4,2,4,6
};
float FG_REDUCED_DATA[] = {
	0.5,0.7,
};

//=====================
// 初期化
//=====================
void LandScape::Init(int stage_no) {
	bg.clear();
	setMainBG(&main,MainBG);
	for (int i = 0; i < LANDSCAPE_MAX;i++) {
		if (!LandScapeObjs[i])continue;
		LandScapeObjs[i]->clear();
	}
	timer = 0;
	data = (bg_effect[stage_no]);

	for (int i = 0; i < BG_REDUCED_LV_MAX;i++) {
		BG_RenderBox[i].Init(BG_REDUCED_DATA[i]);
	}
	for (int i = 0; i < FG_REDUCED_LV_MAX; i++) {
		FG_RenderBox[i].Init(FG_REDUCED_DATA[i]);
	}

}

//==========================================
//  BGデータセット
//==========================================
void LandScape::setMainBG(SPR_DATA * BG, void(*move)(FGOBJ *)) {
	bg.data = BG;
	bg.move = move;
}

//==========================================
//  更新
//==========================================
void LandScape::Update() {
	stage_update();
	//bg.Update();
	for (int i = 0; i < BG_REDUCED_LV_MAX; i++) {
		BG_RenderBox[i].count = 0;
	}
	for (int i = 0; i < FG_REDUCED_LV_MAX; i++) {
		FG_RenderBox[i].count = 0;
	}

	for (int i = 0; i < LANDSCAPE_MAX; i++) {
		if (!LandScapeObjs[i])break;
		if(!LandScapeObjs[i]->init_fg)continue;
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


//==========================================
//  描画
//==========================================
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



void LandScape::searchSet(int type, V2 pos, V2 spd, void(*move)(FGOBJ *), OBJ2D * parent, int _z) {
	//LandScapeObjs;
	//LAND_SCAPE_OBJ** obj;
	for (int i = 0; i < LANDSCAPE_MAX; i++) {
		if (LandScapeObjs[i] && LandScapeObjs[i]->init_fg)continue;
		if (!LandScapeObjs[i])LandScapeObjs[i] = new LAND_SCAPE_OBJ;

		LandScapeObjs[i]->clear();//
		LandScapeObjs[i]->wpos = pos;
		LandScapeObjs[i]->spd = spd;
		LandScapeObjs[i]->move = move;
		LandScapeObjs[i]->init_fg = true;
		LandScapeObjs[i]->parent = parent;
		LandScapeObjs[i]->z = (float)_z;
		LandScapeObjs[i]->type = type;
		break;
	}

}


//==========================================
//  出現管理
//==========================================
void LandScape::stage_update() {
	timer++;
	//timerで管理
	if (data) {
		while (data->appearTime <= timer)
		{
			if (data->appearTime < 0) { break; }
			if (data->moveType == nullptr) { break; }
			searchSet(data->type, data->pos, data->speed, data->moveType, nullptr, data->z);
			data++;
		}
	}
}

//==========================================
//  オブジェクト追加 + ソート
//==========================================
void LandScape::add_RenderObj(LAND_SCAPE_OBJ* obj, int z) {
	ReducedObj* reducedObj;
	if (z > -1) { //0以上なら背景、以下なら前景
		//エラーチェック// 配列サイズに収まっているか
		if (z < 0 || z > BG_REDUCED_LV_MAX) {
			z = (BG_REDUCED_LV_MAX-1);
		}
		reducedObj = &BG_RenderBox[z];
	}
	else {
		z *= -1;
		z--;
		//エラーチェック// 配列サイズに収まっているか
		if (z < 0 || z < FG_REDUCED_LV_MAX) {
			z = (FG_REDUCED_LV_MAX - 1);
		}
		reducedObj = &FG_RenderBox[z];
	}

	reducedObj->data[reducedObj->count] = obj;
	reducedObj->count++;
	obj->custom.scaleX = 1 / reducedObj->Reduced_level;
	obj->custom.scaleY = 1 / reducedObj->Reduced_level;

}

//******************************************************************************
//
//		描画順序制御
//
//******************************************************************************
//------------------------------------------------------------------------------
//		初期設定
//------------------------------------------------------------------------------

void LandScape::ReducedObj::Init(float _Reduced_level) {
	clear();
	Reduced_level = _Reduced_level;
	pos = V2((SCREEN_WIDTH - (SCREEN_WIDTH / Reduced_level))/2, (SCREEN_HEIGHT - (SCREEN_HEIGHT / Reduced_level))/2);
	bot = (pos.y * 2);
	
}

void LandScape::ReducedObj::Update() {
	for (int i = 0; i < count; i++) {
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
	}


#ifdef _DEBUG_REDUCEDLINE_RENDER_

#ifdef _DEBUG_REDUCEDLINE_TOP_
		//横
		iexPolygon::Rect((int)(pos.x), (int)(0), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFFFFFF00);
		iexPolygon::Rect((int)(pos.x), (int)(0 + SCREEN_HEIGHT / Reduced_level), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFFFFFF00);
		//縦
		iexPolygon::Rect((int)(pos.x), (int)(0), 1, (int)SCREEN_HEIGHT / Reduced_level, 0, 0xFFFFFF00);
		iexPolygon::Rect((int)(pos.x + (int)(SCREEN_WIDTH / Reduced_level)), (int)(0), 1, SCREEN_HEIGHT / Reduced_level, 0, 0xFFFFFF00);

#endif //_DEBUG_REDUCEDLINE_TOP_
#ifdef _DEBUG_REDUCEDLINE_CENTER_
		//横
		iexPolygon::Rect((int)(pos.x), (int)(pos.y), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFF00FF00);
		iexPolygon::Rect((int)(pos.x), (int)(pos.y + SCREEN_HEIGHT / Reduced_level), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFF00FF00);
		//縦
		iexPolygon::Rect((int)(pos.x), (int)(pos.y), 1, (int)SCREEN_HEIGHT / Reduced_level, 0, 0xFF00FF00);
		iexPolygon::Rect((int)(pos.x + (int)(SCREEN_WIDTH / Reduced_level)), (int)(pos.y), 1, SCREEN_HEIGHT / Reduced_level, 0, 0xFF00FF00);
#endif //_DEBUG_REDUCEDLINE_CENTER_
#ifdef _DEBUG_REDUCEDLINE_BOT_
		iexPolygon::Rect((int)(pos.x), (int)(bot), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFFFF0000);
		iexPolygon::Rect((int)(pos.x), (int)(bot + SCREEN_HEIGHT / Reduced_level), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFFFF0000);
		//SCREEN_WIDTH / Reduced_level
		////縦
		iexPolygon::Rect((int)(pos.x), (int)(bot), 1, (int)SCREEN_HEIGHT / Reduced_level, 0, 0xFFFF0000);
		iexPolygon::Rect((int)(pos.x + (int)(SCREEN_WIDTH / Reduced_level)), (int)(bot), 1, SCREEN_HEIGHT / Reduced_level, 0, 0xFFFF0000);
#endif //_DEBUG_REDUCEDLINE_BOT_
#endif

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


//*********************************************************************************
//
// 背景Obj
//
//*********************************************************************************
//--プロトタイプ宣言--//
void Reduced(LAND_SCAPE_OBJ* obj);
int check_behind_obj(OBJ2D* obj);
//---------------------------------------------------------------
// 共通関数
//---------------------------------------------------------------

void LAND_SCAPE_OBJ::Init() {
	clear();
	custom.scaleMode = SCALE_MODE::BOTTOMCENTER;
}
void LAND_SCAPE_OBJ::Update() {

	//custom.scaleX = 1.0;
	//custom.scaleY = 1.0;

	if (move)move(this);

	animetion();
	Reduced(this);


	if (z < 0) {
		
		int alpha = custom.argb >> 24;
		if (check_behind_obj(this))
		{
			if (alpha >= BEHIND_OBJ_ALPHA) {
				alpha -= ALPHA_ACT;
			}
		}
		else {
			if (alpha >= 0xFF) {
				alpha & 0xFF;
				alpha | 0xFF;
			}
			else {
				alpha += ALPHA_ACT;
			}
		}
		custom.argb = (custom.argb & 0x00FFFFFF) | (alpha << 24);
	}
}

int check_behind_obj(OBJ2D* obj)
{
	if(Judge(obj, pPlayer)){ return TRUE; }
	Enemy** enemy = pEnemy_Manager->enemy;
	for (int i = 0; i < ENEMY_MAX; i++) {
		//存在チェック
		if (!enemy[i])break;
		if (!enemy[i]->init_fg)continue;
		//判定処理
		if (Judge(obj, enemy[i])) {
			return TRUE;
		}
	}
	return FALSE;
}




void LAND_SCAPE_OBJ::Render() {
	if (!data)return;
	sz =  pEnemy_Manager->get_sz(z) - pFrame->getPintoSize();
	if (sz < 0) {
		sz = 0;
	}

	shader2D->SetValue("FPower", sz > 90 ? (180 - sz) / 90 : sz / 90);
	spr_data::Render(pos, data, &custom, custom.argb, shader2D, "depth");
	//line_rect(pos,V2(size.x * custom.scaleX, size.y * custom.scaleY), 0xFFFFFFFF, custom.scaleMode);
	//if(z < 0)line_rect(pos,V2(size.x, size.y), 0xFFFFFFFF, custom.scaleMode);

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
		obj->custom.scaleMode = SCALE_MODE::BOTTOMCENTER;
		//obj->animeData = spr_pc;
		obj->data = &spr_pc[0];
		obj->state = BEGIN;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

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
		obj->custom.scaleMode = SCALE_MODE::BOTTOMCENTER;

		obj->animeData = spr_container;
		obj->data = &spr_container[0];
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}

//地上大カプセル
void BG_Capsule_l(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::BOTTOMCENTER;

		obj->data = &spr_Capsule_l;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		obj->size = V2(obj->data->dw/2, obj->data->dh/2);

		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}
void BG_Capsule_d(LAND_SCAPE_OBJ* obj) {//ダーク
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::BOTTOMCENTER;

		obj->data = &spr_Capsule_d;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}
//空中大カプセル
void BG_Fly_capsule_l(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;

		obj->data = &spr_Fly_capsule_l;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}
void BG_Fly_capsule_d(LAND_SCAPE_OBJ* obj) {//ダーク
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;
		obj->data = &spr_Fly_capsule_d;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}
void BG_Fly_capsule_m(LAND_SCAPE_OBJ* obj) {//メタル
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;
		obj->data = &spr_Fly_capsule_m;
		obj->size = V2(obj->data->dw/2,obj->data->dh / 2);

		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}

//割れカプセル
void BG_Break_capsule_u(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::BOTTOMCENTER;

		obj->data = &spr_Break_capsule_u;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
		obj->state = BEGIN;

		break;
	case BEGIN:

	default:
		break;
	}
}

//フライminiカプセル
void BG_Fly_mini_capsule_l(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;
		obj->data = &spr_Fly_mini_capsule_l;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
		obj->state = BEGIN;

		break;
	case BEGIN:

	default:
		break;
	}

}
void BG_Fly_mini_capsule_d(LAND_SCAPE_OBJ* obj) {//ダーク
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;

		obj->data = &spr_Fly_mini_capsule_d;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
		obj->state = BEGIN;

		break;
	case BEGIN:

	default:
		break;
	}

}
//フライminiメタルカプセル
void BG_Fly_mini_capsule_m(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;

		obj->data = &spr_Fly_mini_capsule_m;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		obj->state = BEGIN;

		break;
	case BEGIN:

	default:
		break;
	}

}
//地上miniカプセル
void BG_Mini_capsule_l(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::BOTTOMCENTER;

		obj->data = &spr_Mini_capsule_l;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
		obj->state = BEGIN;

		break;
	case BEGIN:

	default:
		break;
	}

}
void BG_Mini_capsule_d(LAND_SCAPE_OBJ* obj) {//ダーク
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::BOTTOMCENTER;

		obj->data = &spr_Mini_capsule_d;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
		obj->state = MOVE;

		break;
	case MOVE:
		


	default:
		break;
	}

}


//ディスプレイ
void BG_Display_a(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;
		obj->data = &spr_Display_a;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		obj->state = MOVE;
		break;
	case MOVE:

		break;
	default:
		break;
	}
}
void BG_Display_b(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;

		obj->data = &spr_Display_b;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
		obj->state = BEGIN;
		break;
	case BEGIN:
	default:
		break;
	}
}

Animetion anime_Display_cd[] = {
	{ &spr_Display_c,300 },
	{ &spr_Display_d,16 },
	{ &spr_Display_d,2 },
	{ &spr_Display_c,2 },
	{ &spr_Display_d,2 },
	{ NULL,	ANIM_FLG_LOOP },
};



void BG_Display_c(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;
		obj->animetion_data = anime_Display_cd;
		obj->data = &spr_Display_c;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
		obj->state = BEGIN;
		break;
	case BEGIN:
	default:
		break;
	}
}
void BG_Display_d(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;

		obj->data = &spr_Display_d;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
		obj->state = BEGIN;
		break;
	case BEGIN:
	default:
		break;
	}
}



//static SPR_DATA anime_circleext[] = {
//	SPR_DATA{ spr_data::Circle, 128 * 0, 0, 128, 128, -64, -64,2 },
//	SPR_DATA{ spr_data::Circle, 128 * 1, 0, 128, 128, -64, -64,2 },
//	SPR_DATA{ spr_data::Circle, 128 * 2, 0, 128, 128, -64, -64,2 },
//	SPR_DATA{ spr_data::Circle, 128 * 3, 0, 128, 128, -64, -64,2 },
//	SPR_DATA{ spr_data::Circle, 128 * 4, 0, 128, 128, -64, -64,2 },
//	SPR_DATA{ spr_data::Circle, 128 * 5, 0, 128, 128, -64, -64,2 },
//	SPR_DATA{ spr_data::Circle, 128 * 6, 0, 128, 128, -64, -64,3 },
//	SPR_STOP
//};
//
//static Animetion anime_circleext_data[] = {
//	{ &anime_circleext[0],4 },
//	{ &anime_circleext[1],4 },
//	{ &anime_circleext[2],4 },
//	{ &anime_circleext[3],4 },
//	{ &anime_circleext[4],4 },
//	{ &anime_circleext[5],4 },
//	{ &anime_circleext[6],4 },
//	{ NULL,ANIM_FLG_LOOP }
//};
//
////空中大カプセル破裂
//void BG_Fly_capsule_l_break(LAND_SCAPE_OBJ* obj) {
//	switch (obj->state)
//	{
//	case INIT:
//		obj->custom.scaleMode = SCALE_MODE::CENTER;
//		obj->data = &spr_Fly_capsule_l;
//		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
//
//		obj->state = BEGIN;
//		break;
//	case BEGIN:
//		obj->timer++;
//		if (obj->timer > 300) {
//			obj->state = BREAK;
//			pLandScape->searchSet(obj->type, obj->wpos, V2(5,1), CircleExt, NULL, obj->z);
//		}
//		break;
//	case BREAK:
//		//pLandScape->searchSet(obj->type, obj->wpos + V2(64,-256), V2(0.2,0), CircleExt, NULL, obj->z);
//		//pLandScape->searchSet(obj->type, obj->wpos + V2(-64, -256), V2(0.2, 0), CircleExt, NULL, obj->z);
//
//		if (obj->timer++ > 60) {
//			obj->timer = 0;
//			{
//				V2 ofs;
//				ofs.x = (rand() % 200) - 100;
//				ofs.y = (rand() % 200) - 100;
//				pLandScape->searchSet(obj->type, obj->wpos + ofs, V2(0.6,0.7), CircleExt, NULL, obj->z);
//			}
//
//		}
//		obj->wpos.y ++;
//		break;
//
//	default:
//		break;
//	}
//}
//
//void CircleExt(LAND_SCAPE_OBJ *obj)
//{
//	switch (obj->state)
//	{
//	case INIT:
//		
//		obj->animetion_data = anime_circleext_data;
//		//obj->data = &obj->animeData[0];
//		obj->custom.scaleMode = CENTER;
//		
//		obj->timer = 0;
//		obj->custom.argb = 0x00FFFFFF | ((int)(255 * obj->spd.y)) << 24;
//		obj->state = MOVE;
//		//break;
//	case MOVE:
//		obj->custom.scaleX = obj->custom.scaleY = obj->spd.x;
//		if (obj->timer++>15) {
//			obj->state = CLEAR; //消去処理へ
//		}
//
//		break;
//	case CLEAR:
//		obj->clear();
//		break;
//	default:
//		break;
//	}
//}
