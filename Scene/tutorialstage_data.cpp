#include "iextreme.h"
#include "system\System.h"
#include "Misc/Misc.h"
#include "Player/Frame.h"
#include "Enemy/Enemy.h"
#include "Map/BGFG.h"
#include "Scene/stage_data.h"


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

	//{ LSD::BOT	,0,BG_Fly_capsule_l_break,V2(200,200),V2(0,0),V2(0,0),V2(0,0),0 },

	{ 0,-1,nullptr, V2(0,0), V2(0, 0), V2(0, -1), V2(0, -2), 0 },
};

