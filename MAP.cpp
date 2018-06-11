//******************************************************************************
//
//
//		MAPクラス
//
//
//******************************************************************************
#include "iextreme.h"
#include "Game.h"
#include "Player.h"
#include "Frame.h"
#include "Enemy.h"
#include "Effect.h"
#include "BGFG.h"
#include "MAP.h"

// Commit test

enum {
	normal = 0,//ターゲットデータ参照
	center_lock,//現在の座標に固定
};

#define BGCODE_BLANK		0x0000

#define SCROLL_CENTER_W (480)
#define SCROLL_CENTER_H (270)

#define SCROLL_L (scrollCenter->sc_w)//スクロール開始位置
#define SCROLL_R (scrollCenter->sc_w)//スクロール開始位置
//#define SCROLL_U (scrollCenter->sc_h)//スクロール開始位置
//#define SCROLL_D (scrollCenter->sc_h)//スクロール開始位置
//#define SCROLL_L (SCROLL_CENTER_W - scrollCenter->sc_w)//スクロール開始位置
//#define SCROLL_R (SCROLL_CENTER_W + scrollCenter->sc_w)//スクロール開始位置
#define SCROLL_U (scrollCenter->sc_h)//スクロール開始位置
#define SCROLL_D (scrollCenter->sc_h)//スクロール開始位置


#define SCROLL_WRITE_L		((  0)>>4)			// スクロール書き込み位置（MAPキャラ単位）
#define SCROLL_WRITE_R		((960)>>4)			// スクロール書き込み位置（MAPキャラ単位）

#define SCROLL_WRITE_U		((  0)>>4)			// スクロール書き込み位置（MAPキャラ単位）
#define SCROLL_WRITE_D		((540)>>4)			// スクロール書き込み位置（MAPキャラ単位）

//******************************************************************************
//
//		初期設定
//
//******************************************************************************

// コンストラクタ
MAP::MAP() : pData(0), limitL(0), limitR(0)
{
	clear();
}

//==============================================================================

// 初期設定
void MAP::init(BG_DATA* p)
{
	clear();
	pData = p;
	limitL = 0;
	limitU = 0;
	limitR = (float)(pData->mapX * 512 - 960);
	limitD = (float)(1024 - 540);

	scroll_written = (int)scrollX >> 4;
	for (int dataX = scroll_written + SCROLL_WRITE_L; dataX <= scroll_written + SCROLL_WRITE_R; dataX++) {
		write(dataX);
	}
	minimap.Init(limitR + SCREEN_WIDTH, limitD + SCREEN_HEIGHT);
}

//==============================================================================

// メンバ変数のクリア
void MAP::clear()
{
	// 仮想RAMクリア
	for (int y = 0; y < 64; y++) {
		for (int x = 0; x < 64; x++) {
			vRam[y][x] = BGCODE_BLANK;
		}
	}
	// 表示位置設定
	scrollX = 0;
	scrollY = 0;
	scroll_state = 0;
	effect_shifted_objects = V2(0,0);
	effect_shifted_all = V2(0, 0);
	Shake_state = 0;
	//ミニマップ初期化

	minimap.clear();
}

//******************************************************************************
//
//		更新処理
//
//******************************************************************************

// 更新処理
void MAP::update()
{

	if (!scrollCenter) { if (nextscrollCenter) { scrollCenter = nextscrollCenter; nextscrollCenter = NULL; }return; }

	float nx;
	//float ny;
	float old_x = nx = scrollX;						// スクロールX位置の保存
	float old_y = scrollY;

	float scroll_dx = 0;
	float scroll_dy = 0;

	switch(scroll_state) {

	case normal:
		// スクロール
		if (scrollCenter->pos.x > SCROLL_R) scroll_dx = scrollCenter->pos.x - SCROLL_R; //プレイヤーとスクロールの差を代入
		if (scrollCenter->pos.x < SCROLL_L) scroll_dx = scrollCenter->pos.x - SCROLL_L; //
		nx += scroll_dx;

		if (scrollCenter->pos.y > SCROLL_D)scroll_dy = scrollCenter->pos.y - SCROLL_D; //プレイヤーとスクロールの差を代入
		if (scrollCenter->pos.y < SCROLL_U)scroll_dy = scrollCenter->pos.y - SCROLL_U; //
		scrollY += scroll_dy;
		break;
	case center_lock:
		if (scrollCenter->pos.x > lock.x) scroll_dx = scrollCenter->pos.x - lock.x; //プレイヤーとスクロールの差を代入
		if (scrollCenter->pos.x < lock.x) scroll_dx = scrollCenter->pos.x - lock.x; //
		nx += scroll_dx;
	
		if (scrollCenter->pos.y > SCROLL_D)scroll_dy = scrollCenter->pos.y - SCROLL_D; //プレイヤーとスクロールの差を代入
		if (scrollCenter->pos.y < SCROLL_U)scroll_dy = scrollCenter->pos.y - SCROLL_U; //
		scrollY += scroll_dy;
		break;
	}



	// スクロール範囲のチェック
	if (nx < limitL) nx = limitL;
	if (nx > limitR) nx = limitR;
	if (scrollY > limitD) scrollY = limitD;
	if (scrollY < limitU) scrollY = limitU;

	//// スクロール補正
	float scroll_rx = nx - old_x;
	float scroll_ry = scrollY - old_y;
	if (scroll_rx != 0) {
		if (scroll_rx < 0) {///左スクロール 
			spd.x += -MAP_ACT;	//速度増加
			if (spd.x < -MAP_SPEED_MAX)spd.x = -MAP_SPEED_MAX;//最高速チェック
			if (scroll_rx > spd.x) {//
				spd.x = scroll_rx;
			}
			else scroll_rx = spd.x;
		}

		if (scroll_rx > 0) {//右スクロール
			spd.x += MAP_ACT;//速度増加
			if (spd.x > MAP_SPEED_MAX)spd.x = MAP_SPEED_MAX;
			if (scroll_rx < spd.x) {
				spd.x = scroll_rx;
			}
			else scroll_rx = spd.x;
		}
	} else {
		spd.x = 0;
	}
	//scroll_rx = spd.x;
	effect_shifted_objects = V2(0, 0);
	effect_shifted_all = V2(0, 0);

	Player* p = pPlayer;
	p->pos.x -= scroll_rx;
	p->pos.y -= scroll_ry;


	//pFrame->pos.x -= scroll_rx;
	//pFrame->pos.y -= scroll_ry;

	Enemy_Manager* em = pEnemy_Manager;
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (em->enemy[i]) {
			em->enemy[i]->pos.x -= scroll_rx;
			em->enemy[i]->pos.y -= scroll_ry;
		}
	}
	Effect_Manager* fm = pEffect_Manager;
	for (int i = 0; i < EFF_MAX; i++) {
		if (fm->effect[i]) {
			fm->effect[i]->pos.x -= scroll_rx;
			fm->effect[i]->pos.y -= scroll_ry;
		}
	}

	//LandScape* lp= 
	//pEffect_Manager->effect[i]->pos.x -= scroll_rx;
	//pEffect_Manager->effect[i]->pos.y -= scroll_ry;


	scrollX += scroll_rx;
	// MAP書き込み
	int dataX = (int)scrollX >> 4;// scrollX/32?

	while (scroll_written < dataX) {
		scroll_written++;
		write(scroll_written + SCROLL_WRITE_R);
	}
	while (scroll_written > dataX) {
		scroll_written--;
		write(scroll_written + SCROLL_WRITE_L);
	}
	if (nextscrollCenter) { scrollCenter = nextscrollCenter; nextscrollCenter = NULL; }

	//ミニマップ更新
	minimap.Update();

}

//******************************************************************************
//
//		描画処理
//
//******************************************************************************

// 描画処理
void MAP::Render()
{
	//マップレンダー
	//RenderMapChip();


}
void MAP::MiniMapRender() {
	minimap.Render();
}

inline void MAP::RenderMapChip()
{
	int		dataY = ((int)scrollY) >> 4;			//0 - 16
	float	scrnY = (float)(dataY << 4) - scrollY;	//
	for (; scrnY < SCREEN_HEIGHT; scrnY += 16, dataY++) {	//
		int		dataX = ((int)scrollX) >> 4;	//
		float	scrnX = (float)(dataX << 4) - scrollX;//
		for (; scrnX < SCREEN_WIDTH; scrnX += 16, dataX++) {//
			int	code = vRam[dataY & 0x3f][dataX & 0x3f];
			if (code == 0)continue;

			int tex = ((code & 0xff00) >> 8);
			float u = (float)((code & 0x0f) << 4);
			float v = (float)((code & 0xf0));

			spr_data::obj[tex + spr_data::MAPCHIP1 - 1]->Render((int)scrnX, (int)scrnY, 16, 16, (int)u, (int)v, 16, 16, 0, 0, 0xFFFFFFFF, 0);
		}
	}
}

//******************************************************************************
//******************************************************************************
//
//		各種関数
//
//******************************************************************************
//==============================================================================
//		スクロール書き込み
//==============================================================================

void MAP::write(int dataX)
{
	if (!pData) return;							// データ未設定のとき
	if (dataX < 0) return;						// データ範囲外のとき
	if (dataX >= (pData->mapX << 5)) return;	// データ範囲外のとき

	SCREEN_DATA*	pScr = pData->pScr;
	pScr += pData->pMap[dataX >> 5];			// 111111100000 0000

	int scr_x = (dataX >> 2) & 0x07;			// 000000011100 0000
	int mdl_x = (dataX)& 0x03;					// 000000000011 0000

	int bg_x = dataX & 0x3f;
	int bg_y = 0;

	for (int scr_y = 0; scr_y < 0x08; scr_y++) {
		MODULE_DATA* pMdl = pData->pMdl;
		pMdl += pScr->m[scr_y][scr_x];
		for (int mdl_y = 0; mdl_y < 0x04; mdl_y++) {
			vRam[bg_y][bg_x] = pMdl->code[mdl_y][mdl_x];
			bg_y++;
		}
	}
}

//==============================================================================
//		画面座標からその場所のMAPキャラコードを返す
//==============================================================================

int MAP::getCode(float x, float y)
{
	return getCode((int)(x + scrollX), (int)(y + scrollY));
}

int MAP::getCode(int dataX, int dataY)
{
	return vRam[(dataY >> 4) & 0x3f][(dataX >> 4) & 0x3f];
}

//==============================================================================
//		（x-w）～（x+w）間で地面にめり込んでいるかどうかを返す
//==============================================================================

bool MAP::isFloor(float x, float y, int w)
{
	int dataX = (int)(x + scrollX);
	int dataY = (int)(y + scrollY);
	for (; w > 0; w -= 16) {
		if (isHitDown(dataX - w, dataY)) return true;		// 左側チェック
		if (isHitDown(dataX + w, dataY)) return true;		// 右側チェック
	}
	return isHitDown(dataX, dataY);							// 中央チェック
}

//==============================================================================
//		（x-w）～（x+w）間で天井にめり込んでいるかどうかを返す
//==============================================================================

bool MAP::isCeiling(float x, float y, int w)
{
	int dataX = (int)(x + scrollX);
	int dataY = (int)(y + scrollY);
	for (; w > 0; w -= 16) {
		if (isHitAll(dataX - w, dataY)) return true;		// 左側チェック
		if (isHitAll(dataX + w, dataY)) return true;		// 右側チェック
	}
	return isHitAll(dataX, dataY);							// 中央チェック
}

//==============================================================================
//		（y-height）～（y）間で横方向にめり込んでいるかどうかを返す
//==============================================================================

bool MAP::isWall(float x, float y, int h)
{
	int dataX = (int)(x + scrollX);
	int dataY = (int)(y + scrollY);
	// 上から下へチェック
	for (; h > 0; h -= 16) {
		if (isHitAll(dataX, dataY - h)) return true;
	}
	return isHitAll(dataX, dataY);							// 足下チェック
}

//==============================================================================

bool MAP::isHitAll(int dataX, int dataY)
{
	switch (getCode(dataX, dataY)&BGHIT_MASK) {
	case BGHIT_ALL:			// あたりあり
		return true;
	}
	return false;
}

//==============================================================================

bool MAP::isHitDown(int dataX, int dataY)
{
	switch (getCode(dataX, dataY)&BGHIT_MASK) {
	case BGHIT_ALL:			// あたりあり
	case BGHIT_DOWN:		// 下方向のみあたりあり
		return true;
	}
	return false;
}

//******************************************************************************

void MAP::SetCenter(OBJ2D* obj) {
	nextscrollCenter = obj;
	scroll_state = 0;
}

OBJ2D* MAP::GetCenter() {
	return scrollCenter;
}


// 天井ぎりぎりの場所に設定する
void bg_crt_up(OBJ2D *obj, float h)
{
	float y;
	y = obj->pos.y - h;							// キャラの頭の上の座標
	y += pMAP->getScrollY();						// マップ上の座標に変換
	y = (float)(((int)y) & 0xfff0);				// 天井にめり込んだ分の補正
	y -= pMAP->getScrollY();						// 画面上の座標に戻す
	y += 16;									// BG1キャラ分ずれているので補正
	obj->pos.y = y + h;							// キャラ本来の座標
	if (obj->spd.y < 0) obj->spd.y = 0;		// 地形にあたっているので速度も0にする
}

//==============================================================================

// 地面ぎりぎりの場所に設定する
void bg_crt_down(OBJ2D *obj)
{
	float	y;
	y = obj->pos.y;
	y += pMAP->getScrollY();						// マップ上の座標に変換
	y = (float)(((int)y) & 0xfff0);				// 地面にめり込んだ分の補正
	y -= pMAP->getScrollY();						// 画面上の座標に戻す
	y -= 0.0125f;								// 地面から少し浮かす
	obj->pos.y = y;
	if (obj->spd.y > 0) obj->spd.y = 0;		// 着地状態なので速度も0にする
}

//==============================================================================

// 左側の地形ぎりぎりにする
void bg_crt_left(OBJ2D *obj, float w)
{
	float x;
	x = obj->pos.x - w;							// キャラの左端の座標
	x += pMAP->getScrollX();						// マップ上の座標に変換
	x = (float)(((int)x) & 0xfff0);				// 地面にめり込んだ分の補正
	x -= pMAP->getScrollX();						// 画面上の座標に戻す
	x += 16;									// BG1キャラ分ずれているので補正
	obj->pos.x = x + w;							// キャラ本来の座標
	if (obj->spd.x < 0) obj->spd.x = 0;		// 地形にあたっているので速度も0にする
}

//==============================================================================

// 右側の地形ぎりぎりにする
void bg_crt_right(OBJ2D *obj, float w)
{
	float x;
	x = obj->pos.x + w;							// キャラの右端の座標
	x += pMAP->getScrollX();						// マップ上の座標に変換
	x = (float)(((int)x) & 0xfff0);				// 地面にめり込んだ分の補正
	x -= pMAP->getScrollX();						// 画面上の座標に戻す
	x -= 0.0125f;								// 地形ぎりぎりの場所にする
	obj->pos.x = x - w;							// キャラ本来の座標
	if (obj->spd.x > 0) obj->spd.x = 0;		// 地形にあたっているので速度も0にする
}

//==============================================================================

// 抗力（抵抗）の計算
float get_Resist(int attr, float spd)
{
	float	Resist = 0;				// 抗力（抵抗）

	switch (attr) {
	case BGATT_WATER:				// 水中のとき
		Resist = -spd / 4;		// 水中の抵抗（速度の関数）
		break;
	}
	return Resist;
}

//==============================================================================


//==============================================================================
//		centerLock を有効化
//==============================================================================

void MAP::Change_centerLock(OBJ2D* obj) {
	if (obj != scrollCenter) return;
	if (scroll_state == center_lock) {
		scroll_state = normal;
		return;
	}
	scroll_state = center_lock;
	lock = obj->pos;

}