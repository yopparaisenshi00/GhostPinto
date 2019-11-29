#include "iextreme.h"
#include "Game.h"
#include "Player/Player.h"
#include "Player/Frame.h"
#include "Enemy.h"
#include "MAP.h"
#include "Effect.h"

enum {
	INIT=0,		//初期設定
	MOVE,		//移動処理
	MOVE2,		//移動処理2
	MOVE3,		//移動処理3
	MOVE4,		//移動処理4
	CLEAR,		//消去処理
};

//※いらない素材
static SPR_DATA Frame_data = SPR_DATA{ spr_data::UI1,0,0,240,160,-120,-80, };

//※いらない素材
static SPR_DATA anime_Jet_data[] = {
	SPR_DATA{ spr_data::Ext, 64 * 0, 0, 64, 64, -32, -32 },
	SPR_DATA{ spr_data::Ext, 64 * 1, 0, 64, 64, -32, -32 },
	SPR_DATA{ spr_data::Ext, 64 * 2, 0, 64, 64, -32, -32 },
	SPR_DATA{ spr_data::Ext, 64 * 3, 0, 64, 64, -32, -32 },
	SPR_DATA{ spr_data::Ext, 64 * 4, 0, 64, 64, -32, -32 },
	SPR_DATA{ spr_data::Ext, 64 * 5, 0, 64, 64, -32, -32 },
	SPR_LOOP
};

//敵消滅エフェクト素材
static SPR_DATA anime_circleext_data[] = {
	SPR_DATA{ spr_data::Circle, 128 * 0, 0, 128, 128, -64, -64,2 },
	SPR_DATA{ spr_data::Circle, 128 * 1, 0, 128, 128, -64, -64,2 },
	SPR_DATA{ spr_data::Circle, 128 * 4, 0, 128, 128, -64, -64,2 },
	SPR_DATA{ spr_data::Circle, 128 * 6, 0, 128, 128, -64, -64,3 },
	SPR_LOOP };

//テレポートエフェクト素材
static SPR_DATA anime_tele_data[] = {
	SPR_DATA{ spr_data::TeleExt, 128 * 0, 0, 128, 128, -64, -64,0 },
	SPR_DATA{ spr_data::TeleExt, 128 * 1, 0, 128, 128, -64, -64,1 },
	SPR_DATA{ spr_data::TeleExt, 128 * 2, 0, 128, 128, -64, -64,2 },
	SPR_DATA{ spr_data::TeleExt, 128 * 3, 0, 128, 128, -64, -64,3 },
	SPR_DATA{ spr_data::TeleExt, 128 * 4, 0, 128, 128, -64, -64,4 },
	SPR_DATA{ spr_data::TeleExt, 128 * 5, 0, 128, 128, -64, -64,5 },
	SPR_DATA{ spr_data::TeleExt, 128 * 6, 0, 128, 128, -64, -64,6 },
	SPR_DATA{ spr_data::TeleExt, 128 * 7, 0, 128, 128, -64, -64,7 },
	SPR_LOOP
};

static SPR_DATA fade_in = {
	spr_data::FADE_IN1,960,0,2048,540, 0, 0,
};

static SPR_DATA fade_out = {
	spr_data::FADE_OUT1,0,0,2048,540, 0, 0,
};


//ジャストピントエフェクト素材(ピントリングの流用)
static SPR_DATA jastpinto_data = SPR_DATA{ spr_data::UI1,0,0,128,128,-64,-64,0 };

//飛行エフェクト素材(消滅エフェクトの流用)
static SPR_DATA jet_data = SPR_DATA{ spr_data::Circle, 128 * 0, 0, 128, 128, -64, -64,0 };

//プレイヤー後方エフェクト
static SPR_DATA p_eff_data[] = {
	SPR_DATA{ spr_data::Player_eff, 128, 1 * 6,	 6,	6, -6 / 2,-6 / 2,1 }, //p_eff2
	SPR_DATA{ spr_data::Player_eff, 128, 4 * 6 + 1 * 9, 9, 9, -9 / 2,-9 / 2,2 }, //p_eff2*1.5
	SPR_LOOP
};

//敵消滅エフェクト素材
static SPR_DATA anime_ext_data[] = {
	SPR_DATA{ spr_data::Ext, 128 * 0, 0, 128, 128, -64, -64,0 },
	SPR_DATA{ spr_data::Ext, 128 * 1, 0, 128, 128, -64, -64,1 },
	SPR_DATA{ spr_data::Ext, 128 * 2, 0, 128, 128, -64, -64,2 },
	SPR_DATA{ spr_data::Ext, 128 * 3, 0, 128, 128, -64, -64,3 },
	SPR_DATA{ spr_data::Ext, 128 * 4, 0, 128, 128, -64, -64,4 },
	SPR_DATA{ spr_data::Ext, 128 * 5, 0, 128, 128, -64, -64,5 },
	SPR_DATA{ spr_data::Ext, 128 * 6, 0, 128, 128, -64, -64,6 },
	SPR_DATA{ spr_data::Ext, 128 * 7, 0, 128, 128, -64, -64,7 },
	SPR_LOOP
};

//敵消滅エフェクト(○)
static SPR_DATA EdgeCircle_ext_data = SPR_DATA{ spr_data::EdgeCircle,0,0,128,128,-64,-64,0 };

//敵消滅エフェクト(●)
static SPR_DATA Circle_ext_data = SPR_DATA{ spr_data::Player_eff,0,0,128,128,-64,-64,0 };

//敵消滅エフェクト(キラキラ)
static SPR_DATA kirakira_ext_data = SPR_DATA{ spr_data::Player_eff,320,56,24,24,-12,-12,0 };

//ピントロック時エフェクト(Lock)
static SPR_DATA Lock_data = SPR_DATA{ spr_data::UI6,0,310,100,50,-50,-25 };

//コンボ
static SPR_DATA combo_number[10] = {
	{ spr_data::Number,64 * 0,64 * 0,64,64,-32,-32,64 / 2,64 / 2 }, //0
	{ spr_data::Number,64 * 1,64 * 0,64,64,-32,-32,64 / 2,64 / 2 }, //1
	{ spr_data::Number,64 * 2,64 * 0,64,64,-32,-32,64 / 2,64 / 2 }, //2
	{ spr_data::Number,64 * 3,64 * 0,64,64,-32,-32,64 / 2,64 / 2 }, //3
	{ spr_data::Number,64 * 4,64 * 0,64,64,-32,-32,64 / 2,64 / 2 }, //4
	{ spr_data::Number,64 * 0,64 * 1,64,64,-32,-32,64 / 2,64 / 2 }, //5
	{ spr_data::Number,64 * 1,64 * 1,64,64,-32,-32,64 / 2,64 / 2 }, //6
	{ spr_data::Number,64 * 2,64 * 1,64,64,-32,-32,64 / 2,64 / 2 }, //7
	{ spr_data::Number,64 * 3,64 * 1,64,64,-32,-32,64 / 2,64 / 2 }, //8
	{ spr_data::Number,64 * 4,64 * 1,64,64,-32,-32,64 / 2,64 / 2 }, //9
};

//コンボテキスト
static SPR_DATA combo_text = SPR_DATA{ spr_data::UI6,0,125,120,40,-60,-20  };


//塵エフェクト
//static SPR_DATA dust_data = SPR_DATA{ spr_data::Player_eff,128,3*6,6,6,-6/2,-6/2 };
static SPR_DATA dust_data = SPR_DATA{ spr_data::Player_eff,128,51,9,9,0,0 };
static SPR_DATA anime_dust_data[] = {
	SPR_DATA{ spr_data::Player_eff,128,3*6,6,6,-6/2,-6/2,0 },
	SPR_DATA{ spr_data::Player_eff,128,3*6,6,6,-6/2,-6/2,0 },
	SPR_DATA{ spr_data::Player_eff,128,3*6,6,6,-6/2,-6/2,0 },
	SPR_DATA{ spr_data::Player_eff,128,3*6,6,6,-6/2,-6/2,0 },
	SPR_DATA{ spr_data::Player_eff,128,51,9,9,-9/2,-9/2,1 },
	SPR_DATA{ spr_data::Player_eff,128,51,9,9,-9/2,-9/2,1 },
	SPR_DATA{ spr_data::Player_eff,128,51,9,9,-9/2,-9/2,1 },
	SPR_DATA{ spr_data::Player_eff,128,51,9,9,-9/2,-9/2,1 },
	SPR_LOOP
};


//ゲームクリア時エフェクト
static SPR_DATA gameclear_data = SPR_DATA{ spr_data::Player_eff,128,32,9,9,-9/2,-9/2 };
//static SPR_DATA noAction_data = SPR_DATA{ spr_data::Player_eff,128,1*6,6,6,-6/2,-6/2 };

//マルチフォーカス使用時エフェクト
static SPR_DATA multi_data = SPR_DATA{spr_data::Mulch_eff,0,0,128,128,-64,-64};


//lineデータ
//static SPR_DATA line_data = SPR_DATA{ spr_data::Player_eff,128+2,3*6,2,2,-2/1,-2/1 };
static SPR_DATA line_data = SPR_DATA{ spr_data::Player_eff,128,60,4,4,-2,-2 }; //4×4
//static SPR_DATA line_data = SPR_DATA{ spr_data::Player_eff,128,60,2,2,-1,-1 }; //2×2
//static SPR_DATA line_data = SPR_DATA{ spr_data::Player_eff,320-64,0,8,8,-4,-4 };



//static SPR_DATA p_eff_data[] = {
//	SPR_DATA{spr_data::Player_eff, 128, 0*6,	 6,	6, -6/2,-6/2,1}, //p_eff1
//	SPR_DATA{spr_data::Player_eff, 128, 4*6,	 9, 9, -9/2,-9/2,2}, //p_eff1*1.5
//	SPR_DATA{			       -1,	 0,       0, 0, 0,    0,   0,3}
//};
//
//static SPR_DATA p_eff_data[] = {
//	SPR_DATA{spr_data::Player_eff, 128, 1*6,	 6,	6, -6/2,-6/2,1}, //p_eff2
//	SPR_DATA{spr_data::Player_eff, 128, 4*6+1*9, 9, 9, -9/2,-9/2,2}, //p_eff2*1.5
//	SPR_DATA{			       -1,	 0,       0, 0, 0,    0,   0,3}
//};
//
//static SPR_DATA p_eff_data[] = {
//	SPR_DATA{spr_data::Player_eff, 128, 2*6,	 6,	6, -6/2,-6/2,1}, //p_eff3
//	SPR_DATA{spr_data::Player_eff, 128, 4*6+2*9, 9, 9, -9/2,-9/2,2}, //p_eff3*1.5
//	SPR_DATA{			       -1,	 0,       0, 0, 0,    0,   0,3}
//};
//
//static SPR_DATA p_eff_data[] = {
//	SPR_DATA{spr_data::Player_eff, 128, 3*6,	 6,	6, -6/2,-6/2,1}, //p_eff4
//	SPR_DATA{spr_data::Player_eff, 128, 4*6+3*9, 9, 9, -9/2,-9/2,2}, //p_eff4*1.5
//	SPR_DATA{			       -1,	 0,       0, 0, 0,    0,   0,3}
//};





void Effect::Update()
{
	//if (move)
	//{
	//	move(this);
	animetion();
	//}
}

//Effect_Manager::Effect_Manager()
//{
//
//}
//
//Effect_Manager::~Effect_Manager()
//{
//
//}

void Effect_Manager::searchSet(V2 pos, V2 spd, void(*move)(Effect*), OBJ2D* parent) {
	for (int i = 0; i < EFF_MAX; i++) {
		if (effect[i] && effect[i]->init_fg)continue;
		if (!effect[i])effect[i] = new Effect();
		effect[i]->clear();
		effect[i]->pos = pos;
		effect[i]->spd = spd;
		effect[i]->move = move;
		effect[i]->init_fg = true;
		effect[i]->parent = parent;
		break;
	}
}




void Effect_Manager::Init() {

	shift_objects = V2(0,0);
	shift_all = V2(0, 0);
	shift_multierror = V2(0,0);
	shift_jast = V2(0, 0);

	for (int i = 0; i < EFF_MAX; i++) {
		if (!effect[i])continue;
		effect[i]->clear();
	}

	shift_objects_trg = false;
	shift_all_trg = false;
	shift_multierror_trg = false;
	shift_jast_trg = false;

}
void Effect_Manager::Update() {

	shift_objects = V2(0,0);
	shift_all = V2(0, 0);
	shift_multierror = V2(0,0);
	shift_jast = V2(0, 0);

	for (int i = 0; i < EFF_MAX; i++) {
		if (effect[i] && effect[i]->move) {
			effect[i]->move(effect[i]);
			effect[i]->Update();
		}
	}
	//pD_TEXT->set_Text(V2(600, 264), "ef_trg_t", shift_objects_trg == true, 0xFFFFFFFF);
	//pD_TEXT->set_Text(V2(600, 280), "ef_trg_f", shift_objects_trg == false, 0xFFFFFFFF);
	//pD_TEXT->set_Text(V2(600, 296), "ef_trg_02", shift_objects_trg == 0x02, 0xFFFFFFFF);
	//pD_TEXT->set_Text(V2(600, 312), "ef_trg_01", shift_objects_trg == 0x01, 0xFFFFFFFF);
	
	if ((shift_objects_trg == true) || (shift_all_trg == true)) {

		//Player* p = pPlayer;
		//p->custom.ef_ofsX = shift_objects.x;
		//p->custom.ef_ofsY = shift_objects.y;
		
		//Enemy** e = pEnemy_Manager->enemy;
		//for (int i = 0; i < ENEMY_MAX; i++) {
		//	if (!e[i])continue;
		//	e[i]->custom.ef_ofsX = shift_objects.x;
		//	e[i]->custom.ef_ofsY = shift_objects.y;
		//}

		//Effect** f = pEffect_Manager->effect;
		//for (int i = 0; i < EFF_MAX; i++) {
		//	if (!f[i])continue;
		//	f[i]->custom.ef_ofsX += shift_objects.x;
		//	f[i]->custom.ef_ofsY += shift_objects.y;
		//}

		Frame* r = pFrame;
		r->custom.ef_ofsX = shift_objects.x;

	}

	if ((shift_all_trg == true)) {

	}




	if ( shift_multierror_trg==true ) {
		Player* p = pPlayer;
		p->custom.ef_ofsX = shift_multierror.x;
		p->custom.ef_ofsY = shift_multierror.y;
	}


	if ( shift_jast_trg==true ) {
		Frame* r = pFrame;
		r->custom.ef_ofsX = shift_jast.x;
		r->custom.ef_ofsY = shift_jast.y;
	}






	if ((shift_objects_trg == TRG_RELEASE) || (shift_all_trg == TRG_RELEASE) || 
		(shift_multierror_trg == TRG_RELEASE) || (shift_jast_trg == TRG_RELEASE)) {
		Player* p = pPlayer;
		p->custom.ef_ofsX = 0;
		p->custom.ef_ofsY = 0;

		Enemy** e = pEnemy_Manager->enemy;

		for (int i = 0; i < ENEMY_MAX; i++) {
			if (!e[i])continue;
			e[i]->custom.ef_ofsX = 0;
			e[i]->custom.ef_ofsY = 0;
		}

		Effect** f = pEffect_Manager->effect;
		for (int i = 0; i < EFF_MAX; i++) {
			if (!f[i])continue;
			f[i]->custom.ef_ofsX = 0;
			f[i]->custom.ef_ofsY = 0;
		}

		Frame* r = pFrame;
		r->custom.ef_ofsX = 0;
		r->custom.ef_ofsY = 0;
	}

	if ((shift_all_trg == 0x10)) {


	}

	//pD_TEXT->set_Text(V2(600, 312 + 24), "shift_obj_x", shift_objects.x, 0xFFFFFFFF);
	//pD_TEXT->set_Text(V2(600, 312 + 40), "shift_obj_y", shift_objects.y, 0xFFFFFFFF);
}
void Effect_Manager::Render() {
	for (int i = 0; i < EFF_MAX; i++) {
		if (effect[i] && effect[i]->move)effect[i]->Render();
	}
}



Effect::Effect()
{
	clear();
}

Effect::~Effect()
{

}

void Effect::clear() {
	OBJ2DEX::clear();
	//delete_flg = false;
	move = nullptr;
	init_fg = false;
	alpha = 255;

	for (int i = 0; i < 16; i++) {
		i_work[i] = 0;
	}
}
void Effect::Init() {
	clear();
}

void Effect_Manager::add_all(V2 v) {
	shift_all += v;
	shift_all_trg = true;

}
void Effect_Manager::add_object(V2 v) {
	shift_objects += v;
	shift_objects_trg = true;
}

//ジャストピント時振動
void Effect_Manager::add_multierror(V2 v) {
	shift_multierror += v;
	shift_multierror_trg = true;
}
//マルチフォーカス失敗振動
void Effect_Manager::add_jast(V2 v) {
	shift_jast += v;
	shift_jast_trg = true;
}


//フレーム回転
void framerotate(Effect *obj)
{
	switch (obj->state)
	{
	case INIT:
		obj->data = &Frame_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 1;
		obj->custom.angle = 0;
		obj->state=MOVE;
	case MOVE:
		obj->custom.scaleX = obj->custom.scaleY -= 0.05f;
		obj->custom.angle -= 15;
		if (obj->custom.scaleX<0) obj->state = CLEAR;
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}


//敵消滅時エフェクト
void Extinction(Effect *obj)
{
	switch (obj->state)
	{
	case INIT:
		//obj->data = &Ext_data;
		obj->animeData = anime_Jet_data;
		obj->data = &obj->animeData[0];
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.7f;
		obj->i_work[0] = (int)obj->pos.y;
		obj->timer = 0;
		obj->alpha = 255;
		obj->state=MOVE;
	case MOVE:
		obj->pos -= obj->spd;
		if ( /*(obj->i_work[0]-100)>obj->pos.y ||*/ obj->timer++>50) {
			if (obj->alpha>25) obj->alpha -= 25; //透明処理
			else {
				obj->alpha = 0;
				obj->state = CLEAR; //透明になったら消去処理へ
			}
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}


//飛行エフェクト
void kemuri(Effect *obj)
{
	switch (obj->state)
	{
	case INIT:
		//obj->data = &Ext_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.7f;
		obj->timer = 0;
		obj->alpha = (int)(255 * 0.7f);
		obj->state=MOVE;
	case MOVE:
		obj->pos += obj->spd;
		obj->custom.scaleX = obj->custom.scaleY -= 0.02f;
		if (obj->custom.scaleX<0) {
			obj->state = CLEAR;
		}
		if (obj->timer++>10) {
			//if ( obj->alpha>25 ) obj->alpha-=50; //透明処理
			//else {
			//	obj->alpha = 0;
			//	obj->state = CLEAR; //透明になったら消去処理へ
			//}
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}

//消滅エフェクト
//void CircleExt(Effect *obj)
//{
//	switch (obj->state)
//	{
//	case INIT:
//		obj->animeData = anime_ext_data;
//		obj->data = &obj->animeData[0];
//		obj->custom.scaleMode = CENTER;
//		obj->custom.scaleX = obj->custom.scaleY = 1.1f;
//		obj->timer = 0;
//		obj->alpha = (int)(255 * 0.7f);
//		obj->state++;
//		
//		//break;
//	case MOVE:
//		//if ( obj->timer++>12 ) {
//		//	obj->state = CLEAR; //消去処理へ
//		//}
//		if (obj->timer++>15) {
//			obj->state = CLEAR; //消去処理へ
//		}
//
//		//if ( obj->data->no < 0 ) {	//アニメーションが最後なら
//		//	obj->state = CLEAR;			//消去処理へ
//		//}
//		//if ( obj->data->frameNum>4 ) {	//frameNumが4以上なら
//		//	obj->state = CLEAR;				//消去処理へ
//		//}
//		break;
//	case CLEAR:
//		obj->clear();
//		break;
//	default:
//		break;
//	}
//}

//******************************************************************************

//敵消滅エフェクト
void Ext(Effect *obj)
{
	switch (obj->state)
	{
	case INIT:
		obj->animeData = anime_ext_data;
		obj->data = &obj->animeData[0];
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 2.0f;
		obj->timer = 0;
		obj->state=MOVE;
		//break;
	case MOVE:
		if (obj->timer++>30) {
			obj->state = CLEAR; //消去処理へ
			obj->timer = 0;
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}

//敵消滅エフェクト(丸)
void CircleExt(Effect *obj) {
	switch (obj->state)
	{
	case INIT:
		//else if (obj->timer%5 <= 2) obj->custom.argb = 0xCCFFFFFF;	//白色
		//if (obj->timer%5 <= 1) obj->custom.argb = 0xCCffab05;	//オレンジ色
		//else if (obj->timer%5 <= 3) obj->custom.argb = 0xCCc577ef;	//紫色
		//else if (obj->timer%5 <= 5) obj->custom.argb = 0xFFD68D8D;	//薄赤色
		obj->data = &EdgeCircle_ext_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.5f;
		obj->alpha = 0; //透明
		obj->timer = 0;
		obj->state = MOVE;
		//break;
	case MOVE:
		//spd.x=0		出現time
		//spd.y=2.0f	拡大限度
		if(obj->timer==(int)(obj->spd.x)) obj->alpha = (int)(255*0.8f);//指定秒数経ったら現れる
		if (obj->timer>=(int)(obj->spd.x)) { 
			obj->custom.scaleX = obj->custom.scaleY += 0.2f;	//拡大処理
				 if (obj->timer%5 <= 1) obj->custom.argb = 0xFFFFFF90;	//赤色
			else if (obj->timer%5 <= 3) obj->custom.argb = 0xFFFFCC90;	//青色
			else if (obj->timer%5 <= 5) obj->custom.argb = 0xFFFFAA90;	//緑色
		}
		if (obj->custom.scaleX>=obj->spd.y) {	//一定の大きさになったら
			obj->alpha -= 255/8;
			if ( obj->alpha<0 ) {	//透明になったら
				obj->alpha = 0;
				obj->timer = 0;
				obj->state = CLEAR;	//消去へ
			}
		}
		obj->timer++;
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}

}

//敵消滅エフェクト(丸)
void CircleExt_lightB(Effect *obj) {
	switch (obj->state)
	{
		case INIT:
			obj->data = &EdgeCircle_ext_data;
			obj->custom.scaleMode = CENTER;
			obj->custom.scaleX = obj->custom.scaleY = 0.5f;
			obj->custom.argb = 0xDD5BE1FF;
			obj->alpha = 0; //透明
			obj->timer = 0;
			obj->state = MOVE;
			//break;
		case MOVE:
			//spd.x=0		出現time
			//spd.y=2.0f	拡大限度
			if(obj->timer==(int)(obj->spd.x)) obj->alpha = (int)(255);//指定秒数経ったら現れる
			if (obj->timer>=(int)(obj->spd.x)) { 
				obj->custom.scaleX = obj->custom.scaleY += 0.2f;	//拡大処理
			}
			if (obj->custom.scaleX>=obj->spd.y) {	//一定の大きさになったら
				obj->alpha -= 255/8;
				if ( obj->alpha<0 ) {	//透明になったら
					obj->alpha = 0;
					obj->timer = 0;
					obj->state = CLEAR;	//消去へ
				}
			}
			obj->timer++;
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}

}

//敵消滅エフェクト(散らばる●)
void ParticleExt_c(Effect* obj) {
	switch (obj->state) {
	case INIT:
		obj->data = &Circle_ext_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.1f;
		obj->custom.argb = 0xFFFFFFFF;
		obj->timer = 0;
		obj->alpha = 0;
		obj->i_work[6] = 0;
		obj->state=MOVE;
		//break;
	case MOVE:
		obj->alpha = (int)(255);
		//obj->custom.scaleX = obj->custom.scaleY =(float)(rand()%30)/10.0f+1.0f;	//大きさ変更(1.0～2.0倍)
		obj->custom.scaleX = obj->custom.scaleY = (float)(rand() % 10) / 15.0f;	//大きさ変更(0.1～1.0倍)
		obj->i_work[6] = rand() % 4;
		if (obj->i_work[6] == 0) obj->custom.argb = 0xFFD68D8D;	//赤色
		if (obj->i_work[6] == 1) obj->custom.argb = 0xFF86ace8;	//青色
		if (obj->i_work[6] == 2) obj->custom.argb = 0xFFE2E268;	//黄色
		if (obj->i_work[6] == 3) obj->custom.argb = 0xFFc577ef;	//紫色
		if (obj->i_work[6] == 4) obj->custom.argb = 0xFFa2f783;	//緑色
		obj->pos.x += obj->spd.x; //散らばる処理
		obj->pos.y += obj->spd.y; //散らばる処理

		if (obj->timer++>20) {	//指定時間経ったら
			obj->state = CLEAR;		//消去処理へ
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}

//敵消滅エフェクト(散らばるキラキラ)
void ParticleExt_k(Effect* obj) {
	switch (obj->state) {
	case INIT:
		obj->data = &kirakira_ext_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.1f;
		obj->custom.argb = 0xFFFFFFFF;
		obj->timer = 0;
		obj->alpha = 0;
		obj->i_work[6] = 0;
		obj->state=MOVE;
		//break;
	case MOVE:
		obj->alpha = (int)(255);
		//obj->custom.scaleX = obj->custom.scaleY =(float)(rand()%10)/10.0f+1.0f;	//大きさ変更(1.0～2.0倍)
		obj->custom.scaleX = obj->custom.scaleY = (float)(rand() % 10) / 5.0f;	//大きさ変更(0.5～2.0倍)
		obj->i_work[6] = rand() % 4;
		if (obj->i_work[6] == 0) obj->custom.argb = 0xFFD68D8D;	//赤色
		if (obj->i_work[6] == 1) obj->custom.argb = 0xFF86ace8;	//青色
		if (obj->i_work[6] == 2) obj->custom.argb = 0xFFE2E268;	//黄色
		if (obj->i_work[6] == 3) obj->custom.argb = 0xFFc577ef;	//紫色
		if (obj->i_work[6] == 4) obj->custom.argb = 0xFFa2f783;	//緑色
		obj->pos.x += obj->spd.x; //散らばる処理
		obj->pos.y += obj->spd.y; //散らばる処理

		if (obj->timer++>20) {	//指定時間経ったら
			obj->state = CLEAR;		//消去処理へ
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}

//******************************************************************************

//Lockエフェクト
void Lock(Effect* obj) {
	switch (obj->state) {
	case INIT:
		obj->data = &Lock_data;
		obj->custom.argb = 0xFFFFFFFF;
		obj->custom.scaleMode = CENTER;
		obj->timer = 0;
		obj->alpha = 255;
		obj->i_work[6] = 0;
		obj->state=MOVE;
		//break;
	case MOVE:
		obj->i_work[6] = obj->timer % 5;
		if (obj->i_work[6] <= 1) obj->custom.argb = 0xCCffab05;	//オレンジ色
		else if (obj->i_work[6] <= 3) obj->custom.argb = 0xCCc577ef;	//紫色
		else if (obj->i_work[6] <= 5) obj->custom.argb = 0xFFD68D8D;	//薄赤色

		if (obj->timer++>18) obj->state = MOVE2; //拡大へ
		break;
	case MOVE2: //拡大
		obj->custom.scaleX = obj->custom.scaleY += 0.7f;
		if (obj->custom.scaleX >= 1.7f) obj->state = MOVE3;
		break;
	case MOVE3: //縮小
		obj->custom.scaleX = obj->custom.scaleY -= 0.2f;
		if (obj->custom.scaleX <= 1.4f) obj->state = MOVE4;
		break;
	case MOVE4: //scaleY縮小
		obj->custom.scaleY -= 0.3f;
		if (obj->custom.scaleY<0.0f) obj->state = CLEAR;
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}



#include "sceneMain.h"
//コンボカラー
void Combo_Color(Effect*obj) {
	if ( pScore->getCombo()<=9 ) { //0～コンボ時の色
		obj->i_work[6] = obj->timer%7+1;
		if (obj->i_work[6]<=3) obj->custom.argb = 0xFFffad21;		//オレンジ色
		else if (obj->i_work[6]<=5) obj->custom.argb = 0xFFc77fef;	//紫色
		else if (obj->i_work[6]<=7) obj->custom.argb = 0xFFed9797;	//薄赤色
	}
	else if ( pScore->getCombo()<=19 ) { //10～コンボ時の色
		obj->i_work[6] = obj->timer%10+1;
		if (obj->i_work[6]<=5) obj->custom.argb = 0xFFd0e021;		//黄色
		else if (obj->i_work[6]<=10) obj->custom.argb = 0xFFf76c8c;	//ピンク色
	}
	else /*if ( pScore->getCombo()<=29 )*/ { //20～コンボ時の色
		obj->i_work[6] = obj->timer%12+1;
		     if (obj->i_work[6]<=2)  obj->custom.argb = 0xFFe65ffc;	//紫色
		else if (obj->i_work[6]<=4)  obj->custom.argb = 0xFFff8426;	//オレンジ色
		else if (obj->i_work[6]<=6)  obj->custom.argb = 0xFFffe942;	//黄色
		else if (obj->i_work[6]<=8)  obj->custom.argb = 0xFF8dff42;	//緑色
		else if (obj->i_work[6]<=10) obj->custom.argb = 0xFF58eaef;	//水色
		else if (obj->i_work[6]<=12) obj->custom.argb = 0xFF5e9bff;	//青色
	}
}

//コンボ
void Combo(Effect* obj) {
	switch (obj->state) {
	case INIT:
		obj->data = &combo_number[0];
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 1.3f;
		obj->timer = 0;
		obj->i_work[6] = 0; //色変更ランダム用
		obj->i_work[7] = 0; //コンボ用
		obj->f_work[8] = obj->pos.y; //座標保存用
		obj->custom.argb = 0xFFffab05;	//オレンジ色
		obj->spd.y = -4;
		obj->state=MOVE;
		//break;
	case MOVE:
		obj->i_work[7] = (int)obj->spd.x; //コンボ
		obj->data = &combo_number[obj->i_work[7]]; //コンボ表示
		Combo_Color(obj); //色
		if ((obj->f_work[8]-40)<obj->pos.y) obj->pos.y += obj->spd.y; //移動処理
		else if (obj->timer>30) obj->state = CLEAR; //消去
		obj->timer++;
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}

//コンボテキスト
void ComboText(Effect* obj) {
	switch ( obj->state ){
	case INIT:
		obj->data = &combo_text;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY =0.6f;
		obj->timer = 0;
		obj->i_work[6] = 0; //色変更ランダム用
		obj->f_work[8] = obj->pos.y; //座標保存用
		obj->custom.argb = 0xFFffab05;	//オレンジ色
		obj->spd.y = -4;
		obj->state=MOVE;
		//break;
	case MOVE:
		Combo_Color(obj); //色
		if ((obj->f_work[8]-40)<obj->pos.y) obj->pos.y += obj->spd.y; //移動処理
		else if (obj->timer>30) obj->state = CLEAR; //消去
		obj->timer++;
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;

	}
}



//塵(ちり)エフェクト
void dust(Effect* obj) {
	switch ( obj->state ) {
		case INIT:
			obj->data = &dust_data;
			//obj->animeData = anime_dust_data;
			//obj->data = &obj->animeData[0];
			obj->custom.scaleMode = CENTER;
			if(obj->spd.y==-1.0f) obj->custom.scaleX = obj->custom.scaleY = 0.8f;
			if(obj->spd.y==-2.0f) obj->custom.scaleX = obj->custom.scaleY = 0.6f;
			if(obj->spd.y==-3.0f) obj->custom.scaleX = obj->custom.scaleY = 0.4f;
			obj->timer = 0;
			obj->alpha = 0;
			obj->state=MOVE;
			//break;
		case MOVE:
			obj->timer++;
			//移動----------------------------------------------
			//obj->pos.x += cosf(obj->timer*0.03f);
			if ( obj->timer>360 )obj->timer = 0;
			obj->pos.x += cosf(obj->timer*obj->spd.x);
			obj->pos.y += obj->spd.y;

			//出現処理------------------------------------------
			if ( obj->timer>(rand()%100) ) obj->alpha += 25;
			if ( obj->alpha>255 ) obj->alpha = 255;

			if ( obj->pos.y<150 ) {
				//透明処理------------------------------------------
				obj->alpha -= 25;
				if ( obj->alpha<0 ) obj->alpha = 0;
				obj->state = CLEAR; //上までいったら消去
			}
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//スカエフェクト
void noAction(Effect *obj) {
	switch (obj->state)
	{
		case INIT:
			obj->data = &EdgeCircle_ext_data;
			obj->custom.scaleMode = CENTER;
			obj->custom.scaleX = obj->custom.scaleY = 0.5f;
			obj->custom.argb = 0xFFffa8a8;
			obj->state=MOVE;
			//break;
		case MOVE:
			obj->custom.scaleX = obj->custom.scaleY += 0.25f;	//拡大処理
			if (obj->custom.scaleX>2.0f) {	//一定の大きさになったら
				obj->alpha -= 255/6;
				if ( obj->alpha<0 ) {	//透明になったら
					obj->alpha = 0;
					obj->state = CLEAR;	//消去へ
				}
			}
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}



//ゲームクリア時エフェクト集合
void gameclear_aggre(Effect*obj) {
	switch ( obj->state ) {
		case INIT:
		case MOVE:
			if ( obj->timer==0 ) pEffect_Manager->searchSet(V2(0,0), V2(0,0), gameclear_screen_many); //画面全体
			if ( obj->timer==0 ) pEffect_Manager->searchSet(obj->pos, obj->spd, gameclear_eight); //8方向
			if ( obj->timer==5 ) pEffect_Manager->searchSet(obj->pos, obj->spd, gameclear_eight); //8方向
			if ( obj->timer==10 ) {
				pEffect_Manager->searchSet(obj->pos, obj->spd, gameclear_eight); //8方向
				pEffect_Manager->searchSet(obj->pos, V2(6,6), gameclear_kirakira); //キラキラ
			}
			if ( obj->timer>10 ) obj->state = CLEAR;
			obj->timer++;
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//ゲームクリア時画面全体エフェクト
void gameclear_screen_many(Effect*obj) {
	switch ( obj->state ) {
		case INIT:
		case MOVE:
			//pEffect_Manager->searchSet(V2(			 0+300,  			 0+250), V2(0,0), gameclear_screen);
			//pEffect_Manager->searchSet(V2(SCREEN_WIDTH-300,  			 0+250), V2(0,0), gameclear_screen);
			//pEffect_Manager->searchSet(V2(			 0+300,  SCREEN_HEIGHT-100), V2(0,0), gameclear_screen);
			//pEffect_Manager->searchSet(V2(SCREEN_WIDTH-300,  SCREEN_HEIGHT-100), V2(0,0), gameclear_screen);
			pEffect_Manager->searchSet(V2(SCREEN_WIDTH/4*1, SCREEN_HEIGHT/4*1), V2(0,0), gameclear_screen);
			pEffect_Manager->searchSet(V2(SCREEN_WIDTH/4*3, SCREEN_HEIGHT/4*1), V2(0,0), gameclear_screen);
			pEffect_Manager->searchSet(V2(SCREEN_WIDTH/4*1, SCREEN_HEIGHT/4*3), V2(0,0), gameclear_screen);
			pEffect_Manager->searchSet(V2(SCREEN_WIDTH/4*3, SCREEN_HEIGHT/4*3), V2(0,0), gameclear_screen);
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//ゲームクリア時画面全体エフェクト
void gameclear_screen(Effect*obj) {
	switch (obj->state) {
		case INIT:
			obj->data = &kirakira_ext_data;
			obj->custom.scaleMode = CENTER;
			obj->custom.scaleX = obj->custom.scaleY = 3.0f;
			obj->custom.argb = 0xFFFFFFFF;
			obj->alpha = (int)(255*0.6f);
			obj->timer = 0;
			obj->i_work[6] = 0; //色
			obj->f_work[1] = obj->pos.x;
			obj->f_work[2] = obj->pos.y;
			obj->state=MOVE;
			//break;
		case MOVE:
			//obj->custom.scaleX = obj->custom.scaleY =(float)(rand()%10)/10.0f+2.0f;	//大きさ変更(1.0～2.0倍)
			//obj->custom.scaleX = obj->custom.scaleY =(float)(rand()%3)+2.0f;	//大きさ変更(2.0～4.0倍)
			obj->i_work[6] = obj->timer % 20+1;
			if (obj->i_work[6] <= 4) obj->custom.argb = 0xFFffa5a5;	//赤色
			else if (obj->i_work[6] <= 8) obj->custom.argb = 0xFFb2d0ff;	//青色
			else if (obj->i_work[6] <= 12) obj->custom.argb = 0xFFffffa3;	//黄色
			else if (obj->i_work[6] <= 16) obj->custom.argb = 0xFFdfa5ff;	//紫色
			else if (obj->i_work[6] <= 20) obj->custom.argb = 0xFFcaffb7;	//緑色

			if ( (obj->timer%2+1)<=1 ) {
				obj->pos.x = obj->f_work[1]+rand()%200-100;
				obj->pos.y = obj->f_work[2]+rand()%200-100;
			}

			if (obj->timer>40) {	//指定時間経ったら
				obj->alpha -= 60;
				if ( obj->alpha<0 ) obj->alpha = 0;
				obj->state = CLEAR;		//消去処理へ
			}
			obj->timer++;
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//ゲームクリア時エフェクトキラキラ
void gameclear_kirakira(Effect* obj) {
	switch ( obj->state ) {
		case INIT:
		case MOVE:
			pEffect_Manager->searchSet(obj->pos, V2( obj->spd.x,		   0), ParticleExt_k); //右
			pEffect_Manager->searchSet(obj->pos, V2(-obj->spd.x,		   0), ParticleExt_k); //左
			pEffect_Manager->searchSet(obj->pos, V2(		  0,  obj->spd.y), ParticleExt_k); //上
			pEffect_Manager->searchSet(obj->pos, V2(		  0,  obj->spd.y), ParticleExt_k); //下
			pEffect_Manager->searchSet(obj->pos, V2( obj->spd.x,  obj->spd.y), ParticleExt_k); //ななめ
			pEffect_Manager->searchSet(obj->pos, V2( obj->spd.x, -obj->spd.y), ParticleExt_k); //ななめ
			pEffect_Manager->searchSet(obj->pos, V2(-obj->spd.x,  obj->spd.y), ParticleExt_k); //ななめ
			pEffect_Manager->searchSet(obj->pos, V2(-obj->spd.x, -obj->spd.y), ParticleExt_k); //ななめ
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//ゲームクリア時エフェクト8方向
void gameclear_eight(Effect* obj) {
	switch ( obj->state ) {
		case INIT:
		case MOVE:
			pEffect_Manager->searchSet(obj->pos, V2( obj->spd.x+2,			  0), gameclear); //右
			pEffect_Manager->searchSet(obj->pos, V2(-obj->spd.x-2,			  0), gameclear); //左
			pEffect_Manager->searchSet(obj->pos, V2(		  0,   obj->spd.x+2), gameclear); //上
			pEffect_Manager->searchSet(obj->pos, V2(		  0,  -obj->spd.x-2), gameclear); //下
			pEffect_Manager->searchSet(obj->pos, V2( obj->spd.x,  obj->spd.y), gameclear); //ななめ
			pEffect_Manager->searchSet(obj->pos, V2( obj->spd.x, -obj->spd.y), gameclear); //ななめ
			pEffect_Manager->searchSet(obj->pos, V2(-obj->spd.x,  obj->spd.y), gameclear); //ななめ
			pEffect_Manager->searchSet(obj->pos, V2(-obj->spd.x, -obj->spd.y), gameclear); //ななめ
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//ゲームクリア時エフェクト
void gameclear(Effect* obj) {
	switch ( obj->state ) {
		case INIT:
			obj->data = &gameclear_data;
			obj->alpha = 0; //透明
			obj->timer = 0;
			obj->custom.scaleMode = CENTER;
			obj->custom.argb = 0xFFffa8da;
			obj->state = MOVE;
			//break;
		case MOVE:
			obj->pos += obj->spd;
			if ( obj->timer==7 ) obj->alpha = 255;
			if ( obj->timer>=18 ) obj->state = CLEAR;
			obj->timer++;
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}



//プレイヤーダメージエフェクト
void P_damage(Effect* obj) {
	switch ( obj->state ) {
		case INIT:
			obj->data = &EdgeCircle_ext_data;
			obj->custom.scaleMode = CENTER;
			obj->custom.scaleX = obj->custom.scaleY = 0.2f;
			obj->custom.argb = 0xFF47dde5;
			obj->state=MOVE;
			//break;
		case MOVE:
			if ( obj->timer++>14 ) obj->state = CLEAR;
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//マルチフォーカス使用時エフェクト
void Multifocus(Effect*obj) {
	switch ( obj->state ) {
		case INIT:
			obj->data = &multi_data;
			obj->custom.scaleMode = CENTER;
			obj->custom.scaleX = obj->custom.scaleY = obj->spd.y;
			obj->custom.argb = 0xFFFFFFFF; //色
			obj->alpha = (int)(255*0.5f);
			obj->i_work[1] = (int)(obj->spd.x); //angle_spd
			obj->state = MOVE;
			//break;
		case MOVE:
			//プレイヤーの座標
			obj->pos.x = pPlayer->pos.x;
			obj->pos.y = pPlayer->pos.y;

			//回転
			obj->custom.angle += obj->i_work[1];
			if ( obj->custom.angle>=360 ) obj->custom.angle = 0;

			//色
			if ( (obj->timer%18)<9 )  obj->custom.argb = 0xFFFFFFFF; //01
			if ( (obj->timer%18)>=9 ) obj->custom.argb = 0xFFff7a7a; //23

			//消去準備------------------------------------------------
			if ( (obj->timer>(MALTIFOCUS_TIME-60)) && (obj->timer<MALTIFOCUS_TIME) ) {
				//点滅
				if ( (obj->timer%4)<2 )  obj->alpha = (int)(255*0.1f); //01
				if ( (obj->timer%4)>=2 ) obj->alpha = (int)(255*0.7f); //23
			}
			//透明
			if ( obj->timer>MALTIFOCUS_TIME ) {
				obj->alpha -= 20;
				obj->custom.scaleX = obj->custom.scaleY += 0.05f;
				if ( obj->alpha<0 ) {
					obj->alpha = 0;
					obj->timer = 0;
					obj->custom.angle = 0;
					obj->state = CLEAR;
				}
			}
			obj->timer++;
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//テレポートエフェクト
void TeleportExt(Effect *obj)
{
	switch (obj->state)
	{
	case INIT:
		obj->animeData = anime_tele_data;
		obj->data = &obj->animeData[0];
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.5f;
		obj->alpha = (int)(255 * 0.7f);
		obj->custom.argb = 0xFFFFFFFF;
		obj->timer = 0;
		obj->state=MOVE;
	case MOVE:
		if (obj->timer++>16) {
			obj->state = CLEAR; //消去処理へ
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}


//ジャストピントエフェクト(衝撃波)
void Just_pinto(Effect *obj)
{
	switch (obj->state)
	{
	case INIT:
		//obj->animeData = anime_ext_data;
		obj->data = &jastpinto_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 1.0f;
		obj->custom.argb = 0xDDff9393; //赤色
		obj->timer = 0;
		obj->alpha = (int)(255 * 0.8f);
		obj->state=MOVE;
		//break;
	case MOVE:
		obj->alpha -= 6;					//透明処理
		if (obj->alpha<0) obj->alpha = 0;	//
		obj->custom.scaleX = obj->custom.scaleY += 0.17f;	//拡大処理
		if (obj->custom.scaleX>3.0f) {	//一定の大きさになったら
			obj->state = CLEAR;					//消去処理へ
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}


//ピントロック(衝撃波)
void pinto_lock(Effect *obj)
{
	switch (obj->state)
	{
	case INIT:
		//obj->animeData = anime_ext_data;
		obj->data = &jastpinto_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 3.0f;
		obj->custom.argb = 0xDDCFCFCF; //赤色
		obj->timer = 0;
		obj->alpha = (int)(255 * 0.8f);
		obj->state++;
		//break;
	case MOVE:
		obj->alpha -= 6;					//透明処理
		if (obj->alpha<0) obj->alpha = 0;	//
		obj->custom.scaleX = obj->custom.scaleY -= 0.17f;	//拡大処理
		if (obj->custom.scaleX<0.5f) {	//一定の大きさになったら
			obj->state = CLEAR;					//消去処理へ
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}


//ジェットエフェクト
void Jet(Effect *obj) {
	switch (obj->state) {
	case INIT:
		//obj->animeData = anime_ext_data;
		obj->data = &jet_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.4f;
		obj->custom.argb = 0xFFFFFFFF;
		obj->timer = 0;
		obj->alpha = (int)(255 * 0.7f);
		obj->state=MOVE;
		//break;
	case MOVE:
		obj->custom.scaleX = obj->custom.scaleY -= 0.01f;							//縮小処理
		if (obj->custom.scaleX<0) obj->custom.scaleX = obj->custom.scaleY = 0;	//
		obj->alpha -= 8;						//透明処理
		if (obj->alpha<0) obj->alpha = 0;		//
		obj->pos.y += 2;

		if (obj->timer++>12) { //指定時間経ったら
			obj->state = CLEAR; //消去処理へ
		}
		break;
	case CLEAR:
		obj->clear();
		//pEffect_Manager->searchSet(V2(pPlayer->pos.x, pPlayer->pos.y+40), V2(0, 0), Jet);
		break;
	default:
		break;
	}
}


//プレイヤー後方エフェクト
void P_particle(Effect* obj) {
	switch (obj->state) {
	case INIT:
		obj->animeData = p_eff_data;
		obj->data = &obj->animeData[0];
		//obj->data = &p_eff_data[5];
		obj->custom.argb = 0xFFFFFF55;
		obj->timer = 0;
		obj->alpha = (int)(255 * 0.6f);
		obj->state = MOVE;
		//break;
	case MOVE:
		if (obj->timer>6) {
			obj->alpha -= 28;						//透明処理
			if (obj->alpha<0) obj->alpha = 0;		//
		}
		obj->pos.y += 0.8f;
		if (obj->timer++>15) { //指定時間経ったら
			obj->state = CLEAR; //消去処理へ
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}



//lineエフェクト
void line(Effect* obj) {
	switch ( obj->state ) {
		case INIT:
			obj->data = &line_data;
			obj->timer = 0;
			obj->alpha = (int)(255*0.5f);
			//obj->custom.scaleMode = CENTER;
			//obj->custom.scaleX = obj->custom.scaleY = 0.7f;
			obj->custom.argb = 0xFFd6fff9;
			obj->state=MOVE;
			//break;
		case MOVE:
			//点滅
			//if ( (obj->timer%2)<1 )  obj->custom.argb = 0xFFFF0000;
			//if ( (obj->timer%2)>=1 ) obj->custom.argb = 0xFFFFFFFF;
			//if ( (obj->timer%2)<1 )  obj->alpha=(int)(255*0.2f);
			//if ( (obj->timer%2)>=1 ) obj->alpha=(int)(255*0.7f);
			if ( obj->timer>=1 ) {
				obj->timer = 0;
				obj->state = CLEAR;
			}
			obj->timer++;
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//フェードイン
void fade_In(Effect* obj) {
	switch (obj->state) {
	case INIT:
		obj->data = &fade_in;
		obj->custom.scaleMode = LEFTTOP;
		obj->timer = 0;
		obj->state = MOVE;
		//break;
	case MOVE:
		obj->pos.x -= 24;

		if (obj->timer++ > 120) { //指定時間経ったら
			obj->state = CLEAR; //消去処理へ
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}

}

//フェードアウト
void fade_Out(Effect* obj) {
	switch (obj->state) {
	case INIT:
		obj->data = &fade_out;
		obj->custom.scaleMode = LEFTTOP;
		obj->timer = 0;
		obj->state = MOVE;
		//break;
	case MOVE:
		obj->pos.x -= 17;
		if (obj->pos.x < -SCREEN_WIDTH) { //指定時間経ったら
			obj->state = MOVE2; //ループへ
			obj->pos.x = -SCREEN_WIDTH;
		}
		break;
	case MOVE2:
		break;

	case CLEAR:
		obj->clear();

		break;
	default:
		break;
	}

}






#define SHAKE_MAX obj->f_work[12]
#define SHAKE_MIN obj->f_work[13]
#define SHAKE_X obj->f_work[14]
#define SHAKE_Y obj->f_work[15]
void Shake(Effect* obj) {

	int randxy = rand();

	switch (obj->state)
	{
	case INIT:
		SHAKE_MAX = obj->pos.x;
		SHAKE_MIN = obj->pos.y;

		obj->timer = (int)obj->spd.x;
		obj->state = (int) obj->spd.y;
		break;
	case MOVE: //ジャストピント時振動もしくは、マルチフォーカス失敗振動
		//SHAKE_Y =  (int)((randxy % (SHAKE_MAX - SHAKE_MIN)) - SHAKE_MIN)/2;
		//SHAKE_X = (int)(randxy % (SHAKE_MAX - SHAKE_MIN)) - SHAKE_MIN;
		SHAKE_X = ((randxy%201)-100)*0.01f*(SHAKE_MAX-SHAKE_MIN)+SHAKE_MIN;
		//-100～100 -1～1 MIN～MAX

		if (obj->timer-- < 0) {
			obj->timer = 0;
			obj->state = CLEAR;
		}
		pEffect_Manager->add_object(V2(SHAKE_X, SHAKE_Y));

		break;
	case MOVE2:
		//SHAKE_X = (randxy % (SHAKE_MAX - SHAKE_MIN)) - SHAKE_MIN;
		//SHAKE_Y = ((randxy % (SHAKE_MAX - SHAKE_MIN)) - SHAKE_MIN)/2;
		SHAKE_X = ((randxy%201)-100)*0.01f*(SHAKE_MAX-SHAKE_MIN)+SHAKE_MIN;
		if (obj->timer-- < 0) {
			obj->timer = 0;
			obj->state = CLEAR;
		}
		pEffect_Manager->add_all(V2(SHAKE_X, SHAKE_Y));
		break;

	case MOVE3: //マルチフォーカス失敗振動(右下UI)
		SHAKE_X = ((randxy%201)-100)*0.01f*(SHAKE_MAX-SHAKE_MIN)+SHAKE_MIN;
		if (obj->timer-- < 0) {
			obj->timer = 0;
			obj->state = CLEAR;
		}
		pEffect_Manager->add_multierror(V2(SHAKE_X, SHAKE_Y));
		break;
	case MOVE4: //ジャストピント時振動
		SHAKE_X = ((randxy%201)-100)*0.01f*(SHAKE_MAX-SHAKE_MIN)+SHAKE_MIN;
		if (obj->timer-- < 0) {
			obj->timer = 0;
			obj->state = CLEAR;
		}
		pEffect_Manager->add_jast(V2(SHAKE_X, SHAKE_Y));
		break;
	case CLEAR:
		obj->clear();
	default:
		obj->state = CLEAR;
		break;
	}

}




void Effect::Render() {
	if (data) {
		//spr_data::Render(pos,data,((alpha << 24) | (0x00FFFFFF)),0);
		custom.argb = (alpha << 24 | custom.argb << 8 >> 8);
		spr_data::Render(pos, data, &custom, custom.argb);
	}
}