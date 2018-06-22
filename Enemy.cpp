#include "iextreme.h"
#include "system\System.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Frame.h"
#include "Enemy.h"
#include "Effect.h"
#include "Number.h"

#include "stage_data.h"
#include "sceneMain.h"
#include "Sound.h"


enum {
	INIT,	//初期設定
	BEGIN,	//
	APPEARANCE,	//
	BEGIN2,	//
	SLIDE_IN,  //スライドイン
	WARP_IN,   //ワープイン
	HOPPING_IN,//ホッピングイン
	HOPPING_IN2,//ホッピングイン
	HOPPING_IN3,//ホッピングイン
	MOVE,	//移動処理
	MOVE2,	//
	MOVE3,	//
	MOVE4,	//
	MOVE5,	//
	STOP,	//停止処理
	STOP2,	//
	ROTATE,	//回転処理
	FLASHING, //点滅処理

	DEAD,	//死亡処理
	DEAD2,	//
	EFFECT, //エフェクト
	CLEAR,	//初期化
};

//仮＿敵データ
static SPR_DATA Enemy_data = SPR_DATA{ spr_data::Enemy1, 0, 0, 64, 64, -32, -32 };


//通常-----------------------------------------------------------------
static SPR_DATA Enemy_data_yellow[] = { //黄
	SPR_DATA{ spr_data::Enemy2, 64 * 0, 64 * 0,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 1, 64 * 0,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 2, 64 * 0,	64,64,-32,-32,2 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,3 },
};
static SPR_DATA Enemy_data_green[] = { //緑
	SPR_DATA{ spr_data::Enemy2, 64 * 0, 64 * 1,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 1, 64 * 1,	64,64,-32,-32,1 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,2 },
};
static SPR_DATA Enemy_data_pink[] = { //ピンク
	SPR_DATA{ spr_data::Enemy2, 64 * 0, 64 * 2,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 1, 64 * 2,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 2, 64 * 2,	64,64,-32,-32,2 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,3 },
};
static SPR_DATA Enemy_data_blue[] = { //青
	SPR_DATA{ spr_data::Enemy2, 64 * 0, 64 * 3,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 1, 64 * 3,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 2, 64 * 3,	64,64,-32,-32,2 },
	SPR_DATA{ spr_data::Enemy2, 64 * 3, 64 * 3,	64,64,-32,-32,3 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,4 },
};
static SPR_DATA Enemy_data_white[] = { //白
	SPR_DATA{ spr_data::Enemy2, 64 * 0, 64 * 4,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 1, 64 * 4,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 2, 64 * 4,	64,64,-32,-32,2 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,3 },
};
static SPR_DATA Enemy_data_kari[] = { //仮
	SPR_DATA{ spr_data::Enemy1, 64 * 0, 0, 64, 64, -32, -32,0 },
	SPR_DATA{ spr_data::Enemy1, 64 * 0, 0, 64, 64, -32, -32,1 },
	SPR_DATA{ spr_data::Enemy1, 64 * 0, 0, 64, 64, -32, -32,2 },
	SPR_DATA{ spr_data::Enemy1, 64 * 0, 0, 64, 64, -32, -32,3 },
	SPR_DATA{ spr_data::Enemy1, 64 * 1, 0, 64, 64, -32, -32,4 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,5 },
};
//白-------------------------------------------------------------------
static SPR_DATA Enemy_data_yellow_damage[] = { //黄
	SPR_DATA{ spr_data::Enemy2, 64 * 4, 64 * 0,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 5, 64 * 0,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 6, 64 * 0,	64,64,-32,-32,2 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,3 },
};
static SPR_DATA Enemy_data_green_damage[] = { //緑
	SPR_DATA{ spr_data::Enemy2, 64 * 4, 64 * 1,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 5, 64 * 1,	64,64,-32,-32,1 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,2 },
};
static SPR_DATA Enemy_data_pink_damage[] = { //ピンク
	SPR_DATA{ spr_data::Enemy2, 64 * 4, 64 * 2,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 5, 64 * 2,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 6, 64 * 2,	64,64,-32,-32,2 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,3 },
};
static SPR_DATA Enemy_data_blue_damage[] = { //青
	SPR_DATA{ spr_data::Enemy2, 64 * 4, 64 * 3,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 5, 64 * 3,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 6, 64 * 3,	64,64,-32,-32,2 },
	SPR_DATA{ spr_data::Enemy2, 64 * 7, 64 * 3,	64,64,-32,-32,3 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,4 },
};
static SPR_DATA Enemy_data_white_damage[] = { //白
	SPR_DATA{ spr_data::Enemy2, 64 * 4, 64 * 4,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 5, 64 * 4,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 6, 64 * 4,	64,64,-32,-32,2 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,3 },
};
static SPR_DATA Enemy_data_kari_damage[] = { //仮
	SPR_DATA{ spr_data::Enemy1, 64 * 2, 0,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy1, 64 * 2, 0,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy1, 64 * 2, 0,	64,64,-32,-32,2 },
	SPR_DATA{ spr_data::Enemy1, 64 * 2, 0,	64,64,-32,-32,3 },
	SPR_DATA{ spr_data::Enemy1, 64 * 2, 0,	64,64,-32,-32,4 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,5},
};
//通常＆白-------------------------------------------------------------
static SPR_DATA* yellow_data[] = {
	{Enemy_data_yellow},
	{Enemy_data_yellow_damage},
};
static SPR_DATA* green_data[] = {
	{Enemy_data_green},
	{Enemy_data_green_damage},
};
static SPR_DATA* pink_data[] = {
	{Enemy_data_pink},
	{Enemy_data_pink_damage},
};
static SPR_DATA* blue_data[] = {
	{Enemy_data_blue},
	{Enemy_data_blue_damage},
};
static SPR_DATA* white_data[] = {
	{Enemy_data_white},
	{Enemy_data_white_damage},
};
static SPR_DATA* kari_data[] = {
	{Enemy_data_kari},
	{Enemy_data_kari_damage},
};

enum {
	normal = 0,
	Damage,
};




enum {	//テクスチャ番号変換
	pinto_s = spr_data::UI1,
	pinto_a = spr_data::UI2,
	pinto_l = spr_data::UI4,
	flame_out = spr_data::UI3,
};

SPR_DATA spr_pinto_s = { pinto_s,0,0,128,128,-64,-64 };//青サークル
SPR_DATA spr_pinto_a = { pinto_a,0,0,128,128,-64,-64 };//赤矢印
SPR_DATA spr_combo = { spr_data::UI6,0,125,120,40,0,0 }; //COMBO



//当たり判定(obj1のサイズ内にobj2のサイズが全て入っているか)
bool E_Judge(OBJ2D *obj1, OBJ2D *obj2)
{
	if (obj1->pos.x + obj1->size.x > obj2->pos.x + obj2->size.x) return false;
	if (obj2->pos.x - obj2->size.x > obj1->pos.x - obj1->size.x) return false;
	if (obj1->pos.y + obj1->size.y > obj2->pos.y + obj2->size.y) return false;
	if (obj2->pos.y - obj2->size.y > obj1->pos.y - obj1->size.y) return false;

	return true;
}

//距離判定(obj1とobj2の距離が_lenge以内)
bool E_lenge(OBJ2D *obj1, OBJ2D *obj2, int _lenge)
{
	float lenge;
	float dx = obj1->pos.x - obj2->pos.x;
	float dy = obj1->pos.y - obj2->pos.y;
	lenge = sqrtf(dx*dx + dy*dy);
	if (lenge < _lenge) {
		return true;
	}
	return false;
}

//プレイヤーまでの距離計算(obj1とobj2の距離)
V2 E_P(OBJ2D *obj1, OBJ2D *obj2, V2 spd)
{
	float dx = obj1->pos.x - obj2->pos.x; //二間の距離
	float dy = obj1->pos.y - obj2->pos.y; //二間の距離
	float lenge = sqrtf(dx*dx + dy*dy);	//
	float ax = spd.x * dx / lenge;		//
	float ay = spd.y * dy / lenge;		//
	return V2(ax, ay);
}



//敵ダメージ点滅関数
void Frash_white(Enemy* obj,int num) {
	obj->flash_timer++;
	pScore->add_ClearlyScore(1); //スコア加算

	if ( (obj->flash_timer%(num*2))<=4 ) { //01234
		obj->animeData = obj->Anime_Box[Damage];
		obj->alpha = 255*0.75f;
	}
	else if ( (obj->flash_timer%(num*2))<=9 ) { //56789
		obj->animeData = obj->Anime_Box[normal];
		obj->alpha = 255;
	}
	else if ( (obj->flash_timer%(num*2))<=14 ) { //1011121314
		obj->animeData = obj->Anime_Box[Damage];
		obj->alpha = 255*0.75f;
	}
	else {
		obj->animeData = obj->Anime_Box[normal];
		obj->alpha = 255;
	}
}

//なにで判断するか,間隔,点滅させたいargb,色１,色２
void Frash_Color(Enemy* obj,int num,D3DCOLOR argb1, D3DCOLOR argb2) {
	obj->flash_timer++;
	if ((obj->flash_timer % (num * 2)) <  num) obj->custom.argb = argb1;
	if ((obj->flash_timer % (num * 2)) >= num) obj->custom.argb = argb2;
}
//点滅関数(色)
//なにで判断するか,間隔,点滅させたいargb,色１,色２
D3DCOLOR Frash_Color(int timer,int num,D3DCOLOR argb,D3DCOLOR argb1, D3DCOLOR argb2) {
	if ((timer % (num * 2)) <  num) argb = argb1;
	if ((timer % (num * 2)) >= num) argb = argb2;
	return argb;
}
//点滅関数(透明度)
//なにで判断するか,間隔,点滅させたいalpha,倍率１,倍率２,いつまで
int Frash_Alpha(int timer, int num, int alpha, float alpha1, float alpha2, int end) {
	if (timer<end) {
		if ((timer % (num * 2)) <  num) alpha = 255 * alpha1;
		if ((timer % (num * 2)) >= num) alpha = 255 * alpha2;
	}
	else alpha = 255;
	return alpha;
}



void Enemy_Manager::just_dragIn(Enemy* obj) {
	if (obj->sz < JUSTPINTO_SIZE) { //ジャストピントの範囲なら
		pEffect_Manager->searchSet(V2(12, 4), V2(10, 2), Shake); //振動
		pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y), V2(0, 0), Just_pinto);
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (!enemy[i] || !enemy[i]->move)continue;
			if (E_lenge(obj, enemy[i], DRAGIN_SCALE)) { //範囲内を
				enemy[i]->z = (pFrame->Get_f_z());		//同じZ値にする(巻き込む)
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------------
//
//	敵型
//
//---------------------------------------------------------------------------------------------------------

//当たり判定に該当するならダメージを追加
void Enemy_Manager::damage_Calculation(Enemy* obj) {

	if (obj->sz < pFrame->getPintoSize())
	{
		if (pFrame->lockPinto_trg == true) {
			pEffect_Manager->searchSet(obj->pos, V2(0, 0), pinto_lock); //ピントロックエフェクト
			pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y - 50), V2(0, 0), Lock); //Lockエフェクト
			obj->zlock_flg = true;
		}
		if ( obj->damage>(obj->damageMAX-obj->damageMAX/4) ) Frash_white(obj,11); //白点滅(早)
		else Frash_white(obj, 35); //白点滅(遅)
		obj->damage += DAMAGE;
		obj->damageflg = true;
	}
	else {
		obj->damageflg = false;
		obj->animeData = obj->Anime_Box[normal];
		obj->alpha = 255;
	}
}




//Enemy_Manager::Enemy_Manager()
//{
//
//}
//
//Enemy_Manager::~Enemy_Manager()
//{
//
//}

//
void Enemy_Manager::searchSet(V2 pos, V2 spd, void(*move)(Enemy*), float _z, Enemy* parent) {
	for (int i = 0; i < ENEMY_MAX; i++) {
		//中身があり、行動が行われているならループ
		if (enemy[i] && enemy[i]->init_fg)continue;
		//中身が無いなら作成
		if (!enemy[i])enemy[i] = new Enemy();
		//初期設定
		enemy[i]->clear();
		enemy[i]->pos = pos;
		enemy[i]->spd = spd;
		enemy[i]->move = move;
		(_z == rand_PINTO) ? enemy[i]->z = ((rand() % (PINTO_MAX * 2)) - PINTO_MAX) : enemy[i]->z = _z;
		enemy[i]->init_fg = true;
		if (parent)enemy[i]->parent = parent;
		break;
	}
}

STAGE_DATA* stageSetData_time[] = {
	tutorial_time,
	stage1_time,
	//stage2_setData,
	//stage3_setData,
};

STAGE_DATA* stageSetData_kill[] = {
	tutorial_time,
	stage1_kill,
};


void Enemy_Manager::Init(int stageNo) {

	for (int i = 0; i < ENEMY_MAX; i++) {
		if (!enemy[i])continue;
		enemy[i]->clear();
	}
	timer = 0;
	data = stageSetData_time[stageNo];
	data2 = stageSetData_kill[stageNo];
}
void Enemy_Manager::Update() {
	//if ((pFrame->Get_f_z() + DAMAGE_SIZE) > 90 || (pFrame->Get_f_z() - DAMAGE_SIZE) < -90)
	//	calculation_refrect_flg = true;
	//else 
	//	calculation_refrect_flg = false;

	stageUpdate();

	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i] && enemy[i]->move) {
			enemy[i]->move(enemy[i]);
			enemy[i]->Update();
			enemy[i]->UIUpdate();

		}
	}
}

void Enemy::UIUpdate() {
	if (sz < JUSTPINTO_SIZE) { //ジャストピントなら
		u.argb = Frash_Color(count, 7, u.argb, 0x33D68D8D, 0xDDE2E268);	//点滅(赤,黄)
		//拡大--------------------------
		custom.scaleMode = CENTER;
		u.custom.scaleX = u.custom.scaleY = 1.2f;
//		if (count == 1)IEX_PlaySound(SE_JUSTPINTO, FALSE);	//ジャストピントが合ったときのSE
		count++;
	}
	else if (damageflg == true) { //ダメージを受けているとき
		u.argb = Frash_Color(count, 15, u.argb, 0x22FFFFFF, 0xDDE26868);	//点滅(白,赤)
		//拡大--------------------------
		custom.scaleMode = CENTER;
		u.custom.scaleX = u.custom.scaleY = 1.2f;
		if (count == 1)IEX_PlaySound(SE_PINTO, FALSE);	//ピントが合ったときのSE
		count++;
	}
	else { //ダメージを受けていないとき
		u.argb = 0xDD5BE1FF; //※水色
		custom.scaleMode = CENTER;
		u.custom.scaleX = u.custom.scaleY = 1.0f;
		count = 0;
	}
	//line_rect(pos, V2(size.x * custom.scaleX, size.y * custom.scaleY), 0xFFFFFFFF, custom.scaleMode);
}
void Enemy_Manager::stageUpdate()
{
	timer++;

	//timerで管理
	while (data->appearTime <= timer)
	{
		if (data->appearTime<0) {
			break;
		}
		if (data->moveType == nullptr) break;
		pEnemy_Manager->searchSet(data->moveType, data->pos - V2(pMAP->getScrollX(), pMAP->getScrollY()), data->speed, data->speedAcc, data->speedMax, (float)data->z);
		data++;
	}

	//撃破数で管理
	while (data2->appearTime <= pScore->getKill_num()) {
		if (data2->appearTime == 0) {
			data2++;
			break;
		}
		if (data2->moveType == nullptr) break;
		pEnemy_Manager->searchSet(data2->moveType, data2->pos - V2(pMAP->getScrollX(), pMAP->getScrollY()), data2->speed, data2->speedAcc, data2->speedMax, (float)data2->z);
		data2++;
	}
}

void Enemy_Manager::Render() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i] && enemy[i]->move)enemy[i]->Render();
	}
}
void Enemy_Manager::UIUpdate() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i] && enemy[i]->move) {
			enemy[i]->UIUpdate();
		}
	}
}
void Enemy_Manager::UIRender() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i] && enemy[i]->move) {
			enemy[i]->UIRender();
		}
	}
}




Enemy::Enemy()
{
	clear();
}

Enemy::~Enemy()
{

}
void Enemy::clear() {
	OBJ2DEX::clear();
	//delete_flg = false;
	move = nullptr;
	z = 0;
	damage = 0;
	damageMAX = 0;
	damageflg = false;
	rangeflg = false;
	alpha = 255;
	count = 0;
	u.argb = 0xFFFFFFFF;

	dx = 0;
	dy = 0;
	dist = 0;
	XCENTER = 0;
	YCENTER = 0;
	ANGLE = 0;
	ANGLEspd = 0;
	RADIUS = 0;

	init_fg = false;
	z_flg = false;
	zlock_flg = false;
	flash_timer = 0;

	for (int i = 0; i < 16; i++) {
		f_work[i] = 0;
	}
	custom.scaleMode = CENTER;
}
void Enemy::Init() {
	clear();
}
void Enemy::Update()
{
	animation();
}



float Enemy_Manager::get_sz(float z) {
	float sz = 0;
	float ez = z;
	float fz = pFrame->Get_f_z();

	if (fz > ez) {
		sz = (fz + 90) - (ez + 90);
	}
	else {
		sz = (ez + 90) - (fz + 90);
	}

	//	if (sz > 90)sz = 180 - sz;
	return sz;
}

//void Enemy::anime() {
//	
//}

//////////////////////////////////////////////////////////////////////////
//
//レンダー
//
//////////////////////////////////////////////////////////////////////////
void Enemy::Render() {
	if (!data)return;
	custom.argb = (alpha << 24 | custom.argb << 8 >> 8);
	shader2D->SetValue("FPower", sz > 90 ? (180 - sz) / 90 : sz / 90);
	spr_data::Render(pos, data, &custom, custom.argb, shader2D, "depth");
	//spr_data::Render(V2(pos.x+custom.ef_ofsX,pos.y), data, &custom, custom.argb, shader2D, "depth");
}

void Enemy::UIRender() {
	if (data) {
		if (E_lenge(this, pFrame, FRAME_SIZE / 2)) {
			if ( state!=APPEARANCE ) {
				spr_data::Render(pos, &spr_pinto_s, u.argb, 0);
				//spr_data::Render(pos, &spr_pinto_s, &u.custom, u.argb);
				spr_data::Render(pos, &spr_pinto_a, 0xFFFFFFFF, /*z + pFrame->Get_f_z()   */z > pFrame->Get_f_z() ? sz : -sz);
				//iexPolygon::Rect((SCREEN_WIDTH / 2) + z - DAMAGE_SIZE, PINTO_POSY, DAMAGE_SIZE + DAMAGE_SIZE, 20, 0, 0xFF00FFFF);// Z
			}
		}
	}

	//iexPolygon::Rect(pos.x,pos.y + 50,damage/ DAMAGE_LINE,10,0,0xFFFF0000); //damage_line
	//
	//iexPolygon::Rect(pos.x, pos.y, 1, 1, 0, 0xFFFF0000);//center

	////横
	//iexPolygon::Rect((pos.x - size.x), (pos.y + size.y), (size.x * 2),1, 0, 0xFFFF0000);//{
	//iexPolygon::Rect((pos.x - size.x), (pos.y - size.y), (size.x * 2),1, 0, 0xFFFF0000);//　judge_line

	//////縦
	//iexPolygon::Rect((pos.x + size.x), (pos.y - size.y),1, size.y * 2, 0, 0xFFFF0000);//
	//iexPolygon::Rect((pos.x - size.x), (pos.y - size.y),1, size.y * 2, 0, 0xFFFF0000);//}

}


//初期化
void Enemy_Init(Enemy* obj) {
	obj->damage = 0;
	obj->timer = 0;
	obj->alpha = 255;
	obj->rangeflg = false;
	obj->noHit_flg = true;
}

inline void Enemy_Update(Enemy* obj) {
	//ダメージ処理
	if (!obj->zlock_flg) {
		obj->sz = pEnemy_Manager->get_sz(obj->z);
	}
	obj->rangeflg = E_lenge(obj, pPlayer, FRAME_SIZE / 2);
	if (obj->rangeflg) {
		pEnemy_Manager->damage_Calculation(obj);
	}
	//反転チェック
	if ((obj->pos.x - pPlayer->pos.x)<0) obj->custom.reflectX = true;
	else obj->custom.reflectX = false;
	//死亡チェック
	if (obj->damage > obj->damageMAX) obj->state = DEAD;
}

//出現直後当たり判定なし(点滅)
void Enemy_appearance(Enemy* obj) {
	obj->alpha = Frash_Alpha(obj->timer, 2, obj->alpha, 0.3f, 0.6f, 80); //点滅(透明度)
	if (obj->timer++ >= 80) { //一定時間経ったら
		obj->state = BEGIN;
		obj->timer = 0;
	}
}

//死亡時エフェクト
void Enemy_DeadEffect(Enemy*obj) {
	for (int i = 0; i<5; i++) pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y), V2((float)(rand() % 20 - 10), (float)(rand() % 20 - 10)), ParticleExt_k);	//パーティクルエフェクトキラキラ
	pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y), V2(0.0f, 1.5f), CircleExt_lightB);	//丸エフェクト
	if (obj->sz < JUSTPINTO_SIZE) { //ジャストピントの範囲ならエフェクト追加
		pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y), V2(0.0f, 1.5f), CircleExt);		//丸エフェクト
		pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y), V2(4.0f, 2.5f), CircleExt);		//丸エフェクト
		for (int i = 0; i<5; i++) pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y), V2((float)(rand() % 20 - 10), (float)(rand() % 20 - 10)), ParticleExt_c);	//パーティクルエフェクト●
		pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y), V2(0, 0), Ext);				//敵消滅エフェクト
		pEffect_Manager->searchSet(V2(6, 2), V2(15, 1), Shake); //振動
	}
}

//コンボ関数
void Combo(Enemy* obj) {
	int combo = pScore->getCombo(); //コンボ数
	if ( combo>=2 ) { //2コンボから
		int _combo = combo;
		int count = 0;
		int n = 0;
		int pos_x = 0;

		//桁数を調べる-----------------------------------
		while ( _combo>=10 ) { //10以上なら
			_combo /= 10;		//10で割って
			count++;		//x位置ずらしカウント
		}
		//描画-------------------------------------------
		do {
			_combo = combo % 10;	//1の位抽出
			combo /= 10;			//1の位切捨て排除
			pos_x = obj->pos.x+50+(count-(count-n)*-32); //x位置ずらし
			pEffect_Manager->searchSet(V2(pos_x, obj->pos.y-40), V2((float)_combo, 0), Combo);		//コンボ
			//count--;
			n++;
		} while ( combo>0 );

		pEffect_Manager->searchSet(V2(pos_x+59+count*32, obj->pos.y-36), V2(0, 0), ComboText);		//コンボテキスト
	}
}


//死亡エフェクト＆消去処理
void Enemy_Dead(Enemy* obj) {
	pFrame->add_Exorcise(KILL_CURE);
	pEnemy_Manager->just_dragIn(obj);
	Enemy_DeadEffect(obj);			//死亡時エフェクト
	pScore->add_KillScore(obj->score);		//スコア,コンボ,kill数加算
	Combo(obj);						//コンボ表示
	IEX_PlaySound(SE_EXT, FALSE);	//消滅時のSE
	pPlayer->mltfcs.add_point(1);
	obj->clear();
}



////////////////////////////////////////////////////////////////////////////////////////////
//
//　敵関数
//
////////////////////////////////////////////////////////////////////////////////////////////

//動かない敵
void Base(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:	//初期設定
		obj->data = &Enemy_data;
		obj->damageMAX = DAMAGE_MAX;
		obj->custom.argb = 0x0000FFFF;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		Enemy_Init(obj);
		obj->state = BEGIN;
		//break;
	case BEGIN:
		//ダメージ判定
		Enemy_Update(obj);
		break;
	case DEAD: //死亡処理
		Enemy_Dead(obj);
		break;
	default:
		break;
	}
}


//近づいたら姿を現す敵
void Sudden(Enemy* obj) {
	switch (obj->state)
	{
	case INIT: //初期設定
		obj->data = &Enemy_data;
		obj->damageMAX = DAMAGE_MAX;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		Enemy_Init(obj);
		obj->state = BEGIN;
		//break;
	case BEGIN:
		Enemy_Update(obj);
		obj->rangeflg = E_lenge(obj, pPlayer, 300); //距離判定
		if (obj->rangeflg == true) {
			obj->alpha += (255 / 20);				//
			if (obj->alpha>255) obj->alpha = 255;	//
		}											//	
		else {										//	神出鬼没処理
			obj->alpha -= (255 / 20);				//
			if (obj->alpha<0) obj->alpha = 0;		//
		}											//
		break;
	case DEAD: //死亡処理
		Enemy_Dead(obj);
		break;
	default:
		break;
	}
}


//テレポート
void Teleport(Enemy* obj) {
	switch (obj->state)
	{
	case INIT: //初期設定
		obj->Anime_Box = blue_data;
		obj->animeData = obj->Anime_Box[normal];
		obj->data = &obj->animeData[0];
		obj->damageMAX = 400;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		obj->score = 100;
		Enemy_Init(obj);
		obj->state = APPEARANCE;
		//break;
	case APPEARANCE:
		Enemy_appearance(obj);
		break;
	case BEGIN:
		obj->rangeflg = E_lenge(obj, pPlayer, 400); //距離判定
		if (obj->rangeflg == true) { //範囲内なら
			obj->state = STOP;
		}
		break;
	case STOP: //停止処理
		Enemy_Update(obj);
		if (obj->timer++>100) {
			obj->timer = 0;
			obj->state = EFFECT;
		}
		break;
	case EFFECT: //テレポートエフェクト
		pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y), V2(0, 0), TeleportExt);
		obj->alpha = 0;
		obj->state = BEGIN2;
		break;
	case BEGIN2: //座標移動
		Enemy_Update(obj);
		//---------------------------------------------------------------------
		//obj->pos.x += ( (rand()%3-1)*200 );
		//obj->pos.y += ( (rand()%3-1)*200 );
		obj->pos.x += ( (float)(rand()%201-100)*0.01f*200.0f );
		obj->pos.y += ( (float)(rand()%201-100)*0.01f*200.0f );
		if ( obj->pos.x<100 ) obj->pos.x += 200;
		if ( (SCREEN_WIDTH*2-100)<obj->pos.x ) obj->pos.x -= 200;
		if ( obj->pos.y<100 ) obj->pos.y += 200;
		if ( (SCREEN_HEIGHT-100)<obj->pos.y ) obj->pos.y -= 200;
		//---------------------------------------------------------------------
		obj->state = FLASHING;
		break;
	case FLASHING: //点滅処理
		Enemy_Update(obj);
		obj->timer++;
		if (obj->timer % 5<3) obj->alpha = (int)(255 * 0.3f); //0,1,2の時
		else				  obj->alpha = (int)(255 * 0.6f); //3,4,5の時
		if (obj->timer >= 50) {
			obj->alpha = 255;
			obj->state = BEGIN;
			obj->timer = 0;
		}
		break;
	case DEAD: //死亡処理
		Enemy_Dead(obj);
		pEnemy_Kill->kill_num_blue++;

		break;
	default:
		break;
	}
}


//襲ってくる敵
void Normal(Enemy* obj) {
	switch (obj->state)
	{
	case INIT: //初期設定
		obj->Anime_Box = pink_data;
		obj->animeData = obj->Anime_Box[normal];
		obj->data = &obj->animeData[0];
		obj->damageMAX = 400;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		Enemy_Init(obj);
		obj->score = 100;
		obj->state = APPEARANCE;
		//break;
	case APPEARANCE:
		Enemy_appearance(obj);
		break;
	case BEGIN:	//もし範囲内ならプレイヤーに近づく
		Enemy_Update(obj);
		obj->rangeflg = E_lenge(obj, pPlayer, 300); //距離判定
		if (obj->rangeflg == true) {
			obj->pos -= E_P(obj, pPlayer, obj->spd); //移動処理
		}
		break;
	case DEAD: //死亡処理
		Enemy_Dead(obj);
		pEnemy_Kill->kill_num_pink++;


		break;
	default:
		break;
	}
}


//敵(突進)
void Tombo(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->Anime_Box = green_data;
		obj->animeData = obj->Anime_Box[normal];
		obj->data = &obj->animeData[0];
		obj->damageMAX = 1000;
		obj->pos.y -= 10;			//----------
		obj->ANGLE = INIT_ANGLE;	//　回転用
		obj->ANGLEspd = 0.5f;		//
		obj->RADIUS = 6.0f;			//----------
		obj->f_work[0] = 0;	//座標保存用
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		obj->size = V2(20 / 2, 20 / 2);
		Enemy_Init(obj);
		obj->score = 100;
		obj->state = APPEARANCE;
		//break;
	case APPEARANCE:
		Enemy_appearance(obj);
		break;
	case BEGIN:
		Enemy_Update(obj);
		obj->rangeflg = E_lenge(obj, pPlayer, 1000); //距離判定
		if (obj->rangeflg == true) { //範囲内なら

//				obj->spd = E_P(obj, pPlayer, obj->spd); //移動処理 8.0f

			obj->dx = obj->pos.x - pPlayer->pos.x;				//
			obj->dy = obj->pos.y - pPlayer->pos.y;				//
			obj->dist = sqrtf(obj->dx*obj->dx + obj->dy*obj->dy);	//移動量計算
			obj->spd.x = 8.0f * obj->dx / obj->dist;				//
			obj->spd.y = 8.0f * obj->dy / obj->dist;				//

			obj->state = MOVE;
		}
		break;
	case MOVE: //移動処理(逆)
		Enemy_Update(obj);
		if (obj->timer++<30) obj->pos += obj->spd*0.2f;
		else {
			obj->state = STOP;
			obj->timer = 0;
		}
		break;
	case STOP: //停止処理
		Enemy_Update(obj);
		if (obj->timer++>10) {
			obj->timer = 0;
			obj->state = MOVE2;
		}
		break;
	case MOVE2: //移動処理(直線)
		Enemy_Update(obj);
		if (obj->timer++>40) {
			obj->state = STOP2;
			obj->timer = 0;
		}
		else obj->pos -= obj->spd;

		break;
	case STOP2: //停止処理
		Enemy_Update(obj);
		if (obj->timer++>100) {
			obj->timer = 0;
			obj->state = ROTATE;
			obj->f_work[0] = obj->pos.x; //座標を保存
		}
		//ダメージ処理
		break;
	case ROTATE: //回転処理
		Enemy_Update(obj);
		obj->XCENTER = obj->pos.x; //回転の中心
		obj->YCENTER = obj->pos.y; //回転の中心
		obj->ANGLE += obj->ANGLEspd;
		obj->pos.x = obj->XCENTER + obj->RADIUS*cosf(obj->ANGLE);
		obj->pos.y = obj->YCENTER + obj->RADIUS*sinf(obj->ANGLE);
		//if ( obj->f_work[0] < obj->pos.x &&  
		//	obj->pos.x < (obj->pos.x + (obj->XCENTER+obj->RADIUS*cosf(obj->ANGLE)) - 0.1f) ) { //前の座標に戻ったら
		//	obj->state = BEGIN;
		//}
		if (obj->timer++>15) {
			obj->state = BEGIN;
			obj->timer = 0;
		}
		break;
	case DEAD: //死亡処理
		Enemy_Dead(obj);
		pEnemy_Kill->kill_num_green++;
		break;
	default:
		break;
	}
}


//襲ってくる敵
void zMove(Enemy* obj) {
	switch (obj->state)
	{
	case INIT: //初期設定
		obj->Anime_Box =white_data;
		obj->animeData = obj->Anime_Box[normal];
		obj->data = &obj->animeData[0];

		obj->f_work[3] = obj->z;
		obj->damageMAX = DAMAGE_MAX;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		obj->size = V2(20 / 2, 20 / 2);
		obj->score = 100;
		Enemy_Init(obj);
		obj->state = APPEARANCE;
		//break;
	case APPEARANCE:
		Enemy_appearance(obj);
		break;
	case BEGIN:	//もし範囲内ならプレイヤーに近づく
		Enemy_Update(obj);
		obj->pos -= E_P(obj, pPlayer, obj->spd); //移動処理
		{
			float y = 100 * (sinf(obj->ANGLE * 0.01745f));
			obj->ANGLE += 0.5f;
			//obj->ANGLE++;
			if (obj->ANGLE > 360) {
				obj->ANGLE = 0;
			}
			obj->z = obj->f_work[3];
			obj->z += y;
			if (90 < obj->z) obj->z -= 180;
			if (-90 > obj->z) obj->z += 180;
		}
		//ダメージ処理
		break;
	case DEAD: //死亡処理
		Enemy_Dead(obj);
		pEnemy_Kill->kill_num_white++;

		break;
	default:
		break;
	}
}


//デカイ(向かってくる)
void Big(Enemy* obj) {
	switch (obj->state) {
	case INIT:
		//obj->data = &Enemy_data;
		obj->Anime_Box =kari_data;
		obj->animeData = obj->Anime_Box[normal];
		obj->data = &obj->animeData[0];
		obj->damageMAX = 1000;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = B_scale;
		obj->size = V2(40, 40);
		obj->score = 200;
		Enemy_Init(obj);
		obj->state = APPEARANCE;
		//break;
	case APPEARANCE:
		Enemy_appearance(obj);
		break;
	case BEGIN:	//もし範囲内ならプレイヤーに近づく
		Enemy_Update(obj);

		obj->rangeflg = E_lenge(obj, pPlayer, 500); //距離判定
		if (obj->rangeflg == true) {
			obj->pos -= E_P(obj, pPlayer, obj->spd); //移動処理
		}
		break;
	case DEAD: //死亡処理
		Enemy_Dead(obj);
		pEnemy_Kill->kill_num_kari++;

		break;
	default:
		break;
	}
}



/////////////////////////////////////////////////////////////
//
//集合体
//
/////////////////////////////////////////////////////////////
enum Ag //Aggre
{
	//制御

	//親
	child_num = 0,
	//子
	lenge = 0,
};

//集合体制御
void Aggre(Enemy* obj) {

	switch (obj->state)
	{
	case INIT:
		//初期設定
		obj->data = NULL;
		obj->noHit_flg = false;
		//親生成
		pEnemy_Manager->searchSet(V2(0.0f, 0.0f), V2(0.0f, 0.0f), &Aggre_parent, (float)rand_PINTO, obj);
		{
			float angle = 360 * 0.16666f;
			//子供生成				//
			pEnemy_Manager->searchSet(V2((float)(angle * 0), 0), V2(0.0f, 0.0f), &Aggre_child, (float)rand_PINTO, obj);
			pEnemy_Manager->searchSet(V2((float)(angle * 1), 0), V2(0.0f, 0.0f), &Aggre_child, (float)rand_PINTO, obj);
			pEnemy_Manager->searchSet(V2((float)(angle * 2), 0), V2(0.0f, 0.0f), &Aggre_child, (float)rand_PINTO, obj);
			pEnemy_Manager->searchSet(V2((float)(angle * 3), 0), V2(0.0f, 0.0f), &Aggre_child, (float)rand_PINTO, obj);
			pEnemy_Manager->searchSet(V2((float)(angle * 4), 0), V2(0.0f, 0.0f), &Aggre_child, (float)rand_PINTO, obj);
			pEnemy_Manager->searchSet(V2((float)(angle * 5), 0), V2(0.0f, 0.0f), &Aggre_child, (float)rand_PINTO, obj);
		}
		obj->f_work[child_num] = 0;
		Enemy_Init(obj);
		obj->size = V2(20 / 2, 20 / 2);
		obj->state = MOVE;
		break;
	case MOVE: //移動処理
		obj->pos.x++;						//仮 //todoふわふわ移動
		if (obj->f_work[child_num] <= 0) {	//子供の有無を確認
			obj->state = DEAD;				//無いなら死亡
		}
		break;
	case DEAD: //死亡処理
		//Enemy_Dead(obj);
		obj->clear();
		break;
	default:
		break;
	}
}
//集合体＿親
void Aggre_parent(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->data = &Enemy_data;
		//親設定(制御に自身の存在を渡す)
		obj->damageMAX = DAMAGE_MAX;

		((Enemy*)(obj->parent))->f_work[child_num]++;
		obj->pos = V2(0, 0);
		obj->spd = V2(0, 0);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = B_scale;
		Enemy_Init(obj);
		obj->state = MOVE;
		//break;
	case MOVE: //移動処理
		Enemy_Update(obj);
		//制御に合わせて動く
		obj->pos = ((Enemy*)(obj->parent))->pos;
		//ダメージ処理
		break;
	case DEAD: //死亡処理
		((Enemy*)(obj->parent))->f_work[child_num]--;
		Enemy_Dead(obj);
		pEnemy_Kill->kill_num_kari++;

		break;
	default:
		break;
	}
}
//集合体＿子
void Aggre_child(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->data = &Enemy_data;
		//親設定(制御に自身の存在を渡す)
		((Enemy*)(obj->parent))->f_work[child_num]++;
		obj->ANGLE = obj->pos.x;
		obj->pos = V2(0, 0);
		obj->spd = V2(0, 0);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = C_scale;
		obj->damageMAX = DAMAGE_MAX;
		obj->size = V2(20 / 2, 20 / 2);
		Enemy_Init(obj);
		obj->state = MOVE;
		//break;
	case MOVE:
		//制御に合わせて動く(親の周囲を回転)
		Enemy_Update(obj);
		{
			//回転計算
			float y = sinf(obj->ANGLE * 0.01745f);
			float x = cosf(obj->ANGLE * 0.01745f);
			obj->pos = ((Enemy*)(obj->parent))->pos;
			obj->pos += V2(x * 100, y * 100);
			obj->ANGLE++;
			if (obj->ANGLE > 360) {
				obj->ANGLE = 0;
			}
		}
		break;
	case DEAD: //死亡処理
		((Enemy*)(obj->parent))->f_work[child_num]--;
		pEnemy_Kill->kill_num_kari++;

		Enemy_Dead(obj);
		break;
	default:
		break;
	}
}





/////////////////////////////////////////////////////////////
//
//回転浮遊
//
/////////////////////////////////////////////////////////////

enum
{
	posx = 0,
	posy = 1,
};

//集合体制御(Rotetion)左
void Rotation_Aggre_4(Enemy* obj) {
	switch (obj->state)
	{
	case INIT: //初期設定
		obj->data = NULL;
		pEnemy_Manager->searchSet(V2(0.0f, 0.0f), V2(0.0f, 0.0f), &Rotation, (float)rand_PINTO);
		pEnemy_Manager->searchSet(V2(50.0f, 80.0f), V2(0.0f, 0.0f), &Rotation, (float)rand_PINTO);
		pEnemy_Manager->searchSet(V2(50.0f, -80.0f), V2(0.0f, 0.0f), &Rotation, (float)rand_PINTO);
		pEnemy_Manager->searchSet(V2(100.0f, 0.0f), V2(0.0f, 0.0f), &Rotation, (float)rand_PINTO);
		obj->state = MOVE;
	case MOVE:
		//Enemy_Update(obj);
		obj->state = CLEAR;
		//ダメージ処理
		break;
	case DEAD: //死亡処理
		Enemy_Dead(obj);
		break;
	case CLEAR:
		obj->clear();
	default:
		break;
	}
}

void Rotation(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->Anime_Box = yellow_data;
		obj->animeData = obj->Anime_Box[normal];
		obj->data = &obj->animeData[0];

		//親設定(制御に自身の存在を渡す)
		obj->damageMAX = DAMAGE_MAX;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		obj->score = 100;
		Enemy_Init(obj);
		obj->state = APPEARANCE;
		//break;
	case APPEARANCE:
		Enemy_appearance(obj);
		break;
	case BEGIN:
		//制御に合わせて動く(親の周囲を回転)
		Enemy_Update(obj);
		{
			//回転計算
			obj->pos -= V2(obj->f_work[posx], obj->f_work[posy]);
			float y = 70 * (sinf(obj->ANGLE * 0.01745f));
			float x = 50 * (cosf(obj->ANGLE * 0.01745f));
			obj->f_work[posx] = x;
			obj->f_work[posy] = y;

			obj->pos += V2(x, y);
			obj->ANGLE += 0.5;
			if (obj->ANGLE > 360) {
				obj->ANGLE = 0;
			}
		}
		break;
	case DEAD: //死亡処理
		Enemy_Dead(obj);
		pEnemy_Kill->kill_num_yellow++;

		break;
	default:
		break;
	}
}


void Tutorial(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:	//初期設定
		obj->data = &Enemy_data;
		obj->damageMAX = DAMAGE_MAX;
		obj->custom.argb = 0x0000FFFF;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		Enemy_Init(obj);
		obj->state = BEGIN;
		//break;
	case BEGIN:
		//ダメージ判定
		Enemy_Update(obj);
		break;
	case DEAD: //死亡処理
		Enemy_Dead(obj);
		break;
	default:
		break;
	}
}