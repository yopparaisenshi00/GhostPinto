#include "iextreme.h"
#include "system/System.h"
#include "Misc/Misc.h"
#include "Player/Frame.h"
#include "Enemy/Enemy.h"
#include "Map/BGFG.h"
#include "Scene/stage_data.h"


//時間による出現データ
STAGE_DATA stage1_time[] = {
	//WAVE1(初期配置) 19匹
	//         出現     関数		座標			速度			加速度    最大速度		Z値
	STAGE_DATA(0,		Rotation,	V2(1570,582),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
//	STAGE_DATA(0,		Rotation,	V2(1570,432),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(1620,512),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(1520,512),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(0,		Rotation,	V2(600, 452),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(700, 452),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(650, 372),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
//	STAGE_DATA(0,		Rotation,	V2(650, 522),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),

//	STAGE_DATA(0,		Rotation,	V2(1320,832),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(1220,832),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(1270,912),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(1270,752),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(0,		Rotation,	V2(400, 832),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(500, 832),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(450, 752),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Rotation,	V2(450, 912),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(0,		Normal	,	V2(200, 912),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Normal	,	V2(280, 832),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Normal	,	V2(660, 700),	V2(0.8f, 0.8f), V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(0,		Normal	,	V2(1260, 700),	V2(0.8f, 0.8f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Normal	,	V2(1600,912),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(0,		Normal	,	V2(1700,832),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),


	//WAVE2 10匹
	//         出現     関数		座標			速度			加速度    最大速度		Z値
	STAGE_DATA(900,		Normal	,	V2(700, 452),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(900,		Normal	,	V2(860, 452),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(900,		Normal	,	V2(1120,452),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(900,		Normal	,	V2(1220,452),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(900,		Tombo,		V2(960, 782),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(900,		Tombo,		V2(960, 512),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(1200,	Teleport,	V2(1500,452),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(1200,	Teleport,	V2(1600,452),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(1200,	Teleport,	V2(1550,372),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(1200,	Teleport,	V2(1550,532),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),

	//末端データ
	STAGE_DATA(10000,	nullptr,	V2(600, 250),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
};


//キル数による出現データ
STAGE_DATA stage1_kill[] = {
	//全21匹(旧)
	//         出現     関数		座標			速度			加速度    最大速度		Z値

	STAGE_DATA(15,		zMove,		V2(660, 512),	V2(1.0f, 1.0f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(15,		zMove,		V2(660, 762),	V2(1.0f, 1.0f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(15,		zMove,		V2(1260,512),	V2(1.0f, 1.0f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(15,		zMove,		V2(1260,762),	V2(1.0f, 1.0f), V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(20,		Tombo,		V2(700, 452),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(20,		Tombo,		V2(800, 452),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(20,		Tombo,		V2(1120,452),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(20,		Tombo,		V2(1220,452),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(30,		Big,		V2(480, 512),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(30,		Big,		V2(960, 512),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(30,		Big,		V2(1440,512),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(30,		Normal,		V2(600, 452),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(30,		Normal,		V2(700, 372),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(30,		Normal,		V2(1200,912),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(30,		Normal,		V2(1300,832),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(35,		zMove,		V2(1260,762),	V2(1.0f, 1.0f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(35,		zMove,		V2(660, 762),	V2(1.0f, 1.0f), V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(35,		Tombo,		V2(200, 352),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(35,		Tombo,		V2(500, 352),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(35,		Tombo,		V2(1720,352),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(35,		Tombo,		V2(1420,352),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),

	//10(追加)

	STAGE_DATA(45,		Tombo,		V2(800, 452),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(45,		Tombo,		V2(1220,452),	V2(0.3f, 0.3f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(45,		Big,		V2(680, 512),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(45,		Big,		V2(1040,512),	V2(0.7f, 0.7f), V2(0,-1), V2(0,-2),	rand_PINTO),

	STAGE_DATA(50,		zMove,		V2(1360,762),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(50,		zMove,		V2(560, 762),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(50,		zMove,		V2(1160,662),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(50,		zMove,		V2(760, 662),	V2(1.5f, 1.5f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(50,		Normal,		V2(800, 622),	V2(2.0f, 2.0f), V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(50,		Normal,		V2(1200, 622),	V2(2.0f, 2.0f), V2(0,-1), V2(0,-2),	rand_PINTO),

	//末端データ
	STAGE_DATA(-1,		nullptr,	V2(600, 250),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
	STAGE_DATA(-1,		nullptr,	V2(600, 250),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
};

LAND_SCAPE_DATA stage1_bg_effect[] = {

	{ LSD::BOT	 ,0,BG_Capsule_l,V2(200,1024),V2(0,0),V2(0,0),V2(0,0),10 },
	{ LSD::BOT	 ,0,BG_Display_a,V2(128,900),V2(0,0),V2(0,0),V2(0,0),0 },

	{ LSD::BOT	 ,0,BG_Capsule_d,V2(400,1024),V2(0,0),V2(0,0),V2(0,0),10 },
	{ LSD::BOT	 ,0,BG_Display_b,V2(464,800),V2(0,0),V2(0,0),V2(0,0),0 },

	{ LSD::BOT	 ,0,BG_Capsule_l,V2(600,1024),V2(0,0),V2(0,0),V2(0,0),10 },
	{ LSD::BOT	 ,0,BG_Display_c,V2(664,900),V2(0,0),V2(0,0),V2(0,0),0 },

	{ LSD::BOT	 ,0,BG_Mini_capsule_l,V2(1000,1024),V2(0,0),V2(0,0),V2(0,0),10 },

	{ LSD::BOT	 ,0,BG_Mini_capsule_d,V2(1160,1024),V2(0,0),V2(0,0),V2(0,0),10 },

	{ LSD::BOT	 ,0,BG_Break_capsule_u,V2(1360,1024),V2(0,0),V2(0,0),V2(0,0),10 },
	{ LSD::BOT	 ,0,BG_Display_b,V2(1300,800),V2(0,0),V2(0,0),V2(0,0),0 },

	{ LSD::BOT	 ,0,BG_container,V2(1850,1024),V2(0,0),V2(0,0),V2(0,0), 0 },
	{ LSD::BOT	 ,0,BG_pc,V2(770,1024),V2(0,0),V2(0,0),V2(0,0), 0 },


	{ LSD::CENTER,0,BG_Fly_mini_capsule_l,V2(200,412),V2(0,0),V2(0,0),V2(0,0),20 },

	{ LSD::CENTER,0,BG_Fly_mini_capsule_d,V2(500,612),V2(0,0),V2(0,0),V2(0,0),20 },

	{ LSD::CENTER,0,BG_Fly_mini_capsule_m,V2(800,412),V2(0,0),V2(0,0),V2(0,0),20 },

	{ LSD::CENTER,0,BG_Fly_mini_capsule_d,V2(1500,512),V2(0,0),V2(0,0),V2(0,0),20 },

	{ LSD::CENTER,0,BG_Fly_mini_capsule_d,V2(1800,612),V2(0,0),V2(0,0),V2(0,0),20 },



	{ LSD::BOT	 ,0,BG_Capsule_l,V2(1200,1024),V2(0,0),V2(0,0),V2(0,0),40 },
	{ LSD::BOT	 ,0,BG_Display_a,V2(1128,700),V2(0,0),V2(0,0),V2(0,0),40 },

	{ LSD::BOT	 ,0,BG_Capsule_d,V2(1500,1024),V2(0,0),V2(0,0),V2(0,0),40 },
	{ LSD::BOT	 ,0,BG_Display_d,V2(1628,740),V2(0,0),V2(0,0),V2(0,0),40 },

	{ LSD::BOT	 ,0,BG_Capsule_l,V2(1800,1024),V2(0,0),V2(0,0),V2(0,0),40 },
	{ LSD::BOT	 ,0,BG_Display_c,V2(1920,700),V2(0,0),V2(0,0),V2(0,0),40 },

	{ LSD::BOT	 ,0,BG_Mini_capsule_d,V2(260,1024),V2(0,0),V2(0,0),V2(0,0),40 },
	{ LSD::BOT	 ,0,BG_Mini_capsule_d,V2(560,1024),V2(0,0),V2(0,0),V2(0,0),40 },

	{ LSD::BOT	 ,0,BG_Fly_capsule_m,V2(2050,400),V2(0,0),V2(0,0),V2(0,0),40 },
	{ LSD::BOT	 ,0,BG_Display_b,V2(2000,400),V2(0,0),V2(0,0),V2(0,0),40 },

	{ LSD::BOT	 ,0,BG_pc,V2(1400,1024),V2(0,0),V2(0,0),V2(0,0), 40 },


	{ LSD::CENTER,0,BG_Fly_capsule_d,V2(0,612),V2(0,0),V2(0,0),V2(0,0),60 },
	{ LSD::CENTER,0,BG_Fly_capsule_l,V2(400,612),V2(0,0),V2(0,0),V2(0,0),60 },
	{ LSD::CENTER,0,BG_Fly_capsule_d,V2(800,612),V2(0,0),V2(0,0),V2(0,0),60 },
	{ LSD::CENTER,0,BG_Fly_capsule_l,V2(1200,612),V2(0,0),V2(0,0),V2(0,0),60 },
	{ LSD::CENTER,0,BG_Fly_capsule_d,V2(1600,612),V2(0,0),V2(0,0),V2(0,0),60 },
	{ LSD::CENTER,0,BG_Fly_capsule_d,V2(2000,612),V2(0,0),V2(0,0),V2(0,0),60 },

	{ LSD::CENTER,0,BG_Fly_capsule_l,V2(1800,352),V2(0,0),V2(0,0),V2(0,0),-60 },
	{ LSD::CENTER,0,BG_Fly_capsule_l,V2(1200,312),V2(0,0),V2(0,0),V2(0,0),-60 },
	{ LSD::CENTER,0,BG_Fly_capsule_d,V2(500,212),V2(0,0),V2(0,0),V2(0,0),-60 },


	{ 0,-1,nullptr, V2(0,0), V2(0, 0), V2(0, -1), V2(0, -2), 0 },
};
