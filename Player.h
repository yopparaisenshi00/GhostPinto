#ifndef _PLAYER_H_
#define _PLAYER_H_
//X
#define PLAYER_SPDX_MAX			(6)		//X�����ړ��ō����x
#define PLAYER_AX			(1.0f)		// �v���C���[�w���������x�i�m�[�}���A�W�����v���j
#define PLAYER_AX1			(0.05f)		// �v���C���[�w���������x�i�X��j
#define PLAYER_RX			(0.05f)	// ��R

//Y
#define PLAYER_DY			(8)		// Y�����ړ��ō����x
#define PLAYER_DY2			(3)		// Y�X�e�B�b�N��|����

#define PLAYER_AY			(2.5f)	// �x���������x
#define PLAYER_AY2			(0.5f)	// Y�X�e�B�b�N��|����
#define PLAYER_RY			(0.05)	// ��R

#define PLAYER_LIMIT_LEFT	(  0+100)		// �v���C���[�ړ��͈́i���[�j
#define PLAYER_LIMIT_RIGHT	(SCREEN_WIDTH -100)		// �v���C���[�ړ��͈́i�E�[�j

#define PLAYER_LIMIT_UP		(  0+40)		// �v���C���[�ړ��͈́i���[�j
#define PLAYER_LIMIT_DOWN	(SCREEN_HEIGHT -40)		// �v���C���[�ړ��͈́i�E�[�j

#define PLAYER_WIDTH		(64)			// �v���C���[�̉�����2
#define PLAYER_SIZE			(32)
#define PLAYER_HEIGHT		(64)				// �v���C���[�̍����i�g���j

//#define SCROLL_PLAYER_W		(32)				// �X�N���[���J�n���W�i���j
#define SCROLL_PLAYER_H		(64)				// �X�N���[���J�n���W�i�E�j

#define SCROLL_LEFT (720 - 240)	//���X�N���[�����S
#define SCROLL_RIGHT (240+240)	//�E�X�N���[�����S

#define MULTIFOCUS_KEY KEY_L1 //�}���`�t�H�[�J�X�L�[�ݒ�
#define PINTOLOCK_KEY  KEY_R1 //�s���g���b�N�L�[�ݒ�

//#define SCROLL_LEFT (960/1)
//#define SCROLL_RIGHT (960/3)



//#define FARE_MAX (900)//���|�x�ő�l
//#define FERE_UP (1)	//���|�x�㏸���x
//#define FERE_CURE (5) //���|�x�񕜑��x

#define NODAMEGE_TIME (180)
#define HP_X (100)
#define HP_Y (40)


//------------------------------------------------
//�@�}���`�t�H�[�J�X
//------------------------------------------------
#define POINT_MAX (30)
#define USE_POINT (10)
#define MLTFCS_MAX_LV (3)
#define	INIT_MLTFCS (10)
struct MLT_FOCUS {
	
	int point;
	int lv;
	void add_point(int);
	SPR_DATA* data;
	spr_data::CUSTOM custom;

	void clear() {
		point = 0;
		lv = 0;
	}
};


class Player:public OBJ2D, public Singleton<Player>
{
public:

	struct Status {
		bool nodamage;
		bool old_nodamage;
		bool ground;
	};
	
	~Player();

	int hp;			//�̗�

	Status s;

	bool	jimen_flg;			// true:�n�ʂɒ��n���Ă���Afalse�F���n���Ă��Ȃ�
	bool	fear_flg;			// true:���|�ő�Afalse�F����ȊO
	
	float	old_x, old_y;		// �X�V�O��X���W�AY���W
	float	dx, dy;				// ���ۂɓ������h�b�g��
	int		attr;				// �̂̒��S�t�߂̒n�`����

	float	x_move;				// �������ɂ��ړ���

	float act;
	int anime_timer;
	int nodamage_timer;
	
	MLT_FOCUS mltfcs;			//�}���`�t�H�[�J�X

	float fearstd;				//�Q�[�W�p�K�i���킹
	
	int jet_eff_timer;			//
	int p_eff_timer;			//

	int old_mlt;

	struct gage { //�Q�[�W�p
		V2 pos;
		D3DCOLOR argb;
		spr_data::CUSTOM custom;
	};
	gage g;

	virtual void clear();		// �����o�ϐ��̃N���A
	
	virtual void Init();
	virtual void Update();		// �ړ�
	virtual void Render();		// �`��
	void UIRender();
	static const int height = 32;static const int widht = 32;
	void SetMain();
	void judge();
	void suffer_damage();
	void Recoil(V2 enemy_pos, V2 enemy_spd); //�_���[�W���̔���
	D3DCOLOR Light(D3DCOLOR color);
	void mlt_Update();

	//void Deat_Enemy() {
	//	
	//}
	//void Deat_Enemy(float heal_num) {

	//}
protected:
	//Player();

	void move();
	void Y_move();
	inline void Get_spdy();

	void X_move();
	inline void Get_spdx();

	void anime();
	
public:

	void Player::R_Update();//���b�N

};

#define pPlayer (Player::getInstance())

//
//class P_Manager 
//{
//public:
//	P_Manager();
//	~P_Manager();
//
//private:
//
//};
//
//P_Manager::P_Manager()
//{
//
//}
//
//P_Manager::~P_Manager()
//{
//
//}
#endif // !_PLAYER_H_
