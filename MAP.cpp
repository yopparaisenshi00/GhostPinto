//******************************************************************************
//
//
//		MAP�N���X
//
//
//******************************************************************************
#include "iextreme.h"
#include "Game.h"
#include "Player.h"
#include "Frame.h"
#include "Enemy.h"
#include "Effect.h"
#include "BGFG.h"
#include "MAP.h"

// Commit test

enum {
	normal = 0,//�^�[�Q�b�g�f�[�^�Q��
	center_lock,//���݂̍��W�ɌŒ�
};

#define BGCODE_BLANK		0x0000

#define SCROLL_CENTER_W (480)
#define SCROLL_CENTER_H (270)

#define SCROLL_L (scrollCenter->sc_w)//�X�N���[���J�n�ʒu
#define SCROLL_R (scrollCenter->sc_w)//�X�N���[���J�n�ʒu
//#define SCROLL_U (scrollCenter->sc_h)//�X�N���[���J�n�ʒu
//#define SCROLL_D (scrollCenter->sc_h)//�X�N���[���J�n�ʒu
//#define SCROLL_L (SCROLL_CENTER_W - scrollCenter->sc_w)//�X�N���[���J�n�ʒu
//#define SCROLL_R (SCROLL_CENTER_W + scrollCenter->sc_w)//�X�N���[���J�n�ʒu
#define SCROLL_U (scrollCenter->sc_h)//�X�N���[���J�n�ʒu
#define SCROLL_D (scrollCenter->sc_h)//�X�N���[���J�n�ʒu


#define SCROLL_WRITE_L		((  0)>>4)			// �X�N���[���������݈ʒu�iMAP�L�����P�ʁj
#define SCROLL_WRITE_R		((960)>>4)			// �X�N���[���������݈ʒu�iMAP�L�����P�ʁj

#define SCROLL_WRITE_U		((  0)>>4)			// �X�N���[���������݈ʒu�iMAP�L�����P�ʁj
#define SCROLL_WRITE_D		((540)>>4)			// �X�N���[���������݈ʒu�iMAP�L�����P�ʁj

//******************************************************************************
//
//		�����ݒ�
//
//******************************************************************************

// �R���X�g���N�^
MAP::MAP() : pData(0), limitL(0), limitR(0)
{
	clear();
}

//==============================================================================

// �����ݒ�
void MAP::init(BG_DATA* p)
{
	clear();
	pData = p;
	limitL = 0;
	limitU = 0;
	limitR = (float)(pData->mapX * 512 - 960);
	limitD = (float)(1024 - 540);

	scroll_written = (int)scrollX >> 4;
	for (int dataX = scroll_written + SCROLL_WRITE_L; dataX <= scroll_written + SCROLL_WRITE_R; dataX++) {
		write(dataX);
	}
	minimap.Init(limitR + SCREEN_WIDTH, limitD + SCREEN_HEIGHT);
}

//==============================================================================

// �����o�ϐ��̃N���A
void MAP::clear()
{
	// ���zRAM�N���A
	for (int y = 0; y < 64; y++) {
		for (int x = 0; x < 64; x++) {
			vRam[y][x] = BGCODE_BLANK;
		}
	}
	// �\���ʒu�ݒ�
	scrollX = 0;
	scrollY = 0;
	scroll_state = 0;
	effect_shifted_objects = V2(0,0);
	effect_shifted_all = V2(0, 0);
	Shake_state = 0;
	//�~�j�}�b�v������

	minimap.clear();
}

//******************************************************************************
//
//		�X�V����
//
//******************************************************************************

// �X�V����
void MAP::update()
{

	if (!scrollCenter) { if (nextscrollCenter) { scrollCenter = nextscrollCenter; nextscrollCenter = NULL; }return; }

	float nx;
	//float ny;
	float old_x = nx = scrollX;						// �X�N���[��X�ʒu�̕ۑ�
	float old_y = scrollY;

	float scroll_dx = 0;
	float scroll_dy = 0;

	switch(scroll_state) {

	case normal:
		// �X�N���[��
		if (scrollCenter->pos.x > SCROLL_R) scroll_dx = scrollCenter->pos.x - SCROLL_R; //�v���C���[�ƃX�N���[���̍�����
		if (scrollCenter->pos.x < SCROLL_L) scroll_dx = scrollCenter->pos.x - SCROLL_L; //
		nx += scroll_dx;

		if (scrollCenter->pos.y > SCROLL_D)scroll_dy = scrollCenter->pos.y - SCROLL_D; //�v���C���[�ƃX�N���[���̍�����
		if (scrollCenter->pos.y < SCROLL_U)scroll_dy = scrollCenter->pos.y - SCROLL_U; //
		scrollY += scroll_dy;
		break;
	case center_lock:
		if (scrollCenter->pos.x > lock.x) scroll_dx = scrollCenter->pos.x - lock.x; //�v���C���[�ƃX�N���[���̍�����
		if (scrollCenter->pos.x < lock.x) scroll_dx = scrollCenter->pos.x - lock.x; //
		nx += scroll_dx;
	
		if (scrollCenter->pos.y > SCROLL_D)scroll_dy = scrollCenter->pos.y - SCROLL_D; //�v���C���[�ƃX�N���[���̍�����
		if (scrollCenter->pos.y < SCROLL_U)scroll_dy = scrollCenter->pos.y - SCROLL_U; //
		scrollY += scroll_dy;
		break;
	}



	// �X�N���[���͈͂̃`�F�b�N
	if (nx < limitL) nx = limitL;
	if (nx > limitR) nx = limitR;
	if (scrollY > limitD) scrollY = limitD;
	if (scrollY < limitU) scrollY = limitU;

	//// �X�N���[���␳
	float scroll_rx = nx - old_x;
	float scroll_ry = scrollY - old_y;
	if (scroll_rx != 0) {
		if (scroll_rx < 0) {///���X�N���[�� 
			spd.x += -MAP_ACT;	//���x����
			if (spd.x < -MAP_SPEED_MAX)spd.x = -MAP_SPEED_MAX;//�ō����`�F�b�N
			if (scroll_rx > spd.x) {//
				spd.x = scroll_rx;
			}
			else scroll_rx = spd.x;
		}

		if (scroll_rx > 0) {//�E�X�N���[��
			spd.x += MAP_ACT;//���x����
			if (spd.x > MAP_SPEED_MAX)spd.x = MAP_SPEED_MAX;
			if (scroll_rx < spd.x) {
				spd.x = scroll_rx;
			}
			else scroll_rx = spd.x;
		}
	} else {
		spd.x = 0;
	}
	//scroll_rx = spd.x;
	effect_shifted_objects = V2(0, 0);
	effect_shifted_all = V2(0, 0);

	Player* p = pPlayer;
	p->pos.x -= scroll_rx;
	p->pos.y -= scroll_ry;


	//pFrame->pos.x -= scroll_rx;
	//pFrame->pos.y -= scroll_ry;

	Enemy_Manager* em = pEnemy_Manager;
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (em->enemy[i]) {
			em->enemy[i]->pos.x -= scroll_rx;
			em->enemy[i]->pos.y -= scroll_ry;
		}
	}
	Effect_Manager* fm = pEffect_Manager;
	for (int i = 0; i < EFF_MAX; i++) {
		if (fm->effect[i]) {
			fm->effect[i]->pos.x -= scroll_rx;
			fm->effect[i]->pos.y -= scroll_ry;
		}
	}

	//LandScape* lp= 
	//pEffect_Manager->effect[i]->pos.x -= scroll_rx;
	//pEffect_Manager->effect[i]->pos.y -= scroll_ry;


	scrollX += scroll_rx;
	// MAP��������
	int dataX = (int)scrollX >> 4;// scrollX/32?

	while (scroll_written < dataX) {
		scroll_written++;
		write(scroll_written + SCROLL_WRITE_R);
	}
	while (scroll_written > dataX) {
		scroll_written--;
		write(scroll_written + SCROLL_WRITE_L);
	}
	if (nextscrollCenter) { scrollCenter = nextscrollCenter; nextscrollCenter = NULL; }

	//�~�j�}�b�v�X�V
	minimap.Update();

}

//******************************************************************************
//
//		�`�揈��
//
//******************************************************************************

// �`�揈��
void MAP::Render()
{
	//�}�b�v�����_�[
	//RenderMapChip();


}
void MAP::MiniMapRender() {
	minimap.Render();
}

inline void MAP::RenderMapChip()
{
	int		dataY = ((int)scrollY) >> 4;			//0 - 16
	float	scrnY = (float)(dataY << 4) - scrollY;	//
	for (; scrnY < SCREEN_HEIGHT; scrnY += 16, dataY++) {	//
		int		dataX = ((int)scrollX) >> 4;	//
		float	scrnX = (float)(dataX << 4) - scrollX;//
		for (; scrnX < SCREEN_WIDTH; scrnX += 16, dataX++) {//
			int	code = vRam[dataY & 0x3f][dataX & 0x3f];
			if (code == 0)continue;

			int tex = ((code & 0xff00) >> 8);
			float u = (float)((code & 0x0f) << 4);
			float v = (float)((code & 0xf0));

			spr_data::obj[tex + spr_data::MAPCHIP1 - 1]->Render((int)scrnX, (int)scrnY, 16, 16, (int)u, (int)v, 16, 16, 0, 0, 0xFFFFFFFF, 0);
		}
	}
}

//******************************************************************************
//******************************************************************************
//
//		�e��֐�
//
//******************************************************************************
//==============================================================================
//		�X�N���[����������
//==============================================================================

void MAP::write(int dataX)
{
	if (!pData) return;							// �f�[�^���ݒ�̂Ƃ�
	if (dataX < 0) return;						// �f�[�^�͈͊O�̂Ƃ�
	if (dataX >= (pData->mapX << 5)) return;	// �f�[�^�͈͊O�̂Ƃ�

	SCREEN_DATA*	pScr = pData->pScr;
	pScr += pData->pMap[dataX >> 5];			// 111111100000 0000

	int scr_x = (dataX >> 2) & 0x07;			// 000000011100 0000
	int mdl_x = (dataX)& 0x03;					// 000000000011 0000

	int bg_x = dataX & 0x3f;
	int bg_y = 0;

	for (int scr_y = 0; scr_y < 0x08; scr_y++) {
		MODULE_DATA* pMdl = pData->pMdl;
		pMdl += pScr->m[scr_y][scr_x];
		for (int mdl_y = 0; mdl_y < 0x04; mdl_y++) {
			vRam[bg_y][bg_x] = pMdl->code[mdl_y][mdl_x];
			bg_y++;
		}
	}
}

//==============================================================================
//		��ʍ��W���炻�̏ꏊ��MAP�L�����R�[�h��Ԃ�
//==============================================================================

int MAP::getCode(float x, float y)
{
	return getCode((int)(x + scrollX), (int)(y + scrollY));
}

int MAP::getCode(int dataX, int dataY)
{
	return vRam[(dataY >> 4) & 0x3f][(dataX >> 4) & 0x3f];
}

//==============================================================================
//		�ix-w�j�`�ix+w�j�ԂŒn�ʂɂ߂荞��ł��邩�ǂ�����Ԃ�
//==============================================================================

bool MAP::isFloor(float x, float y, int w)
{
	int dataX = (int)(x + scrollX);
	int dataY = (int)(y + scrollY);
	for (; w > 0; w -= 16) {
		if (isHitDown(dataX - w, dataY)) return true;		// �����`�F�b�N
		if (isHitDown(dataX + w, dataY)) return true;		// �E���`�F�b�N
	}
	return isHitDown(dataX, dataY);							// �����`�F�b�N
}

//==============================================================================
//		�ix-w�j�`�ix+w�j�ԂœV��ɂ߂荞��ł��邩�ǂ�����Ԃ�
//==============================================================================

bool MAP::isCeiling(float x, float y, int w)
{
	int dataX = (int)(x + scrollX);
	int dataY = (int)(y + scrollY);
	for (; w > 0; w -= 16) {
		if (isHitAll(dataX - w, dataY)) return true;		// �����`�F�b�N
		if (isHitAll(dataX + w, dataY)) return true;		// �E���`�F�b�N
	}
	return isHitAll(dataX, dataY);							// �����`�F�b�N
}

//==============================================================================
//		�iy-height�j�`�iy�j�Ԃŉ������ɂ߂荞��ł��邩�ǂ�����Ԃ�
//==============================================================================

bool MAP::isWall(float x, float y, int h)
{
	int dataX = (int)(x + scrollX);
	int dataY = (int)(y + scrollY);
	// �ォ�牺�փ`�F�b�N
	for (; h > 0; h -= 16) {
		if (isHitAll(dataX, dataY - h)) return true;
	}
	return isHitAll(dataX, dataY);							// �����`�F�b�N
}

//==============================================================================

bool MAP::isHitAll(int dataX, int dataY)
{
	switch (getCode(dataX, dataY)&BGHIT_MASK) {
	case BGHIT_ALL:			// �����肠��
		return true;
	}
	return false;
}

//==============================================================================

bool MAP::isHitDown(int dataX, int dataY)
{
	switch (getCode(dataX, dataY)&BGHIT_MASK) {
	case BGHIT_ALL:			// �����肠��
	case BGHIT_DOWN:		// �������݂̂����肠��
		return true;
	}
	return false;
}

//******************************************************************************

void MAP::SetCenter(OBJ2D* obj) {
	nextscrollCenter = obj;
	scroll_state = 0;
}

OBJ2D* MAP::GetCenter() {
	return scrollCenter;
}


// �V�䂬�肬��̏ꏊ�ɐݒ肷��
void bg_crt_up(OBJ2D *obj, float h)
{
	float y;
	y = obj->pos.y - h;							// �L�����̓��̏�̍��W
	y += pMAP->getScrollY();						// �}�b�v��̍��W�ɕϊ�
	y = (float)(((int)y) & 0xfff0);				// �V��ɂ߂荞�񂾕��̕␳
	y -= pMAP->getScrollY();						// ��ʏ�̍��W�ɖ߂�
	y += 16;									// BG1�L����������Ă���̂ŕ␳
	obj->pos.y = y + h;							// �L�����{���̍��W
	if (obj->spd.y < 0) obj->spd.y = 0;		// �n�`�ɂ������Ă���̂ő��x��0�ɂ���
}

//==============================================================================

// �n�ʂ��肬��̏ꏊ�ɐݒ肷��
void bg_crt_down(OBJ2D *obj)
{
	float	y;
	y = obj->pos.y;
	y += pMAP->getScrollY();						// �}�b�v��̍��W�ɕϊ�
	y = (float)(((int)y) & 0xfff0);				// �n�ʂɂ߂荞�񂾕��̕␳
	y -= pMAP->getScrollY();						// ��ʏ�̍��W�ɖ߂�
	y -= 0.0125f;								// �n�ʂ��班��������
	obj->pos.y = y;
	if (obj->spd.y > 0) obj->spd.y = 0;		// ���n��ԂȂ̂ő��x��0�ɂ���
}

//==============================================================================

// �����̒n�`���肬��ɂ���
void bg_crt_left(OBJ2D *obj, float w)
{
	float x;
	x = obj->pos.x - w;							// �L�����̍��[�̍��W
	x += pMAP->getScrollX();						// �}�b�v��̍��W�ɕϊ�
	x = (float)(((int)x) & 0xfff0);				// �n�ʂɂ߂荞�񂾕��̕␳
	x -= pMAP->getScrollX();						// ��ʏ�̍��W�ɖ߂�
	x += 16;									// BG1�L����������Ă���̂ŕ␳
	obj->pos.x = x + w;							// �L�����{���̍��W
	if (obj->spd.x < 0) obj->spd.x = 0;		// �n�`�ɂ������Ă���̂ő��x��0�ɂ���
}

//==============================================================================

// �E���̒n�`���肬��ɂ���
void bg_crt_right(OBJ2D *obj, float w)
{
	float x;
	x = obj->pos.x + w;							// �L�����̉E�[�̍��W
	x += pMAP->getScrollX();						// �}�b�v��̍��W�ɕϊ�
	x = (float)(((int)x) & 0xfff0);				// �n�ʂɂ߂荞�񂾕��̕␳
	x -= pMAP->getScrollX();						// ��ʏ�̍��W�ɖ߂�
	x -= 0.0125f;								// �n�`���肬��̏ꏊ�ɂ���
	obj->pos.x = x - w;							// �L�����{���̍��W
	if (obj->spd.x > 0) obj->spd.x = 0;		// �n�`�ɂ������Ă���̂ő��x��0�ɂ���
}

//==============================================================================

// �R�́i��R�j�̌v�Z
float get_Resist(int attr, float spd)
{
	float	Resist = 0;				// �R�́i��R�j

	switch (attr) {
	case BGATT_WATER:				// �����̂Ƃ�
		Resist = -spd / 4;		// �����̒�R�i���x�̊֐��j
		break;
	}
	return Resist;
}

//==============================================================================


//==============================================================================
//		centerLock ��L����
//==============================================================================

void MAP::Change_centerLock(OBJ2D* obj) {
	if (obj != scrollCenter) return;
	if (scroll_state == center_lock) {
		scroll_state = normal;
		return;
	}
	scroll_state = center_lock;
	lock = obj->pos;

}