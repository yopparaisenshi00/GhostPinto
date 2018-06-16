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
Number combo;		//�R���{
Number gametimer;	//�Q�[���^�C�}�[
Number gametimer2;	//�Q�[���^�C�}�[2
Number crushnum;	//���j��
Number crushnum2;	//���j�ڕW��
Number exorcisetimer; //��̓^�C�}�[


SPR_DATA ui_data[] = {
	{ spr_data::UI6,  0,190,  120,40,  0,0 },//SCORE
	{ spr_data::UI6,  0,125,  120,40,  0,0 },//COMBO
	{ spr_data::UI6,  0,250,  120,40,  0,0 },//NORMA�@������������������������������������������������������������������������
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
	score.numImage = new iex2DObj("DATA\\Public\\number.png");
	combo.numImage = new iex2DObj("DATA\\Public\\number.png");
	gametimer.numImage = new iex2DObj("DATA\\Public\\number.png");
	gametimer2.numImage = new iex2DObj("DATA\\Public\\number.png");
	crushnum.numImage = new iex2DObj("DATA\\Public\\number.png");
	crushnum2.numImage = new iex2DObj("DATA\\Public\\number.png");
	exorcisetimer.numImage = new iex2DObj("DATA\\Public\\number.png");


	score.SetSize(32);			//�X�R�A�����T�C�Y�ݒ�
	combo.SetSize(32);			//�R���{�����T�C�Y�ݒ�
	gametimer.SetSize(64);		//�Q�[���^�C�}�[ (��2�P�^)�����T�C�Y�ݒ�
	gametimer2.SetSize((int)(64 * 0.6f));	//�Q�[���^�C�}�[2(��2�P�^)�����T�C�Y�ݒ�
	crushnum.SetSize((int)(64 * 0.6f));		//���j�������T�C�Y�ݒ�
	crushnum2.SetSize((int)(64 * 0.6f));		//���j�������T�C�Y�ݒ�
	exorcisetimer.SetSize((int)(64 * 0.6f));	//��̓^�C�}�[�T�C�Y�ݒ�

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

void Number::Update(int timer) {
	score.SetNum(pScore->getScore(), 5);			//�X�R�A����
	combo.SetNum(pScore->getCombo(), 5);			//�R���{����
	combo.AddScale();							//�R���{���Z���̊g��\��	
	if ((timer / 60)>10) gametimer_argb = 0xFFFFFFFF; //��
	else gametimer_argb = 0xFFFF0000; //10�b�����Ȃ��
	gametimer.SetNum(timer / 60, 2);				//�Q�[���^�C�}�[ (��2�P�^)����
	gametimer2.SetNum(timer % 60, 2);			//�Q�[���^�C�}�[2(��2�P�^)����
	crushnum.SetNum(pScore->getKill_num(), 2);	//���j������
	crushnum2.SetNum(50, 2);	//���j������
								//				 ���X�e�[�W�ɉ����ĕύX
	exorcisetimer.SetNum(pFrame->exorciseDwon_timer / 60 + 1, 1);	//��̓^�C�}�[����
	n_timer = timer;
}


void Number::Render() {
	score.Render(790, 60, 5);								//�X�R�A�`��
	//combo.Render2(580, 130, pScore->getCombo());			//�R���{�`��
	gametimer.Render3(400, 15, 2, gametimer_argb);			//�Q�[���^�C�}�[ (��2�P�^)�`��
	gametimer2.Render3(400 + 125, 39, 2, gametimer_argb);	//�Q�[���^�C�}�[2(��2�P�^)�`��
	crushnum.Render(775, 150, 2);								//���j���`��
	crushnum2.Render(875, 150, 2);							//���j���`��
	if (pFrame->exorciseDwon_timer>0) {					//��̓^�C�}�[
		exorcisetimer.Render(450, 150, 1);					//��̓^�C�}�[�`��
	}
	spr_data::Render(V2(750, 20), &ui_data[0]);	//�@SCORE
	//spr_data::Render(V2(550,100),&ui_data[1]);	//�@COMBO
	spr_data::Render(V2(750, 100), &ui_data[2]);	//�@���j��
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
void Number::AddScale() {
	after = pScore->getCombo(); //���̃R���{��
	if (after>front) { //�R���{����������
		custom.scaleMode = CENTER;
		//custom.scaleY = custom.scaleX = rand() % 40/100.0f + 1; //�@1�{(0.0�`0.4)�{
		custom.scaleY = custom.scaleX = 1.8f; //�@1.4�{
	}
	else { //�R���{�������Ă��Ȃ�������
		custom.scaleMode = CENTER;
		custom.scaleY = custom.scaleX = 1.0f;
	}
	front = after; //���̃R���{����O�̃R���{���Ƃ��ĕۑ�

}


//���l�`��֐�(�����������`��)
void  Number::Render2(int x, int y, int num)
{
	//�\������������
	int digit_max = 0;
	for (int i = 0; i<5; i++) {
		digit_max++;
		if (num<10) break;
		num /= 10;
	}

	x += digitDispSize * digit_max;  //  ��̈ʂ���`�悷��̂ŉE�[�ɂ��炷

	for (int i = 0; i<digit_max; i++)
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

	for (int i = 0; i<digit_max; i++)
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

	for (int i = 0; i<digit_max; i++)
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
