#include "iextreme.h"
#include "system\System.h"
#include "Game.h"
#include "Frame.h"
#include "Enemy.h"
#include "BGFG.h"
#include "stage_data.h"


//時間による出現データ
STAGE_DATA stage1_time[] = {
	//WAVE1(初期配置) 19匹
	//         出現     関数		座標			速度			加速度    最大速度		Z値
	STAGE_DATA(0,		Rotation,	V2(1620,512),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(1520,512),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(1570,452),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(600, 452),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(700, 452),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(650, 372),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(1320,832),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(1220,832),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(1270,912),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(400, 832),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(500, 832),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(450, 752),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(450, 912),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Normal	,	V2(200, 912),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Normal	,	V2(280, 832),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Normal	,	V2(600, 452),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Normal	,	V2(700, 372),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Normal	,	V2(1200,912),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Normal	,	V2(1300,832),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),


	//WAVE2 10匹
	//         出現     関数		座標			速度			加速度    最大速度		Z値
	STAGE_DATA(900,		Normal	,	V2(700, 452),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(900,		Normal	,	V2(860, 452),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(900,		Normal	,	V2(1120,452),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(900,		Normal	,	V2(1220,452),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(900,		Rotation,	V2(960, 782),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(900,		Rotation,	V2(960, 512),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(1200,	Teleport,	V2(1500,452),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(1200,	Teleport,	V2(1600,452),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(1200,	Teleport,	V2(1550,372),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(1200,	Teleport,	V2(1550,532),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),

	//末端データ
	STAGE_DATA(10000,	nullptr,	V2(600, 250),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
};


//キル数による出現データ
STAGE_DATA stage1_kill[] = {
	//全21匹
	//         出現     関数		座標			速度			加速度    最大速度		Z値
	STAGE_DATA(15,		zMove,		V2(1260,762),	V2(0.5f, 0.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(15,		zMove,		V2(660, 762),	V2(0.5f, 0.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(15,		zMove,		V2(660, 512),	V2(0.5f, 0.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(15,		zMove,		V2(1260,512),	V2(0.5f, 0.5f), V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(20,		Tombo,		V2(700, 452),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(20,		Tombo,		V2(800, 452),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(20,		Tombo,		V2(1120,452),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(20,		Tombo,		V2(1220,452),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(30,		Big,		V2(960, 512),	V2(0.5f, 0.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(30,		Big,		V2(1440,512),	V2(0.5f, 0.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(30,		Big,		V2(480, 512),	V2(0.5f, 0.5f), V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(30,		Normal,		V2(600, 452),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(30,		Normal,		V2(700, 372),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(30,		Normal,		V2(1200,912),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(30,		Normal,		V2(1300,832),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(35,		zMove,		V2(1260,762),	V2(0.5f, 0.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(35,		zMove,		V2(660, 762),	V2(0.5f, 0.5f), V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(35,		Tombo,		V2(200, 352),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(35,		Tombo,		V2(500, 352),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(35,		Tombo,		V2(1720,352),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(35,		Tombo,		V2(1420,352),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),

	//末端データ
	STAGE_DATA(-1,		nullptr,	V2(600, 250),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(-1,		nullptr,	V2(600, 250),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
};

LAND_SCAPE_DATA stage1_bg_effct[] = {
	//{ LSD::CENTER,0,BG_pc,V2(770,1024),V2(0,0),V2(0,0),V2(0,0),0},
	//{ LSD::CENTER,0,BG_pc,V2(770,1024),V2(0,0),V2(0,0),V2(0,0),10},
	//{ LSD::CENTER,0,BG_pc,V2(770,1024),V2(0,0),V2(0,0),V2(0,0),20},
	//{ LSD::CENTER,0,BG_pc,V2(770,1024),V2(0,0),V2(0,0),V2(0,0),30},
	//{ LSD::CENTER,0,BG_pc,V2(770,1024),V2(0,0),V2(0,0),V2(0,0),40},
	//{ LSD::CENTER,0,BG_pc,V2(770,1024),V2(0,0),V2(0,0),V2(0,0),50},
	//{ LSD::CENTER,0,BG_pc,V2(770,1024),V2(0,0),V2(0,0),V2(0,0),60},
	//{ LSD::CENTER,0,BG_pc,V2(770,1024),V2(0,0),V2(0,0),V2(0,0),70},
	//{ LSD::CENTER,0,BG_pc,V2(770,1024),V2(0,0),V2(0,0),V2(0,0),80 },
	//{ LSD::CENTER,0,BG_pc,V2(770,1024),V2(0,0),V2(0,0),V2(0,0),90 },
	{ LSD::BOT	 ,0,BG_Capsule_l,V2(770,1024),V2(0,0),V2(0,0),V2(0,0),0 },
	{ LSD::BOT	 ,0,BG_Capsule_l,V2(770,1024),V2(0,0),V2(0,0),V2(0,0),20 },
	{ LSD::BOT	 ,0,BG_Capsule_l,V2(770,1024),V2(0,0),V2(0,0),V2(0,0),40 },
	{ LSD::BOT	 ,0,BG_Capsule_l,V2(770,1024),V2(0,0),V2(0,0),V2(0,0),60 },
	{ LSD::BOT	 ,0,BG_Capsule_l,V2(770,1024),V2(0,0),V2(0,0),V2(0,0),90 },
	{ LSD::BOT	 ,0,BG_pc,V2(770,1024),V2(0,0),V2(0,0),V2(0,0), 0 },
	{ LSD::BOT	 ,0,BG_pc,V2(700,200),V2(0,0),V2(0,0),V2(0,0), 10 },
	{ LSD::BOT	 ,0,BG_pc,V2(770,400),V2(0,0),V2(0,0),V2(0,0), 90 },
	{ LSD::BOT	 ,0,BG_pc,V2(700,600),V2(0,0),V2(0,0),V2(0,0), 90 },
	{ LSD::BOT	 ,0,BG_pc,V2(770,700),V2(0,0),V2(0,0),V2(0,0), 90 },
	{ LSD::BOT	 ,0,BG_pc,V2(700,800),V2(0,0),V2(0,0),V2(0,0),90 },
	{ LSD::BOT	 ,0,BG_pc,V2(770,900),V2(0,0),V2(0,0),V2(0,0),90 },
	{ LSD::BOT	 ,0,BG_pc,V2(700,1000),V2(0,0),V2(0,0),V2(0,0),90 },
	{ LSD::BOT	 ,0,BG_pc,V2(770,100),V2(0,0),V2(0,0),V2(0,0),90 },
	{ LSD::BOT	 ,0,BG_pc,V2(700,800),V2(0,0),V2(0,0),V2(0,0),90 },

	{0,-1,nullptr, V2(0,0), V2(0, 0), V2(0, -1), V2(0, -2), 0 },
};						  