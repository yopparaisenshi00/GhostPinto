#include "iextreme.h"
#include "system\System.h"
#include "Game.h"
#include "Frame.h"
#include "Enemy.h"
#include "BGFG.h"
#include "stage_data.h"


//���Ԃɂ��o���f�[�^
STAGE_DATA tutorial_time[] = {
	//         �o��     �֐�		���W			���x			�����x    �ő呬�x		Z�l
	//���[�f�[�^
	STAGE_DATA(10000,	nullptr,	V2(600, 250),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
};


//�L�����ɂ��o���f�[�^
STAGE_DATA tutorial_kill[] = {
	//         �o��     �֐�		���W			���x			�����x    �ő呬�x		Z�l
	STAGE_DATA(-1,		nullptr,	V2(600, 250),	V2(0, 0),		V2(0,-1), V2(0,-2),	rand_PINTO),
};

LAND_SCAPE_DATA tutorial_bg_effect[] = {

	{ LSD::BOT	 ,0,BG_Mini_capsule_l,V2(1000,1024),V2(0,0),V2(0,0),V2(0,0),0 },

	{ 0,-1,nullptr, V2(0,0), V2(0, 0), V2(0, -1), V2(0, -2), 0 },
};

