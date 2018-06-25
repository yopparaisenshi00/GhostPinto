//*****************************************************************************
//
//			��������
//
//*****************************************************************************
#include "iextreme.h"
#include "system\System.h"
#include "Game.h"
#include "Player.h"
#include "Frame.h"
#include "Number.h"
#include "sceneMain.h"


Number score;		//�X�R�A
Number gametimer;	//�Q�[���^�C�}�[
Number gametimer2;	//�Q�[���^�C�}�[2
Number crushnum;	//���j��
Number crushnum2;	//���j�ڕW��
Number exorcisetimer; //��̓^�C�}�[
Number eval_addscore;	//�R���{���U���g�p�B�e�X�R�A
Number eval_combo;		//�R���{���U���g�p�R���{��
Number eval_justpinto;	//�R���{���U���g�p�W���X�g�s���g
Number eval_total;		//�R���{���U���g�pTOTAL


SPR_DATA ui_data[] = {
	{ spr_data::UI6,  0,190,  120,40,  0,0 },//SCORE
	{ spr_data::UI6,  0,250,  120,40,  0,0 },//NORMA
	{ spr_data::UI6,  0,190,  120,40,  0,0,  (int)(120*0.8f),(int)(40*0.8f) },//COMBORESULT------
	{ spr_data::UI6,  0,190,  120,40,  0,0,  (int)(120*0.8f),(int)(40*0.8f) },//TIMETOSHOOT
	{ spr_data::UI6,  0,190,  120,40,  0,0,  (int)(120*0.8f),(int)(40*0.8f) },//COMBO COUNT
	{ spr_data::UI6,  0,190,  120,40,  0,0,  (int)(120*0.8f),(int)(40*0.8f) },//JUST COUNT
	{ spr_data::UI6,  0,190,  120,40,  0,0,  (int)(120*0.8f),(int)(40*0.8f) },//TOTAL SCORE
};


//static SPR_DATA anime_Number_data[] = {
//	SPR_DATA{spr_data::Ext, 64*0, 0, 64, 64, -32, -32}, //0
//	SPR_DATA{spr_data::Ext, 64*1, 0, 64, 64, -32, -32}, //1
//	SPR_DATA{spr_data::Ext, 64*2, 0, 64, 64, -32, -32}, //2
//	SPR_DATA{spr_data::Ext, 64*3, 0, 64, 64, -32, -32}, //3
//	SPR_DATA{spr_data::Ext, 64*4, 0, 64, 64, -32, -32}, //4
//	SPR_DATA{spr_data::Ext, 64*0,64, 64, 64, -32, -32}, //5
//	SPR_DATA{spr_data::Ext, 64*1,64, 64, 64, -32, -32}, //6
//	SPR_DATA{spr_data::Ext, 64*2,64, 64, 64, -32, -32}, //7
//	SPR_DATA{spr_data::Ext, 64*3,64, 64, 64, -32, -32}, //8
//	SPR_DATA{spr_data::Ext, 64*4,64, 64, 64, -32, -32}, //9
//	SPR_DATA{			-1,	   0, 0,  0,  0,   0,   0}
//};


Number::Number() {
	//score.data = &anime_Number_data[0];
	numImage = new iex2DObj("DATA\\Public\\number.png");
	score.numImage = numImage;
	gametimer.numImage = numImage;
	gametimer2.numImage = numImage;
	crushnum.numImage = numImage;
	crushnum2.numImage = numImage;
	exorcisetimer.numImage = numImage;
	eval_addscore.numImage = numImage;
	eval_combo.numImage = numImage;
	eval_justpinto.numImage = numImage;
	eval_total.numImage = numImage;

	score.SetSize(32);			//�X�R�A�����T�C�Y�ݒ�
	gametimer.SetSize(64);		//�Q�[���^�C�}�[ (��2�P�^)�����T�C�Y�ݒ�
	gametimer2.SetSize((int)(64 * 0.6f));	//�Q�[���^�C�}�[2(��2�P�^)�����T�C�Y�ݒ�
	crushnum.SetSize((int)(64 * 0.6f));		//���j�������T�C�Y�ݒ�
	crushnum2.SetSize((int)(64 * 0.6f));		//���j�������T�C�Y�ݒ�
	exorcisetimer.SetSize((int)(64 * 0.6f));	//��̓^�C�}�[�T�C�Y�ݒ�
	eval_addscore.SetSize((int)(32 * 0.9f));
	eval_combo.SetSize((int)(32 * 0.9f));
	eval_justpinto.SetSize((int)(32 * 0.9f));
	eval_total.SetSize((int)(32 * 0.9f));
	
	//score.custom.clear();
	//gametimer.custom.clear();
	//gametimer2.custom.clear();
	
	//score.custom.scaleMode = CENTER;
	//gametimer.custom.scaleMode = CENTER;
	//gametimer2.custom.scaleMode = CENTER;
	
	//score.custom.scaleY = score.custom.scaleX = 1;
	//gametimer.custom.scaleY = gametimer.custom.scaleX = 1;
	//gametimer.custom.scaleX = gametimer.custom.scaleY = 1;

}

Number::~Number() {

}

void Number::Init() {

}



//�]���p�֐�
void Number::eval_agree() {
	eval.p_pos.x = pPlayer->pos.x; //�v���C���[��x���W
	eval.p_pos.y = pPlayer->pos.y; //�v���C���[��y���W
	//�v���C���[���E���Ɋ���Ă�����(����)
	if ( (eval.p_pos.x>(SCREEN_WIDTH-300)) && (eval.p_pos.y>(SCREEN_HEIGHT-160)) ) {
		eval.result_pos =	V2(eval.p_pos.x-260,eval.p_pos.y-170);
		eval.time_pos =		V2(eval.p_pos.x-260,eval.p_pos.y-130);
		eval.combo_pos =	V2(eval.p_pos.x-260,eval.p_pos.y-90);
		eval.just_pos =		V2(eval.p_pos.x-260,eval.p_pos.y-50);
		eval.total_pos =	V2(eval.p_pos.x-260,eval.p_pos.y-10);
	}
	//�v���C���[���E�Ɋ���Ă�����(����)
	else if ( eval.p_pos.x>(SCREEN_WIDTH-300) ) {
		eval.result_pos =	V2(eval.p_pos.x-250,eval.p_pos.y+0);
		eval.time_pos =		V2(eval.p_pos.x-250,eval.p_pos.y+40);
		eval.combo_pos =	V2(eval.p_pos.x-250,eval.p_pos.y+80);
		eval.just_pos =		V2(eval.p_pos.x-250,eval.p_pos.y+120);
		eval.total_pos =	V2(eval.p_pos.x-250,eval.p_pos.y+160);
	}
	//�v���C���[�����Ɋ���Ă�����(�E��)
	else if ( eval.p_pos.y>(SCREEN_HEIGHT-160) ) {
		eval.result_pos =	V2(eval.p_pos.x+60,eval.p_pos.y-170);
		eval.time_pos =		V2(eval.p_pos.x+60,eval.p_pos.y-130);
		eval.combo_pos =	V2(eval.p_pos.x+60,eval.p_pos.y-90);
		eval.just_pos =		V2(eval.p_pos.x+60,eval.p_pos.y-50);
		eval.total_pos =	V2(eval.p_pos.x+60,eval.p_pos.y-10);
	}
	//��{�v���C���[��(�E��)
	else {
		eval.result_pos =	V2(eval.p_pos.x+60,eval.p_pos.y+0);
		eval.time_pos =		V2(eval.p_pos.x+60,eval.p_pos.y+40);
		eval.combo_pos =	V2(eval.p_pos.x+60,eval.p_pos.y+80);
		eval.just_pos =		V2(eval.p_pos.x+60,eval.p_pos.y+120);
		eval.total_pos =	V2(eval.p_pos.x+60,eval.p_pos.y+160);
	}



	if ( pScore->getcombotimer()>=COMBO_TIME/* && (pScore->getCombo()>5) */ ) {
		eval.addscore = pScore->getAddscore();						//�ۑ�
		eval.combo = pScore->getCombo();							//�ۑ�
		eval.just = pScore->getEval_justpinto();					//�ۑ�
		eval.total = eval.addscore+eval.combo*200+eval.just*100;	//TOTAL�v�Z

		eval_addscore.SetNum(eval.addscore,3);	//�B�e�X�R�A�i�f���Ă�ԑ�������X�R�A�j
		eval_combo.SetNum(eval.combo,2);		//�|������
		eval_justpinto.SetNum(eval.just,2);		//�W���X�g�s���g�����߂���
		eval_total.SetNum(eval.total,4);		//TOTAL

		eval.flg = true;
	}

	if ( eval.flg == true ) eval.timer++;
	//�ړ�����
	//
	//
	//
	if ( eval.timer>60 ) {
		eval.flg = false;
		eval.timer = 0;
		pScore->addscore = 0;
		pScore->eval_justpinto = 0;
	}
}


void Number::Update(int timer) {
	//score.AddScale(pScore->getScore(),1.25f);
	score.SetNum(pScore->getScore(), 5);		//�X�R�A����
	if ((timer / 60)>10) gametimer_argb = 0xFFFFFFFF;	//��
	else gametimer_argb = 0xFFFF0000;					//10�b�����Ȃ��
	//gametimer.AddScale((int)(timer/60),1.5f);
	//gametimer2.AddScale((int)(timer/60),1.5f);
	gametimer.SetNum(timer / 60, 2);			//�Q�[���^�C�}�[ (��2�P�^)����
	gametimer2.SetNum(timer % 60, 2);			//�Q�[���^�C�}�[2(��2�P�^)����
	crushnum.AddScale(pScore->getKill_num(),1.7f);	//���j�����Z���̊g��\��
	crushnum.SetNum(pScore->getKill_num(), 2);	//���j������
	crushnum2.SetNum(50, 2);					//���j������(�X�e�[�W�ɉ����ĕύX)
	exorcisetimer.SetNum(pFrame->exorciseDwon_timer / 60 + 1, 1);	//��̓^�C�}�[����
	eval_agree();
	n_timer = timer;
}


void Number::Render() {
	//score.Render(780, 35, 5);								//�X�R�A�`��
	score.Render(790, 60, 5);								//�X�R�A�`��
	gametimer.Render3(400, 15, 2, gametimer_argb);			//�Q�[���^�C�}�[ (��2�P�^)�`��
	gametimer2.Render3(400 + 125, 39, 2, gametimer_argb);	//�Q�[���^�C�}�[2(��2�P�^)�`��
	crushnum.Render(770, 124, 2);							//���j���`��
	crushnum2.Render(875, 150, 2);							//���j���`��
	if (pFrame->exorciseDwon_timer>0) {						//��̓^�C�}�[
		exorcisetimer.Render(450, 150, 1);					//��̓^�C�}�[�`��
	}
	spr_data::Render(V2(750, 20), &ui_data[0]);		//SCORE
	spr_data::Render(V2(750, 100), &ui_data[1]);	//���j��

	if ( eval.flg ) {
		eval_addscore.Render(	eval.time_pos.x  +120,  eval.time_pos.y,3);
		eval_combo.Render(		eval.combo_pos.x +120,  eval.combo_pos.y,2);
		eval_justpinto.Render(	eval.just_pos.x  +120,  eval.just_pos.y,2);
		eval_total.Render(		eval.total_pos.x +120,  eval.total_pos.y,4);
		spr_data::Render(eval.result_pos,&ui_data[2]);	//�R���{���U���g------------------------
		spr_data::Render(eval.time_pos,&ui_data[3]);	//TIMETOSHOOT�F�B�e�X�R�A�i�f���Ă�ԑ�������X�R�A�j
		spr_data::Render(eval.combo_pos,&ui_data[4]);	//COMBO COUNT�F�|������
		spr_data::Render(eval.just_pos,&ui_data[5]);	//JUST COUNT �F�W���X�g�s���g�����߂���
		spr_data::Render(eval.total_pos,&ui_data[6]);	//TOTAL SCORE�F�R���{�ŉ҂������_
	}
}







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	�֐�
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//�\�������T�C�Y�ύX�֐�
void Number::SetSize(int size)
{
if (size > 0)	digitDispSize = size;
if (size < 0)	digitDispSize = DIGIT_SIZE;
}


//���l�ݒ�֐�
void  Number::SetNum(int num, int digit_max)
{
	for (int i = 0; i < digit_max; i++)
	{
		digit[i].val = num % 10;	//  ��̈ʂ𒊏o
		digit[i].x = 0;
		digit[i].y = 0;
		digit[i].w = digit[i].h = 1;
		digit[i].timer = 0;
		num /= 10;					//  ����1�V�t�g
	}
}


//���Z���̊g��\��
void Number::AddScale(int n, float scale) {
	after = n; //���̐�
	if (after>front) { //�O�̐��Ɣ�ׂđ�������
		custom.scaleMode = BOTTOMCENTER;
		custom.scaleX = custom.scaleY = scale; //�g��
	}
	else { //�ς���ĂȂ�������
		custom.scaleMode = BOTTOMCENTER;
		if ( custom.scaleX>1.0f ) custom.scaleY = custom.scaleX -= 0.2f;
		else custom.scaleY = custom.scaleX = 1.0f;
	}
	front = after; //���̐���O�̐��Ƃ��ĕۑ�

}


//���l�`��֐�(�����������`��)
void  Number::Render2(int x, int y, int num)
{
	int _num = num;
	int digit_max = 0;

	while ( _num>=10 ) { //10�ȏ�Ȃ�
		_num /= 10;		//10�Ŋ�����
		digit_max++;		//x�ʒu���炵�J�E���g
	}

	x += digitDispSize * digit_max;  //  ��̈ʂ���`�悷��̂ŉE�[�ɂ��炷

	for (int i = 0; i < digit_max; i++)
	{
		x -= digitDispSize;
		int  sx = (digit[i].val % NUM_DIGIT_1LINE) * DIGIT_SIZE;
		int  sy = (digit[i].val / NUM_DIGIT_1LINE) * DIGIT_SIZE;

		numImage->customRender(
			x + digit[i].x - 3, y + digit[i].y,														//�`��ʒux,�`��ʒuy
			custom.scaleX*digitDispSize*digit[i].w, custom.scaleY*digitDispSize*digit[i].h,		//�`�敝x,�`�敝y
			sx, sy,
			DIGIT_SIZE, DIGIT_SIZE,														//�ؔ��ʒux,�ؔ��ʒuy, �����T�C�Y,�����T�C�Y
			custom.angle, custom.centRotate, custom.centX, custom.centY, RS_ALPH,
			custom.argb, custom.reflectX, custom.scaleMode);
	}
}


//���l�`��֐�(�w�蕪�`��)           (digitmax = �\��������)
void  Number::Render(int x, int y, int digit_max)
{
	x += digitDispSize * digit_max;  //  ��̈ʂ���`�悷��̂ŉE�[�ɂ��炷

	for (int i = 0; i < digit_max; i++)
	{
		x -= digitDispSize;
		int  sx = (digit[i].val % NUM_DIGIT_1LINE) * DIGIT_SIZE;
		int  sy = (digit[i].val / NUM_DIGIT_1LINE) * DIGIT_SIZE;

		//if (i == 2) x -= digitDispSize / 2;		//2�P�^�ڂŊԂ�������	���R���}�̍ۂɎg���H

		numImage->customRender(
			x + digit[i].x - 3, y + digit[i].y,														//�`��ʒux,�`��ʒuy
			custom.scaleX*digitDispSize*digit[i].w, custom.scaleY*digitDispSize*digit[i].h,		//�`�敝x,�`�敝y
			sx, sy,
			DIGIT_SIZE, DIGIT_SIZE,														//�ؔ��ʒux,�ؔ��ʒuy, �����T�C�Y,�����T�C�Y
			custom.angle, custom.centRotate, custom.centX, custom.centY, RS_ALPH,
			custom.argb, custom.reflectX, custom.scaleMode);
	}
	//numImage->Render(		//�F
	//	x + 57, y,
	//	digitDispSize, digitDispSize,
	//	0 * 64, 2 * 64, DIGIT_SIZE, DIGIT_SIZE);
}


//���l�`��֐�(�w�蕪�`��+color)           (digitmax = �\��������)
void  Number::Render3(int x, int y, int digit_max, D3DCOLOR argb)
{
	x += digitDispSize * digit_max;  //  ��̈ʂ���`�悷��̂ŉE�[�ɂ��炷

	for (int i = 0; i < digit_max; i++)
	{
		x -= digitDispSize;
		int  sx = (digit[i].val % NUM_DIGIT_1LINE) * DIGIT_SIZE;
		int  sy = (digit[i].val / NUM_DIGIT_1LINE) * DIGIT_SIZE;

		numImage->customRender(
			x + digit[i].x - 3, y + digit[i].y,														//�`��ʒux,�`��ʒuy
			custom.scaleX*digitDispSize*digit[i].w, custom.scaleY*digitDispSize*digit[i].h,		//�`�敝x,�`�敝y
			sx, sy,
			DIGIT_SIZE, DIGIT_SIZE,														//�ؔ��ʒux,�ؔ��ʒuy, �����T�C�Y,�����T�C�Y
			custom.angle, custom.centRotate, custom.centX, custom.centY, RS_ALPH,
			argb, custom.reflectX, custom.scaleMode);
	}
}

//���l�`��֐�(�w���l�`��(num) + �w�蕪�`�� + color)           (digitmax = �\��������)
void  Number::RenderFree(int x, int y, int num, int digit_max, int _digitDispSize, D3DCOLOR argb = 0xFFFFFFFF)
{
	int Size = _digitDispSize;
	Number::tagDIGIT _digit[DIGIT_MAX];
	for (int i = 0; i < digit_max; i++)
	{
		_digit[i].val = num % 10;	//  ��̈ʂ𒊏o
		_digit[i].x = 0;
		_digit[i].y = 0;
		_digit[i].w = _digit[i].h = 1;
		_digit[i].timer = 0;
		num /= 10;					//  ����1�V�t�g
	}
	for (int i = 0; i < digit_max; i++) {
		x -= Size * i;
		int  sx = (_digit[i].val % NUM_DIGIT_1LINE) * DIGIT_SIZE;
		int  sy = (_digit[i].val / NUM_DIGIT_1LINE) * DIGIT_SIZE;

		numImage->customRender(
			x + _digit[i].x - 3, y + _digit[i].y,														//�`��ʒux,�`��ʒuy
			custom.scaleX*Size *_digit[i].w, custom.scaleY*Size *_digit[i].h,		//�`�敝x,�`�敝y
			sx, sy,
			DIGIT_SIZE, DIGIT_SIZE,														//�ؔ��ʒux,�ؔ��ʒuy, �����T�C�Y,�����T�C�Y
			custom.angle, custom.centRotate, custom.centX, custom.centY, RS_ALPH,
			argb, custom.reflectX, custom.scaleMode);
	}
}

