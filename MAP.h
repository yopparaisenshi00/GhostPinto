#include "MiniMap.h"
#ifndef _BG_H_
#define	_BG_H_

//******************************************************************************
//
//
//		MAPクラス
//
//
//******************************************************************************

// 地形あたりデータ
#define	BGHIT_NONE			0x00000000			// あたりなし
#define	BGHIT_ALL			0x01000000			// あたりあり
#define BGHIT_DOWN			0x02000000			// 上→下のみあたりあり

#define BGHIT_MASK			0x0f000000

// 地形属性データ
#define	BGATT_NORMAL		0x00000000			// 通常（地面、空中）
#define	BGATT_ICE			0x10000000			// 氷
#define	BGATT_WATER			0x20000000			// 水中
#define BGATT_LEFT			0x30000000			// ベルトコンベア（左）
#define	BGATT_RIGHT			0x40000000			// ベルトコンベア（右）

#define BGATT_MASK			0xf0000000

//#define MAP_ACT (3.0f)
#define MAP_ACT (MAP_SPEED_MAX)
#define MAP_SPEED_MAX (PLAYER_SPDX_MAX + 12.0f)


// モジュールデータ
struct MODULE_DATA
{
	int	code[4][4];
};

// スクリーンデータ
struct SCREEN_DATA
{
	int	m[8][8];
};

// MAPデータ
struct BG_DATA
{
	MODULE_DATA*	pMdl;
	SCREEN_DATA*	pScr;
	int*			pMap;
	int				mapX;			// 横画面数
};

//==============================================================================
class MiniMap;
// MAPクラス
class MAP :public Singleton<MAP>
{
private:
//public:
	OBJ2D*		scrollCenter;		// スクロール基準
	OBJ2D*		nextscrollCenter;		// スクロール基準
	MiniMap		minimap;
	BG_DATA*	pData;				// MAPデータへのポインタ
	float		limitR, limitL;		// スクロール制限
	float		limitD, limitU;		// スクロール制限

	int			vRam[64][64];		// 背景描画用仮想RAM
	float		scrollX, scrollY;	// 背景表示位置
	int			scroll_written;		// 


	//******************************************************************************************
	//
	//	エフェクト変数
	//
	//******************************************************************************************
	enum {
		None = 0,
		ShakeObj = 1,
		ShakeAll = 2,
	};
	int	Shake_state;
	int Shake_Size_Min;
	int Shake_Size_Max;


	V2 effect_shifted_objects;
	V2 effect_shifted_all;

	int Shake_timer;
	
	//******************************************************************************************


	bool		scroll_state;		//スクロールの状態設定

public:
	MAP();
	void SetCenter(OBJ2D* obj);
	OBJ2D* GetCenter();
	void Change_centerLock(OBJ2D* obj);

	V2 spd;
	V2 lock;


		
	void init(BG_DATA* p);
	void clear();
	void update();
	void Render();
	inline void MAP::RenderMapChip();

	void MiniMapRender();

	//******************************************************************************************
	//
	//	エフェクト発生、更新
	//	
	//******************************************************************************************



	//******************************************************************************************
	//
	//	情報呼び出し
	//
	//******************************************************************************************
	float getScrollX() { return scrollX; }
	float getScrollY() { return scrollY; }

	int getCode(float x, float y);
	int getHit(float x, float y) { return getCode(x, y) & BGHIT_MASK; }
	int getAttr(float x, float y) { return getCode(x, y) & BGATT_MASK; }

	int getCode(int dataX, int dataY);
	//******************************************************************************************
	//
	//	マップとのあたり判定
	//
	//******************************************************************************************
	bool isFloor(float x, float y, int w);
	bool isCeiling(float x, float y, int w);
	bool isWall(float x, float y, int h);

	bool isFloor(float x, float y, float w) { return isFloor(x, y, (int)w); }
	bool isCeiling(float x, float y, float w) { return isCeiling(x, y, (int)w); }
	bool isWall(float x, float y, float h) { return isWall(x, y, (int)h); }

private:
	bool isHitAll(int dataX, int dataY);
	bool isHitDown(int dataX, int dataY);

	void write(int dataX);

};

void bg_crt_up(OBJ2D *obj, float h);
void bg_crt_down(OBJ2D *obj);
void bg_crt_left(OBJ2D *obj, float w);
void bg_crt_right(OBJ2D *obj, float w);
float get_Resist(int attr, float spd);


#define pMAP			(MAP::getInstance())
#define SCROLL_X	(pBG->getScrollX())
#define SCROLL_Y	(pBG->getScrollY())

//******************************************************************************
#endif // !_BG_H_
