#include "iextreme.h"
#include "system\System.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Frame.h"
#include "MAP.h"
#include "BGFG.h"
#include "stage_data.h"

enum 
{
	BG_CASE = spr_data::BG2,
	BG_PC = spr_data::BG3,
	BG_PIPE = spr_data::BG4,
	Capsule_l = spr_data::BG2,
	Capsule_d = spr_data::BG2,

	Mini_capsule_l = spr_data::BG2,
	Mini_capsule_d = spr_data::BG2,

	Break_capsule_u = spr_data::BG2,
	Break_capsule_o = spr_data::BG2,

	Fly_capsule_l = spr_data::BG2,
	Fly_capsule_d = spr_data::BG2,

	Fly_capsule_m = spr_data::BG2,

	Fly_mini_capsule_l = spr_data::BG2,
	Fly_mini_capsule_d = spr_data::BG2,

	Fly_mini_capsule_m = spr_data::BG2,

	Display_a = spr_data::BG2,
	Display_b = spr_data::BG2,
	Display_c = spr_data::BG2,
	Display_d = spr_data::BG2,

};


SPR_DATA spr_pc[] = {
	SPR_DATA{ BG_PC,0,0,248,157,-124,-157,0 } ,
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,1 },
};
SPR_DATA spr_container[] = {
	SPR_DATA{ BG_PC,0,256,248,157 ,-128,-157 ,0},
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,1 }
};
 
//�n���J�v�Z��
SPR_DATA spr_Capsule_l = { Capsule_l,0,  0,	177,512,-89,-512 };
SPR_DATA spr_Capsule_d = { Capsule_d,256,0,	177,512,-89,-512 };

//�n�㏬�J�v�Z��
SPR_DATA spr_Mini_capsule_l = { Mini_capsule_l,512,0,128,226,-128 / 2,-226 };
SPR_DATA spr_Mini_capsule_d = { Mini_capsule_d,640,0,128,226,-128 / 2,-226 };

//�n�㊄�J�v�Z���r
SPR_DATA spr_Break_capsule_u = { Break_capsule_u,512,256,158,256,-158 / 2,-256 };
//���J�v�Z����
SPR_DATA spr_Break_capsule_o = { Break_capsule_o,1664,0,153,141,-76,-70 };

//�󒆑�J�v�Z��
SPR_DATA spr_Fly_capsule_d = { Fly_capsule_d,896,0,128,512,-128 / 2,-512 / 2 };
SPR_DATA spr_Fly_capsule_l = { Fly_capsule_l,768,0,128,512,-128 / 2,-512 / 2 };

//�󒆑僁�^���J�v�Z��
SPR_DATA spr_Fly_capsule_m = { Fly_capsule_m,1024,0,153,448,-77,-448 / 2 };

//�󒆏��J�v�Z��
SPR_DATA spr_Fly_mini_capsule_l = { Fly_mini_capsule_l,1280,0,113,384,-57,-384 / 2 };
SPR_DATA spr_Fly_mini_capsule_d = { Fly_mini_capsule_d,1408,0,113,384,-57,-384 / 2 };

//�󒆏����^���J�v�Z��
SPR_DATA spr_Fly_mini_capsule_m = { Fly_mini_capsule_m,1536,0,113,337,-57,-169 };

//�f�B�X�v���C��
SPR_DATA spr_Display_a = { Display_a,1280,384,128,93,-128 / 2,-93 / 2 };
SPR_DATA spr_Display_b = { Display_b,1408,384,128,75,-128 / 2,-75 / 2 };
SPR_DATA spr_Display_c = { Display_c,1536,384,128,97,-128 / 2,-97 / 2 };
SPR_DATA spr_Display_d = { Display_d,  1664,384,128,97,-128 / 2,-97 / 2 };

enum {
	INIT = 0,	//�����ݒ�
	BEGIN,	//
	BEGIN2,	//
	
	MOVE,	//�ړ�����
	MOVE2,	//
	MOVE3,	//
	MOVE4,	//
	MOVE5,	//

	CLEAR,	//������
};

float BG_REDUCED_DATA[] = {
	1,1.2,1.4,2,4,6
};
float FG_REDUCED_DATA[] = {
	0.5,0.7,
};

void LandScape::Init(int stage_no) {
	
	bg.clear();
	for (int i = 0; i < LANDSCAPE_MAX;i++) {
		if (!LandScapeObjs[i])continue;
		LandScapeObjs[i]->clear();
	}
	timer = 0;
	data = &stage1_bg_effct[stage_no];

	for (int i = 0; i < BG_REDUCED_LV_MAX;i++) {
		BG_RenderBox[i].Init(BG_REDUCED_DATA[i]);
	}
	for (int i = 0; i < FG_REDUCED_LV_MAX; i++) {
		FG_RenderBox[i].Init(FG_REDUCED_DATA[i]);
	}

}


void LandScape::Update() {
	stage_update();

	//bg.Update();
	for (int i = 0; i < LANDSCAPE_MAX; i++) {
		if (!LandScapeObjs[i])break;
		if(!LandScapeObjs[i]->init_fg)continue;
		LandScapeObjs[i]->Update();
	}
	for (int i = 0; i < BG_REDUCED_LV_MAX; i++) {
		BG_RenderBox[i].Update();
	}
	for (int i = 0; i < FG_REDUCED_LV_MAX; i++) {
		FG_RenderBox[i].Update();
	}

}
static int d_txt_x = 0;
static int d_txt_y = 0;

void LandScape::RenderBG() {
	bg.Render();
	d_txt_y = 0;
	d_txt_x = 0;
	for (int i = BG_REDUCED_LV_MAX -1; i >= 0; i--) {
		BG_RenderBox[i].Render();
	}
}
void LandScape::RenderFG() {

	for (int i = FG_REDUCED_LV_MAX - 1; i >= 0; i--) {
		FG_RenderBox[i].Render();
	}

}



void LandScape::stage_update() {
	timer++;
	//timer�ŊǗ�
	while (data->appearTime <= timer)
	{
		if (data->appearTime < 0) {
			data++;
			break;
		}
		if (data->moveType == nullptr) break;
		searchSet(data->type,data->pos, data->speed,data->moveType,nullptr,data->z);
		data++;
	}
}

void LandScape::add_RenderObj(LAND_SCAPE_OBJ* obj, int z) {
	ReducedObj* data;
	if (z > -1) { //0�ȏ�Ȃ�w�i�A�ȉ��Ȃ�O�i
		//�G���[�`�F�b�N// �z��T�C�Y�Ɏ��܂��Ă��邩
		if (z < 0 || z < FG_REDUCED_LV_MAX) {
			z = (BG_REDUCED_LV_MAX-1);
		}
		BG_RenderBox[z].data[(BG_RenderBox[z].count++)] = obj;
		data = &BG_RenderBox[z];

	}
	else {
		z *= -1;
		z -= 1;
		//�G���[�`�F�b�N// �z��T�C�Y�Ɏ��܂��Ă��邩
		if (z < 0 || z < FG_REDUCED_LV_MAX) {
			z = (FG_REDUCED_LV_MAX - 1);
		}
		FG_RenderBox[z].data[FG_RenderBox[z].count++] = obj;
		data = &FG_RenderBox[z];
	}
	obj->custom.scaleX = 1 / data->Reduced_level;
	obj->custom.scaleY = 1 / data->Reduced_level;

}

//******************************************************************************
//
//		�`�揇������
//
//******************************************************************************
//------------------------------------------------------------------------------
//		�����ݒ�
//------------------------------------------------------------------------------

void LandScape::ReducedObj::Init(float _Reduced_level) {
	clear();
	Reduced_level = _Reduced_level;
	pos = V2((SCREEN_WIDTH - (SCREEN_WIDTH / Reduced_level))/2, (SCREEN_HEIGHT - (SCREEN_HEIGHT / Reduced_level))/2);
	bot = (pos.y * 2);
	
}

void LandScape::ReducedObj::Update() {
	for (int i = 0; i < count; i++) {
		switch (data[i]->type)
		{
		case LSD::CENTER:
			data[i]->pos = pos + (data[i]->pos / Reduced_level);
			
			break;
		case LSD::TOP:
			data[i]->pos =V2(pos.x,0) + (data[i]->pos / Reduced_level);
			break;
		case LSD::BOT:
			data[i]->pos = V2(pos.x,bot) + V2((data[i]->pos.x / Reduced_level),(data[i]->pos.y / Reduced_level));
			
			break;
		default:
			data[i]->pos = pos + (data[i]->pos / Reduced_level);
			break;
		}
	}
}
void LandScape::ReducedObj::Render() {

	for (int i = 0; i < count; i++) {
		data[i]->Render();
	}
	count = 0;
#ifdef _DEBUG_REDUCEDLINE_RENDER_

#ifdef _DEBUG_REDUCEDLINE_TOP_
		//��
		iexPolygon::Rect((int)(pos.x), (int)(0), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFFFFFF00);
		iexPolygon::Rect((int)(pos.x), (int)(0 + SCREEN_HEIGHT / Reduced_level), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFFFFFF00);
		//�c
		iexPolygon::Rect((int)(pos.x), (int)(0), 1, (int)SCREEN_HEIGHT / Reduced_level, 0, 0xFFFFFF00);
		iexPolygon::Rect((int)(pos.x + (int)(SCREEN_WIDTH / Reduced_level)), (int)(0), 1, SCREEN_HEIGHT / Reduced_level, 0, 0xFFFFFF00);

#endif //_DEBUG_REDUCEDLINE_TOP_
#ifdef _DEBUG_REDUCEDLINE_CENTER_
		//��
		iexPolygon::Rect((int)(pos.x), (int)(pos.y), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFF00FF00);
		iexPolygon::Rect((int)(pos.x), (int)(pos.y + SCREEN_HEIGHT / Reduced_level), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFF00FF00);
		//�c
		iexPolygon::Rect((int)(pos.x), (int)(pos.y), 1, (int)SCREEN_HEIGHT / Reduced_level, 0, 0xFF00FF00);
		iexPolygon::Rect((int)(pos.x + (int)(SCREEN_WIDTH / Reduced_level)), (int)(pos.y), 1, SCREEN_HEIGHT / Reduced_level, 0, 0xFF00FF00);
#endif //_DEBUG_REDUCEDLINE_CENTER_
#ifdef _DEBUG_REDUCEDLINE_BOT_
		iexPolygon::Rect((int)(pos.x), (int)(bot), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFFFF0000);
		iexPolygon::Rect((int)(pos.x), (int)(bot + SCREEN_HEIGHT / Reduced_level), (int)(SCREEN_WIDTH / Reduced_level), 1, 0, 0xFFFF0000);
		//SCREEN_WIDTH / Reduced_level
		////�c
		iexPolygon::Rect((int)(pos.x), (int)(bot), 1, (int)SCREEN_HEIGHT / Reduced_level, 0, 0xFFFF0000);
		iexPolygon::Rect((int)(pos.x + (int)(SCREEN_WIDTH / Reduced_level)), (int)(bot), 1, SCREEN_HEIGHT / Reduced_level, 0, 0xFFFF0000);
#endif //_DEBUG_REDUCEDLINE_BOT_
#endif

}


//---------------------------------------------------------------
//
// �w�i :: �p�~
//
//---------------------------------------------------------------

//BG::BG()
//{
//
//}
//
//BG::~BG()
//{
//			
//}
//
//void BG::Init() {
//	
//	for (int i = 0; i < BG_MAX; i++) {
//		if (obj[i])obj[i]->Init();
//	}
//}
//
//
//
//void BG::Update() {
//	for (int i = 0; i < BG_MAX; i++) {
//		if (obj[i] && obj[i]->move)
//			obj[i]->Update();
//	}
//}
//void BG::Render() {
//	for (int i = 0; i < BG_MAX;i++ ) {
//		if(obj[i])obj[i]->Render();
//	}
//}

//---------------------------------------------------------------
//
//	�O�i::�p�~
//
//---------------------------------------------------------------

//FG::FG()
//{
//	}
//
//FG::~FG()
//{
//
//}
//
//void FG::Init() {
//	for (int i = 0; i < BG_MAX; i++) {
//		if (obj[i])obj[i]->Init();
//	}
//
//}
//
//void FG::Update() {
//
//	for (int i = 0; i < BG_MAX; i++) {
//		if (obj[i] && obj[i]->move)
//			obj[i]->Update();
//	}
//}
//void FG::Render() {
//	for (int i = 0; i < BG_MAX; i++) {
//		if (obj[i])obj[i]->Render();
//	}
//}


//*********************************************************************************
//
// �w�iObj
//
//*********************************************************************************
//--�v���g�^�C�v�錾--//
void Reduced(LAND_SCAPE_OBJ* obj);
int check_behind_obj(OBJ2D* obj);
//---------------------------------------------------------------
// ���ʊ֐�
//---------------------------------------------------------------

void LAND_SCAPE_OBJ::Init() {
	clear();
	custom.scaleMode = SCALE_MODE::BOTTOMCENTER;
}
void LAND_SCAPE_OBJ::Update() {
	if (move)move(this);


	animation();
	Reduced(this);


	if (z < 0) {
		
		int alpha = custom.argb >> 24;
		if (check_behind_obj(this))
		{
			if (alpha >= BEHIND_OBJ_ALPHA) {
				alpha -= ALPHA_ACT;
			}
		}
		else {
			if (alpha >= 0xFF) {
				alpha & 0xFF;
				alpha | 0xFF;
			}
			else {
				alpha += ALPHA_ACT;
			}
		}
		custom.argb = (custom.argb & 0x00FFFFFF) | (alpha << 24);
	}
}

int check_behind_obj(OBJ2D* obj)
{
	if(Judge(obj, pPlayer)){ return TRUE; }
	Enemy** enemy = pEnemy_Manager->enemy;
	for (int i = 0; i < ENEMY_MAX; i++) {
		//���݃`�F�b�N
		if (!enemy[i])break;
		if (!enemy[i]->init_fg)continue;
		//���菈��
		if (Judge(obj, enemy[i])) {
			return TRUE;
		}
	}
	return FALSE;
}




void LAND_SCAPE_OBJ::Render() {
	if (!data)return;
	sz = pEnemy_Manager->get_sz(z);
	shader2D->SetValue("FPower", sz > 90 ? (180 - sz) / 90 : sz / 90);
	spr_data::Render(pos, data, &custom, custom.argb, shader2D, "depth");
	//line_rect(pos,V2(size.x * custom.scaleX, size.y * custom.scaleY), 0xFFFFFFFF, custom.scaleMode);
	//if(z < 0)line_rect(pos,V2(size.x, size.y), 0xFFFFFFFF, custom.scaleMode);

}



void Reduced(LAND_SCAPE_OBJ* obj) {
	int scale = obj->z / 10;
	//int ScrollX = pMAP->getScrollX();
	//int ScrollY = pMAP->getScrollY();
	V2 Scroll(pMAP->getScrollX(), pMAP->getScrollY());
	obj->pos = obj->wpos - Scroll;
	
	if (scale > -1) {
		obj->pos = obj->wpos - Scroll;
		switch (scale)
		{
		case 0:
		case 1:
			scale = 0;
			break;
		case 2:
		case 3:
			scale = 1;
			break;
		case 4:
		case 5:
			scale = 2;
			break;
		case 6:
		case 7:
			scale = 3;
			break;
		case 8:
		case 9:
			scale = 4;
			break;
		default:
			break;
		}
	}
	//�O�i
	else {
		switch (scale)
		{
		case -1://break;
		case -2://break;
		case -3://break;
		case -4://break;
		case -5:
			scale = -1;
			break;
		case -6://break;
		case -7://break;
		case -8://break;
		case -9:
			scale = -2;
			break;
		default:
			break;
		}
	}

	pLandScape->add_RenderObj(obj,scale);
}



//---------------------------------------------------------------
// �ʓ���֐�
//---------------------------------------------------------------

void MainBG(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:

	case BEGIN:
		
	default:
		break;
	}
}

void BG_pc(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::BOTTOMCENTER;
		//obj->animeData = spr_pc;
		obj->data = &spr_pc[0];
		obj->state = BEGIN;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		break;
	case BEGIN:
		obj->state = MOVE;
		break;
	case MOVE:
		break;
	case CLEAR:
		break;
	default:
		break;
	}

}
void BG_container(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::BOTTOMCENTER;

		obj->animeData = spr_container;
		obj->data = &spr_container[0];
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}

//�n���J�v�Z��
void BG_Capsule_l(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::BOTTOMCENTER;

		obj->data = &spr_Capsule_l;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		obj->size = V2(obj->data->dw/2, obj->data->dh/2);

		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}
void BG_Capsule_d(LAND_SCAPE_OBJ* obj) {//�_�[�N
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::BOTTOMCENTER;

		obj->data = &spr_Capsule_d;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}
//�󒆑�J�v�Z��
void BG_Fly_capsule_l(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;

		obj->data = &spr_Fly_capsule_l;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}
void BG_Fly_capsule_d(LAND_SCAPE_OBJ* obj) {//�_�[�N
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;
		obj->data = &spr_Fly_capsule_d;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}
void BG_Fly_capsule_m(LAND_SCAPE_OBJ* obj) {//���^��
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;
		obj->data = &spr_Fly_capsule_m;
		obj->size = V2(obj->data->dw/2,obj->data->dh / 2);

		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}

//����J�v�Z��
void BG_Break_capsule_u(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::BOTTOMCENTER;

		obj->data = &spr_Break_capsule_u;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
		obj->state = BEGIN;

		break;
	case BEGIN:

	default:
		break;
	}
}

//�t���Cmini�J�v�Z��
void BG_Fly_mini_capsule_l(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;
		obj->data = &spr_Fly_mini_capsule_l;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
		obj->state = BEGIN;

		break;
	case BEGIN:

	default:
		break;
	}

}
void BG_Fly_mini_capsule_d(LAND_SCAPE_OBJ* obj) {//�_�[�N
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;

		obj->data = &spr_Fly_mini_capsule_d;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
		obj->state = BEGIN;

		break;
	case BEGIN:

	default:
		break;
	}

}
//�t���Cmini���^���J�v�Z��
void BG_Fly_mini_capsule_m(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;

		obj->data = &spr_Fly_mini_capsule_m;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		obj->state = BEGIN;

		break;
	case BEGIN:

	default:
		break;
	}

}
//�n��mini�J�v�Z��
void BG_Mini_capsule_l(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::BOTTOMCENTER;

		obj->data = &spr_Mini_capsule_l;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		obj->state = BEGIN;

		break;
	case BEGIN:

	default:
		break;
	}

}
void BG_Mini_capsule_d(LAND_SCAPE_OBJ* obj) {//�_�[�N
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::BOTTOMCENTER;

		obj->data = &spr_Mini_capsule_d;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
		obj->state = BEGIN;

		break;
	case BEGIN:

	default:
		break;
	}

}

//�f�B�X�v���C
void BG_Display_a(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;
		obj->data = &spr_Display_a;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);

		obj->state = BEGIN;
		break;
	case BEGIN:
	default:
		break;
	}
}
void BG_Display_b(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;

		obj->data = &spr_Display_b;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
		obj->state = BEGIN;
		break;
	case BEGIN:
	default:
		break;
	}
}
void BG_Display_c(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;

		obj->data = &spr_Display_c;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
		obj->state = BEGIN;
		break;
	case BEGIN:
	default:
		break;
	}
}
void BG_Display_d(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->custom.scaleMode = SCALE_MODE::CENTER;

		obj->data = &spr_Display_d;
		obj->size = V2(obj->data->dw / 2, obj->data->dh / 2);
		obj->state = BEGIN;
		break;
	case BEGIN:
	default:
		break;
	}
}