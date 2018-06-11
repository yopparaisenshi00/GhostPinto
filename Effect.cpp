
#include "iextreme.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "MAP.h"
#include "Effect.h"


//������Ȃ��f��
static SPR_DATA Frame_data = SPR_DATA{ spr_data::UI1,0,0,240,160,-120,-80, };

//������Ȃ��f��
static SPR_DATA anime_Jet_data[] = {
	SPR_DATA{ spr_data::Ext, 64 * 0, 0, 64, 64, -32, -32 },
	SPR_DATA{ spr_data::Ext, 64 * 1, 0, 64, 64, -32, -32 },
	SPR_DATA{ spr_data::Ext, 64 * 2, 0, 64, 64, -32, -32 },
	SPR_DATA{ spr_data::Ext, 64 * 3, 0, 64, 64, -32, -32 },
	SPR_DATA{ spr_data::Ext, 64 * 4, 0, 64, 64, -32, -32 },
	SPR_DATA{ spr_data::Ext, 64 * 5, 0, 64, 64, -32, -32 },
	SPR_LOOP
};

//�G���ŃG�t�F�N�g�f��
static SPR_DATA anime_circleext_data[] = {
	SPR_DATA{ spr_data::Circle, 128 * 0, 0, 128, 128, -64, -64,0 },
	SPR_DATA{ spr_data::Circle, 128 * 1, 0, 128, 128, -64, -64,1 },
	SPR_DATA{ spr_data::Circle, 128 * 4, 0, 128, 128, -64, -64,2 },
	SPR_DATA{ spr_data::Circle, 128 * 6, 0, 128, 128, -64, -64,3 },
	SPR_LOOP };

//�e���|�[�g�G�t�F�N�g�f��
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


//�W���X�g�s���g�G�t�F�N�g�f��(�s���g�����O�̗��p)
static SPR_DATA justpinto_data = SPR_DATA{ spr_data::UI1,0,0,128,128,-64,-64,0 };

//��s�G�t�F�N�g�f��(���ŃG�t�F�N�g�̗��p)
static SPR_DATA jet_data = SPR_DATA{ spr_data::Circle, 128 * 0, 0, 128, 128, -64, -64,0 };


////�v���C���[����G�t�F�N�g
//static SPR_DATA p_eff_data[] = {
//	SPR_DATA{ spr_data::Player_eff, 128, 0 * 6,	 6,	6, -6 / 2,-6 / 2,0 }, //p_eff1
//	SPR_DATA{ spr_data::Player_eff, 128, 1 * 6,	 6,	6, -6 / 2,-6 / 2,1 }, //p_eff2
//	SPR_DATA{ spr_data::Player_eff, 128, 2 * 6,	 6,	6, -6 / 2,-6 / 2,2 }, //p_eff3
//	SPR_DATA{ spr_data::Player_eff, 128, 3 * 6,	 6,	6, -6 / 2,-6 / 2,3 }, //p_eff4
//	SPR_DATA{ spr_data::Player_eff, 128, 4 * 6,	 9, 9, -9 / 2,-9 / 2,4 }, //p_eff1*1.5
//	SPR_DATA{ spr_data::Player_eff, 128, 4 * 6 + 1 * 9, 9, 9, -9 / 2,-9 / 2,5 }, //p_eff2*1.5
//	SPR_DATA{ spr_data::Player_eff, 128, 4 * 6 + 2 * 9, 9, 9, -9 / 2,-9 / 2,6 }, //p_eff3*1.5
//	SPR_DATA{ spr_data::Player_eff, 128, 4 * 6 + 3 * 9, 9, 9, -9 / 2,-9 / 2,7 }, //p_eff4*1.5
//	SPR_LOOP
//};

//�v���C���[����G�t�F�N�g
static SPR_DATA p_eff_data[] = {
	SPR_DATA{ spr_data::Player_eff, 128, 1 * 6,	 6,	6, -6 / 2,-6 / 2,1 }, //p_eff2
	SPR_DATA{ spr_data::Player_eff, 128, 4 * 6 + 1 * 9, 9, 9, -9 / 2,-9 / 2,2 }, //p_eff2*1.5
	SPR_LOOP
};

//�G���ŃG�t�F�N�g�f��
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

//�G���ŃG�t�F�N�g(��)
static SPR_DATA EdgeCircle_ext_data = SPR_DATA{ spr_data::EdgeCircle,0,0,128,128,-64,-64,0 };

//�G���ŃG�t�F�N�g(��)
static SPR_DATA Circle_ext_data = SPR_DATA{ spr_data::Player_eff,0,0,128,128,-64,-64,0 };

//�G���ŃG�t�F�N�g(�L���L��)
static SPR_DATA kirakira_ext_data = SPR_DATA{ spr_data::Player_eff,320,56,24,24,-12,-12,0 };

//�s���g���b�N���G�t�F�N�g(Lock)
static SPR_DATA Lock_data = SPR_DATA{ spr_data::UI6,0,310,100,50,-50,-25 };

//�R���{
SPR_DATA combo_number[10] = {
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



//�v���C���[����G�t�F�N�g

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
	animation();
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

	for (int i = 0; i < EFF_MAX; i++) {
		if (!effect[i])continue;
		effect[i]->clear();
	}

	shift_objects_trg = false;
	shift_all_trg = false;

}
void Effect_Manager::Update() {

	shift_objects = V2(0, 0);
	shift_all = V2(0, 0);

	for (int i = 0; i < EFF_MAX; i++) {
		if (effect[i] && effect[i]->move) {
			effect[i]->move(effect[i]);
			effect[i]->Update();
		}
	}
	pD_TEXT->set_Text(V2(600, 264), "ef_trg_t", shift_objects_trg == true, 0xFFFFFFFF);
	pD_TEXT->set_Text(V2(600, 280), "ef_trg_f", shift_objects_trg == false, 0xFFFFFFFF);
	pD_TEXT->set_Text(V2(600, 296), "ef_trg_02", shift_objects_trg == 0x02, 0xFFFFFFFF);
	pD_TEXT->set_Text(V2(600, 312), "ef_trg_01", shift_objects_trg == 0x01, 0xFFFFFFFF);
	
	if ((shift_objects_trg == true) || (shift_all_trg == true)) {

		Player* p = pPlayer;
		p->custom.ef_ofsX = shift_objects.x;
		p->custom.ef_ofsY = shift_objects.y;
		
		Enemy** e = pEnemy_Manager->enemy;

		for (int i = 0; i < ENEMY_MAX; i++) {
			if (!e[i])continue;
			e[i]->custom.ef_ofsX = shift_objects.x;
			e[i]->custom.ef_ofsY = shift_objects.y;
		}

		Effect** f = pEffect_Manager->effect;
		for (int i = 0; i < EFF_MAX; i++) {
			if (!f[i])continue;
			f[i]->custom.ef_ofsX += shift_objects.x;
			f[i]->custom.ef_ofsY += shift_objects.y;
		}


	}
	if ((shift_all_trg == true)) {
						
	}

	if ((shift_objects_trg == 0x02) || (shift_all_trg == 0x02)) {
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

	}

	if ((shift_all_trg == 0x10)) {


	}

	pD_TEXT->set_Text(V2(600, 312 + 24), "shift_obj_x", shift_objects.x, 0xFFFFFFFF);
	pD_TEXT->set_Text(V2(600, 312 + 40), "shift_obj_y", shift_objects.y, 0xFFFFFFFF);
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

//�t���[����]
void framerotate(Effect *obj)
{
	switch (obj->state)
	{
	case 0:
		obj->data = &Frame_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 1;
		obj->custom.angle = 0;
		obj->state++;
	case 1:
		obj->custom.scaleX = obj->custom.scaleY -= 0.05f;
		obj->custom.angle -= 15;
		if (obj->custom.scaleX<0) obj->state = 2;
		break;
	case 2:
		obj->clear();
		break;
	default:
		break;
	}
}


//�G���Ŏ��G�t�F�N�g
void Extinction(Effect *obj)
{
	switch (obj->state)
	{
	case 0:
		//obj->data = &Ext_data;
		obj->animeData = anime_Jet_data;
		obj->data = &obj->animeData[0];
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.7f;
		obj->i_work[0] = (int)obj->pos.y;
		obj->timer = 0;
		obj->alpha = 255;
		obj->state++;
	case 1:
		obj->pos -= obj->spd;
		if ( /*(obj->i_work[0]-100)>obj->pos.y ||*/ obj->timer++>50) {
			if (obj->alpha>25) obj->alpha -= 25; //��������
			else {
				obj->alpha = 0;
				obj->state = 2; //�����ɂȂ��������������
			}
		}
		break;
	case 2:
		obj->clear();
		break;
	default:
		break;
	}
}


//��s�G�t�F�N�g
void kemuri(Effect *obj)
{
	switch (obj->state)
	{
	case 0:
		//obj->data = &Ext_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.7f;
		obj->timer = 0;
		obj->alpha = (int)(255 * 0.7f);
		obj->state++;
	case 1:
		obj->pos += obj->spd;
		obj->custom.scaleX = obj->custom.scaleY -= 0.02f;
		if (obj->custom.scaleX<0) {
			obj->state = 2;
		}
		if (obj->timer++>10) {
			//if ( obj->alpha>25 ) obj->alpha-=50; //��������
			//else {
			//	obj->alpha = 0;
			//	obj->state = 2; //�����ɂȂ��������������
			//}
		}
		break;
	case 2:
		obj->clear();
		break;
	default:
		break;
	}
}


////���ŃG�t�F�N�g
//void CircleExt(Effect *obj)
//{
//	switch (obj->state)
//	{
//	case 0:
//		obj->animeData = anime_ext_data;
//		obj->data = &obj->animeData[0];
//		obj->custom.scaleMode = CENTER;
//		obj->custom.scaleX = obj->custom.scaleY = 1.1f;
//		obj->timer = 0;
//		obj->alpha = (int)(255 * 0.7f);
//		obj->state++;
//		//break;
//	case 1:
//		//if ( obj->timer++>12 ) {
//		//	obj->state = 2; //����������
//		//}
//		if (obj->timer++>7) {
//			obj->state = 2; //����������
//		}
//
//		//if ( obj->data->no < 0 ) {	//�A�j���[�V�������Ō�Ȃ�
//		//	obj->state = 2;			//����������
//		//}
//		//if ( obj->data->frameNum>4 ) {	//frameNum��4�ȏ�Ȃ�
//		//	obj->state = 2;				//����������
//		//}
//		break;
//	case 2:
//		obj->clear();
//		break;
//	default:
//		break;
//	}
//}

//******************************************************************************
//�G���ŃG�t�F�N�g
void Ext(Effect *obj)
{
	switch (obj->state)
	{
	case 0:
		obj->animeData = anime_ext_data;
		obj->data = &obj->animeData[0];
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 2.0f;
		obj->timer = 0;
		obj->state++;
		//break;
	case 1:
		if (obj->timer++>30) {
			obj->state = 2; //����������
			obj->timer = 0;
		}
		break;
	case 2:
		obj->clear();
		break;
	default:
		break;
	}
}

//�G���ŃG�t�F�N�g(��)
void CircleExt1(Effect *obj) {
	switch (obj->state)
	{
	case 0:
		obj->data = &EdgeCircle_ext_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.5f;
		obj->custom.argb = 0xFF7ce2ef; //���F
		obj->alpha = (int)(255 * 0.8f);
		obj->state++;
		//break;
	case 1:
		obj->custom.scaleX = obj->custom.scaleY += 0.2f;	//�g�又��
		if (obj->custom.scaleX>1.7f) {	//���̑傫���ɂȂ�����
			obj->state = 2;				//����������
		}
		break;
	case 2:
		obj->clear();
		break;
	default:
		break;
	}

}

//�G���ŃG�t�F�N�g(��)
void CircleExt2(Effect *obj) {
	switch (obj->state)
	{
	case 0:
		obj->data = &EdgeCircle_ext_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.7f;
		obj->custom.argb = 0xFF7ce2ef; //���F
		obj->alpha = 0; //����
		obj->timer = 0;
		obj->state++;
		//break;
	case 1:
		if (obj->timer++>2) { //�w��b���o������
			obj->alpha = (int)(255 * 0.8f); //�����
			obj->custom.scaleX = obj->custom.scaleY += 0.2f;	//�g�又��
			if (obj->custom.scaleX>2.0f) {	//���̑傫���ɂȂ�����
				obj->state = 2;				//����������
				obj->timer = 0;
			}
		}
		break;
	case 2:
		obj->clear();
		break;
	default:
		break;
	}

}

//�G���ŃG�t�F�N�g(�U��΂遜)
void ParticleExt_c(Effect* obj) {
	switch (obj->state) {
	case 0:
		obj->data = &Circle_ext_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.1f;
		obj->custom.argb = 0xFFFFFFFF;
		obj->timer = 0;
		obj->alpha = 0;
		obj->i_work[6] = 0;
		obj->state++;
		//break;
	case 1:
		obj->alpha = (int)(255);
		//obj->custom.scaleX = obj->custom.scaleY =(float)(rand()%30)/10.0f+1.0f;	//�傫���ύX(1.0�`2.0�{)
		obj->custom.scaleX = obj->custom.scaleY = (float)(rand() % 10) / 15.0f;	//�傫���ύX(0.1�`1.0�{)
		obj->i_work[6] = rand() % 4;
		if (obj->i_work[6] == 0) obj->custom.argb = 0xFFD68D8D;	//�ԐF
		if (obj->i_work[6] == 1) obj->custom.argb = 0xFF86ace8;	//�F
		if (obj->i_work[6] == 2) obj->custom.argb = 0xFFE2E268;	//���F
		if (obj->i_work[6] == 3) obj->custom.argb = 0xFFc577ef;	//���F
		if (obj->i_work[6] == 4) obj->custom.argb = 0xFFa2f783;	//�ΐF
		obj->pos.x += obj->spd.x; //�U��΂鏈��
		obj->pos.y += obj->spd.y; //�U��΂鏈��

		if (obj->timer++>20) {	//�w�莞�Ԍo������
			obj->state = 2;		//����������
		}
		break;
	case 2:
		obj->clear();
		break;
	default:
		break;
	}
}

//�G���ŃG�t�F�N�g(�U��΂�L���L��)
void ParticleExt_k(Effect* obj) {
	switch (obj->state) {
	case 0:
		obj->data = &kirakira_ext_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.1f;
		obj->custom.argb = 0xFFFFFFFF;
		obj->timer = 0;
		obj->alpha = 0;
		obj->i_work[6] = 0;
		obj->state++;
		//break;
	case 1:
		obj->alpha = (int)(255);
		//obj->custom.scaleX = obj->custom.scaleY =(float)(rand()%10)/10.0f+1.0f;	//�傫���ύX(1.0�`2.0�{)
		obj->custom.scaleX = obj->custom.scaleY = (float)(rand() % 10) / 5.0f;	//�傫���ύX(0.5�`2.0�{)
		obj->i_work[6] = rand() % 4;
		if (obj->i_work[6] == 0) obj->custom.argb = 0xFFD68D8D;	//�ԐF
		if (obj->i_work[6] == 1) obj->custom.argb = 0xFF86ace8;	//�F
		if (obj->i_work[6] == 2) obj->custom.argb = 0xFFE2E268;	//���F
		if (obj->i_work[6] == 3) obj->custom.argb = 0xFFc577ef;	//���F
		if (obj->i_work[6] == 4) obj->custom.argb = 0xFFa2f783;	//�ΐF
		obj->pos.x += obj->spd.x; //�U��΂鏈��
		obj->pos.y += obj->spd.y; //�U��΂鏈��

		if (obj->timer++>20) {	//�w�莞�Ԍo������
			obj->state = 2;		//����������
		}
		break;
	case 2:
		obj->clear();
		break;
	default:
		break;
	}
}

//******************************************************************************

//Lock�G�t�F�N�g
void Lock(Effect* obj) {
	switch (obj->state) {
	case 0:
		obj->data = &Lock_data;
		obj->custom.argb = 0xFFFFFFFF;
		obj->custom.scaleMode = CENTER;
		obj->timer = 0;
		obj->alpha = 255;
		obj->i_work[6] = 0;
		obj->state++;
		//break;
	case 1:
		obj->i_work[6] = obj->timer % 5;
		if (obj->i_work[6] <= 1) obj->custom.argb = 0xCCffab05;	//�I�����W�F
		else if (obj->i_work[6] <= 3) obj->custom.argb = 0xCCc577ef;	//���F
		else if (obj->i_work[6] <= 5) obj->custom.argb = 0xFFD68D8D;	//���ԐF

		if (obj->timer++>18) obj->state = 2; //�g���
		break;
	case 2: //�g��
		obj->custom.scaleX = obj->custom.scaleY += 0.7f;
		if (obj->custom.scaleX >= 1.7f) obj->state = 3;
		break;
	case 3: //�k��
		obj->custom.scaleX = obj->custom.scaleY -= 0.2f;
		if (obj->custom.scaleX <= 1.4f) obj->state = 4;
		break;
	case 4: //scaleY�k��
		obj->custom.scaleY -= 0.3f;
		if (obj->custom.scaleY<0.0f) obj->state = 5;
		break;
	case 5:
		obj->clear();
		break;
	default:
		break;
	}
}


//�R���{
void Combo(Effect* obj) {
	switch (obj->state) {
	case 0:
		obj->data = &combo_number[0];
		obj->custom.argb = 0xFFff644c;
		obj->custom.scaleMode = CENTER;
		obj->timer = 0;
		obj->alpha = 255;
		obj->i_work[6] = 0;
		obj->i_work[7] = 0; //�R���{�p
		obj->i_work[8] = obj->pos.y; //���W�ۑ��p
		obj->spd.y -= 8;
		obj->state++;
		//break;
	case 1:
		obj->i_work[7] = obj->spd.x; //�R���{
		obj->data = &combo_number[obj->i_work[7]]; //�R���{�\��

												  //obj->i_work[6] = obj->timer%5;
												  //if (obj->i_work[6]<=1) obj->custom.argb = 0xCCffab05;	//�I�����W�F
												  //else if (obj->i_work[6]<=3) obj->custom.argb = 0xCCc577ef;	//���F
												  //else if (obj->i_work[6]<=5) obj->custom.argb = 0xFFD68D8D;	//���ԐF

												  //obj->pos.y += obj->spd.y;
												  //if ( obj->i_work[8]>=obj->pos.y ) {
												  //	obj->spd.y += 1;
												  //}
												  //else obj->spd.y = 0;
												  //if (obj->i_work[8]-obj->spd.y > obj->pos.y ) obj->state = 2; //�g���



		if (obj->timer++>18) obj->state = 2; //�g���
		break;
	case 2:
		obj->clear();
		break;
	default:
		break;
	}

}

//�e���|�[�g�G�t�F�N�g
void TeleportExt(Effect *obj)
{
	switch (obj->state)
	{
	case 0:
		obj->animeData = anime_tele_data;
		obj->data = &obj->animeData[0];
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.5f;
		obj->alpha = (int)(255 * 0.7f);
		obj->custom.argb = 0xFF6ba5ce;
		obj->timer = 0;
		obj->state++;
	case 1:
		if (obj->timer++>16) {
			obj->state = 2; //����������
		}
		//if ( obj->data->texNum < 0 ) { //�A�j���[�V�������Ō�Ȃ�
		//	obj->state = 2;					//����������
		//}
		break;
	case 2:
		obj->clear();
		break;
	default:
		break;
	}
}


//�W���X�g�s���g�G�t�F�N�g(�Ռ��g)
void Just_pinto(Effect *obj)
{
	switch (obj->state)
	{
	case 0:
		//obj->animeData = anime_ext_data;
		obj->data = &justpinto_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 1.0f;
		obj->custom.argb = 0xDDff9393; //�ԐF
		obj->timer = 0;
		obj->alpha = (int)(255 * 0.8f);
		obj->state++;
		//break;
	case 1:
		obj->alpha -= 6;					//��������
		if (obj->alpha<0) obj->alpha = 0;	//
		obj->custom.scaleX = obj->custom.scaleY += 0.17f;	//�g�又��
		if (obj->custom.scaleX>3.0f) {	//���̑傫���ɂȂ�����
			obj->state = 2;					//����������
		}
		break;
	case 2:
		obj->clear();
		break;
	default:
		break;
	}
}


//�s���g���b�N(�Ռ��g)
void pinto_lock(Effect *obj)
{
	switch (obj->state)
	{
	case 0:
		//obj->animeData = anime_ext_data;
		obj->data = &justpinto_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 3.0f;
		obj->custom.argb = 0xDDCFCFCF; //�ԐF
		obj->timer = 0;
		obj->alpha = (int)(255 * 0.8f);
		obj->state++;
		//break;
	case 1:
		obj->alpha -= 6;					//��������
		if (obj->alpha<0) obj->alpha = 0;	//
		obj->custom.scaleX = obj->custom.scaleY -= 0.17f;	//�g�又��
		if (obj->custom.scaleX<0.5f) {	//���̑傫���ɂȂ�����
			obj->state = 2;					//����������
		}
		break;
	case 2:
		obj->clear();
		break;
	default:
		break;
	}
}


//�W�F�b�g�G�t�F�N�g
void Jet(Effect *obj) {
	switch (obj->state) {
	case 0:
		//obj->animeData = anime_ext_data;
		obj->data = &jet_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.4f;
		obj->custom.argb = 0xFFFFFFFF;
		obj->timer = 0;
		obj->alpha = (int)(255 * 0.7f);
		obj->state++;
		//break;
	case 1:
		obj->custom.scaleX = obj->custom.scaleY -= 0.01f;							//�k������
		if (obj->custom.scaleX<0) obj->custom.scaleX = obj->custom.scaleY = 0;	//
		obj->alpha -= 8;						//��������
		if (obj->alpha<0) obj->alpha = 0;		//
		obj->pos.y += 2;

		if (obj->timer++>12) { //�w�莞�Ԍo������
			obj->state = 2; //����������
		}
		break;
	case 2:
		obj->clear();
		//pEffect_Manager->searchSet(V2(pPlayer->pos.x, pPlayer->pos.y+40), V2(0, 0), Jet);
		break;
	default:
		break;
	}
}


//�v���C���[����G�t�F�N�g
void P_particle(Effect* obj) {
	switch (obj->state) {
	case 0:
		obj->animeData = p_eff_data;
		obj->data = &obj->animeData[0];
		//obj->data = &p_eff_data[5];
		obj->custom.argb = 0xFFFFFF55;
		obj->timer = 0;
		obj->alpha = (int)(255 * 0.5f);
		obj->state++;
		//break;
	case 1:
		if (obj->timer>6) {
			obj->alpha -= 32;						//��������
			if (obj->alpha<0) obj->alpha = 0;		//
		}
		obj->pos.y += 0.8f;
		if (obj->timer++>10) { //�w�莞�Ԍo������
			obj->state = 2; //����������
		}
		break;
	case 2:
		obj->clear();
		break;
	default:
		break;
	}
}


//�t�F�[�h�C��
void fade_In(Effect* obj) {
	switch (obj->state) {
	case 0:
		obj->data = &fade_in;
		obj->custom.scaleMode = LEFTTOP;
		obj->timer = 0;
		obj->state++;
		//break;
	case 1:
		obj->pos.x -= 24;

		if (obj->timer++ > 120) { //�w�莞�Ԍo������
			obj->state = 2; //����������
		}
		break;
	case 2:
		obj->clear();
		break;
	default:
		break;
	}

}

//�t�F�[�h�A�E�g
void fade_Out(Effect* obj) {
	switch (obj->state) {
	case 0:
		obj->data = &fade_out;
		obj->custom.scaleMode = LEFTTOP;
		obj->timer = 0;
		obj->state++;
		//break;
	case 1:
		obj->pos.x -= 17;
		if (obj->pos.x < -SCREEN_WIDTH) { //�w�莞�Ԍo������
			obj->state = 2; //���[�v��
			obj->pos.x = -SCREEN_WIDTH;
		}
		break;
	case 2:
		break;

	case 3:
		obj->clear();

		break;
	default:
		break;
	}

}






#define SHAKE_MAX obj->i_work[2]
#define SHAKE_MIN obj->i_work[3]
#define SHAKE_X obj->i_work[7]
#define SHAKE_Y obj->i_work[8]
void Shake(Effect* obj) {
								//Shake_timer = time;
								//Shake_Size_Max = sizeMax;
							//Shake_Size_Min = sizeMin;
	int randxy = rand();

	switch (obj->state)
	{
	case 0:

		obj->timer = obj->spd.x;
		obj->state = obj->spd.y;
		
		SHAKE_MAX = (int)obj->pos.x;
		SHAKE_MIN = (int)obj->pos.y;
		break;
	case 1:
		//SHAKE_Y =  (int)((randxy % (SHAKE_MAX - SHAKE_MIN)) - SHAKE_MIN)/2;
		SHAKE_X = (int)(randxy % (SHAKE_MAX - SHAKE_MIN)) - SHAKE_MIN;
		if (obj->timer-- < 0) {
			obj->timer = 0;
			obj->state = 3;
		}
		pEffect_Manager->add_object(V2(SHAKE_X, SHAKE_Y));

		break;
	case 2:
		SHAKE_X = (randxy % (SHAKE_MAX - SHAKE_MIN)) - SHAKE_MIN;
		//SHAKE_Y = ((randxy % (SHAKE_MAX - SHAKE_MIN)) - SHAKE_MIN)/2;
		if (obj->timer-- < 0) {
			obj->timer = 0;
			obj->state = 3;
		}
		pEffect_Manager->add_all(V2(SHAKE_X, SHAKE_Y));
		break;
	case 3:
		obj->clear();
	default:
		obj->state = 3;
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