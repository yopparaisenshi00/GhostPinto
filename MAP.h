#include "MiniMap.h"
#ifndef _BG_H_
#define	_BG_H_

//******************************************************************************
//
//
//		MAP�N���X
//
//
//******************************************************************************

// �n�`������f�[�^
#define	BGHIT_NONE			0x00000000			// ������Ȃ�
#define	BGHIT_ALL			0x01000000			// �����肠��
#define BGHIT_DOWN			0x02000000			// �と���݂̂����肠��

#define BGHIT_MASK			0x0f000000

// �n�`�����f�[�^
#define	BGATT_NORMAL		0x00000000			// �ʏ�i�n�ʁA�󒆁j
#define	BGATT_ICE			0x10000000			// �X
#define	BGATT_WATER			0x20000000			// ����
#define BGATT_LEFT			0x30000000			// �x���g�R���x�A�i���j
#define	BGATT_RIGHT			0x40000000			// �x���g�R���x�A�i�E�j

#define BGATT_MASK			0xf0000000

//#define MAP_ACT (3.0f)
#define MAP_ACT (MAP_SPEED_MAX)
#define MAP_SPEED_MAX (PLAYER_SPDX_MAX + 12.0f)


// ���W���[���f�[�^
struct MODULE_DATA
{
	int	code[4][4];
};

// �X�N���[���f�[�^
struct SCREEN_DATA
{
	int	m[8][8];
};

// MAP�f�[�^
struct BG_DATA
{
	MODULE_DATA*	pMdl;
	SCREEN_DATA*	pScr;
	int*			pMap;
	int				mapX;			// ����ʐ�
};

//==============================================================================
class MiniMap;
// MAP�N���X
class MAP :public Singleton<MAP>
{
private:
//public:
	OBJ2D*		scrollCenter;		// �X�N���[���
	OBJ2D*		nextscrollCenter;		// �X�N���[���
	MiniMap		minimap;
	BG_DATA*	pData;				// MAP�f�[�^�ւ̃|�C���^
	float		limitR, limitL;		// �X�N���[������
	float		limitD, limitU;		// �X�N���[������

	int			vRam[64][64];		// �w�i�`��p���zRAM
	float		scrollX, scrollY;	// �w�i�\���ʒu
	int			scroll_written;		// 


	//******************************************************************************************
	//
	//	�G�t�F�N�g�ϐ�
	//
	//******************************************************************************************
	enum {
		None = 0,
		ShakeObj = 1,
		ShakeAll = 2,
	};
	int	Shake_state;
	int Shake_Size_Min;
	int Shake_Size_Max;


	V2 effect_shifted_objects;
	V2 effect_shifted_all;

	int Shake_timer;
	
	//******************************************************************************************


	bool		scroll_state;		//�X�N���[���̏�Ԑݒ�

public:
	MAP();
	void SetCenter(OBJ2D* obj);
	OBJ2D* GetCenter();
	void Change_centerLock(OBJ2D* obj);

	V2 spd;
	V2 lock;


		
	void init(BG_DATA* p);
	void clear();
	void update();
	void Render();
	inline void MAP::RenderMapChip();

	void MiniMapRender();

	//******************************************************************************************
	//
	//	�G�t�F�N�g�����A�X�V
	//	
	//******************************************************************************************



	//******************************************************************************************
	//
	//	���Ăяo��
	//
	//******************************************************************************************
	float getScrollX() { return scrollX; }
	float getScrollY() { return scrollY; }

	int getCode(float x, float y);
	int getHit(float x, float y) { return getCode(x, y) & BGHIT_MASK; }
	int getAttr(float x, float y) { return getCode(x, y) & BGATT_MASK; }

	int getCode(int dataX, int dataY);
	//******************************************************************************************
	//
	//	�}�b�v�Ƃ̂����蔻��
	//
	//******************************************************************************************
	bool isFloor(float x, float y, int w);
	bool isCeiling(float x, float y, int w);
	bool isWall(float x, float y, int h);

	bool isFloor(float x, float y, float w) { return isFloor(x, y, (int)w); }
	bool isCeiling(float x, float y, float w) { return isCeiling(x, y, (int)w); }
	bool isWall(float x, float y, float h) { return isWall(x, y, (int)h); }

private:
	bool isHitAll(int dataX, int dataY);
	bool isHitDown(int dataX, int dataY);

	void write(int dataX);

};

void bg_crt_up(OBJ2D *obj, float h);
void bg_crt_down(OBJ2D *obj);
void bg_crt_left(OBJ2D *obj, float w);
void bg_crt_right(OBJ2D *obj, float w);
float get_Resist(int attr, float spd);


#define pMAP			(MAP::getInstance())
#define SCROLL_X	(pBG->getScrollX())
#define SCROLL_Y	(pBG->getScrollY())

//******************************************************************************
#endif // !_BG_H_
