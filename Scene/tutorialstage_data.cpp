#include "iextreme.h"
#include "system\System.h"
#include "Misc/Misc.h"
#include "Player/Frame.h"
#include "Enemy/Enemy.h"
#include "Map/BGFG.h"
#include "Scene/stage_data.h"


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

	//{ LSD::BOT	,0,BG_Fly_capsule_l_break,V2(200,200),V2(0,0),V2(0,0),V2(0,0),0 },

	{ 0,-1,nullptr, V2(0,0), V2(0, 0), V2(0, -1), V2(0, -2), 0 },
};

