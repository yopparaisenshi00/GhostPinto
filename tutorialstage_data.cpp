#include "iextreme.h"
#include "system\System.h"
#include "Game.h"
#include "Frame.h"
#include "Enemy.h"
#include "BGFG.h"
#include "stage_data.h"


//時間による出現データ
STAGE_DATA tutorial_time[] = {
	//         出現     関数		座標			速度			加速度    最大速度		Z値
	//末端データ
	STAGE_DATA(10000,	nullptr,	V2(600, 250),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
};


//キル数による出現データ
STAGE_DATA tutorial_kill[] = {
	//         出現     関数		座標			速度			加速度    最大速度		Z値
	STAGE_DATA(-1,		nullptr,	V2(600, 250),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
};

LAND_SCAPE_DATA tutorial_bg_effect[] = {

	{ LSD::BOT	 ,0,BG_Mini_capsule_l,V2(1000,1024),V2(0,0),V2(0,0),V2(0,0),0 },

	{ 0,-1,nullptr, V2(0,0), V2(0, 0), V2(0, -1), V2(0, -2), 0 },
};

