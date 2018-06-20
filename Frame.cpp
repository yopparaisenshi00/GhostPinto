#include "iextreme.h"
#include "Game.h"
#include "MAP.h"
#include "Frame.h"
#include "Player.h"
#include "Sound.h"
#include "sceneMain.h"

enum {
	pinto_s = spr_data::UI1,
	pinto_a = spr_data::UI2,
	flame_out = spr_data::UI3,
	pinto_l = spr_data::UI4,

};

enum {
	INIT,
	READY,
	MOVE,
};



//SPR_DATA spr_flame_out = { flame_out,0,0,960,540,-480,-270 };
SPR_DATA spr_flame_out = { flame_out,0,0,1024,540,-512,-270 };
SPR_DATA spr_pinto_l = { pinto_l,0,0,774,774,-774 / 2,-774 / 2 };



//SPR_DATA spr_pinto_l = { pinto_l,0,0,774,774,-774 / 2,-774 / 2 };
SPR_DATA spr_pinto_a2 = { pinto_a,0,0,128,128,-64,-64 };

SPR_DATA spr_exorcise_frame= { flame_out,1000,540,14,44,0,0 };


//SPR_DATA spr_Frame[] = {
//};

//Frame::Frame()
//{
//
//}
//
//Frame::~Frame()
//{
//
//}


void Frame::Init() {

	OBJ2D::clear();
	f_z = 0;
	lock_flg = false;
	sc_w = 0;
	sc_h = 0;
	angle = 0;
	axisx = 0;
	axisy = 0;
	exorcise = 0;
	f_timer = 0;
	exorciseDwon_flg = 0;
	exorciseDwon_timer = 0;

	argb = 0xFFFFFF00;	//��̓Q�[�W�_�ŗp
	old_exorcise = 0;	//��̓Q�[�W�_�ŗp
	flash_timer = 0;	//��̓Q�[�W�_�ŗp
	flash_flg = false;	//��̓Q�[�W�_�ŗp

	pinto_argb = 0xFFFFFFFF; //��
	multi_flg = false;
	out_argb = 0xFF000000; //��
	count = 0;
}

void Frame::Update() {
	//if (pPlayer->fear_flg) {
	//	state = 3;
	//	lock_flg = true;
	//}

	switch (state)
	{
	case INIT:
		pos = V2((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
		sc_w = 0;
		sc_h = 0;
		size = V2(240/2,160/2);
		exorcise = EXORCISE_MAX;

		old_exorcise = EXORCISE_MAX;
		flash_timer = 0;
		flash_flg = false;

		pinto_argb = 0xFFFFFFFF; //��

		state = MOVE;
		break;
	case MOVE:

		f_move();
		exorcise_Update();

		//�}���`�t�H�[�J�X����
		if (pFrame->multifocus_flg == true && multi_flg == false) {
			pinto_argb = 0xFFFF0000; //�Ԃɂ���
			multi_flg = true;
		}
		if (pFrame->multifocus_flg == false && multi_flg == true) {
			pinto_argb = 0xFFFFFFFF; //false�Ȃ甒�ɂ���
			multi_flg = false;
		}

		if (pFrame->multifocus_timer>0 && multi_flg == true) {
			if (pFrame->multifocus_timer % 12 == 0) { //15��ɕ�����(12�Ŋ������]�肪0�̎�)
				pinto_argb += 0x00001111; //���X�ɔ���
			}
		}


		///////////////////////////////////////////////////////////////////////////////////
		//frame_out(���g)����
		if (pPlayer->nodamage_timer > 150) { //�v���C���[���_���[�W���󂯂���(30f�̊�)
			if ((pPlayer->nodamage_timer % 8)<  4) out_argb = 0xFF000000;	//�_�ŏ���	���F
			if ((pPlayer->nodamage_timer % 8) >= 4) out_argb = 0xFFFF0000;	//			�ԐF
		}
		else out_argb = 0xFF000000; //���F
		///////////////////////////////////////////////////////////////////////////////////


		///////////////////////////////////////////////////////////////////////////////////
		//�U������
		if (pPlayer->s.old_nodamage == false && pPlayer->s.nodamage == true) { //�v���C���[���_���[�W���󂯂���
			Vib_Set(7, 1); //(�h�ꕝ,����)
			//s.old_nodamage=true (Player.cpp�ŏ���)
		}
		//if (pScore->getCombo()>2) { //
		//	Vib_Set(7, 1); //(�h�ꕝ,����)
		//}

		pD_TEXT->set_Text(V2(600, 200), "PL_trg_t", lockPinto_trg == true, 0xFFFFFFFF);
		pD_TEXT->set_Text(V2(600, 216), "PL_trg_f", lockPinto_trg == false, 0xFFFFFFFF);
		pD_TEXT->set_Text(V2(600, 232), "PL_trg_02", lockPinto_trg == 0x02, 0xFFFFFFFF);
		pD_TEXT->set_Text(V2(600, 248), "PL_trg_01", lockPinto_trg == 0x01, 0xFFFFFFFF);


		Vib_Update();
		///////////////////////////////////////////////////////////////////////////////////

		break;
	default:
		break;
	}

}

//�����֐�
D3DCOLOR Light(D3DCOLOR color) {
	if ( color>=0x11FFFFFF ) color -= 0x03000000;
	else color = 0x00FFFFFF;
	return color;
}



void Frame::Render() {

	//iexPolygon::Rect(160,30,exorcise*2,30,0,0xFFFFFF00,0); //��̓Q�[�W�`��(��ɂ��炵��)
	//iexPolygon::Rect(20,180,30,exorcise*2,0,0xFFFFFF00,0); //��̓Q�[�W�`��(�c ��sceneMain�ύX)
	if (!pFrame->exorciseDwon_flg) {
		iexPolygon::Rect((int)(pPlayer->pos.x + 30), (int)((pPlayer->pos.y-40) + (50-exorcise/2)), 10, (int)(exorcise/2), 0, argb, 0); //��̓Q�[�W�`��(�v���C���[�E��)
		//spr_data::Render(V2((int)(pPlayer->pos.x + 30),(int)(pPlayer->pos.y-40)), &spr_exorcise_frame); //��̓Q�[�W�g
		//iexPolygon::Rect((int)(pPlayer->pos.x + 30), (int)((pPlayer->pos.y - 40) + (200 - exorcise * 2)), 10, (int)(exorcise / 2), 0, argb, 0); //��̓Q�[�W�`��(�v���C���[�E��)
		//iexPolygon::Rect((int)pos.x, (int)pos.y, 1, 1, 0, 0xFFFF0000);
	}

	if ( multifocus_flg ) {
		iexPolygon::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, light_argb, 0); //��
		light_argb = Light(light_argb);	//�}���`�t�H�[�J�X���g�����甭��
	}
	else light_argb = 0xCCFFFFFF;							//�}���`�t�H�[�J�X���g�����甭��

	spr_data::Render(V2((SCREEN_WIDTH / 2) + vibX, (SCREEN_HEIGHT / 2)), &spr_pinto_l, pinto_argb, pFrame->Get_f_z() * 0.25f);

	spr_data::Render(V2((SCREEN_WIDTH / 2) + vibX, (SCREEN_HEIGHT / 2)), &spr_flame_out, out_argb, 0);
	if (pFrame->exorciseDwon_flg) {
		iexPolygon::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0x3F000000, 0);
	}

}

void Frame::R_Update() {
	//if (pPlayer->fear_flg) {
	//	state = 3;
	//	lock_flg = true;
	//}

	switch (state)
	{
	case INIT:
		pos = V2((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
		sc_w = 0;
		sc_h = 0;
		size = V2(240 / 2, 160 / 2);
		exorcise = EXORCISE_MAX;
		state = MOVE;
		break;
	case MOVE:
		f_move();
		exorcise_Update();
		pintoSize = PINTOMODE_READY;

		break;
	default:
		break;
	}
}



void Frame::SetMain() {
	pMAP->SetCenter((OBJ2D*)(this));
	state = 2;
}


float normalizeAngle(float radian)
{
	while (radian >  D3DX_PI) radian -= D3DX_PI * 2;
	while (radian < -D3DX_PI) radian += D3DX_PI * 2;
	return radian;
}

void Frame::f_move() {

	float old_axisx = axisx;
	float old_axisy = axisy;
	axisx = (float)(KEY_Get(KEY_AXISX2));
	axisy = (float)(KEY_Get(KEY_AXISY2));
	if (!move_flg) {
		if (axisx < PINTO_SENSITIVE && axisx > -PINTO_SENSITIVE && axisy < PINTO_SENSITIVE && axisy > -PINTO_SENSITIVE) 
		{ 
			
			if (f_timer++ > EXORCISE_AUTOHEEL_TIME) {
				f_timer &= 0x0000FFFF;
				add_Exorcise(EXORCISE_AUTOHEEL);
			}
			move_flg = false; 		}
		else move_flg = true;
	}
	else {
		//if (axisx < PINTO_SENSITIVE && axisx > -PINTO_SENSITIVE&& 
		//	axisy < PINTO_SENSITIVE && axisy > -PINTO_SENSITIVE) 
		//{ 
		f_timer &= 0;
		if (axisy < PINTO_SENSITIVE && axisy > -PINTO_SENSITIVE)
		{

			move_flg = false;
			return;
		}

		f_spd = 0;
		if(PINTO_X_USE)
			f_spd += axisx * 0.001f;				//�p�b�h��1�`-1�ɕϊ�
		if(PINTO_Y_USE)
			f_spd += axisy * 0.001f;				//�p�b�h��1�`-1�ɕϊ�
		
		f_spd *= PINTO_ACT;
		f_z += f_spd;
		while(f_z < -PINTO_MAX)f_z += PINTO_MAX * 2;
		while(f_z > PINTO_MAX) f_z += -PINTO_MAX * 2;

		
	}

	if (multifocus_flg) {
		if (multifocus_timer > 0) {
			multifocus_timer--;
		}
		else
		{
			multifocus_flg = false;
		}
	}
	else pintoSize = PINTOMODE_DEFAULT;

	
}
static float cadd = 0;

//----------------------------------------------------------------------------------------------------
//�@��̓f�[�^�X�V
//----------------------------------------------------------------------------------------------------
void Frame::exorcise_Update() {

	switch (exorciseDwon_flg)
	{
	case true:
		if (exorciseDwon_timer-- < 0) { //��̓^�C�}�[
			exorciseDwon_timer = 0;
			exorciseDwon_flg = false;
			exorcise = EXORCISE_MAX;
			IEX_PlaySound(SE_RETURN, FALSE); //��͕�����SE�@

		}
		break;
	case false:
		axisy = (float)(KEY_Get(KEY_AXISY2));				// �X�e�B�b�N���擾
		if (0 > axisy) { axisy *= -1; }				// ���̒l�Ȃ�t�]
		if (axisy < 100)axisy = 0;					// �X�e�B�b�N���x�ȉ��Ȃ�0
		axisy *= 0.001f;							// �X�e�B�b�N��� 0�`1�ɐ��K�� 
		{
			pD_TEXT->set_Text(V2(400, 200), "axisy", axisy, 0xFFFFFF00);

			float Ex = (PINTO_COST_S)*(axisy);//  
			pD_TEXT->set_Text(V2(400, 220), "Ex/s", Ex * 60, 0xFFFFFF00);

			//if (0 > Ex) { Ex *= -1; }
			exorcise -= Ex;

		}
		//��̓_�E���`�F�b�N(UI�ꎞ�폜)
		if (0 >= exorcise) {						//��͂�0�ȉ��Ȃ��̓_�E��
			if (exorcise)exorcise = 0;				//��͏�����
			exorciseDwon_timer = PINTO_DOWN_TIME;	//�_�E���^�C���ݒ�
			exorciseDwon_flg = true;				//��̓_�E���t���O
			IEX_PlaySound(SE_LOSS, FALSE);			//��͂�0��SE

		}
		break;
	}

	//******************************************************************************************************
	//��̓Q�[�W�_��
	if (exorcise!=EXORCISE_MAX &&
		old_exorcise != (exorcise-EXORCISE_AUTOHEEL)) flash_flg = true; //��̓Q�[�W��MAX�ł͂Ȃ�,���R�񕜈ȊO�̕ω��������

	if (flash_flg == true) {
		if ( exorcise<(EXORCISE_MAX/3) && flash_timer++<60 ) {
			if ((flash_timer % 14) <  7) argb = 0xFFff765e;	//�_�ŏ���	�ԐF
			if ((flash_timer % 14) >= 7) argb = 0xFFFFFF00;	//�@		���F
		}
		else if (flash_timer++<60) { //�w��b���̊�
			if ((flash_timer % 14) <  7) argb = 0xFFFFFFFF;	//�_�ŏ���	���F
			if ((flash_timer % 14) >= 7) argb = 0xFFFFFF00;	//�@		���F
		}
		else { //�w��b���o������
			argb = 0xFFFFFF00; //���F
			flash_timer = 0;
			flash_flg = false;
		}
	}
	old_exorcise = exorcise; //�ω��O�̗�̓Q�[�W��ۑ�
	//******************************************************************************************************


	old_exorcise = exorcise;


	//UI�_�E���^�C�}�[�X�V
	//pD_TEXT->set_Text(V2(400, 260), "multiF_timer", multifocus_timer, 0xFFFFFFFF);
	//pD_TEXT->set_Text(V2(400, 280), "multiF_flg", (int)multifocus_flg, 0xFFFFFFFF);

	//pD_TEXT->set_Text(V2(400, 240), "exorcise", exorcise,0xFFFFFF00);

}

//----------------------------------------------------------------------------------------------------
//  �s���g�擾,�s���g�T�C�Y�擾
//----------------------------------------------------------------------------------------------------
float Frame::Get_f_z() {
	return f_z;
}
float Frame::getPintoSize() {
	return pintoSize;
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
//  ��͉�
//----------------------------------------------------------------------------------------------------
void Frame::add_Exorcise(float add) {
	///////////////////////////////////
	//
	//
	cadd = add;
	//
	////////////////////////////////////

	if (exorciseDwon_flg)return;
	exorcise += add ;
	if (100 < exorcise)exorcise = EXORCISE_MAX;
	if ( 0 > exorcise)exorcise = 0;

}

//----------------------------------------------------------------------------------------------------
//  �}���`�t�H�[�J�X�g�p�A�ݒ�
//----------------------------------------------------------------------------------------------------
void Frame::use_Multifocus(int power) {
	multifocus_timer = MALTIFOCUS_TIME;
	multifocus_flg = true;
	IEX_PlaySound(SE_MULCH_FIRE, FALSE); //�}���`�t�H�[�J�X�g�p��

	switch (power)
	{
	case 1:
		pintoSize = PINTOMODE_MULTIFOCUSLV1;
		break;
	case 2:
		pintoSize = PINTOMODE_MULTIFOCUSLV2;
		break;
	case 3:
		pintoSize = PINTOMODE_MULTIFOCUSLV3;
		break;
	default:
		break;
	}
}
#define USE_PINTOLOCK (20)
//----------------------------------------------------------------------------------------------------
//  �s���g���b�N�g�p�A�ݒ�
//----------------------------------------------------------------------------------------------------
void Frame::use_lockPinto() {
	if(!exorciseDwon_flg){
		exorcise -= USE_PINTOLOCK;
		lockPinto_trg = true;
	}
}



//*****************************************************************************
//		�U��
//*****************************************************************************

void Frame::Vib_Set(float width, int timer) {
	vibWidth = width;		//-width �` +width�̕��ŗh���
	vibTimer = 0;
	vibTimerMax = timer;
}


void Frame::Vib_Update() {
	//�U�����p�������̃`�F�b�N
	if (vibTimer >= vibTimerMax)
	{
		vibTimer = vibTimerMax;
		vibX = vibY = 0.0f;		//���ꕝ�����Z�b�g
		return;
	}

	//���ꕝ�̌v�Z
	vibX = ((rand() % 201) - 100)*0.01f * vibWidth;
	vibY = ((rand() % 201) - 100)*0.01f * vibWidth;
	vibTimer++;

}

