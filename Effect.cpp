#include "iextreme.h"
#include "Game.h"
#include "Player/Player.h"
#include "Player/Frame.h"
#include "Enemy.h"
#include "MAP.h"
#include "Effect.h"

enum {
	INIT=0,		//�����ݒ�
	MOVE,		//�ړ�����
	MOVE2,		//�ړ�����2
	MOVE3,		//�ړ�����3
	MOVE4,		//�ړ�����4
	CLEAR,		//��������
};

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
	SPR_DATA{ spr_data::Circle, 128 * 0, 0, 128, 128, -64, -64,2 },
	SPR_DATA{ spr_data::Circle, 128 * 1, 0, 128, 128, -64, -64,2 },
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
static SPR_DATA jastpinto_data = SPR_DATA{ spr_data::UI1,0,0,128,128,-64,-64,0 };

//��s�G�t�F�N�g�f��(���ŃG�t�F�N�g�̗��p)
static SPR_DATA jet_data = SPR_DATA{ spr_data::Circle, 128 * 0, 0, 128, 128, -64, -64,0 };

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
static SPR_DATA combo_number[10] = {
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

//�R���{�e�L�X�g
static SPR_DATA combo_text = SPR_DATA{ spr_data::UI6,0,125,120,40,-60,-20  };


//�o�G�t�F�N�g
//static SPR_DATA dust_data = SPR_DATA{ spr_data::Player_eff,128,3*6,6,6,-6/2,-6/2 };
static SPR_DATA dust_data = SPR_DATA{ spr_data::Player_eff,128,51,9,9,0,0 };
static SPR_DATA anime_dust_data[] = {
	SPR_DATA{ spr_data::Player_eff,128,3*6,6,6,-6/2,-6/2,0 },
	SPR_DATA{ spr_data::Player_eff,128,3*6,6,6,-6/2,-6/2,0 },
	SPR_DATA{ spr_data::Player_eff,128,3*6,6,6,-6/2,-6/2,0 },
	SPR_DATA{ spr_data::Player_eff,128,3*6,6,6,-6/2,-6/2,0 },
	SPR_DATA{ spr_data::Player_eff,128,51,9,9,-9/2,-9/2,1 },
	SPR_DATA{ spr_data::Player_eff,128,51,9,9,-9/2,-9/2,1 },
	SPR_DATA{ spr_data::Player_eff,128,51,9,9,-9/2,-9/2,1 },
	SPR_DATA{ spr_data::Player_eff,128,51,9,9,-9/2,-9/2,1 },
	SPR_LOOP
};


//�Q�[���N���A���G�t�F�N�g
static SPR_DATA gameclear_data = SPR_DATA{ spr_data::Player_eff,128,32,9,9,-9/2,-9/2 };
//static SPR_DATA noAction_data = SPR_DATA{ spr_data::Player_eff,128,1*6,6,6,-6/2,-6/2 };

//�}���`�t�H�[�J�X�g�p���G�t�F�N�g
static SPR_DATA multi_data = SPR_DATA{spr_data::Mulch_eff,0,0,128,128,-64,-64};


//line�f�[�^
//static SPR_DATA line_data = SPR_DATA{ spr_data::Player_eff,128+2,3*6,2,2,-2/1,-2/1 };
static SPR_DATA line_data = SPR_DATA{ spr_data::Player_eff,128,60,4,4,-2,-2 }; //4�~4
//static SPR_DATA line_data = SPR_DATA{ spr_data::Player_eff,128,60,2,2,-1,-1 }; //2�~2
//static SPR_DATA line_data = SPR_DATA{ spr_data::Player_eff,320-64,0,8,8,-4,-4 };



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
	animetion();
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
	shift_multierror = V2(0,0);
	shift_jast = V2(0, 0);

	for (int i = 0; i < EFF_MAX; i++) {
		if (!effect[i])continue;
		effect[i]->clear();
	}

	shift_objects_trg = false;
	shift_all_trg = false;
	shift_multierror_trg = false;
	shift_jast_trg = false;

}
void Effect_Manager::Update() {

	shift_objects = V2(0,0);
	shift_all = V2(0, 0);
	shift_multierror = V2(0,0);
	shift_jast = V2(0, 0);

	for (int i = 0; i < EFF_MAX; i++) {
		if (effect[i] && effect[i]->move) {
			effect[i]->move(effect[i]);
			effect[i]->Update();
		}
	}
	//pD_TEXT->set_Text(V2(600, 264), "ef_trg_t", shift_objects_trg == true, 0xFFFFFFFF);
	//pD_TEXT->set_Text(V2(600, 280), "ef_trg_f", shift_objects_trg == false, 0xFFFFFFFF);
	//pD_TEXT->set_Text(V2(600, 296), "ef_trg_02", shift_objects_trg == 0x02, 0xFFFFFFFF);
	//pD_TEXT->set_Text(V2(600, 312), "ef_trg_01", shift_objects_trg == 0x01, 0xFFFFFFFF);
	
	if ((shift_objects_trg == true) || (shift_all_trg == true)) {

		//Player* p = pPlayer;
		//p->custom.ef_ofsX = shift_objects.x;
		//p->custom.ef_ofsY = shift_objects.y;
		
		//Enemy** e = pEnemy_Manager->enemy;
		//for (int i = 0; i < ENEMY_MAX; i++) {
		//	if (!e[i])continue;
		//	e[i]->custom.ef_ofsX = shift_objects.x;
		//	e[i]->custom.ef_ofsY = shift_objects.y;
		//}

		//Effect** f = pEffect_Manager->effect;
		//for (int i = 0; i < EFF_MAX; i++) {
		//	if (!f[i])continue;
		//	f[i]->custom.ef_ofsX += shift_objects.x;
		//	f[i]->custom.ef_ofsY += shift_objects.y;
		//}

		Frame* r = pFrame;
		r->custom.ef_ofsX = shift_objects.x;

	}

	if ((shift_all_trg == true)) {

	}




	if ( shift_multierror_trg==true ) {
		Player* p = pPlayer;
		p->custom.ef_ofsX = shift_multierror.x;
		p->custom.ef_ofsY = shift_multierror.y;
	}


	if ( shift_jast_trg==true ) {
		Frame* r = pFrame;
		r->custom.ef_ofsX = shift_jast.x;
		r->custom.ef_ofsY = shift_jast.y;
	}






	if ((shift_objects_trg == TRG_RELEASE) || (shift_all_trg == TRG_RELEASE) || 
		(shift_multierror_trg == TRG_RELEASE) || (shift_jast_trg == TRG_RELEASE)) {
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

		Frame* r = pFrame;
		r->custom.ef_ofsX = 0;
		r->custom.ef_ofsY = 0;
	}

	if ((shift_all_trg == 0x10)) {


	}

	//pD_TEXT->set_Text(V2(600, 312 + 24), "shift_obj_x", shift_objects.x, 0xFFFFFFFF);
	//pD_TEXT->set_Text(V2(600, 312 + 40), "shift_obj_y", shift_objects.y, 0xFFFFFFFF);
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

//�W���X�g�s���g���U��
void Effect_Manager::add_multierror(V2 v) {
	shift_multierror += v;
	shift_multierror_trg = true;
}
//�}���`�t�H�[�J�X���s�U��
void Effect_Manager::add_jast(V2 v) {
	shift_jast += v;
	shift_jast_trg = true;
}


//�t���[����]
void framerotate(Effect *obj)
{
	switch (obj->state)
	{
	case INIT:
		obj->data = &Frame_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 1;
		obj->custom.angle = 0;
		obj->state=MOVE;
	case MOVE:
		obj->custom.scaleX = obj->custom.scaleY -= 0.05f;
		obj->custom.angle -= 15;
		if (obj->custom.scaleX<0) obj->state = CLEAR;
		break;
	case CLEAR:
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
	case INIT:
		//obj->data = &Ext_data;
		obj->animeData = anime_Jet_data;
		obj->data = &obj->animeData[0];
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.7f;
		obj->i_work[0] = (int)obj->pos.y;
		obj->timer = 0;
		obj->alpha = 255;
		obj->state=MOVE;
	case MOVE:
		obj->pos -= obj->spd;
		if ( /*(obj->i_work[0]-100)>obj->pos.y ||*/ obj->timer++>50) {
			if (obj->alpha>25) obj->alpha -= 25; //��������
			else {
				obj->alpha = 0;
				obj->state = CLEAR; //�����ɂȂ��������������
			}
		}
		break;
	case CLEAR:
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
	case INIT:
		//obj->data = &Ext_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.7f;
		obj->timer = 0;
		obj->alpha = (int)(255 * 0.7f);
		obj->state=MOVE;
	case MOVE:
		obj->pos += obj->spd;
		obj->custom.scaleX = obj->custom.scaleY -= 0.02f;
		if (obj->custom.scaleX<0) {
			obj->state = CLEAR;
		}
		if (obj->timer++>10) {
			//if ( obj->alpha>25 ) obj->alpha-=50; //��������
			//else {
			//	obj->alpha = 0;
			//	obj->state = CLEAR; //�����ɂȂ��������������
			//}
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}

//���ŃG�t�F�N�g
//void CircleExt(Effect *obj)
//{
//	switch (obj->state)
//	{
//	case INIT:
//		obj->animeData = anime_ext_data;
//		obj->data = &obj->animeData[0];
//		obj->custom.scaleMode = CENTER;
//		obj->custom.scaleX = obj->custom.scaleY = 1.1f;
//		obj->timer = 0;
//		obj->alpha = (int)(255 * 0.7f);
//		obj->state++;
//		
//		//break;
//	case MOVE:
//		//if ( obj->timer++>12 ) {
//		//	obj->state = CLEAR; //����������
//		//}
//		if (obj->timer++>15) {
//			obj->state = CLEAR; //����������
//		}
//
//		//if ( obj->data->no < 0 ) {	//�A�j���[�V�������Ō�Ȃ�
//		//	obj->state = CLEAR;			//����������
//		//}
//		//if ( obj->data->frameNum>4 ) {	//frameNum��4�ȏ�Ȃ�
//		//	obj->state = CLEAR;				//����������
//		//}
//		break;
//	case CLEAR:
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
	case INIT:
		obj->animeData = anime_ext_data;
		obj->data = &obj->animeData[0];
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 2.0f;
		obj->timer = 0;
		obj->state=MOVE;
		//break;
	case MOVE:
		if (obj->timer++>30) {
			obj->state = CLEAR; //����������
			obj->timer = 0;
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}

//�G���ŃG�t�F�N�g(��)
void CircleExt(Effect *obj) {
	switch (obj->state)
	{
	case INIT:
		//else if (obj->timer%5 <= 2) obj->custom.argb = 0xCCFFFFFF;	//���F
		//if (obj->timer%5 <= 1) obj->custom.argb = 0xCCffab05;	//�I�����W�F
		//else if (obj->timer%5 <= 3) obj->custom.argb = 0xCCc577ef;	//���F
		//else if (obj->timer%5 <= 5) obj->custom.argb = 0xFFD68D8D;	//���ԐF
		obj->data = &EdgeCircle_ext_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.5f;
		obj->alpha = 0; //����
		obj->timer = 0;
		obj->state = MOVE;
		//break;
	case MOVE:
		//spd.x=0		�o��time
		//spd.y=2.0f	�g����x
		if(obj->timer==(int)(obj->spd.x)) obj->alpha = (int)(255*0.8f);//�w��b���o�����猻���
		if (obj->timer>=(int)(obj->spd.x)) { 
			obj->custom.scaleX = obj->custom.scaleY += 0.2f;	//�g�又��
				 if (obj->timer%5 <= 1) obj->custom.argb = 0xFFFFFF90;	//�ԐF
			else if (obj->timer%5 <= 3) obj->custom.argb = 0xFFFFCC90;	//�F
			else if (obj->timer%5 <= 5) obj->custom.argb = 0xFFFFAA90;	//�ΐF
		}
		if (obj->custom.scaleX>=obj->spd.y) {	//���̑傫���ɂȂ�����
			obj->alpha -= 255/8;
			if ( obj->alpha<0 ) {	//�����ɂȂ�����
				obj->alpha = 0;
				obj->timer = 0;
				obj->state = CLEAR;	//������
			}
		}
		obj->timer++;
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}

}

//�G���ŃG�t�F�N�g(��)
void CircleExt_lightB(Effect *obj) {
	switch (obj->state)
	{
		case INIT:
			obj->data = &EdgeCircle_ext_data;
			obj->custom.scaleMode = CENTER;
			obj->custom.scaleX = obj->custom.scaleY = 0.5f;
			obj->custom.argb = 0xDD5BE1FF;
			obj->alpha = 0; //����
			obj->timer = 0;
			obj->state = MOVE;
			//break;
		case MOVE:
			//spd.x=0		�o��time
			//spd.y=2.0f	�g����x
			if(obj->timer==(int)(obj->spd.x)) obj->alpha = (int)(255);//�w��b���o�����猻���
			if (obj->timer>=(int)(obj->spd.x)) { 
				obj->custom.scaleX = obj->custom.scaleY += 0.2f;	//�g�又��
			}
			if (obj->custom.scaleX>=obj->spd.y) {	//���̑傫���ɂȂ�����
				obj->alpha -= 255/8;
				if ( obj->alpha<0 ) {	//�����ɂȂ�����
					obj->alpha = 0;
					obj->timer = 0;
					obj->state = CLEAR;	//������
				}
			}
			obj->timer++;
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}

}

//�G���ŃG�t�F�N�g(�U��΂遜)
void ParticleExt_c(Effect* obj) {
	switch (obj->state) {
	case INIT:
		obj->data = &Circle_ext_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.1f;
		obj->custom.argb = 0xFFFFFFFF;
		obj->timer = 0;
		obj->alpha = 0;
		obj->i_work[6] = 0;
		obj->state=MOVE;
		//break;
	case MOVE:
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
			obj->state = CLEAR;		//����������
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}

//�G���ŃG�t�F�N�g(�U��΂�L���L��)
void ParticleExt_k(Effect* obj) {
	switch (obj->state) {
	case INIT:
		obj->data = &kirakira_ext_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.1f;
		obj->custom.argb = 0xFFFFFFFF;
		obj->timer = 0;
		obj->alpha = 0;
		obj->i_work[6] = 0;
		obj->state=MOVE;
		//break;
	case MOVE:
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
			obj->state = CLEAR;		//����������
		}
		break;
	case CLEAR:
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
	case INIT:
		obj->data = &Lock_data;
		obj->custom.argb = 0xFFFFFFFF;
		obj->custom.scaleMode = CENTER;
		obj->timer = 0;
		obj->alpha = 255;
		obj->i_work[6] = 0;
		obj->state=MOVE;
		//break;
	case MOVE:
		obj->i_work[6] = obj->timer % 5;
		if (obj->i_work[6] <= 1) obj->custom.argb = 0xCCffab05;	//�I�����W�F
		else if (obj->i_work[6] <= 3) obj->custom.argb = 0xCCc577ef;	//���F
		else if (obj->i_work[6] <= 5) obj->custom.argb = 0xFFD68D8D;	//���ԐF

		if (obj->timer++>18) obj->state = MOVE2; //�g���
		break;
	case MOVE2: //�g��
		obj->custom.scaleX = obj->custom.scaleY += 0.7f;
		if (obj->custom.scaleX >= 1.7f) obj->state = MOVE3;
		break;
	case MOVE3: //�k��
		obj->custom.scaleX = obj->custom.scaleY -= 0.2f;
		if (obj->custom.scaleX <= 1.4f) obj->state = MOVE4;
		break;
	case MOVE4: //scaleY�k��
		obj->custom.scaleY -= 0.3f;
		if (obj->custom.scaleY<0.0f) obj->state = CLEAR;
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}



#include "sceneMain.h"
//�R���{�J���[
void Combo_Color(Effect*obj) {
	if ( pScore->getCombo()<=9 ) { //0�`�R���{���̐F
		obj->i_work[6] = obj->timer%7+1;
		if (obj->i_work[6]<=3) obj->custom.argb = 0xFFffad21;		//�I�����W�F
		else if (obj->i_work[6]<=5) obj->custom.argb = 0xFFc77fef;	//���F
		else if (obj->i_work[6]<=7) obj->custom.argb = 0xFFed9797;	//���ԐF
	}
	else if ( pScore->getCombo()<=19 ) { //10�`�R���{���̐F
		obj->i_work[6] = obj->timer%10+1;
		if (obj->i_work[6]<=5) obj->custom.argb = 0xFFd0e021;		//���F
		else if (obj->i_work[6]<=10) obj->custom.argb = 0xFFf76c8c;	//�s���N�F
	}
	else /*if ( pScore->getCombo()<=29 )*/ { //20�`�R���{���̐F
		obj->i_work[6] = obj->timer%12+1;
		     if (obj->i_work[6]<=2)  obj->custom.argb = 0xFFe65ffc;	//���F
		else if (obj->i_work[6]<=4)  obj->custom.argb = 0xFFff8426;	//�I�����W�F
		else if (obj->i_work[6]<=6)  obj->custom.argb = 0xFFffe942;	//���F
		else if (obj->i_work[6]<=8)  obj->custom.argb = 0xFF8dff42;	//�ΐF
		else if (obj->i_work[6]<=10) obj->custom.argb = 0xFF58eaef;	//���F
		else if (obj->i_work[6]<=12) obj->custom.argb = 0xFF5e9bff;	//�F
	}
}

//�R���{
void Combo(Effect* obj) {
	switch (obj->state) {
	case INIT:
		obj->data = &combo_number[0];
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 1.3f;
		obj->timer = 0;
		obj->i_work[6] = 0; //�F�ύX�����_���p
		obj->i_work[7] = 0; //�R���{�p
		obj->f_work[8] = obj->pos.y; //���W�ۑ��p
		obj->custom.argb = 0xFFffab05;	//�I�����W�F
		obj->spd.y = -4;
		obj->state=MOVE;
		//break;
	case MOVE:
		obj->i_work[7] = (int)obj->spd.x; //�R���{
		obj->data = &combo_number[obj->i_work[7]]; //�R���{�\��
		Combo_Color(obj); //�F
		if ((obj->f_work[8]-40)<obj->pos.y) obj->pos.y += obj->spd.y; //�ړ�����
		else if (obj->timer>30) obj->state = CLEAR; //����
		obj->timer++;
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}

//�R���{�e�L�X�g
void ComboText(Effect* obj) {
	switch ( obj->state ){
	case INIT:
		obj->data = &combo_text;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY =0.6f;
		obj->timer = 0;
		obj->i_work[6] = 0; //�F�ύX�����_���p
		obj->f_work[8] = obj->pos.y; //���W�ۑ��p
		obj->custom.argb = 0xFFffab05;	//�I�����W�F
		obj->spd.y = -4;
		obj->state=MOVE;
		//break;
	case MOVE:
		Combo_Color(obj); //�F
		if ((obj->f_work[8]-40)<obj->pos.y) obj->pos.y += obj->spd.y; //�ړ�����
		else if (obj->timer>30) obj->state = CLEAR; //����
		obj->timer++;
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;

	}
}



//�o(����)�G�t�F�N�g
void dust(Effect* obj) {
	switch ( obj->state ) {
		case INIT:
			obj->data = &dust_data;
			//obj->animeData = anime_dust_data;
			//obj->data = &obj->animeData[0];
			obj->custom.scaleMode = CENTER;
			if(obj->spd.y==-1.0f) obj->custom.scaleX = obj->custom.scaleY = 0.8f;
			if(obj->spd.y==-2.0f) obj->custom.scaleX = obj->custom.scaleY = 0.6f;
			if(obj->spd.y==-3.0f) obj->custom.scaleX = obj->custom.scaleY = 0.4f;
			obj->timer = 0;
			obj->alpha = 0;
			obj->state=MOVE;
			//break;
		case MOVE:
			obj->timer++;
			//�ړ�----------------------------------------------
			//obj->pos.x += cosf(obj->timer*0.03f);
			if ( obj->timer>360 )obj->timer = 0;
			obj->pos.x += cosf(obj->timer*obj->spd.x);
			obj->pos.y += obj->spd.y;

			//�o������------------------------------------------
			if ( obj->timer>(rand()%100) ) obj->alpha += 25;
			if ( obj->alpha>255 ) obj->alpha = 255;

			if ( obj->pos.y<150 ) {
				//��������------------------------------------------
				obj->alpha -= 25;
				if ( obj->alpha<0 ) obj->alpha = 0;
				obj->state = CLEAR; //��܂ł����������
			}
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//�X�J�G�t�F�N�g
void noAction(Effect *obj) {
	switch (obj->state)
	{
		case INIT:
			obj->data = &EdgeCircle_ext_data;
			obj->custom.scaleMode = CENTER;
			obj->custom.scaleX = obj->custom.scaleY = 0.5f;
			obj->custom.argb = 0xFFffa8a8;
			obj->state=MOVE;
			//break;
		case MOVE:
			obj->custom.scaleX = obj->custom.scaleY += 0.25f;	//�g�又��
			if (obj->custom.scaleX>2.0f) {	//���̑傫���ɂȂ�����
				obj->alpha -= 255/6;
				if ( obj->alpha<0 ) {	//�����ɂȂ�����
					obj->alpha = 0;
					obj->state = CLEAR;	//������
				}
			}
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}



//�Q�[���N���A���G�t�F�N�g�W��
void gameclear_aggre(Effect*obj) {
	switch ( obj->state ) {
		case INIT:
		case MOVE:
			if ( obj->timer==0 ) pEffect_Manager->searchSet(V2(0,0), V2(0,0), gameclear_screen_many); //��ʑS��
			if ( obj->timer==0 ) pEffect_Manager->searchSet(obj->pos, obj->spd, gameclear_eight); //8����
			if ( obj->timer==5 ) pEffect_Manager->searchSet(obj->pos, obj->spd, gameclear_eight); //8����
			if ( obj->timer==10 ) {
				pEffect_Manager->searchSet(obj->pos, obj->spd, gameclear_eight); //8����
				pEffect_Manager->searchSet(obj->pos, V2(6,6), gameclear_kirakira); //�L���L��
			}
			if ( obj->timer>10 ) obj->state = CLEAR;
			obj->timer++;
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//�Q�[���N���A����ʑS�̃G�t�F�N�g
void gameclear_screen_many(Effect*obj) {
	switch ( obj->state ) {
		case INIT:
		case MOVE:
			//pEffect_Manager->searchSet(V2(			 0+300,  			 0+250), V2(0,0), gameclear_screen);
			//pEffect_Manager->searchSet(V2(SCREEN_WIDTH-300,  			 0+250), V2(0,0), gameclear_screen);
			//pEffect_Manager->searchSet(V2(			 0+300,  SCREEN_HEIGHT-100), V2(0,0), gameclear_screen);
			//pEffect_Manager->searchSet(V2(SCREEN_WIDTH-300,  SCREEN_HEIGHT-100), V2(0,0), gameclear_screen);
			pEffect_Manager->searchSet(V2(SCREEN_WIDTH/4*1, SCREEN_HEIGHT/4*1), V2(0,0), gameclear_screen);
			pEffect_Manager->searchSet(V2(SCREEN_WIDTH/4*3, SCREEN_HEIGHT/4*1), V2(0,0), gameclear_screen);
			pEffect_Manager->searchSet(V2(SCREEN_WIDTH/4*1, SCREEN_HEIGHT/4*3), V2(0,0), gameclear_screen);
			pEffect_Manager->searchSet(V2(SCREEN_WIDTH/4*3, SCREEN_HEIGHT/4*3), V2(0,0), gameclear_screen);
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//�Q�[���N���A����ʑS�̃G�t�F�N�g
void gameclear_screen(Effect*obj) {
	switch (obj->state) {
		case INIT:
			obj->data = &kirakira_ext_data;
			obj->custom.scaleMode = CENTER;
			obj->custom.scaleX = obj->custom.scaleY = 3.0f;
			obj->custom.argb = 0xFFFFFFFF;
			obj->alpha = (int)(255*0.6f);
			obj->timer = 0;
			obj->i_work[6] = 0; //�F
			obj->f_work[1] = obj->pos.x;
			obj->f_work[2] = obj->pos.y;
			obj->state=MOVE;
			//break;
		case MOVE:
			//obj->custom.scaleX = obj->custom.scaleY =(float)(rand()%10)/10.0f+2.0f;	//�傫���ύX(1.0�`2.0�{)
			//obj->custom.scaleX = obj->custom.scaleY =(float)(rand()%3)+2.0f;	//�傫���ύX(2.0�`4.0�{)
			obj->i_work[6] = obj->timer % 20+1;
			if (obj->i_work[6] <= 4) obj->custom.argb = 0xFFffa5a5;	//�ԐF
			else if (obj->i_work[6] <= 8) obj->custom.argb = 0xFFb2d0ff;	//�F
			else if (obj->i_work[6] <= 12) obj->custom.argb = 0xFFffffa3;	//���F
			else if (obj->i_work[6] <= 16) obj->custom.argb = 0xFFdfa5ff;	//���F
			else if (obj->i_work[6] <= 20) obj->custom.argb = 0xFFcaffb7;	//�ΐF

			if ( (obj->timer%2+1)<=1 ) {
				obj->pos.x = obj->f_work[1]+rand()%200-100;
				obj->pos.y = obj->f_work[2]+rand()%200-100;
			}

			if (obj->timer>40) {	//�w�莞�Ԍo������
				obj->alpha -= 60;
				if ( obj->alpha<0 ) obj->alpha = 0;
				obj->state = CLEAR;		//����������
			}
			obj->timer++;
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//�Q�[���N���A���G�t�F�N�g�L���L��
void gameclear_kirakira(Effect* obj) {
	switch ( obj->state ) {
		case INIT:
		case MOVE:
			pEffect_Manager->searchSet(obj->pos, V2( obj->spd.x,		   0), ParticleExt_k); //�E
			pEffect_Manager->searchSet(obj->pos, V2(-obj->spd.x,		   0), ParticleExt_k); //��
			pEffect_Manager->searchSet(obj->pos, V2(		  0,  obj->spd.y), ParticleExt_k); //��
			pEffect_Manager->searchSet(obj->pos, V2(		  0,  obj->spd.y), ParticleExt_k); //��
			pEffect_Manager->searchSet(obj->pos, V2( obj->spd.x,  obj->spd.y), ParticleExt_k); //�ȂȂ�
			pEffect_Manager->searchSet(obj->pos, V2( obj->spd.x, -obj->spd.y), ParticleExt_k); //�ȂȂ�
			pEffect_Manager->searchSet(obj->pos, V2(-obj->spd.x,  obj->spd.y), ParticleExt_k); //�ȂȂ�
			pEffect_Manager->searchSet(obj->pos, V2(-obj->spd.x, -obj->spd.y), ParticleExt_k); //�ȂȂ�
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//�Q�[���N���A���G�t�F�N�g8����
void gameclear_eight(Effect* obj) {
	switch ( obj->state ) {
		case INIT:
		case MOVE:
			pEffect_Manager->searchSet(obj->pos, V2( obj->spd.x+2,			  0), gameclear); //�E
			pEffect_Manager->searchSet(obj->pos, V2(-obj->spd.x-2,			  0), gameclear); //��
			pEffect_Manager->searchSet(obj->pos, V2(		  0,   obj->spd.x+2), gameclear); //��
			pEffect_Manager->searchSet(obj->pos, V2(		  0,  -obj->spd.x-2), gameclear); //��
			pEffect_Manager->searchSet(obj->pos, V2( obj->spd.x,  obj->spd.y), gameclear); //�ȂȂ�
			pEffect_Manager->searchSet(obj->pos, V2( obj->spd.x, -obj->spd.y), gameclear); //�ȂȂ�
			pEffect_Manager->searchSet(obj->pos, V2(-obj->spd.x,  obj->spd.y), gameclear); //�ȂȂ�
			pEffect_Manager->searchSet(obj->pos, V2(-obj->spd.x, -obj->spd.y), gameclear); //�ȂȂ�
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//�Q�[���N���A���G�t�F�N�g
void gameclear(Effect* obj) {
	switch ( obj->state ) {
		case INIT:
			obj->data = &gameclear_data;
			obj->alpha = 0; //����
			obj->timer = 0;
			obj->custom.scaleMode = CENTER;
			obj->custom.argb = 0xFFffa8da;
			obj->state = MOVE;
			//break;
		case MOVE:
			obj->pos += obj->spd;
			if ( obj->timer==7 ) obj->alpha = 255;
			if ( obj->timer>=18 ) obj->state = CLEAR;
			obj->timer++;
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}



//�v���C���[�_���[�W�G�t�F�N�g
void P_damage(Effect* obj) {
	switch ( obj->state ) {
		case INIT:
			obj->data = &EdgeCircle_ext_data;
			obj->custom.scaleMode = CENTER;
			obj->custom.scaleX = obj->custom.scaleY = 0.2f;
			obj->custom.argb = 0xFF47dde5;
			obj->state=MOVE;
			//break;
		case MOVE:
			if ( obj->timer++>14 ) obj->state = CLEAR;
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//�}���`�t�H�[�J�X�g�p���G�t�F�N�g
void Multifocus(Effect*obj) {
	switch ( obj->state ) {
		case INIT:
			obj->data = &multi_data;
			obj->custom.scaleMode = CENTER;
			obj->custom.scaleX = obj->custom.scaleY = obj->spd.y;
			obj->custom.argb = 0xFFFFFFFF; //�F
			obj->alpha = (int)(255*0.5f);
			obj->i_work[1] = (int)(obj->spd.x); //angle_spd
			obj->state = MOVE;
			//break;
		case MOVE:
			//�v���C���[�̍��W
			obj->pos.x = pPlayer->pos.x;
			obj->pos.y = pPlayer->pos.y;

			//��]
			obj->custom.angle += obj->i_work[1];
			if ( obj->custom.angle>=360 ) obj->custom.angle = 0;

			//�F
			if ( (obj->timer%18)<9 )  obj->custom.argb = 0xFFFFFFFF; //01
			if ( (obj->timer%18)>=9 ) obj->custom.argb = 0xFFff7a7a; //23

			//��������------------------------------------------------
			if ( (obj->timer>(MALTIFOCUS_TIME-60)) && (obj->timer<MALTIFOCUS_TIME) ) {
				//�_��
				if ( (obj->timer%4)<2 )  obj->alpha = (int)(255*0.1f); //01
				if ( (obj->timer%4)>=2 ) obj->alpha = (int)(255*0.7f); //23
			}
			//����
			if ( obj->timer>MALTIFOCUS_TIME ) {
				obj->alpha -= 20;
				obj->custom.scaleX = obj->custom.scaleY += 0.05f;
				if ( obj->alpha<0 ) {
					obj->alpha = 0;
					obj->timer = 0;
					obj->custom.angle = 0;
					obj->state = CLEAR;
				}
			}
			obj->timer++;
			break;
		case CLEAR:
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
	case INIT:
		obj->animeData = anime_tele_data;
		obj->data = &obj->animeData[0];
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.5f;
		obj->alpha = (int)(255 * 0.7f);
		obj->custom.argb = 0xFFFFFFFF;
		obj->timer = 0;
		obj->state=MOVE;
	case MOVE:
		if (obj->timer++>16) {
			obj->state = CLEAR; //����������
		}
		break;
	case CLEAR:
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
	case INIT:
		//obj->animeData = anime_ext_data;
		obj->data = &jastpinto_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 1.0f;
		obj->custom.argb = 0xDDff9393; //�ԐF
		obj->timer = 0;
		obj->alpha = (int)(255 * 0.8f);
		obj->state=MOVE;
		//break;
	case MOVE:
		obj->alpha -= 6;					//��������
		if (obj->alpha<0) obj->alpha = 0;	//
		obj->custom.scaleX = obj->custom.scaleY += 0.17f;	//�g�又��
		if (obj->custom.scaleX>3.0f) {	//���̑傫���ɂȂ�����
			obj->state = CLEAR;					//����������
		}
		break;
	case CLEAR:
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
	case INIT:
		//obj->animeData = anime_ext_data;
		obj->data = &jastpinto_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 3.0f;
		obj->custom.argb = 0xDDCFCFCF; //�ԐF
		obj->timer = 0;
		obj->alpha = (int)(255 * 0.8f);
		obj->state++;
		//break;
	case MOVE:
		obj->alpha -= 6;					//��������
		if (obj->alpha<0) obj->alpha = 0;	//
		obj->custom.scaleX = obj->custom.scaleY -= 0.17f;	//�g�又��
		if (obj->custom.scaleX<0.5f) {	//���̑傫���ɂȂ�����
			obj->state = CLEAR;					//����������
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}


//�W�F�b�g�G�t�F�N�g
void Jet(Effect *obj) {
	switch (obj->state) {
	case INIT:
		//obj->animeData = anime_ext_data;
		obj->data = &jet_data;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = 0.4f;
		obj->custom.argb = 0xFFFFFFFF;
		obj->timer = 0;
		obj->alpha = (int)(255 * 0.7f);
		obj->state=MOVE;
		//break;
	case MOVE:
		obj->custom.scaleX = obj->custom.scaleY -= 0.01f;							//�k������
		if (obj->custom.scaleX<0) obj->custom.scaleX = obj->custom.scaleY = 0;	//
		obj->alpha -= 8;						//��������
		if (obj->alpha<0) obj->alpha = 0;		//
		obj->pos.y += 2;

		if (obj->timer++>12) { //�w�莞�Ԍo������
			obj->state = CLEAR; //����������
		}
		break;
	case CLEAR:
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
	case INIT:
		obj->animeData = p_eff_data;
		obj->data = &obj->animeData[0];
		//obj->data = &p_eff_data[5];
		obj->custom.argb = 0xFFFFFF55;
		obj->timer = 0;
		obj->alpha = (int)(255 * 0.6f);
		obj->state = MOVE;
		//break;
	case MOVE:
		if (obj->timer>6) {
			obj->alpha -= 28;						//��������
			if (obj->alpha<0) obj->alpha = 0;		//
		}
		obj->pos.y += 0.8f;
		if (obj->timer++>15) { //�w�莞�Ԍo������
			obj->state = CLEAR; //����������
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}
}



//line�G�t�F�N�g
void line(Effect* obj) {
	switch ( obj->state ) {
		case INIT:
			obj->data = &line_data;
			obj->timer = 0;
			obj->alpha = (int)(255*0.5f);
			//obj->custom.scaleMode = CENTER;
			//obj->custom.scaleX = obj->custom.scaleY = 0.7f;
			obj->custom.argb = 0xFFd6fff9;
			obj->state=MOVE;
			//break;
		case MOVE:
			//�_��
			//if ( (obj->timer%2)<1 )  obj->custom.argb = 0xFFFF0000;
			//if ( (obj->timer%2)>=1 ) obj->custom.argb = 0xFFFFFFFF;
			//if ( (obj->timer%2)<1 )  obj->alpha=(int)(255*0.2f);
			//if ( (obj->timer%2)>=1 ) obj->alpha=(int)(255*0.7f);
			if ( obj->timer>=1 ) {
				obj->timer = 0;
				obj->state = CLEAR;
			}
			obj->timer++;
			break;
		case CLEAR:
			obj->clear();
			break;
		default:
			break;
	}
}

//�t�F�[�h�C��
void fade_In(Effect* obj) {
	switch (obj->state) {
	case INIT:
		obj->data = &fade_in;
		obj->custom.scaleMode = LEFTTOP;
		obj->timer = 0;
		obj->state = MOVE;
		//break;
	case MOVE:
		obj->pos.x -= 24;

		if (obj->timer++ > 120) { //�w�莞�Ԍo������
			obj->state = CLEAR; //����������
		}
		break;
	case CLEAR:
		obj->clear();
		break;
	default:
		break;
	}

}

//�t�F�[�h�A�E�g
void fade_Out(Effect* obj) {
	switch (obj->state) {
	case INIT:
		obj->data = &fade_out;
		obj->custom.scaleMode = LEFTTOP;
		obj->timer = 0;
		obj->state = MOVE;
		//break;
	case MOVE:
		obj->pos.x -= 17;
		if (obj->pos.x < -SCREEN_WIDTH) { //�w�莞�Ԍo������
			obj->state = MOVE2; //���[�v��
			obj->pos.x = -SCREEN_WIDTH;
		}
		break;
	case MOVE2:
		break;

	case CLEAR:
		obj->clear();

		break;
	default:
		break;
	}

}






#define SHAKE_MAX obj->f_work[12]
#define SHAKE_MIN obj->f_work[13]
#define SHAKE_X obj->f_work[14]
#define SHAKE_Y obj->f_work[15]
void Shake(Effect* obj) {

	int randxy = rand();

	switch (obj->state)
	{
	case INIT:
		SHAKE_MAX = obj->pos.x;
		SHAKE_MIN = obj->pos.y;

		obj->timer = (int)obj->spd.x;
		obj->state = (int) obj->spd.y;
		break;
	case MOVE: //�W���X�g�s���g���U���������́A�}���`�t�H�[�J�X���s�U��
		//SHAKE_Y =  (int)((randxy % (SHAKE_MAX - SHAKE_MIN)) - SHAKE_MIN)/2;
		//SHAKE_X = (int)(randxy % (SHAKE_MAX - SHAKE_MIN)) - SHAKE_MIN;
		SHAKE_X = ((randxy%201)-100)*0.01f*(SHAKE_MAX-SHAKE_MIN)+SHAKE_MIN;
		//-100�`100 -1�`1 MIN�`MAX

		if (obj->timer-- < 0) {
			obj->timer = 0;
			obj->state = CLEAR;
		}
		pEffect_Manager->add_object(V2(SHAKE_X, SHAKE_Y));

		break;
	case MOVE2:
		//SHAKE_X = (randxy % (SHAKE_MAX - SHAKE_MIN)) - SHAKE_MIN;
		//SHAKE_Y = ((randxy % (SHAKE_MAX - SHAKE_MIN)) - SHAKE_MIN)/2;
		SHAKE_X = ((randxy%201)-100)*0.01f*(SHAKE_MAX-SHAKE_MIN)+SHAKE_MIN;
		if (obj->timer-- < 0) {
			obj->timer = 0;
			obj->state = CLEAR;
		}
		pEffect_Manager->add_all(V2(SHAKE_X, SHAKE_Y));
		break;

	case MOVE3: //�}���`�t�H�[�J�X���s�U��(�E��UI)
		SHAKE_X = ((randxy%201)-100)*0.01f*(SHAKE_MAX-SHAKE_MIN)+SHAKE_MIN;
		if (obj->timer-- < 0) {
			obj->timer = 0;
			obj->state = CLEAR;
		}
		pEffect_Manager->add_multierror(V2(SHAKE_X, SHAKE_Y));
		break;
	case MOVE4: //�W���X�g�s���g���U��
		SHAKE_X = ((randxy%201)-100)*0.01f*(SHAKE_MAX-SHAKE_MIN)+SHAKE_MIN;
		if (obj->timer-- < 0) {
			obj->timer = 0;
			obj->state = CLEAR;
		}
		pEffect_Manager->add_jast(V2(SHAKE_X, SHAKE_Y));
		break;
	case CLEAR:
		obj->clear();
	default:
		obj->state = CLEAR;
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